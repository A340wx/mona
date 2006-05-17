///////////////////////////////
//This file is derived form NE2000.cpp by Mr. Yamami.
///////////////////////////////

#include "NE2000.h"

using namespace mones;

NE2000::NE2000()
{
    ne_ringbuf_status=0;
    ne_ringbuf_bound=0;
    ne_ringbuf_len=0;
    ne_rx_start=0;      /* ��M�p�P�b�g�{�̂̊J�n�A�h���X */
    frame_len=0;        /* ��M�p�P�b�g�{�̂̒��� */
    ne_rx_bound=0;      /* ��M��̋��E���W�X�^�l */
    ne_rx_write_p=0;    /* ��M�p�P�b�g�������݃A�h���X */
    ne_rx_sub_len=0;    /* �܂�Ԃ����̒��� */
    ne_rx_remain_len=0; /* �c��̒���(�܂�Ԃ����Ȃ��Ƃ��͖{�̂̒����Ɠ���) */
}

NE2000::~NE2000()
{

}

int NE2000::init(void)
{
    // DMA ��������~����B 
    w_reg( NE_P0_COMMAND, NE_CR_RD2|NE_CR_STP );
    //  �p�P�b�g���������ɏ�����Ȃ��悤�ɂ���
    w_reg( NE_P0_RCR, NE_RCR_MON );
    // ���[�h���]���A���[�v�o�b�N���[�h
    w_reg( NE_P0_DCR, NE_DCR_WTS | NE_DCR_FT1 | NE_DCR_LS );
    // ��M�o�b�t�@�J�n�A�h���X
    w_reg( NE_P0_PSTART, NE_MEM_START );
    // ��M�o�b�t�@�I���A�h���X
    w_reg( NE_P0_PSTOP, NE_MEM_END );
    // EEPROM �f�[�^�ǂ݂���
    byte buf[16];
    ne_pio_readmem( 0, buf, 16 );
    // �C�[�T�l�b�g�A�h���X�擾
    for(int i=0;i<6;i++){
        macaddress[i]=buf[2*i];
        printf("%x.",macaddress[i]);
    }
    printf("\n");
    // ���荞�݃X�e�[�^�X���W�X�^�N���A
    w_reg( NE_P0_ISR, 0xff );
    //NIC���Z�b�g
    w_reg(NE_ASIC_RESET, r_reg(NE_ASIC_RESET));
    //���Z�b�g�����܂ő҂�
    sleep(300);
    // �����[�gDMA ��~
    w_reg( NE_P0_COMMAND, NE_CR_RD2 | NE_CR_STP );
    // FIFO �X���b�V�����h 8Byte,�����[�gDMA �����������֎~
    // 8086 �o�C�g�I�[�_,16bit�� DMA �]��
    // Page0_0Eh DATA CONFIGURATION REGISTER (DCR) 0EH (WRITE)
    //   7 6   5   4   3  2   1    0
    //   - FT1 FT0 ARM LS LAS BOS WTS
    //   0 1   0   0   1   0   0    1
    w_reg( NE_P0_DCR, NE_DCR_FT1 + NE_DCR_WTS + NE_DCR_LS );

    // �����[�gDMA �o�C�g�J�E���^�N���A
    w_reg( NE_P0_RBCR0, 0 );
    w_reg( NE_P0_RBCR1, 0 );

    // ���j�^���[�h
    // (�p�P�b�g��M�����������Ȃ����A�o�b�t�@�����O�͂��Ȃ�)
    // RECEIVE CONFIGURATION REGISTER (RCR) 0CH (WRITE)
    w_reg( NE_P0_RCR, NE_RCR_MON );

    // �������[�v�o�b�N���[�h
    // TRANSMIT CONFIGURATION REGISTER (TCR) 0DH (WRITE)
    w_reg( NE_P0_TCR, NE_TCR_LB0 );

    // ���M�����O�o�b�t�@�J�n�A�h���X�̐ݒ�
    // 64
    w_reg( NE_P0_TPSR, NE_TX_PAGE_START );
    // ��M�����O�o�b�t�@�J�n�A�h���X�̐ݒ�
    // 70
    w_reg( NE_P0_PSTART, NE_RX_PAGE_START );

    // ��M�����O�o�b�t�@���E�A�h���X�̐ݒ�
    // 70
    w_reg( NE_P0_BNRY, NE_RX_PAGE_START );
    // ��M�����O�o�b�t�@�I���A�h���X�̐ݒ�
    // 128
    w_reg( NE_P0_PSTOP, NE_RX_PAGE_STOP );

    // ���荞�݃X�e�[�^�X���W�X�^�̃N���A
    w_reg( NE_P0_ISR, 0xff );
    //  ���荞�݋������̐ݒ�
    w_reg( NE_P0_IMR, NE_IMR_PRXE | NE_IMR_PTXE );

    // Page 1 �̐ݒ�
    w_reg( NE_P0_COMMAND, NE_CR_RD2 | ( NE_CR_PS1 + NE_CR_STP ) );

    // Ethernet �A�h���X�̐ݒ�
    for(int i=0;i<6;i++){
        w_reg( NE_P1_PAR0 + i, macaddress[i] );
    }

    // �ŏ��Ɏ�M�����p�P�b�g���i�[����A�h���X�̐ݒ�
    w_reg( NE_P1_CURR, NE_RX_PAGE_START + 1 );

    /* �}���`�L���X�g���W�X�^�̐ݒ� */
    for(int i=0;i<8;i++)
        w_reg( NE_P1_MAR0+i, 0 );

    // Page 0 �ɂ��ǂ�
    w_reg( NE_P0_COMMAND, NE_CR_RD2 | NE_CR_STP );

    // ��M�p�P�b�g�t�B���^�̐ݒ�
    // �u���[�h�L���X�g�Ǝ������݂̂��������Ɋi�[
    // accept broadcast
    w_reg( NE_P0_RCR, NE_RCR_AB );
    // NIC ���A�N�e�B�u�ɂ���
    w_reg( NE_P0_COMMAND, NE_CR_RD2 | NE_CR_STA );

    // ���[�v�o�b�N���[�h�𔲂��Ēʏ퓮�샂�[�h�ɓ���
    w_reg( NE_P0_TCR, 0 );
    printf("initalize completed.\n");
    return 0;
}

int NE2000::interrupt() 
{
    byte ret=0x0000;
    byte val = r_reg(NE_P0_ISR);
    if( val & NE_ISR_PRX){
        rxihandler();
        ret |= RX_INT;
    }
    if (val & NE_ISR_PTX){
        txihandler();
        ret |= TX_INT;
    }
    if( val & (NE_ISR_RXE|NE_ISR_TXE|NE_ISR_OVW|NE_ISR_CNT|NE_ISR_RST)){
        ret |= ER_INT;
    }
    w_reg( NE_P0_ISR, 0xFF );
    //Interrupt was masked by OS handler.
    enableNetwork(); //Now be enabled here. 
    return ret;
}

int NE2000::rxihandler()//void NE2000::inputFrame(void)
{
    // Page 0
    w_reg( NE_P0_COMMAND, NE_CR_STA );
    byte sts=r_reg( NE_P0_ISR );//Recive Stats Register.
    if( ( sts & NE_RSTAT_OVER ) !=0 ){
        printf("RX FIFO OverFlow\n");
        return ER_INT;
    }
    if( ( r_reg( NE_P0_ISR ) & NE_ISR_OVW ) !=0 ){
        printf("RX RING OverFlow\n");
        return ER_INT;
    }
    if( ( sts & NE_RSTAT_PRX ) ==0 ){
        printf("Not Exist RX Packet \n");
        return ER_INT;
    }

    w_reg(NE_P0_COMMAND, NE_CR_PS0 | NE_CR_STA); // Page 0
    word bnd=r_reg( NE_P0_BNRY ) + 1;      // Boundary
    w_reg(NE_P1_COMMAND, NE_CR_PS1 | NE_CR_STA); // Page 1
    word cpg=r_reg( NE_P1_CURR );          //Current Page
    //Page0�ɖ߂��Ă���
    w_reg( NE_P0_COMMAND, NE_CR_PS0 );

    if( bnd == NE_RX_PAGE_STOP ){
        // if last page then set to start page
        bnd=NE_RX_PAGE_START;
    }
    if( cpg == NE_RX_PAGE_STOP ){
        /* if last page then set to start page */
        cpg=NE_RX_PAGE_START;
    }
    if( cpg == bnd ){        // Current Page = bound ?
        printf("Not Exist RX Packet buffer \n");
        return ER_INT;
    }

    // bound+1 �y�[�W�̐擪4�o�C�g��ǂݍ���
    byte bndBuf[4];
    ne_pio_readmem( bnd << 8, bndBuf, 4 );

    ne_ringbuf_status = bndBuf[0]; /* Receive Status */
    ne_ringbuf_bound = bndBuf[1] & 0xFF; /* Next Packet Pointer */
    ne_ringbuf_len = bndBuf[3] * 256 + bndBuf[2];   /* Receive Byte Count */

    ne_rx_start=(bnd << 8) + 4; // �p�P�b�g�{�̂̊J�n�A�h���X

    // CRC�̕��̒���������
    frame_len=ne_ringbuf_len - 4; /* �p�P�b�g�{�̂̒��� */

    // ��M�I����̋��E���W�X�^�l
    ne_rx_bound=ne_ringbuf_bound;

    if( ( ne_ringbuf_status & NE_RSTAT_PRX ) !=0 ){//��M����I��
        if((ETHER_HEADER_SIZE <= frame_len)  && (frame_len < ETHER_MAX_PACKET )) {
            ne_rx_remain_len=frame_len;
            // �p�P�b�g�̎�荞�ݏ���
            // �܂�Ԃ����̒���
            ne_rx_sub_len=NE_RX_PAGE_STOP * 256 - ne_rx_start;
            //byte* buf=frame_buf;
            Ether* frame= new Ether;
            byte* buf=(byte*)frame;
            if( ne_rx_sub_len < frame_len ){
                // ��M���ׂ��p�P�b�g�͐܂�Ԃ��Ă���
                // �O�����̓ǂݍ���
                ne_pio_readmem( ne_rx_start, buf, ne_rx_sub_len );
                ne_rx_start=NE_RX_PAGE_START * 256;

                // �������݃A�h���X�̍X�V
                buf+=ne_rx_sub_len;
                // �c��̓ǂݍ��ݒ��̍X�V
                ne_rx_remain_len=frame_len - ne_rx_sub_len;
            }
            // �p�P�b�g�̓ǂݍ���
            ne_pio_readmem( ne_rx_start, buf, ne_rx_remain_len );            
            frame->payloadsize=frame_len;
            rxFrameList.add(frame);
        }
    }
    // Yamami �o�E���_�����W�X�^ �̍X�V
    bnd=ne_rx_bound;
    if( bnd == NE_RX_PAGE_START ){
        bnd=NE_RX_PAGE_STOP;
    }
    bnd--;
    w_reg( NE_P0_BNRY, bnd );    // ���E���W�X�^ = ���̃o�b�t�@ - 1

    //  ���荞�݃X�e�[�^�X���W�X�^�N���A
    w_reg( NE_P0_ISR, 0xff );
 
    w_reg(NE_P0_IMR, NE_IMR_PRXE); /* Packet Receive interrupt enable */
    enableNetwork();
    return 0;
}

int NE2000::txihandler()
{
    return 0;
}

void NE2000::Send(Ether* frame)
{
    dword ptx_size=frame->payloadsize;
    byte* ptx_packet=(byte*)frame;
    // ���M���������Ă��邩�ǂ����`�F�b�N����
    while( ( r_reg( NE_P0_COMMAND ) & 0x04 ) !=0 );
    // ���M�������Ɏ�M����ƃ��W�X�^�������Ă��܂�
    disableNetwork();

    ne_pio_writemem( ptx_packet, ( NE_TX_PAGE_START << 8 ) , ptx_size );
    ptx_size+=ETHER_HEADER_SIZE;

    // �ŏ��p�P�b�g�����Z�����ǂ������`�F�b�N����
    if( ptx_size < ETHER_MIN_PACKET ){
        ptx_size=ETHER_MIN_PACKET;
    }

    w_reg( NE_P0_COMMAND, NE_CR_PS0 + NE_CR_RD2 + NE_CR_STA );

    // ���M�o�b�t�@�̈�̎w��
    w_reg( NE_P0_TPSR, NE_TX_PAGE_START );

    // ���M���̎w��
    w_reg( NE_P0_TBCR0, ptx_size & 0xff);
    w_reg( NE_P0_TBCR1, ptx_size >> 8 );

    // ���M���߂𔭍s����
    w_reg( NE_P0_COMMAND, NE_CR_PS0 + NE_CR_TXP + NE_CR_RD2 + NE_CR_STA );

    printf("send.\n");  
    delete frame;
    // ���荞�݋���
    enableNetwork();
}

void NE2000::ne_pio_writemem( byte *src, dword dest, dword size )
{
    /* �X�e�[�^�X���W�X�^�N���A */
    w_reg( NE_P0_COMMAND, NE_CR_RD2 + NE_CR_STA );
    w_reg( NE_P0_ISR, NE_ISR_RDC);
    // ����
    w_reg( NE_P0_RBCR0, size & 0xff );
    w_reg( NE_P0_RBCR1, size >> 8 );
    // �]����A�h���X
    w_reg( NE_P0_RSAR0, dest & 0xff );
    w_reg( NE_P0_RSAR1, dest >> 8 );
    w_reg( NE_P0_COMMAND, NE_CR_RD1 + NE_CR_STA );
    for(dword i = 0 ; i < size ; i+=2){
        w_regw( NE_ASIC_DATA, *(word*)(src+i) );
    }
    //wait 
    for(dword i=0;i<0xff;i++){
        if( ( r_reg(NE_P0_ISR) & NE_ISR_RDC ) == 0 )
            break;
    }
}

void NE2000::ne_pio_readmem( dword src, byte *dest, dword size )
{
    // abort DMA, start NIC
    w_reg( NE_P0_COMMAND, NE_CR_RD2 + NE_CR_STA );
    // length
    w_reg( NE_P0_RBCR0, size & 0xff );
    w_reg( NE_P0_RBCR1, size >> 8 );
    // source address
    w_reg( NE_P0_RSAR0, src & 0xff );
    w_reg( NE_P0_RSAR1, src >> 8 );
    w_reg( NE_P0_COMMAND, NE_CR_RD0 + NE_CR_STA );
    for(dword i = 0 ; i < size ; i+=2 , dest+=2){
        *(word*)dest=r_regw( NE_ASIC_DATA );
    }
}
