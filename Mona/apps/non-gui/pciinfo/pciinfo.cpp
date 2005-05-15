/*!
    \file  mypciinf.cpp
    \brief Get PCI Information

    Copyright (c) 2004 Yamami
    All rights reserved.
    License=MIT/X License

    \author  Yamami
    \version $Revision$
    \date   create:2004/05/09 update:$Date$
*/

#include <monapi.h>
#include <monapi/messages.h>
#include <monapi/io.h>
#include <monapi/CString.h>
#include "pciinfo.h"

using namespace MonAPI;

int MonaMain(List<char*>* pekoe) {

    int reti;
    dword c_deviceid;
    dword InValue;

    word Vendor;
    word Device;

    syscall_get_io();

    CString bundlePath = MonAPI::System::getBundlePath();
    //pciinfo�t�@�C�����I�[�v��
    monapi_cmemoryinfo* pciinfData = monapi_call_file_decompress_bz2_file(bundlePath + "/" + PCIINFO_FILE, MONAPI_TRUE);
    //�G���[����
    if(pciinfData == NULL){
        printf("PCI DATA FILE OPEN ERROR !!!\n");
    }

    printf("PCI Information !!!\n");

    //�o�X�ԍ�0�ɂ��āA�f�o�C�X�ԍ���0�`31�̂��ꂼ��ɂ��āA�x���_�[ID��ǂݏo��
    for(c_deviceid = 0; c_deviceid < 32 ; c_deviceid++ ){
        reti = lookup_pci_hw( c_deviceid , 0, 0 ,0, &InValue);
        if (InValue != 0xFFFFFFFF){
            //�x���_�[ID�̎擾
            Vendor = InValue & 0x0000FFFF;
            Device = InValue >> 16;
            //�x���_�[����/�f�o�C�X���̂̎擾
            CString VendorName;
            CString DeviceName;

            CString Dummy = getPciInfName(pciinfData->Data , InValue , &VendorName , &DeviceName);
            printf("DeviceNo=%d , Vendor=%x VendorName=%s Device=%x DeviceName=%s \n" ,c_deviceid , Vendor , (const char*)VendorName , Device , (const char*)DeviceName );
        }
    }


    monapi_cmemoryinfo_dispose(pciinfData);
    monapi_cmemoryinfo_delete(pciinfData);


    return 0;
}



/*!
    \brief lookup_pci_hw
        PCI�f�o�C�X�T��
    \param  dword deviceid [in] �f�o�C�X�ԍ�
    \param  dword func [in] �t�@���N�V�����ԍ�
    \param  dword bus [in] �o�X�ԍ�
    \param  dword regaddr [in] ���W�X�^�A�h���X
    \param  dword * InValue [OUT] �擾���W�X�^�̒l
    \return int ����

    \author Yamami
    \date   create:2004/05/15 update:2004/05/15
*/

int lookup_pci_hw( dword deviceid , dword func , dword bus , dword regaddr , dword *InValue)
{

    dword   outvalue;
    dword   outport;
    dword   inport;
    dword   tmp;

    //printf("lookup_pci_hw !!!\n");

    tmp = 0;
    //PCI CONFIG_ADDRESS���W�X�^�̒l�ݒ�
    //bit0-1�F0�ɌŒ�
    //bit2-7�F���W�X�^�A�h���X

    //bit8-10�F�@�\�ԍ�
    //bit11-15�F�f�o�C�X�ԍ�

    //bit16-23�F�o�X�ԍ�
    //bit24-30�F���U�[�u�ŁA0�ɌŒ�
    //bit31�F�C�l�[�u���r�b�g�ŁA1�ɌŒ�
    //���W�X�^ �r�b�g�ʒu 31,30�E�E�E�E0(32�r�b�g)

    //;�C�l�[�u���r�b�g�ƁA�o�X�ԍ����Z�b�g����B
    outvalue = 0x8000;
    outvalue = outvalue | bus;
    outvalue = outvalue << 16;

    //�f�o�C�X�ԍ��A�@�\�ԍ��ݒ�
    tmp = deviceid;
    tmp = tmp << 3;
    tmp = tmp + func;
    tmp = tmp << 8;

    outvalue = outvalue + tmp;

    tmp = 0;
    //���W�X�^�A�h���X�̎w��
    tmp = regaddr;
    tmp = tmp << 2;

    outvalue = outvalue + tmp;


    //I/O�|�[�g�̎w�� (0x0cf8�A32bit�ARead/Write��)
    outport = PCI_CONFIG_ADDRESS_ADDR;

    //�����ŁA�f�o�b�O�v�����g�����Ă݂�B
    //printf("Value= %x \n" , outvalue);
    //printf("Port= %x \n" , outport);

    outp32(outport,outvalue);


    //CONFIG_DATA���W�X�^�i0x0cfc�`0x0cff�A�C�ӂ̃T�C�Y�ARead/Write�j
    inport = PCI_CONFIG_DATA_ADDR;
    *InValue = inp32(inport);

    //�C�l�[�u���r�b�g�̃N���A
    outp32(outport,0);

    return 0;
}




/*!
    \brief IsLineSeparator
        �Z�p���[�^����

    \param  char ch [IN] �L�����N�^
    \return bool �Z�p���[�^�����Ȃ�true �ȊO�Ȃ�false
    \author Tino��
    \date   create:2004/06/111 update:2004/06/11
*/

inline bool IsLineSeparator(char ch)
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

CString getPciInfName( byte* PciInfData, dword InValue , CString* VendorName , CString* DeviceName){

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
