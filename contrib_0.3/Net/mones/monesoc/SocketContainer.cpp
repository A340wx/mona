/*!
    \file   SocketContainer.cpp
    \brief  SocketContainer�N���X

    Copyright (c) 2005 Yamami
    All rights reserved.
    License=MIT/X License

    \author  Yamami
    \version $Revision$
    \date   create:2005/07/15 update:$Date$
*/

/*! \class SocketContainer
 *  \brief SocketContainer�N���X
 */


#include <monesoc/SocketContainer.h>


/*!
    \brief initialize
         SocketContainer �R���X�g���N�^
    \author Yamami
    \date   create:2004/10/11 update:$Date$
*/
SocketContainer::SocketContainer()
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
         SocketContainer �f�X�N�g���N�^
    \author Yamami
    \date   create:2004/10/11 update:$Date$
*/
SocketContainer::~SocketContainer()
{
 
}


/*!
    \brief addBuffer
         SocketContainer�ցA��M/���M�o�b�t�@��o�^
    \param  char *pac [in] �p�P�b�g
    \param  int pacsize [in] �p�P�b�g�T�C�Y
    \param  int rorsFlag [in] ��M?���M?�t���O 0:��M/1:���M
    
    \return int ���� 
    
    \author Yamami
    \date   create:2005/05/22 update:
*/
int SocketContainer::addBuffer(char *pac , int pacsize ,int rorsFlag)
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
    
    
    if(rorsFlag == 0){
        nowRecvBufCount++;
        recvBuff[nowRecvBufCount].Handle = cmInfo->Handle;
        recvBuff[nowRecvBufCount].Owner = cmInfo->Owner;
        recvBuff[nowRecvBufCount].Size = cmInfo->Size;         
        //recvBuff->add(pcm);

    }
    else{
        nowSendBufCount++;
        sendBuff[nowSendBufCount].Handle = cmInfo->Handle;
        sendBuff[nowSendBufCount].Owner = cmInfo->Owner;
        sendBuff[nowSendBufCount].Size = cmInfo->Size;
        //sendBuff->add(pcm);
    }
    
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
packet_cmemoryinfo SocketContainer::getBuffer(int rorsFlag)
{
    packet_cmemoryinfo pcm;
    
    if(rorsFlag == 0){
        pcm = recvBuff[nowRecvBufCount];
        
logprintf("Get nowRecvBufCount=%d\n",nowRecvBufCount);
logprintf("Get pcm.Handle=%d pcm.Owner=%d pcm.Size=%d\n",pcm.Handle , pcm.Owner ,pcm.Size);
        nowRecvBufCount--;        
        
    }
    else{
        pcm = sendBuff[nowSendBufCount];
        
logprintf("Get nowSendBufCount=%d\n",nowSendBufCount);
logprintf("Get pcm.Handle=%d pcm.Owner=%d pcm.Size=%d\n",pcm.Handle , pcm.Owner ,pcm.Size);        
        
        nowSendBufCount--;
        
    }
    
    return pcm;
    
}




/*!
    \brief createPacMonaMsg
         �p�P�b�g�i�[���b�Z�[�W�쐬
    \param  MessageInfo *info [OUT] �쐬���b�Z�[�W
    \param  dword protno [IN] �v���g�R��No
    \return int ���� 
    
    \author Yamami
    \date   create:2005/05/22 update:
*/
int SocketContainer::createPacMonaMsg(MessageInfo *info , dword protno )
{

    //���L��������SocketContainer�i�[
    //�܂��Amonapi_cmemoryinfo�\���̂�new
    monapi_cmemoryinfo* cmInfo = new monapi_cmemoryinfo();
    
    if (!monapi_cmemoryinfo_create(cmInfo, sizeof(SocketContainer) + 1, 0))
    {
        monapi_cmemoryinfo_delete(cmInfo);
        logprintf("SocketContainer::createPacMonaMsg monapi_cmemoryinfo_create Faild!! \n");
        return 1;
    }
    
    //���L���������}�b�v�AData�v�f�Ɋm�ۂ����o�C�g�񂪃Z�b�g�����B
    //Yamami �}�b�v����H�H
    monapi_cmemoryinfo_map(cmInfo);
    
    //���L�������ցASocketContainer�i�[ 
    memcpy(cmInfo->Data , this, sizeof(SocketContainer));
    
    info->length = sizeof(SocketContainer);
    
    info->arg1 = protno;  //�v���g�R��NO
    info->arg2 = cmInfo->Handle;
    info->arg3 = cmInfo->Size;
    
    return 0;
  

}
