/*!
    \file  mypciinf.h
    \brief Get PCI Information �w�b�_�t�@�C��

    Copyright (c) 2004 Yamami
    All rights reserved.
    License=MIT/X Licnese

    \author  Yamami
    \version $Revision$
    \date   create:2004/05/09 update:$Date$
*/
//2004/09/03 Yamami CVS �X�V�e�X�g

#ifndef _MY_PCI_INF
#define _MY_PCI_INF


#include <sys/types.h>
#include <monapi/CString.h>


//�萔�錾
//I/O�|�[�g CONFIG_ADDRESS
#define PCI_CONFIG_ADDRESS_ADDR 0x0CF8
//I/O�|�[�g CONFIG_DATA
#define PCI_CONFIG_DATA_ADDR 0x0CFC

//PCIINFO�t�@�C��
#define PCIINFO_FILE "PCIINF.BZ2"

//���s�R�[�h
#define CHR_CRLF 0x0D0A


//�G�C���A�X�錾
#define uchar unsigned char
#define int32 long
#define uint32 unsigned long
#define float32 float
#define int16 short
#define uint16 unsigned short


//�֐��錾
int lookup_pci_hw( dword , dword , dword , dword , dword*);
MonAPI::CString getPciInfName( byte* , dword , MonAPI::CString* , MonAPI::CString* );

#endif
