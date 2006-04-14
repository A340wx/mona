/*!
    \file   tulipMoNic.cpp
    \brief  tulip�h���C�o�N���X ���F������ �ЂȌ`�����B�B

    Copyright (c) 2005 Yamami
    All rights reserved.
    License=MIT/X License

    \author  Yamami
    \version $Revision$
    \date   create:2005/08/24 update:$Date$
*/

/*! \class tulipMoNic
 *  \brief tulip�h���C�o�N���X
 */



#include "tulipMoNic.h"


/*!
    \brief initialize
         tulipMoNic �R���X�g���N�^
    \author Yamami
    \date   create:2004/08/08 update:
*/
tulipMoNic::tulipMoNic()
{

}


/*!
    \brief initialize
         tulipMoNic init
    \author Yamami
    \return int ���� 0:���� �A 0�ȊO:�ُ�
    \date   create:2004/08/12 update:
*/
int tulipMoNic::init() 
{

    int reti;
    

    //�v���C�x�[�g�����o������
    ne_ringbuf_status=0;
    ne_ringbuf_bound=0;
    ne_ringbuf_len=0;

    ne_rx_start=0;      /* ��M�p�P�b�g�{�̂̊J�n�A�h���X */
    frame_len=0;        /* ��M�p�P�b�g�{�̂̒��� */
    ne_rx_bound=0;      /* ��M��̋��E���W�X�^�l */
    ne_rx_write_p=0;    /* ��M�p�P�b�g�������݃A�h���X */
    ne_rx_sub_len=0;    /* �܂�Ԃ����̒��� */
    ne_rx_remain_len=0; /* �c��̒���(�܂�Ԃ����Ȃ��Ƃ��͖{�̂̒����Ɠ���) */
    
    ne_sizeof_test_pattern=20;

    //tulip ���݊m�F
    reti = nic_probe();
    if(reti != 0 ){
        printf("Does Not Exist tulip!!!\n");
        return -1;
    }

    //tulip ������
    nic_init();

    return 0;
}


/*!
    \brief frame_input
        tulip �f�[�^���̓��[�`��
        �{���́Atulip����̊��荞�݂ɂăR�[�������B
        �e�X�g�v���O�����ł́A�����I��MonaMain �ŃR�[���B
    \param  void
    \return void

    \author Yamami
    \date   create:2004/08/03 update:$Date$
*/
void tulipMoNic::frame_input(void)
{

    byte sts,*buf;
    //�o�E���_�����W�X�^ �ƁA�J�����g�y�[�W���W�X�^��8�r�b�g��
    //�f�[�^�ɃA�N�Z�X����ہA8�r�b�g�V�t�g����16�r�b�g���A�N�Z�X���s��
    word  bnd,cpg;

    buf=frame_buf;

    // Page 0
    outp8( NE_P0_COMMAND, NE_CR_STA );
    // sts <- ��M�X�e�[�^�X���W�X�^(Receive Status Reg)
    sts=inp8( NE_P0_RSR );

//Yamami �f�o�b�O
//printf("sts : %x\n",sts);

    if( ( sts & NE_RSTAT_OVER ) !=0 ){
        printf("FIFO OverFlow\n");
        return; // ��MFIFO�I�[�o�[�t���[����
    }

    if( ( inp8( NE_P0_ISR ) & NE_ISR_OVW ) !=0 ){
        printf("RING OverFlow\n");
        return; // ��M�����O�o�b�t�@�I�[�o�[�t���[
    }

    //  ��M����
    if( ( sts & NE_RSTAT_PRX ) ==0 ){
        printf("Not Exist Packet \n");
        return; //  ��M�p�P�b�g�Ȃ�
    }

    //�y�[�W�𖾎��I�ɐ؂�ւ��� bnd �� cpg ��ǂ�
    outp8(NE_P0_COMMAND, NE_CR_PS0 | NE_CR_STA); /* Page 0 */
    bnd=inp8( NE_P0_BNRY ) + 1;      // bnd <-bnd  
    //bnd=inp8( NE_P0_BNRY );      // bnd <-bnd ������+1���Ȃ�
    outp8(NE_P1_COMMAND, NE_CR_PS1 | NE_CR_STA); /* Page 1 */
    cpg=inp8( NE_P1_CURR );          // cpg <- Current Page
    
    //Page0�ɖ߂��Ă���
    outp8( NE_P0_COMMAND, NE_CR_PS0 );


//Yamami �f�o�b�O
//printf("bnd : %x\n",bnd);
//printf("cpg : %x\n",cpg);


    if( bnd == NE_RX_PAGE_STOP ){
        // if last page then set to start page
        bnd=NE_RX_PAGE_START;
    }
    if( cpg == NE_RX_PAGE_STOP ){
        /* if last page then set to start page */
        cpg=NE_RX_PAGE_START; 
    }
    if( cpg == bnd ){        // Current Page = bound ?
        //printf("Not Exist Packet buffer \n");
        return;         // = �Ȃ� �o�b�t�@��Ƀp�P�b�g�Ȃ�
    }

    
    // bound+1 �y�[�W�̐擪4�o�C�g��ǂݍ���
    // Yamami �����ƁA�A�������ϐ��錾���A�A������4�o�C�g�ł��鎖�ɗ����Ă���H�H
    // �o�b�t�@�Ɉ�U���[�h���āA������鏈���ɕύX
    //ne_pio_readmem( bnd << 8, &ne_ringbuf_status, 4 );

    byte bndBuf[4];
    ne_pio_readmem( bnd << 8, bndBuf, 4 );

// Yamami�f�o�b�O ���[�h�A�h���X�̕\��
//printf("Read Src = bnd << 8 : %x\n",bnd << 8);

    ne_ringbuf_status = bndBuf[0]; /* Receive Status */
    ne_ringbuf_bound = bndBuf[1] & 0xFF; /* Next Packet Pointer */
    ne_ringbuf_len = bndBuf[3] * 256 + bndBuf[2];   /* Receive Byte Count */

    //�����ꂪ�A���ꂼ��t�̂悤�ȋC������B�G���f�B�A���̈Ⴂ�H�H
    //  ���̎��́ARead/Write����ύX
    //ne_ringbuf_status = bndBuf[1]; /* Receive Status */
    //ne_ringbuf_bound = bndBuf[0] & 0xFF; /* Next Packet Pointer */
    //ne_ringbuf_len = bndBuf[2] * 256 + bndBuf[3];   /* Receive Byte Count */

// Yamami�f�o�b�O
//printf("ne_ringbuf_status : %x\n",ne_ringbuf_status);
//printf("ne_ringbuf_bound  : %x\n",ne_ringbuf_bound);
//printf("ne_ringbuf_len : %x\n",ne_ringbuf_len);

    ne_rx_start=(bnd << 8) + 4; // �p�P�b�g�{�̂̊J�n�A�h���X

    // CRC�̕��̒���������
    // CRC�̕��̒��������� ? CRC����Ȃ���ne_ringbuf_*��4 byte?
    frame_len=ne_ringbuf_len - 4; /* �p�P�b�g�{�̂̒��� */

    // ��M�I����̋��E���W�X�^�l
    ne_rx_bound=ne_ringbuf_bound;

    if( ( ne_ringbuf_status & NE_RSTAT_PRX ) !=0 ){
                    // ��M������I������
        if( frame_len >= ETHER_HEADER_SIZE ){
                    // �ŒZ�����Z���Ƃ��̓G���[
            if( frame_len < ETHER_MAX_PACKET ) {
                    // �ő咷��蒷���Ƃ��̓G���[

                ne_rx_remain_len=frame_len;

                // �p�P�b�g�̎�荞�ݏ���
                // �܂�Ԃ����̒���
                ne_rx_sub_len=NE_RX_PAGE_STOP * 256 - ne_rx_start;

// Yamami�f�o�b�O
//printf("frame_input 03 ne_rx_start=%x\n",ne_rx_start);
//printf("frame_input 04 ne_rx_sub_len=%x\n",ne_rx_sub_len);

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
                
            }
            else{
                //printf("Error frame_len >= ETHER_MAX_PACKET \n");
            }
        }
        else{
            //printf("Error frame_len >= ETHER_HEADER_SIZE \n");
        }
    }
    else{
        //printf("Error ne_ringbuf_status & NE_RSTAT_PRX = 0 \n");
    }

    // Yamami �o�E���_�����W�X�^ �̍X�V
    bnd=ne_rx_bound; 
    if( bnd == NE_RX_PAGE_START ){
        bnd=NE_RX_PAGE_STOP;
    }
    bnd--;
    outp8( NE_P0_BNRY, bnd );    // ���E���W�X�^ = ���̃o�b�t�@ - 1

    //  ���荞�݃X�e�[�^�X���W�X�^�N���A
    outp8( NE_P0_ISR, 0xff );
    
    //H8 ���
    outp8(NE_P0_IMR, NE_IMR_PRXE); /* Packet Receive interrupt enable */

}



/*!
    \brief frame_output
        tulip �f�[�^�o�̓��[�`��
    \param  byte *pkt [in] �f�[�^�p�P�b�g�ւ̃|�C���^
    \param  byte *mac [in] �����MAC�A�h���X�ւ̃|�C���^
    \param  dword size [in] �p�P�b�g�T�C�Y
    \param  word pid [in] �v���g�R��ID(ETHER_PROTO)
    \return void

    \author Yamami
    \date   create:2004/08/03 update:$Date$
*/
void tulipMoNic::frame_output( byte *pkt, byte *mac, dword size, word pid )
{
    
    dword        ptx_type=0;
    dword        ptx_size=0;
    byte       *ptx_packet=0;
    byte       *ptx_dest=0;
    
    
    // ���M���������Ă��邩�ǂ����`�F�b�N����
    while( ( inp8( NE_P0_COMMAND ) & 0x04 ) !=0 );

//Yamami �f�o�b�O
//printf("frame_output 01\n");
    
    ptx_dest=mac;
    ptx_size=size;
    ptx_packet=pkt;
    // �l�b�g���[�N�o�C�g�I�[�_�[�ɕϊ�����
    // Yamami �ϊ��s�v�H
    ptx_type=(pid >> 8)+(pid << 8);

//Yamami �f�o�b�O
//int i;
//for(i=0 ; i<2 ; i++){
//    printf("ptx[1] = %x \n",(byte *)(&ptx_type + 1));
//}


    // ���荞�݋֎~
    // ���M�������Ɏ�M����ƃ��W�X�^�������Ă��܂�
    //disableInterrupt();
    disableNetWork();

    // ����A�h���X�̏�������
    ne_pio_writemem( ptx_dest, NE_TX_PAGE_START << 8, 6 );
    // ���M���A�h���X�̏�������
    ne_pio_writemem( ether_mac_addr, ( NE_TX_PAGE_START << 8 ) + 6, 6 );
    // �v���g�R��ID�̏�������
    ne_pio_writemem( (byte *)&ptx_type, ( NE_TX_PAGE_START << 8 ) + 12, 2 );
    // �f�[�^�����̏�������
    ne_pio_writemem( ptx_packet, ( NE_TX_PAGE_START << 8 ) + 14, ptx_size );

    ptx_size+=ETHER_HEADER_SIZE;

    // �ŏ��p�P�b�g�����Z�����ǂ������`�F�b�N����
    if( ptx_size < ETHER_MIN_PACKET ){
        ptx_size=ETHER_MIN_PACKET;
    }

    outp8( NE_P0_COMMAND, NE_CR_PS0 + NE_CR_RD2 + NE_CR_STA );
    
    // ���M�o�b�t�@�̈�̎w��
    outp8( NE_P0_TPSR, NE_TX_PAGE_START );
    
    // ���M���̎w��
    outp8( NE_P0_TBCR0, ptx_size & 0xff);
    outp8( NE_P0_TBCR1, ptx_size >> 8 );

    // ���M���߂𔭍s����
    outp8( NE_P0_COMMAND, NE_CR_PS0 + NE_CR_TXP + NE_CR_RD2 + NE_CR_STA );

    // ���荞�݋���
    //enableInterrupt();
    enableNetWork();

//Yamami �f�o�b�O
//printf("frame_output 02\n");

    // ���M���������Ă��邩�ǂ����`�F�b�N����
    // 2004/11/16 Yamami QEMU on tulip ���Ƃ��̃`�F�b�N���i���ɒʂ�Ȃ��悤�Ȃ̂Ń`�F�b�N���Ȃ�
    //while( ( inp8( NE_P0_COMMAND ) & 0x04 ) !=0 );

//Yamami �f�o�b�O
//printf("frame_output 03\n");

}


/*!
    \brief nic_probe
        tulip�������[�`��
        �o�b�t�@�������ɏ������݂Ɠǂݍ��݂��s���Atulip�����݂��邱�Ƃ��m�F����
    \param  void
    \return void

    \author Yamami
    \date   create:2004/08/01 update:$Date$
*/
int tulipMoNic::nic_probe(void)
{
    int i;

    return(0);
}


/*!
    \brief nic_init
        tulip���������[�`��
    \param  void
    \return void

    \author Yamami
    \date   create:2005/08/24 update:$Date$
*/
void tulipMoNic::nic_init(void)
{
    // �e�ϐ��̏�����

    //�Ƃ肠���������ŁAI/O�S�ĕ\�����Ă݂�B
    logprintf("nicIo_Base = %x\n",nicIo_Base);
    
    dword sts;
    //byte sts;
    dword iopt;

    sts = 1;
    
    for(iopt = nicIo_Base ; iopt < 0xEC7F ; iopt=iopt+4){
        sts=inp32( iopt );
        //sts=inp8( iopt );    
        logprintf("iopt(%x) = %x\n",iopt,sts);
    }

}





/*!
    \brief ne_pio_writemem
        ����J���[�`��
        tulip �o�b�t�@��������������
    \param  byte *src [in] �]�����A�h���X
    \param  dword dest [in] �]����A�h���X
    \param  dword size [in] ���� 
    \return void

    \author Yamami
    \date   create:2004/08/02 update:$Date$
*/
void tulipMoNic::ne_pio_writemem( byte *src, dword dest, dword size )
{
    dword i;

    word writetmp;

    /* �X�e�[�^�X���W�X�^�N���A */
    outp8( NE_P0_COMMAND, NE_CR_RD2 + NE_CR_STA );
    outp8( NE_P0_ISR, NE_ISR_RDC);

    /* ���� */
    outp8( NE_P0_RBCR0, size & 0xff );
    outp8( NE_P0_RBCR1, size >> 8 );

    /* �]����A�h���X */
    outp8( NE_P0_RSAR0, dest & 0xff );
    outp8( NE_P0_RSAR1, dest >> 8 );
    outp8( NE_P0_COMMAND, NE_CR_RD1 + NE_CR_STA );

//    for(i=0;i<size;i+=2){
//        outp8( PIO_ADATA, *(src+1) );
//        outp8( NE_ASIC_DATA, *src );
//        src+=2;
//    }


    // 2004/08/02 DATA��16�r�b�g���ł��Ƃ肷��̂ŁAWord�ϊ�����I/O
    for(i = 0 ; i < size ; i+=2 , src+=2){
        //writetmp = (word)(*(src) << 8) + (word)*(src+1);
        //���g���G���f�B�A���Ȃ炱���H�H
        writetmp = (word)(*(src + 1) << 8) + (word)*(src);
        outp16( NE_ASIC_DATA, writetmp );
    }
    
    /* wait */
    for(i=0;i<0xff;i++){
        if( ( inp8(NE_P0_ISR) & NE_ISR_RDC ) == 0 )
            break;
    }

}


/*!
    \brief ne_pio_readmem
        ����J���[�`��
         tulip �̃���������ǂ݂���
    \param  dword src [in] �]�����A�h���X
    \param  byte *dest [in] �]����A�h���X
    \param  dword size [in] ���� 
    \return void

    \author Yamami
    \date   create:2004/08/02 update:$Date$
*/
void tulipMoNic::ne_pio_readmem( dword src, byte *dest, dword size )
{
    dword i;

    word readtmp;

//Yamami �f�o�b�O
//printf("ne_pio_readmem src=%x \n",src);

    // abort DMA, start NIC
    outp8( NE_P0_COMMAND, NE_CR_RD2 + NE_CR_STA );
    // length
    outp8( NE_P0_RBCR0, size & 0xff );
    outp8( NE_P0_RBCR1, size >> 8 );
    // source address
    outp8( NE_P0_RSAR0, src & 0xff );
    outp8( NE_P0_RSAR1, src >> 8 );
    outp8( NE_P0_COMMAND, NE_CR_RD0 + NE_CR_STA );

//    for(i=0;i<size;i+=2){
//        *dest=inp8( NE_ASIC_DATA );
//        *(dest+1)=inp8( PIO_ADATA );
//        dest+=2;
//    }
    
    // 2004/08/02 DATA��16�r�b�g���ł��Ƃ肷��̂ŁAWord�ϊ�����I/O
    for(i = 0 ; i < size ; i+=2 , dest+=2){
        readtmp=inp16( NE_ASIC_DATA );
        //*dest=(byte)(readtmp >> 8);
        //*(dest+1)=(byte)(readtmp & 0xff);
        //���g���G���f�B�A���Ȃ炱���H�H
        *(dest+1)=(byte)(readtmp >> 8);
        *(dest)=(byte)(readtmp & 0xff);
    }
    
}



/*!
    \brief ne_bcompare
        ����J���[�`��
         �o�C�i����r���[�`��
    \param  byte *src [in] ��r���A�h���X
    \param  byte *dest [in] ��r��A�h���X
    \param  dword size [in] ����
    \return int ����:��v==0,�s��v==0�ȊO

    \author Yamami
    \date   create:2004/08/02 update:$Date$
*/
int tulipMoNic::ne_bcompare( byte *src, byte *dest, dword size )
{
    dword i;

    for(i=0;i<size;i++){
        if( src[i]!=dest[i] )
            return(1);
    }

    return(0);
}



/*!
    \brief getNicIRQ
       NIC IRQ �Q�b�^�[
    \author Yamami
    \date   create:2004/08/30 update:
*/
int tulipMoNic::getNicIRQ() 
{

    //TODO Yamami!! �{���́A�ݒ�t�@�C��������IRQ���𓾂�
    return nicIRQ;
}

/*!
    \brief setNicIRQ
       NIC IRQ �Z�b�^�[
    \author Yamami
    \date   create:2004/10/31 update:2004/10/31
*/
void tulipMoNic::setNicIRQ(int value) 
{
    nicIRQ = value;

}


/*!
    \brief getNicIOBASE
       NIC IO_BASE �Q�b�^�[
    \author Yamami
    \date   create:2004/10/31 update:2004/10/31
*/
int tulipMoNic::getNicIOBASE() 
{

    //TODO Yamami!! �{���́A�ݒ�t�@�C��������IRQ���𓾂�
    return nicIo_Base;
}

/*!
    \brief setNicIOBASE
       NIC IO_BASE  �Z�b�^�[
    \author Yamami
    \date   create:2004/10/31 update:2004/10/31
*/
void tulipMoNic::setNicIOBASE(int value) 
{
    nicIo_Base = value;

}
