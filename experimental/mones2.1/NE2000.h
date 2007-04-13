//$Id$
//    All rights reserved.
//    License=MIT/X License
//    Original Author of this file is Yamami
#pragma once
#include <sys/types.h>
#include <monapi.h>
#include "Nic.h"

namespace mones {

class NE2000 : public Nic
{
public:
    void  SendFrm(Ether*);
    int interrupt();
    NE2000();
    ~NE2000();
    int init();
    enum{
        VENDORID   =0x10EC,
        DEVICEID   =0x8029,
    };
private:
    void w_reg(uint16_t reg,uint8_t val){ outp8(iobase+reg,val); };
    uint8_t r_reg(uint16_t reg){ return inp8(iobase+reg); };
    void w_regw(uint16_t reg,uint16_t val){ outp16(iobase+reg,val); };
    uint16_t r_regw(uint16_t reg){ return inp16(iobase+reg); };

    void ne_pio_writemem( uint8_t*, uint32_t, uint32_t );
    void ne_pio_readmem( uint32_t, uint8_t*, uint32_t );
    int rxihandler();

    uint8_t       ne_ringbuf_status;
    uint8_t       ne_ringbuf_bound;
    uint32_t      ne_ringbuf_len;
    uint32_t      ne_rx_start;      // ��M�p�P�b�g�{�̂̊J�n�A�h���X //
    uint8_t       ne_rx_bound;      // ��M��̋��E���W�X�^�l //
    uint32_t      ne_rx_write_p;    // ��M�p�P�b�g�������݃A�h���X //
    uint32_t      ne_rx_sub_len;    // �܂�Ԃ����̒��� //
    uint32_t      ne_rx_remain_len; // �c��̒���(�܂�Ԃ����Ȃ��Ƃ��͖{�̂̒����Ɠ���) // 
    uint32_t      frame_len;
    enum{
        // QEMU PCI NE2000
        NE_ASIC          =0x10,
        NE_ASIC_DATA     =NE_ASIC,  
        NE_ASIC_RESET    =NE_ASIC+0x0f,  

        //Yamami
        NE_MEM_START     =64,    // �o�b�t�@�������J�n�y�[�W�ԍ� (�A�h���X4000h)
        NE_MEM_END       =128,    // �o�b�t�@�������I���y�[�W�ԍ� (�A�h���X8000h)
        NE_PAGE_SIZE     =256,    // �P�y�[�W�̃o�C�g�� //
        NE_TX_PAGE_START =0x40,    // ���M�o�b�t�@�J�n�y�[�W�ԍ�
        NE_RX_PAGE_START =0x46,    // ��M�o�b�t�@�J�n�y�[�W�ԍ�
        NE_RX_PAGE_STOP  =0x80,    // ��M�o�b�t�@�I���y�[�W�ԍ�

        // NE2000 ���W�X�^�A�h���X��`
        NE_P0_COMMAND    =0,  
        NE_P0_PSTART     =1,  
        NE_P0_PSTOP      =2,  
        NE_P0_BNRY       =3,        // Boundary Reg
        NE_P0_TSR        =4,        // Transmit Status
        NE_P0_TPSR       =4,        // Transmit Page
        NE_P0_TBCR0      =5,        // Transmit Byte
        NE_P0_NCR        =5,        // Nubmer of
        NE_P0_TBCR1      =6,  
        NE_P0_ISR        =7,        // Interrupt Status
        NE_P0_RSAR0      =8,        // Remote Start
        NE_P0_RSAR1      =9,  
        NE_P0_RBCR0      =0xa,      // Remote Byte
        NE_P0_RBCR1      =0xb,  
        NE_P0_RSR        =0xc,      // Receive Status
        NE_P0_RCR        =0xc,      // Receive Configuration
        NE_P0_TCR        =0xd,      // Transmit Configuration
        NE_P0_DCR        =0xe,      // Data Configuration
        NE_P0_IMR        =0xf,      // Interrupt Mask
        NE_P0_CNTR0      =0xd,  
        NE_P0_CNTR1      =0xe,  
        NE_P0_CNTR2      =0xf,  

        NE_P1_COMMAND    =0,  
        NE_P1_PAR0       =1,        // Physical Addres
        NE_P1_PAR1       =2,  
        NE_P1_PAR2       =3,  
        NE_P1_PAR3       =4,  
        NE_P1_PAR4       =5,  
        NE_P1_PAR5       =6,  
        NE_P1_CURR       =7,        // Current Page
        NE_P1_MAR0       =8,        // Multicast Address  
        // NE2000 ���W�X�^�萔��`
        NE_CR_PS0        =0,        // Page 0
        NE_CR_PS1        =0x40,     // Page 1
        NE_CR_PS2        =0x80,     // Page 2
        NE_CR_RD0        =8,        // Remote DMA
        NE_CR_RD1        =0x10,  
        NE_CR_RD2        =0x20,  
        NE_CR_TXP        =4,        // Transmit packet
        NE_CR_STA        =2,        // start 
        NE_CR_STP        =1,        // stop
  
        NE_RCR_AB        =4,        // accept broadcast
        NE_RCR_APROMIS   =0x10,     // PROMISCUOUS PHYSICAL:
        NE_RCR_MON       =0x20,     // monitor mode
  
        NE_DCR_FT1       =0x40,     // fifo //
        NE_DCR_LS        =8,        // Loopback select
        NE_DCR_WTS       =1,        // Word Transfer

        NE_ISR_PRX       =1,        // successful receive
        NE_ISR_PTX       =2,        // successful trasmit
        NE_ISR_RXE       =4,        // receive error
        NE_ISR_TXE       =8,        // transmit error
        NE_ISR_OVW       =0x10,     // overflow //
        NE_ISR_CNT       =0x20,     // counter overflow
        NE_ISR_RDC       =0x40,     // Remote DMA
        NE_ISR_RST       =0x80,     // reset //

        NE_IMR_PRXE      =1,        // successful receive
        NE_IMR_PTXE      =2,        // successful trasmit
        NE_IMR_RXEE      =4,        // receive error
        NE_IMR_TXEE      =8,        // transmit error
        NE_IMR_OVWE      =0x10,     // overflow //
        NE_IMR_CNTE      =0x20,     // counter overflow
        NE_IMR_RDCE      =0x40,     // Remote DMA

        NE_RSTAT_PRX     =1,        // successful receive
        NE_RSTAT_CRC     =2,        // CRC error
        NE_RSTAT_FAE     =4,        // Frame alignment
        NE_RSTAT_OVER    =8,        // overflow //

        NE_TSR_ABT       =8,        // Transmit Aborted
        NE_TCR_LB0       =2,        // Internal loopback
    };
};

}; // namespace mones

