#ifndef __JPEGLS_H_
#define __JPEGLS_H_

//�W�O�U�O�e�[�u��
static int zigzag_table[]={
     0, 1, 8, 16,9, 2, 3,10,
    17,24,32,25,18,11, 4, 5,
    12,19,26,33,40,48,41,34,
    27,20,13, 6, 7,14,21,28,
    35,42,49,56,57,50,43,36,
    29,22,15,23,30,37,44,51,
    58,59,52,45,38,31,39,46,
    53,60,61,54,47,55,62,63,
    0
};

// �n�t�}���e�[�u��
typedef struct{
    int elem; //�v�f��
    unsigned short code[256];
    unsigned char  size[256];
    unsigned char  value[256];
}HUFF;

class CJPEGLS {

protected:

    // SOF
    int width;
    int height;

    // MCU
    int mcu_width;
    int mcu_height;

    int max_h,max_v;
    int compo_count;
    int compo_id[3];
    int compo_sample[3];
    int compo_h[3];
    int compo_v[3];
    int compo_qt[3];

    // SOS
    int scan_count;
    int scan_id[3];
    int scan_ac[3];
    int scan_dc[3];
    int scan_h[3];  // �T���v�����O�v�f��
    int scan_v[3];  // �T���v�����O�v�f��
    int scan_qt[3]; // �ʎq���e�[�u���C���f�N�X

    // DRI
    int interval;

    int mcu_buf[32*32*4]; //�o�b�t�@
    int*mcu_yuv[4];
    int mcu_preDC[3];

    // DQT
    int qt[3][64];
    int n_qt;

    // ���摜 ( [�����g��u��][�c���g��v��][���ʑ�(M/8)][�c�ʑ�(N/8)]
    int base_img[64][64];

    // DHT
    HUFF huff[2][3];


    // i/o
    unsigned char *data;
    int data_index;
    int data_size;

    unsigned long bit_buff;
    int bit_remain;

    unsigned char  get_byte(void);
    unsigned short get_word(void);
    unsigned short get_bits(int bit);

    void init(void);

    // �w�b�_�֌W
    void skip(void); // �������Z�O�����g
    void sof(void); // Start of Frame
    void sos(void); // Start Of Scan
    void dri(void); // Define Restart Interval
    void dqt(void); // Define Quantize Table
    void dht(void); // Define Huffman Table
    int header(void);

    // �f�R�[�h�֌W
    int decode_init(void);
    int get_huff(int tc,int th);
    int get_value(int size);
    int decode_huff(int scan,int *block);
    void idct_init(void);
    void idct(int *,int *);

    // MCU
    void mcu_bitblt(int *src,int *dest,int width,
                    int x0,int y0,int x1,int y1);
    void decode_mcu(void);
    void decode_yuv(int h,int v,unsigned char *rgb);
    void decode(unsigned char *rgb);

public:

    //�C���^�[�t�F�C�X
    CJPEGLS();
    ~CJPEGLS();
    int Open(unsigned char *data,int size);
    void GetInfo(int *width,int *height);
    void Decode(unsigned char * dest);
};


#endif
