
/*!
    \file   Pci.cpp
    \brief  PCI���C�u���� PCI�N���X

    Copyright (c) 2004 Yamami
    All rights reserved.
    License=MIT/X License

    \author  Yamami
    \version $Revision$
    \date   create:2004/10/15 update:$Date$
*/

/*! \class Pci
 *  \brief PCI���C�u���� PCI�N���X
 */


#include <monapi.h>
#include <monapi/messages.h>
#include <monapi/io.h>
#include <monapi/CString.h>
#include <monalibc/stdio.h>

#include <pci/Pci.h>


//PCIINFO�t�@�C��
#define PCIINFO_FILE "libPci.a"

using namespace MonAPI;




/*!
    \brief initialize
         Pci �R���X�g���N�^
    \author Yamami
    \date   create:2004/10/15 update:$Date$
*/
Pci::Pci()
{
    //I/O�擾
    syscall_get_io();

}


/*!
    \brief initialize
         Pci �f�X�N�g���N�^
    \author Yamami
    \date   create:2004/10/15 update:$Date$
*/
Pci::~Pci() 
{
    //�����ŁAI/O���������������E�E�E

}




/*!
    \brief CheckPciExist
         Pci�f�o�C�X���݊m�F�B�w�肵��Vendor/Device��PCI�f�o�C�X�̑��݂��m�F����B
    \author Yamami
    \param  word Vendor [in] �x���_�[ID
    \param  word Device [in] �f�o�C�XID
    \return PciInf�\���̂ւ̃|�C���^
    \date   create:2004/10/15 update:$Date$
*/
void Pci::CheckPciExist(word ChkVendor , word ChkDevice ,PciInf* RetPciInf) 
{
    
    byte DeviceNo;
    dword Vendor_Dev;

    word Vendor;
    word Device;

    dword BaseAd;
    dword  IrqLine;

    //�ԋp�l������ �f�o�C�X�͑��݂��Ȃ��B
    RetPciInf->Exist = 1;

    //Yamami!!! 2004/10/18 PCI���t�@�C���́A�o���h���ł͖����A�Ɨ������������
    //CString bundlePath = MonAPI::System::getBundlePath();
    //pciinfo�t�@�C�����I�[�v��
    //monapi_cmemoryinfo* pciinfData = monapi_call_file_decompress_bz2_file(bundlePath + "/" + PCIINFO_FILE, MONAPI_TRUE);
    //�G���[����
    //if(pciinfData == NULL){
    //    printf("PCI DATA FILE OPEN ERROR !!!\n");
    //}

    //�o�X�ԍ�0�ɂ��āA�f�o�C�X�ԍ���0�`31�̂��ꂼ��ɂ��āA�x���_�[ID��ǂݏo��
    for(DeviceNo = 0; DeviceNo < 32 ; DeviceNo++ ){
        //ReadConfig ��p����Vendor�̎擾
        Vendor = ReadConfig(0, DeviceNo, 0, PCI_VENDOR_ID, 2);
        
        if (Vendor != 0xFFFF){
            Device = ReadConfig(0, DeviceNo, 0, PCI_DEVICE_ID, 2);
            if (Device != 0xFFFF && ChkVendor == Vendor && ChkDevice == Device){
                //�f�o�C�X�����݂���B
                //�f�o�C�X�ƃx���_�[������ getPciInfName �ɃC���^�[�t�F�[�X�����킹��B
                Vendor_Dev = Vendor + (dword)(Device << 16);
                
                //Base�A�h���X�̎擾
                BaseAd = ReadConfig(0, DeviceNo, 0, PCI_BASE_ADDRESS1, 4);
logprintf(" BaseAd = %x \n"  , BaseAd);                
                //IRQ���C���̎擾  google PCI IRQ�擾�Ō���
                IrqLine = ReadConfig(0, DeviceNo, 0, PCI_IRQ_LINE, 1);
                
logprintf(" IrqLine = %x \n"  , IrqLine);                
                //�x���_�[����/�f�o�C�X���̂̎擾
                CString VendorName;
                CString DeviceName;

                //CString Dummy = getPciInfName(pciinfData->Data , Vendor_Dev , &VendorName , &DeviceName);
                
                //�ԋp�l����
                RetPciInf->Exist = 0;
                RetPciInf->DeviceNo = DeviceNo;
                RetPciInf->Vendor = Vendor;
                RetPciInf->Device = Device;
                RetPciInf->VendorName = VendorName;
                RetPciInf->DeviceName = DeviceName;
                RetPciInf->BaseAd = BaseAd;
                RetPciInf->IrqLine = IrqLine;
                
                //���������ꍇ�́A�����[�v�𔲂���
                break;
            }
        }
    }

    //�t�@�C���㏈��
    //monapi_cmemoryinfo_dispose(pciinfData);
    //monapi_cmemoryinfo_delete(pciinfData);

    //Return
    //return &RetPciInf;
    
}


/*!
    \brief ReadConfig
        PCI�f�o�C�X���擾
    \param  byte bus [in] �o�X�ԍ�
    \param  byte deviceid [in] �f�o�C�X�ԍ�
    \param  byte func [in] �t�@���N�V�����ԍ�
    \param  byte reg [in] ���W�X�^�A�h���X
    \param  byte readSize [I] �擾�T�C�Y
    \return dword �擾���W�X�^�̒l

    \author Yamami
    \date   create:2004/05/15 update:2004/05/15
*/
dword Pci::ReadConfig(byte bus, byte device, byte function, byte reg, byte readSize)
{
   dword result;
   PciPacket packet;

   packet.p.enabled   = 1;
   packet.p.bus       = bus;
   packet.p.device    = device;
   packet.p.function  = function;
   //packet.p.reg       = reg & ~3;
   packet.p.reg       = reg >> 2;
   packet.p.reserved1 = 0;
   packet.p.reserved2 = 0;

   /* set request and enable */
logprintf(" packet.command = %x \n"  , packet.command);
   outp32(REG_CONFIG_ADDRESS, packet.command);

   switch (readSize)
   {
   case 1:
       result = inp8(REG_CONFIG_DATA + (reg & 3));
       break;

   case 2:
       result = inp16(REG_CONFIG_DATA + (reg & 3));
       break;

   case 4:
       result = inp32(REG_CONFIG_DATA);
       break;

   default:
       result = 0xFFFFFFFF;
       break;
   }

   packet.p.enabled = 0;
   outp32(REG_CONFIG_ADDRESS, packet.command);
logprintf(" result = %x \n"  , result);

   return result;
}



/*!
    \brief IsLineSeparator
        �Z�p���[�^����

    \param  char ch [IN] �L�����N�^
    \return bool �Z�p���[�^�����Ȃ�true �ȊO�Ȃ�false
    \author Tino��
    \date   create:2004/06/111 update:2004/06/11
*/
inline bool Pci::IsLineSeparator(char ch)
{
    return ch == '\r' || ch == '\n' || ch == '\0';
}


/*!
    \brief getPciInfName
        PCI��񖼏�(�x���_�[�A�f�o�C�X)���擾
        PCI���W�X�^�l �������ɂƂ�APCIINF.TXT ����Y������x���_�[���̃x���_���̂��擾����B�B
    \param  byte* PciInfData [IN] PCI���f�[�^
    \param  dword InValue [IN] PCI���W�X�^�l(�x���_�[CD & �f�o�C�XCD)
    \param  CString& VendorName [OUT] �x���_�[����
    \param  CString& DeviceName [OUT] �f�o�C�X����

    \return MonAPI::CString dummy(�_�~�[�߂�l)

    \author Yamami
    \date   create:2004/05/16 update:2004/06/11
*/
CString Pci::getPciInfName( byte* PciInfData, dword InValue , CString* VendorName , CString* DeviceName){

    word Vendor;
    word Device;

    //�x���_�[ID�̎擾
    Vendor = InValue & 0x0000FFFF;
    Device = InValue >> 16;

    char VendorHex[5];    //�x���_�[CD�i�[�p
    char DeviceHex[5];    //�x���_�[CD�i�[�p
    sprintf(VendorHex, "%04X", Vendor);
    sprintf(DeviceHex, "%04X", Device);

    //NULL�܂ŌJ��Ԃ�
    while (*PciInfData != 0){

        //printf("%c",*PciInfData);

        //�܂��A�x���_�[���̂�T��
        //���C���Z�p���[�^�Ȃ玟�̕�����
        if (IsLineSeparator(*PciInfData)){
            PciInfData++;
        }
        else if (strncmp((const char*)PciInfData, VendorHex, 4) == 0){
            const char* ps = (const char*)(PciInfData + 5), * pe = ps;
            for (; !IsLineSeparator(*pe); pe++);

            //return CString(ps, pe - ps);
            //�x���_�[���m��
            *VendorName = CString(ps, pe - ps);

            //printf("%s\n",(const char*)VendorName);

            //�x���_�[���ȉ��̃f�o�C�X����������B
            //1�s�ǂݔ�΂�
            for (; !IsLineSeparator(*PciInfData); PciInfData++);
            while (*PciInfData != 0){
                if (IsLineSeparator(*PciInfData)){
                    PciInfData++;

                    //���C���Z�p���[�^�̎����^�u�Ȃ�A�f�o�C�X���
                    if (strncmp((const char*)PciInfData, "\t", 1) == 0){
                        PciInfData++;
                        if (strncmp((const char*)PciInfData, DeviceHex, 4) == 0){
                            const char* ps = (const char*)(PciInfData + 5), * pe = ps;
                            for (; !IsLineSeparator(*pe); pe++);
                            *DeviceName = CString(ps, pe - ps);

                            //printf("%s\n",(const char*)DeviceName);

                            return "dumy";
                        }
                        else{
                            //���̃f�o�C�X��
                            for (; !IsLineSeparator(*PciInfData); PciInfData++);
                        }
                    }
                    //�x���_�[���ύX�����܂œǂ�Ō�����Ȃ�������A�s���Ƃ���B
                    else{
                        *DeviceName = "???";
                        //printf("%s\n",(const char*)DeviceName);
                        return "dumy";
                    }
                }
                else{
                    printf("tobashi\n");

                    //�ǂ�ɂ��Y�����Ȃ��s�͓ǂݔ�΂�
                    for (; !IsLineSeparator(*PciInfData); PciInfData++);
                }

            }
        }
        else{
            //�ǂ�ɂ��Y�����Ȃ��s�͓ǂݔ�΂�
            for (; !IsLineSeparator(*PciInfData); PciInfData++);
        }
    }

    // �s��
    *VendorName = "???";
    *DeviceName = "???";
    return "???";
}
