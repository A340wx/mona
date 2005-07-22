/*!
    \file   Socket.cpp
    \brief  �Ȉ�Socket�N���X

    Copyright (c) 2005 Yamami
    All rights reserved.
    License=MIT/X License

    \author  Yamami
    \version $Revision$
    \date   create:2005/07/15 update:$Date$
*/

/*! \class Socket
 *  \brief �Ȉ�Socket�N���X
 */


#include <monesoc/Socket.h>


/*!
    \brief initialize
         Socket �R���X�g���N�^
    \author Yamami
    \date   create:2004/10/11 update:$Date$
*/
Socket::Socket()
{
    //��M�o�b�t�@�C���X�^���X��(���L������)
    //recvBuff = new HList<packet_cmemoryinfo*>();
    
    //���M�o�b�t�@�C���X�^���X��(���L������)
    //sendBuff = new HList<packet_cmemoryinfo*>(); 
    
    nowRecvBufCount = -1;
    nowSendBufCount = -1;
}

/*!
    \brief initialize
         Socket �f�X�N�g���N�^
    \author Yamami
    \date   create:2004/10/11 update:$Date$
*/
Socket::~Socket()
{
 
}


/*!
    \brief addBuffer
         Socket�ցA��M/���M�o�b�t�@��o�^
    \param  char *pac [in] �p�P�b�g
    \param  int pacsize [in] �p�P�b�g�T�C�Y
    \param  int rorsFlag [in] ��M?���M?�t���O 0:��M/1:���M
    
    \return int ���� 
    
    \author Yamami
    \date   create:2005/05/22 update:
*/
int Socket::addBuffer(char *pac , int pacsize ,int rorsFlag)
{

    //���L�������փp�P�b�g�i�[
    //�܂��Amonapi_cmemoryinfo�\���̂�new
    monapi_cmemoryinfo* cmInfo = new monapi_cmemoryinfo();
    
    if (!monapi_cmemoryinfo_create(cmInfo, (dword)pacsize + 1, 0))
    {
        monapi_cmemoryinfo_delete(cmInfo);
        return 1;
    }
    
    
    //���L���������}�b�v�AData�v�f�Ɋm�ۂ����o�C�g�񂪃Z�b�g�����B
    //create����MAP�͂���Ȃ��H�H
    //monapi_cmemoryinfo_map(cmInfo);
    
    //���L�������ցA�p�P�b�g�Z�b�g
    memcpy(cmInfo->Data , pac, pacsize);
    
    
    //���� ��M�A���M�o�b�t�@�ɓo�^����̂͂����܂Ńn���h�����̂�
    

logprintf("Pre!!! if(rorsFlag == 0)\n");  
logprintf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");  

    
    if(rorsFlag == 0){
logprintf("flag0 ON\n");
        nowRecvBufCount++;
logprintf("nowRecvBufCount=%d\n",nowRecvBufCount);

        recvBuff[nowRecvBufCount].Handle = cmInfo->Handle;
        recvBuff[nowRecvBufCount].Owner = cmInfo->Owner;
        recvBuff[nowRecvBufCount].Size = cmInfo->Size;         
        //recvBuff->add(pcm);

logprintf("Add pcm.Handle=%d pcm.Owner=%d pcm.Size=%d\n",recvBuff[nowRecvBufCount].Handle , recvBuff[nowRecvBufCount].Owner ,recvBuff[nowRecvBufCount].Size);

    }
    else{
logprintf("flag1 ON\n");        
        nowSendBufCount++;
        sendBuff[nowSendBufCount].Handle = cmInfo->Handle;
        sendBuff[nowSendBufCount].Owner = cmInfo->Owner;
        sendBuff[nowSendBufCount].Size = cmInfo->Size;
        
        //sendBuff->add(pcm);
    }
    

logprintf("After!!! pcm.Handle Set;\n");
    
    return 0;
}


/*!
    \brief getBuffer
         �J�����g�̃o�b�t�@���擾����B
    \param  int rorsFlag [in] ��M?���M?�t���O 0:��M/1:���M
    
    \return int ���� 
    
    \author Yamami
    \date   create:2005/05/22 update:
*/
packet_cmemoryinfo Socket::getBuffer(int rorsFlag)
{
    packet_cmemoryinfo pcm;
    
    if(rorsFlag == 0){
        pcm = recvBuff[nowRecvBufCount];
        
logprintf("Get nowRecvBufCount=%d\n",nowRecvBufCount);
logprintf("Get pcm.Handle=%d pcm.Owner=%d pcm.Size=%d\n",pcm.Handle , pcm.Owner ,pcm.Size);
        nowRecvBufCount--;        
        
    }
    else{
        pcm = recvBuff[nowRecvBufCount];
        nowSendBufCount--;
        
    }
    
    return pcm;
    
}

