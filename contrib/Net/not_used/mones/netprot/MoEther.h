/*!
    \file  MoEther.h
    \brief �C�[�T�l�b�g�����N���X �w�b�_

    class MoEther

    Copyright (c) 2004 Yamami
    All rights reserved.
    License=MIT/X License

    \author  Yamami 
    \version $Revision$
    \date   create:2004/08/12 update:$Date$
*/
#ifndef _MONA_MOETHER_
#define _MONA_MOETHER_

#include <sys/types.h>
#include <monapi.h>


#include <nicdrv/AbstractMonic.h>


/*! 
 *  \struct ETHER_FRAME
 *  \brief �C�[�T�l�b�g�t���[���\����
 */
typedef struct{
    uint8_t  dstmac[6];   // ���M�� MAC ID
    uint8_t  srcmac[6];   // ���M�� MAC ID
    uint16_t    type;     // �t���[���^�C�v Frame type(DIX) or frame length(IEEE)
    uint8_t   data[0x600];// Data
}ETHER_FRAME;


/*!
    MoEther class
*/
class MoEther
{
    
  public:
    
    //�R���X�g���N�^
    MoEther();
    ~MoEther();
    void etherInit(AbstractMonic*);
    int setEtherFrame(uint8_t* , int);
    int receiveEther();
    
//    int receiveEther(ETHER_FRAME*); //�����I�ɑ��d��` ���ڎ�M(�o�b�t�@�����O����)
    
    void sendEther(uint8_t* , uint32_t , uint32_t);
    


  private:
    //�C�[�T�l�b�g�t���[���ێ����X�g
    //List<ETHER_FRAME*>* Ether_FrameList_;
    
    ETHER_FRAME Ether_FrameBuf_;
    
    //NIC�h���C�o
    AbstractMonic* insAbstractNic;
    
};

#endif
