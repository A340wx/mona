/*!
    \file  Pci.h
    \brief PCI���C�u���� �w�b�_

    class Pci

    Copyright (c) 2004 Yamami
    All rights reserved.
    License=MIT/X License

    \author  Yamami 
    \version $Revision$
    \date   create:2004/10/15 update:$Date$
	$Id$
*/

#ifndef _LIB_PCI_INF
#define _LIB_PCI_INF


#include <sys/types.h>
#include <monapi/CString.h>

using namespace MonAPI;

/*! 
 *  \struct PciPacket
 *  \brief PciPacket�\���� ���p��
 *   //PCI CONFIG_ADDRESS���W�X�^�̒l�ݒ�
 *   //bit0-1�F0�ɌŒ�
 *   //bit2-7�F���W�X�^�A�h���X
 *   //bit8-10�F�@�\�ԍ�
 *   //bit11-15�F�f�o�C�X�ԍ�
 *   //bit16-23�F�o�X�ԍ�
 *   //bit24-30�F���U�[�u�ŁA0�ɌŒ�
 *   //bit31�F�C�l�[�u���r�b�g�ŁA1�ɌŒ�
 *
 *   //���W�X�^ �r�b�g�ʒu 31,30�E�E�E�E0(32�r�b�g)
 */
typedef union
{
   uint32_t command;
   struct
   {
       unsigned reserved1 : 2;
       unsigned reg       : 6;
       unsigned function  : 3;
       unsigned device    : 5;
       unsigned bus       : 8;
       unsigned reserved2 : 7;
       unsigned enabled   : 1;
   } p;
} PciPacket;


/*! 
 *  \enum PciPacket
 *  \brief PCI�f�o�C�X�e��錾
 */
enum
{
   REG_CONFIG_ADDRESS = 0x0CF8,
   REG_CONFIG_DATA    = 0x0CFC,

   PCI_VENDOR_ID      = 0x00,
   PCI_DEVICE_ID      = 0x02,
   PCI_COMMAND        = 0x04,
   PCI_STATUS         = 0x06,
   PCI_REVISION       = 0x08,
   PCI_API            = 0x09,
   PCI_SUBCLASS       = 0x0a,
   PCI_BASECLASS      = 0x0b,
   PCI_HEADER         = 0x0e,
   PCI_BASE_ADDRESS1  = 0x10,
   PCI_BASE_ADDRESS2  = 0x14,
   PCI_BASE_ADDRESS3  = 0x18,
   PCI_BASE_ADDRESS4  = 0x1C,
   PCI_BASE_ADDRESS5  = 0x20,
   PCI_IRQ_LINE       = 0x3C,
   PCI_IRQ_PIN        = 0x3D
};


/*! 
 *  \struct PciInf
 *  \brief PciInf PCI�f�o�C�X���\����
 */
typedef struct
{
    int  Exist;       //���݊m�F���(���݂���=0  , ���݂��Ȃ�=0�ȊO)
    uint8_t DeviceNo;
    uint16_t Vendor;
    uint16_t Device;
    CString VendorName;
    CString DeviceName;
    uint32_t BaseAd;
    uint32_t  IrqLine;
} PciInf;



//���s�R�[�h
#define CHR_CRLF 0x0D0A


//�G�C���A�X�錾
#define uchar unsigned char
#define int32 long
#define uint32 unsigned long
#define float32 float
#define int16 short
#define uint16 unsigned short




/*!
    Pci class
*/
class Pci
{
    
  public:
    

    //�R���X�g���N�^
    Pci();
    ~Pci();

    void CheckPciExist(uint16_t , uint16_t ,PciInf*);
    uint32_t ReadConfig(uint8_t , uint8_t , uint8_t , uint8_t , uint8_t );
    void WriteConfig(uint8_t ,uint8_t ,uint8_t ,uint8_t ,uint8_t ,uint32_t );
  private:
    
    MonAPI::CString getPciInfName( uint8_t* , uint32_t , MonAPI::CString* , MonAPI::CString* );
    bool IsLineSeparator(char );
};




#endif
