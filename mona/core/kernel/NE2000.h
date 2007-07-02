/*!
    \file  NE2000.h
    \brief NE2000�h���C�o�N���X �w�b�_

    Copyright (c) 2004 Yamami, Higepon
    All rights reserved.
    License=MIT/X License

    \author  Yamami Higepon
    \version $Revision: 3948 $
    \date   create:2004/08/08 update:$Date: 2007-01-16 23:54:00 +0900 (火, 16  1月 2007) $
*/
#ifndef _MONA_MONES_NE2000_
#define _MONA_MONES_NE2000_

#include <sys/types.h>
#include <io.h>
#include "Nic.h"

// don't include NE2000const.h at here.

namespace mones {

class NE2000 : public Nic
{
public:
    NE2000();
    virtual ~NE2000();

    int init();
    int probe();
    void inputFrame();
    void outputFrame(uint8_t* packet, uint8_t* macAddress, uint32_t size, uint16_t protocolId);

    virtual uint32_t getFrameBufferSize();
    virtual void getFrameBuffer(uint8_t* buffer, uint32_t size);
    void getMacAddress(uint8_t* dest);
    uint8_t getIRQ() const {return this->nicIRQ;}
    int getIOBase() const {return this->nicIo_Base;}
    void setIRQ(uint8_t irq) {this->nicIRQ = irq;}
    void setIOBase(int iobase) {this->nicIo_Base = iobase;}

private:
    int nicIRQ;
    int nicIo_Base;

    void nic_init(void);
    void ne_pio_writemem( uint8_t *, uint32_t, uint32_t );
    void ne_pio_readmem( uint32_t, uint8_t *, uint32_t );
    int ne_bcompare( uint8_t *, uint8_t *, uint32_t );
    void xfer_buf( uint8_t *, uint8_t *, uint32_t, uint32_t *, uint32_t, uint32_t,uint32_t );

    //private�����o
    /* ��M�����O�o�b�t�@�̃����N���̈��ǂݍ��ނƂ��� */
    /* ne_ring_buffer */
    uint8_t       ne_ringbuf_status;
    uint8_t       ne_ringbuf_bound;
    uint32_t        ne_ringbuf_len;

    uint32_t        ne_rx_start;      /* ��M�p�P�b�g�{�̂̊J�n�A�h���X */

    uint8_t       ne_rx_bound;      /* ��M��̋��E���W�X�^�l */
    uint32_t        ne_rx_write_p;    /* ��M�p�P�b�g�������݃A�h���X */
    uint32_t        ne_rx_sub_len;    /* �܂�Ԃ����̒��� */
    uint32_t        ne_rx_remain_len; /* �c��̒���(�܂�Ԃ����Ȃ��Ƃ��͖{�̂̒����Ɠ���) */
    /*! \brief ��M�p�P�b�g�{�̂̒��� */ 
    uint32_t    frame_len;
    uint8_t   frame_buf[1500];
    uint8_t   ether_mac_addr[6];
    /* NE2000 ���[�N�G���A */
    int        ne_sizeof_test_pattern;
    uint8_t       ne_test_buffer[20];
};

}; // namespace mones
#endif
