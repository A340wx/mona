/*!
    \file  NE2000.h
    \brief NE2000�h���C�o�N���X �w�b�_

    Copyright (c) 2004 Yamami, Higepon
    All rights reserved.
    License=MIT/X License

    \author  Yamami Higepon
    $Date: 2006/01/02 15:12:55 $
*/

#pragma once
#include <sys/types.h>
#include <monapi.h>
#include "Nic.h"

// don't include NE2000const.h at here.

namespace mones {

class NE2000 : public Nic
{
public:
    void  Send(Ether::Frame*);
    Ether::Frame* Recv(int n);
	int interrupt();
    NE2000();
    ~NE2000();
    int init();
	void getMacAddress(byte* dest){ memcpy(dest, ether_mac_addr, 6);}
private:
    dword getFrameBufferSize(){ return frame_len; }
    void ne_pio_writemem( byte *, dword, dword );
    void ne_pio_readmem( dword, byte *, dword );
    int  ne_bcompare( byte *, byte *, dword );
/////////
    void inputFrame();	
    void outputFrame(byte* packet, byte* macAddress, dword size, word protocolId);
    void getFrameBuffer(byte* buffer, dword size);
////////
    byte       ne_ringbuf_status;
    byte       ne_ringbuf_bound;
    dword      ne_ringbuf_len;
    dword      ne_rx_start;      /* ��M�p�P�b�g�{�̂̊J�n�A�h���X */
    byte       ne_rx_bound;      /* ��M��̋��E���W�X�^�l */
    dword      ne_rx_write_p;    /* ��M�p�P�b�g�������݃A�h���X */
    dword      ne_rx_sub_len;    /* �܂�Ԃ����̒��� */
    dword      ne_rx_remain_len; /* �c��̒���(�܂�Ԃ����Ȃ��Ƃ��͖{�̂̒����Ɠ���) */ 
    dword      frame_len;
    byte       frame_buf[1500];
    byte       ether_mac_addr[6];
    int        ne_sizeof_test_pattern;
    byte       ne_test_buffer[20];
};

}; // namespace mones

