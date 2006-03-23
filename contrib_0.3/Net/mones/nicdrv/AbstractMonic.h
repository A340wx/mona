/*!
    \file  AbstractMonic.h
    \brief ����NIC�N���X �w�b�_
    
    Copyright (c) 2004 Yamami
    WITHOUT ANY WARRANTY

    \author  Yamami
    \version $Revision$
    \date   create:2004/09/04 update:$Date$
*/
#ifndef _MONA_ABSTRACT_MONIC_
#define _MONA_ABSTRACT_MONIC_

#include <sys/types.h>
#include <monapi.h>
#include <monapi/io.h>
//���L�������g�p
#include <monapi/cmemoryinfo.h>


/*! 
 *  \struct WAIT_FRAME_BUF
 *  \brief �����҂��t���[���\����
 */
typedef struct{
    dword cmHandle;  //���L�������n���h��
    dword cmSize;  //���L�������T�C�Y
}WAIT_FRAME_BUF;



/*!
    abstract class AbstractMonic
*/

class AbstractMonic {

  private:

  protected:
    /*! \brief AbstractMonic �e���|������M�o�b�t�@ */ 
    byte   frame_buf[1500];
    
    /*! \brief ��M�p�P�b�g�{�̂̒��� */ 
    dword    frame_len;
    
    virtual void frame_input(void) = 0;
    
  public:
  
    //Public�����o
    
    /*! \brief �����҂��t���[�����X�g */ 
    List<WAIT_FRAME_BUF*>* waitFrameBufList;
    
    /*! \brief MAC�A�h���X */ 
    byte   ether_mac_addr[6];

    
    AbstractMonic();
    //���N���X�Ȃ̂ŁA���z�f�X�N�g���N�^���`
    virtual ~AbstractMonic();
    
    virtual void enableNetWork(void);
    virtual void disableNetWork(void);
    
    //�e��C���^�[�t�F�[�X���\�b�h �T�u�N���X(��ۃN���X(NIC)�Ŏ���������)
    virtual void frame_output( byte *, byte *, dword, word ) = 0;
    virtual int init(void) = 0;
    virtual int nic_probe(void) = 0;
    //virtual void nic_init(void) = 0;
    virtual int getNicIRQ() = 0;
    virtual void setNicIRQ(int) = 0;
    virtual int getNicIOBASE() = 0;
    virtual void setNicIOBASE(int) = 0;
    
    void frame_input_public(void);
    //void pop_frame_list

};

#endif
