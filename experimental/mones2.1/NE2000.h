/*!
    \file  NE2000.h
    \brief NE2000�h���C�o�N���X �w�b�_

    Copyright (c) 2004 Yamami, Higepon
    All rights reserved.
    License=MIT/X License

    \author  Yamami Higepon
    \version $Revision: 1.1 $
    \date   create:2004/08/08 update:$Date: 2006/01/02 15:12:55 $
*/
#ifndef _MONA_MONES_NE2000_
#define _MONA_MONES_NE2000_

#include <sys/types.h>
#include <monapi.h>
#include "Nic.h"

// don't include NE2000const.h at here.

namespace mones {

class NE2000 : public Nic
{
    void inputFrame();	
    void outputFrame(byte* packet, byte* macAddress, dword size, word protocolId);
    dword getFrameBufferSize();
    void getFrameBuffer(byte* buffer, dword size);
public:
    void  Send(Ether::Frame*){};
    Ether::Frame* Read(int n){return NULL;};
	int interrupt(){return 0;};

    NE2000();
    ~NE2000();
    int init();
    int probe();
	void getMacAddress(byte* dest);
    byte getIRQ() const {return this->nicIRQ;}
    int getIOBase() const {return this->nicIo_Base;}
    void setIRQ(byte irq) {this->nicIRQ = irq;}
    void setIOBase(int iobase) {this->nicIo_Base = iobase;}
private:
    int nicIRQ;
    int nicIo_Base;
    void nic_init(void);
    void ne_pio_writemem( byte *, dword, dword );
    void ne_pio_readmem( dword, byte *, dword );
    int ne_bcompare( byte *, byte *, dword );
    void xfer_buf( byte *, byte *, dword, dword *, dword, dword,dword );

    //private�����o
    /* ��M�����O�o�b�t�@�̃����N���̈��ǂݍ��ނƂ��� */
    /* ne_ring_buffer */
    byte       ne_ringbuf_status;
    byte       ne_ringbuf_bound;
    dword      ne_ringbuf_len;
    dword      ne_rx_start;      /* ��M�p�P�b�g�{�̂̊J�n�A�h���X */
    byte       ne_rx_bound;      /* ��M��̋��E���W�X�^�l */
    dword      ne_rx_write_p;    /* ��M�p�P�b�g�������݃A�h���X */
    dword      ne_rx_sub_len;    /* �܂�Ԃ����̒��� */
    dword      ne_rx_remain_len; /* �c��̒���(�܂�Ԃ����Ȃ��Ƃ��͖{�̂̒����Ɠ���) */
    /*! \brief ��M�p�P�b�g�{�̂̒��� */ 
    dword      frame_len;
    byte       frame_buf[1500];
    byte       ether_mac_addr[6];
    /* NE2000 ���[�N�G���A */
    int        ne_sizeof_test_pattern;
    byte       ne_test_buffer[20];
};

}; // namespace mones
#endif
