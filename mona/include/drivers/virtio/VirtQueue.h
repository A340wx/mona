/*
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

#ifndef _VIRTQUEUE_
#define _VIRTQUEUE_

#include <drivers/virtio/VirtBuffer.h>
#include <vector>

class VirtioDevice;
class VirtQueue
{
private:
    VirtQueue(uint16_t queueIndex, VirtioDevice& dev);

public:
    virtual ~VirtQueue()
    {
        deactivate();
        delete mem_;
    }

    intptr_t addBuf(const std::vector<VirtBuffer>& out, const std::vector<VirtBuffer>& in, void* cookie)
    {
        _logprintf("vring_.avail->idx=%d %d %d\n", vring_.avail->idx, addedBufCount_, __LINE__);
        uintptr_t bufCount = in.size() + out.size();
        if (bufCount == 0 || freeDescCount_ < bufCount) {
            return M_NO_SPACE;
        }

        freeDescCount_ -= bufCount;

        const int descToAddIndex = freeHeadIndex_;
        int i = freeHeadIndex_;
        for (std::vector<VirtBuffer>::const_iterator it = out.begin(); it != out.end(); ++it, ++i) {
            vring_.desc[i].addr = (*it).getPhysicalAddress();
            vring_.desc[i].len = (*it).length;
            vring_.desc[i].flags = VRING_DESC_F_NEXT;
        }
        for (std::vector<VirtBuffer>::const_iterator it = in.begin(); it != in.end(); ++it, ++i) {
            vring_.desc[i].addr = (*it).getPhysicalAddress();
            vring_.desc[i].len = (*it).length;
            vring_.desc[i].flags = VRING_DESC_F_NEXT | VRING_DESC_F_WRITE;
        }
        _logprintf("vring_.avail->idx=%d %d %d\n", vring_.avail->idx, addedBufCount_, __LINE__);
        vring_.desc[i - 1].flags &= ~VRING_DESC_F_NEXT;
        freeHeadIndex_ = i;

        // Just set desc to avail ring, don't change vring_.avail->idx
        _logprintf("added to ring[%d]\n", (vring_.avail->idx + addedBufCount_) % vring_.num);
        vring_.avail->ring[(vring_.avail->idx + addedBufCount_) % vring_.num] = descToAddIndex;
        addedBufCount_++;
        return M_OK;
    }

    void kick();
    static VirtQueue* findVirtQueue(int queueIndex, VirtioDevice& dev);

// public for testability
public:
    struct vring& getVring()
    {
        return vring_;
    }

    uintptr_t getFreeDescCount() const
    {
        return freeDescCount_;
    }

    uintptr_t getAddedBufCount() const
    {
        return addedBufCount_;
    }

    bool isUsedBufExist() const
    {
        return vring_.used->idx != lastUsedIndex_;
    }

private:
    void deactivate();
    void activate(uintptr_t paddr);

    uint16_t queueIndex_;
    struct vring vring_;
    uintptr_t freeDescCount_;
    uintptr_t freeHeadIndex_;
    uintptr_t lastUsedIndex_;
    uintptr_t addedBufCount_;
    VirtioDevice& dev_;
    ContigousMemory* mem_;
};

#endif // _VIRTQUEUE_