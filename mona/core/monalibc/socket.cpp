/*
 * socket.cpp - BSD socket
 *
 *   Copyright (c) 2010  Higepon(Taro Minowa)  <higepon@users.sourceforge.jp>
 *
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 *
 *   1. Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *
 *   2. Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 *   TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 *   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 *   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 *   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <sys/socket.h>
#include <netdb.h>
#include <monapi.h>
#include <monapi/messages.h>
#include <servers/net.h>
#include <monalibc/errno.h>

using namespace MonAPI;

typedef struct GetaddrinfoPacket {
    uintptr_t nodeLen;
    struct addrinfo hints;
    char data[0];
} GetaddrinfoPacket;

int getaddrinfo(const char *node, const char *service,
                const struct addrinfo *hints,
                struct addrinfo **res)
{
    // construct addrinfo to struct
    uintptr_t nodeLen = node == NULL ? 0 : strlen(node) + 1;
    uintptr_t serviceLen = service == NULL ? 0 : strlen(service) + 1;
    uintptr_t structSize = sizeof(GetaddrinfoPacket) + nodeLen + serviceLen;
    uint8_t* p = new uint8_t[structSize];
    GetaddrinfoPacket* pack = (GetaddrinfoPacket*)p;
    pack->nodeLen = nodeLen;
    pack->hints = *hints;
    if (node != NULL) {
        strcpy(pack->data, node);
    }
    if (service != NULL) {
        strcpy(pack->data + nodeLen, service);
    }

    uintptr_t id = monapi_get_server_thread_id(ID_NET_SERVER);
    if (Message::send(id, MSG_NET_GET_ADDR_INFO) != M_OK) {
        return EBADF;
    }
    if (Message::sendBuffer(id, p, structSize) != M_OK) {
        return EBADF;
    }
    BufferReceiver* receiver = Message::receiveBuffer(id);
    if (receiver->bufferSize() != 0) {
        struct addrinfo* ainfo = new struct addrinfo;
        memcpy(ainfo, receiver->buffer(), sizeof(struct addrinfo));
        ainfo->ai_addr = (struct sockaddr*)(new uint8_t[ainfo->ai_addrlen]);
        memcpy(ainfo->ai_addr, receiver->buffer() + sizeof(struct addrinfo), ainfo->ai_addrlen);
        ASSERT(receiver->bufferSize() == (sizeof(struct addrinfo) + ainfo->ai_addrlen));
        *res = ainfo;
    }
    delete receiver;
    MessageInfo src;
    MessageInfo dst;
    src.from = id;
    src.header = MSG_RESULT_OK;
    src.arg1 = MSG_NET_GET_ADDR_INFO;
    if (Message::receive(&dst, &src, Message::equalsFromHeaderArg1) != M_OK) {
        return EBADF;
    }
    return dst.arg2;
}

void freeaddrinfo(struct addrinfo *res)
{
    delete res;
}

int connect(int sockfd, const struct sockaddr* name, socklen_t namelen)
{
    uintptr_t id = monapi_get_server_thread_id(ID_NET_SERVER);
    if (Message::send(id, MSG_NET_SOCKET_CONN, sockfd, namelen) != M_OK) {
        return EBADF;
    }

    if (Message::sendBuffer(id, name, namelen) != M_OK) {
        return EBADF;
    }

    MessageInfo src;
    MessageInfo dst;
    src.from = id;
    src.header = MSG_RESULT_OK;
    src.arg1 = MSG_NET_SOCKET_CONN;
    if (Message::receive(&dst, &src, Message::equalsFromHeaderArg1) != M_OK) {
        return EBADF;
    }
    errno = dst.arg3;
    return dst.arg2;
}

int socket(int domain, int type, int protocol)
{
    uintptr_t id = monapi_get_server_thread_id(ID_NET_SERVER);
    MessageInfo ret;
    if (Message::sendReceive(&ret, id, MSG_NET_SOCKET_SOCK, domain, type, protocol) != M_OK) {
        return EINVAL;
    }
    errno = ret.arg3;
    return ret.arg2;
}

int closesocket(int sockfd)
{
    uintptr_t id = monapi_get_server_thread_id(ID_NET_SERVER);
    MessageInfo ret;
    if (Message::sendReceive(&ret, id, MSG_NET_SOCKET_CLOSE, sockfd) != M_OK) {
        return EINVAL;
    }
    return ret.arg2;
}

int send(int sockfd, void* buf, size_t len, int flags)
{
    uintptr_t id = monapi_get_server_thread_id(ID_NET_SERVER);
    if (Message::send(id, MSG_NET_SOCKET_SEND, sockfd, len, flags) != M_OK) {
        return EBADF;
    }

    if (Message::sendBuffer(id, buf, len) != M_OK) {
        return EBADF;
    }

    MessageInfo src;
    MessageInfo dst;
    src.from = id;
    src.header = MSG_RESULT_OK;
    src.arg1 = MSG_NET_SOCKET_SEND;
    if (Message::receive(&dst, &src, Message::equalsFromHeaderArg1) != M_OK) {
        return EBADF;
    }
    errno = dst.arg3;
    return dst.arg2;
}

int recv(int sockfd, void* buf, size_t len, int flags)
{
    uintptr_t id = monapi_get_server_thread_id(ID_NET_SERVER);
    if (Message::send(id, MSG_NET_SOCKET_RECV, sockfd, len, flags) != M_OK) {
        return EBADF;
    }

    BufferReceiver* receiver = Message::receiveBuffer(id);
    if (receiver->bufferSize() > 0) {
        memcpy(buf, receiver->buffer(), receiver->bufferSize());
    }

    MessageInfo src;
    MessageInfo dst;
    src.from = id;
    src.header = MSG_RESULT_OK;
    src.arg1 = MSG_NET_SOCKET_RECV;
    if (Message::receive(&dst, &src, Message::equalsFromHeaderArg1) != M_OK) {
        return EBADF;
    }
    errno = dst.arg3;
    return dst.arg2;
}

int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen)
{
    uintptr_t id = monapi_get_server_thread_id(ID_NET_SERVER);
    if (Message::send(id, MSG_NET_SOCKET_SET_OPTION, sockfd, level, optname) != M_OK) {
        return EBADF;
    }

    if (Message::sendBuffer(id, optval, optlen) != M_OK) {
        return EBADF;
    }

    MessageInfo src;
    MessageInfo dst;
    src.from = id;
    src.header = MSG_RESULT_OK;
    src.arg1 = MSG_NET_SOCKET_SET_OPTION;
    if (Message::receive(&dst, &src, Message::equalsFromHeaderArg1) != M_OK) {
        return EBADF;
    }
    errno = dst.arg3;
    return dst.arg2;
}

int getsockopt(int sockfd, int level, int optname, void *optval, socklen_t *optlen)
{
    uintptr_t id = monapi_get_server_thread_id(ID_NET_SERVER);
    char buf[sizeof(socklen_t)];
    memcpy(buf, optlen, sizeof(socklen_t));
    if (Message::send(id, MSG_NET_SOCKET_GET_OPTION, sockfd, level, optname, buf) != M_OK) {
        return EBADF;
    }

    BufferReceiver* receiver = Message::receiveBuffer(id);
    *optlen = receiver->bufferSize();
    memcpy(optval, receiver->buffer(), *optlen);
    delete receiver;

    MessageInfo src;
    MessageInfo dst;
    src.from = id;
    src.header = MSG_RESULT_OK;
    src.arg1 = MSG_NET_SOCKET_GET_OPTION;
    if (Message::receive(&dst, &src, Message::equalsFromHeaderArg1) != M_OK) {
        return EBADF;
    }
    errno = dst.arg3;
    return dst.arg2;
}

int shutdown(int sockfd, int how)
{
    uintptr_t id = monapi_get_server_thread_id(ID_NET_SERVER);
    MessageInfo ret;
    if (Message::sendReceive(&ret, id, MSG_NET_SOCKET_SHUTDOWN, sockfd, how) != M_OK) {
        return EINVAL;
    }
    errno = ret.arg3;
    return ret.arg2;
}

int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
    uintptr_t id = monapi_get_server_thread_id(ID_NET_SERVER);
    if (Message::send(id, MSG_NET_SOCKET_BIND, sockfd, addrlen) != M_OK) {
        return EBADF;
    }

    if (Message::sendBuffer(id, addr, addrlen) != M_OK) {
        return EBADF;
    }

    MessageInfo src;
    MessageInfo dst;
    src.from = id;
    src.header = MSG_RESULT_OK;
    src.arg1 = MSG_NET_SOCKET_BIND;
    if (Message::receive(&dst, &src, Message::equalsFromHeaderArg1) != M_OK) {
        return EBADF;
    }
    errno = dst.arg3;
    return dst.arg2;
}

int listen(int sockfd, int backlog)
{
    uintptr_t id = monapi_get_server_thread_id(ID_NET_SERVER);
    MessageInfo ret;
    if (Message::sendReceive(&ret, id, MSG_NET_SOCKET_LISTEN, sockfd, backlog) != M_OK) {
        return EINVAL;
    }
    errno = ret.arg3;
    return ret.arg2;
}

int accept(int sockfd, struct sockaddr* addr, socklen_t* addrlen)
{
    uintptr_t id = monapi_get_server_thread_id(ID_NET_SERVER);
    if (Message::send(id, MSG_NET_SOCKET_ACCEPT, sockfd) != M_OK) {
        return EBADF;
    }

    BufferReceiver* receiver = Message::receiveBuffer(id);
    *addrlen = receiver->bufferSize();
    if (receiver->bufferSize() != 0) {
        memcpy(addr, receiver->buffer(), (*addrlen) > sizeof(sockaddr) ? sizeof(sockaddr) : *addrlen);
    }
    delete receiver;
    MessageInfo src;
    MessageInfo dst;
    src.from = id;
    src.header = MSG_RESULT_OK;
    src.arg1 = MSG_NET_SOCKET_ACCEPT;
    if (Message::receive(&dst, &src, Message::equalsFromHeaderArg1) != M_OK) {
        return EBADF;
    }
    errno = dst.arg3;
    return dst.arg2;
}


int select(int nfds, fd_set *readfds, fd_set *writefds,
           fd_set *exceptfds, struct timeval *timeout)
{
    ASSERT((4 + sizeof(fd_set) * 3 + sizeof(struct timeval)) <= MESSAGE_INFO_MAX_STR_LENGTH);
    uint8_t buf[MESSAGE_INFO_MAX_STR_LENGTH];

    bool haveReadFds = readfds != NULL;
    bool haveWritefds =  writefds != NULL;
    bool haveExceptFds =  exceptfds != NULL;
    bool haveTimeout =  timeout != NULL;

    buf[0] = haveReadFds;
    buf[1] = haveWritefds;
    buf[2] = haveExceptFds;
    buf[3] = haveTimeout;

    if (haveReadFds) {
        memcpy(buf + 4, readfds, sizeof(fd_set));
    }
    if (haveWritefds) {
        memcpy(buf + 4 + sizeof(fd_set), writefds, sizeof(fd_set));
    }
    if (haveExceptFds) {
        memcpy(buf + 4 + sizeof(fd_set) * 2, exceptfds, sizeof(fd_set));
    }
    if (haveTimeout) {
        memcpy(buf + 4 + sizeof(fd_set) * 3, timeout, sizeof(struct timeval));
    }

    uintptr_t id = monapi_get_server_thread_id(ID_NET_SERVER);
    MessageInfo ret;
    if (Message::sendReceive(&ret, id, MSG_NET_SELECT, nfds, 0, 0, (char*)buf) != M_OK) {
        return EINVAL;
    }
    if (haveReadFds) {
        memcpy(readfds, ret.str, sizeof(fd_set));
    }
    if (haveWritefds) {
        memcpy(writefds, ret.str + sizeof(fd_set), sizeof(fd_set));
    }
    if (haveExceptFds) {
        memcpy(exceptfds, ret.str + sizeof(fd_set) * 2, sizeof(fd_set));
    }
    if (haveTimeout) {
        memcpy(timeout, ret.str + sizeof(fd_set) * 3, sizeof(struct timeval));
    }
    errno = ret.arg3;
    return ret.arg2;
}

int ioctlsocket(int sockfd, long cmd, void *argp)
{
    uintptr_t id = monapi_get_server_thread_id(ID_NET_SERVER);
    MessageInfo ret;
    uint8_t buf[MESSAGE_INFO_MAX_STR_LENGTH];
    if (argp != NULL) {
        *((uint32_t*)buf) = *((uint32_t*)argp); // for lwip uint32_t is enough
    }

    if (Message::sendReceive(&ret, id, MSG_NET_SOCKET_CONTROL, sockfd, cmd, argp != NULL, (char*)buf) != M_OK) {
        return EINVAL;
    }

    if (argp != NULL) {
        *((uint32_t*)argp) = *((uint32_t*)buf);
    }
    errno = ret.arg3;
    return ret.arg2;
}
