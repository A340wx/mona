#include <sys/types.h>
#include <monapi.h>
#include <pci/Pci.h>

using namespace MonAPI;

#define MAIN_2


#ifdef MAIN_1

//Yamami FileOutputStream�g�p�e�X�g
int MonaMain(List<char*>* pekoe)
{
    //Yamami �e�X�g���W�b�N

    int reti;

    char buf[1024];
    memset(buf, 0, sizeof(buf));

    sprintf(buf , "protType:%04x \n",1234);

    //FileOutputStream �̃e�X�g
    FileOutputStream fos("YTEST.TXT");

    printf("fileout:open=%d\n", fos.open());

    reti = fos.write((byte*)buf , 512);
    printf("fileout:read=%d\n", reti);

    printf("fos close pre\n");
    fos.close();
    printf("fos close after\n");
    return 0;
}

#endif

#ifdef MAIN_2

//Yamami Pci���C�u�����g�p�e�X�g
int MonaMain(List<char*>* pekoe)
{
    PciInf *pciinfo;
    
    //PCI���C�u�����N���X�̃C���X�^���X��
    Pci* pcilib = new Pci();
    
    pciinfo = pcilib->CheckPciExist(0x10EC,0x8029);
    
    if(pciinfo->Exist == 0){
        //�f�o�C�X��������΁A���̏���\��
        //printf("VendorName=%s\n",(const char*)pciinfo->VendorName);
        //printf("DeviceName=%s\n",(const char*)pciinfo->DeviceName);
        printf("DeviceNo=%d\n",pciinfo->DeviceNo);
        printf("BaseAd=%x\n",pciinfo->BaseAd);
        printf("IrqLine=%x\n",pciinfo->IrqLine);
    }
    else{
        printf("Device Not Exist!! \n");
    }
    
    
    pciinfo = pcilib->CheckPciExist(0x10AA,0x80AA);
    
    if(pciinfo->Exist == 0){
        //�f�o�C�X��������΁A���̏���\��
        //printf("VendorName=%s\n",(const char*)pciinfo->VendorName);
        //printf("DeviceName=%s\n",(const char*)pciinfo->DeviceName);
        printf("DeviceNo=%d\n",pciinfo->DeviceNo);
        printf("BaseAd=%x\n",pciinfo->BaseAd);
        printf("IrqLine=%x\n",pciinfo->IrqLine);
    }
    else{
        printf("Device Not Exist!! \n");
    }
    
    return 0;

}

#endif