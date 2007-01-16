/*!
    \file   UdpSocket.cpp
    \brief  UdpSocket�N���X

    Copyright (c) 2005 Yamami
    All rights reserved.
    License=MIT/X License

    \author  Yamami
    \version $Revision$
    \date   create:2005/08/09 update:$Date$
*/

/*! \class UdpSocket
 *  \brief UdpSocket�N���X
 */


#include <monesoc/UdpSocket.h>

using namespace MonAPI;

/*!
    \brief UdpSocket
         UdpSocket �R���X�g���N�^
    \author Yamami
    \date   create:2005/08/09 update:$Date$
*/
UdpSocket::UdpSocket()
{
    useport=0;
}

/*!
    \brief ~UdpSocket
         UdpSocket �f�X�N�g���N�^
    \author Yamami
    \date   create:2005/08/09 update:$Date$
*/
UdpSocket::~UdpSocket()
{
 
}


/*!
    \brief bind
         Socket���w��|�[�g��bind
    \param  uint16_t port [in] �|�[�g�ԍ�
    
    \return int ���� 
    
    \author Yamami
    \date   create:2005/08/09 update:$Date$
*/
int UdpSocket::bind(uint16_t port)
{
    //�����ŁAMones�ɓo�^���b�Z�[�W�𑗂�
    MessageInfo info;

    uint32_t targetID = Message::lookupMainThread("MONES.EX5");
    if (targetID == 0xFFFFFFFF)
    {
        logprintf("MONES.EX5 not found\n");
        return 1;
    }

    //Mones�֓o�^
    //�|�[�g2600�Ń��X��
    Message::create(&info, MSG_MONES_REGIST, 0, 2600, 0, NULL);
    // send
    if (Message::send(targetID, &info)) {
        logprintf("MSG_MONES_REGIST error\n");
        return 1;
    }
    
    //use�|�[�g�́Abind�����|�[�g�Ō��p����B
    useport = port;
    
    return 0;
}


/*!
    \brief recv
         bind�ς݃|�[�g����̎�M
         �o�b�t�@�T�C�Y���傫���f�[�^�͔j������܂��B
    \param  char* buff [OUT] ��M�o�b�t�@
    \param  uint32_t len [in] �o�b�t�@�T�C�Y    
    \return int ���� 
    
    \author Yamami
    \date   create:2005/08/09 update:$Date$
*/
int UdpSocket::recv(char* buff ,uint32_t len)
{

    MessageInfo info;

    /* Message loop */
    //�����Ń��b�Z�[�W���[�v���āA������҂��Ă݂�B
    for (;;)
    {
        /* receive */
        if (!Message::receive(&info))
        {
            
            switch(info.header)
            {
            case MSG_MONES_ICMP_NOTICE:
                //�Ԃ��Ă�����
                
                SocketContainer *soc;
                
                //���L������
                monapi_cmemoryinfo* cmSoc;

                cmSoc = monapi_cmemoryinfo_new();
                cmSoc->Handle = info.arg2;
                cmSoc->Size   = info.arg3;
                
                monapi_cmemoryinfo_map(cmSoc);
                
                //���L����������SocketContainer�����o���B
                soc = (SocketContainer*)cmSoc->Data;

                //SocketContainer����A�p�P�b�g(�o�C�g��)�����o���B
                //UDP�́A�ő咴����Ɠǂݎ̂Ă�BTCP�̓t���[���䂪�K�v UDPSocket ��TCPSocket�̎d��
                packet_cmemoryinfo pcm;
                
                pcm = soc->getBuffer(0);

                //���L����������p�P�b�g �o�C�g ���擾                
                monapi_cmemoryinfo* cmPacByte;
                
                cmPacByte = monapi_cmemoryinfo_new();
                cmPacByte->Handle = pcm.Handle;
                cmPacByte->Size   = pcm.Size;
                monapi_cmemoryinfo_map(cmPacByte);                
                
                //�A�v������n����Ă���o�b�t�@�փR�s�[
                memcpy(buff,cmPacByte->Data , len);                
                
                //SocketContainer�́A�A�v���ŋ��L������������Ȃ�!!
                //monapi_cmemoryinfo_dispose(cmSoc);
                //monapi_cmemoryinfo_delete(cmSoc);                

                //���L���������
                monapi_cmemoryinfo_dispose(cmPacByte);
                monapi_cmemoryinfo_delete(cmPacByte);                
                
                return 0;
                
                break;

            default:
                /* igonore this message */
                break;
            }

        }
    }
}



/*!
    \brief send
         UDP���M
    \param  char* mesg [IN] ���M���b�Z�[�W�o�b�t�@
    \param  uint32_t len [in] �o�b�t�@�T�C�Y
    \param  char* host [in] ���M�z�X�g (���� X.X.X.X �`���̂݃T�|�[�g)
    \param  uint16_t port [in] ���M�|�[�g�ԍ�
    \return int ���� 
    
    \author Yamami
    \date   create:2005/08/09 update:$Date$
*/
int UdpSocket::send(char* mesg, uint32_t len, char* host, uint16_t port)
{
    
    MessageInfo info;
    SocketContainer *soc;
    uint32_t ipaddr;

    if(useport == 0){
        //���ȃ|�[�g���܂������蓖�ĂȂ�
        //TODO �{���Ȃ�mones�v���g�R���T�[�o�ɖ₢���킹�󂫃|�[�g���擾����!
        // �Ƃ肠�����A�K����2800��
        useport = 2800;
    }
    
    //IP�A�h���X�g�ݗ���
     int a,b,c,d;
    
    sscanf(host,"%d.%d.%d.%d",&a,&b,&c,&d);
    ipaddr = 0;
    ipaddr = (uint8_t)a;
    ipaddr = (ipaddr << 8) + (uint8_t)b;
    ipaddr = (ipaddr << 8) + (uint8_t)c;
    ipaddr = (ipaddr << 8) + (uint8_t)d;
    
logprintf("UdpSocket::send ipaddr = %x\n",ipaddr);
    
    soc = new SocketContainer();
    soc->tid = MonAPI::System::getThreadID();
    soc->myport = useport;
    soc->ip = ipaddr;
    soc->youport = port; 
    soc->status = 0;  //TODO �����͂ǂ������H

    int reti;
    
    //�\�P�b�g�̑��M�o�b�t�@�֒ǉ�
    reti = soc->addBuffer(mesg , len , 1);
    
    //MSG_MONES_IP_SEND ���b�Z�[�W�쐬
    Message::create(&info, MSG_MONES_IP_SEND, 0, 0, 0, NULL);
    
    //���b�Z�[�W��SocketContainer���Z�b�g
    reti = soc->createPacMonaMsg(&info , 17);
    
    uint32_t targetID = Message::lookupMainThread("MONES.EX5");
    if (targetID == 0xFFFFFFFF)
    {
        logprintf("MONES.EX5 not found\n");
        return 1;
    }
    
    // send
    if (Message::send(targetID, &info)) {

    }
    
}

