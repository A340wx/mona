#include <monapi.h>
#include <monapi/messages.h>
using namespace MonAPI;

#define  MONA 1
#undef   WIN32
#define  WABA_VERSION    "0.1.3"
#define  VM_OS           "MONA"
#define  VM_USER         "MONA"
#define  g_mainWinOffX   200
#define  g_mainWinOffY   200
#define  g_mainWinWidth  200
#define  g_mainWinHeight 200

extern "C" {
#include "waba.c"
}

class myApplication : public MonaApplication {
/* MONA�A�v���P�[�V�������^ */
public:
	myApplication();
	virtual ~myApplication() {}

public:
	virtual int main(List<char*>* pekoe);
	virtual void onKeyDown(int keycode, int modifiers);
	virtual void onMouseClick(int x, int y);
};


myApplication::myApplication() : MonaApplication() {
	// �������g�̃X���b�hID�𓾂�
	dword myPid = System::getThreadID();

	// �}�E�X�T�[�o�[��T��
	dword targetID = Message::lookupMainThread("MOUSE.BIN");
	if (targetID == 0xFFFFFFFF)
	{
		printf("Waba:MouseServer not found\n");
		exit(1);
	}

	// �}�E�X�T�[�o�[�Ƀ}�E�X���������悤�Ɏ������g��o�^���郁�b�Z�[�W�𑗐M
	MessageInfo info;
	Message::create(&info, MSG_MOUSE_REGIST_TO_SERVER, myPid, 0, 0, NULL);
	if (Message::send(targetID, &info)) {
		printf("Waba:MouseServer not found\n");
		exit(1);
	}

}

int myApplication::main(List<char*>* pekoe) {
	char *filename;

	// �t�@�C����I��
	if(pekoe->size() != 1){
		filename = "/APPS/HELLO.WRP";
	}else{
		filename = pekoe->get(0);
	}

	// �A�v���P�[�V�����X�^�[�g
	startApp(filename);

	// �C�x���g��҂�
	run();
	return 0;
}

void myApplication::onKeyDown(int keycode, int modifiers) {
	int vlist[6];

	//printf("keycode %d\n", keycode);
	vlist[0] = 100; // type
	vlist[1] = keycode; // key
	vlist[2] = 0; // x
	vlist[3] = 0; // y
	vlist[4] = modifiers; // modifiers
	vlist[5] = 0; // timeStamp
	processEvent(vlist);

}

void myApplication::onMouseClick(int x, int y) {
	int vlist[6];

	//printf("x, y %d,%d\n", x, y);
	vlist[0] = 200; // type
	vlist[1] = 0; // key
	vlist[2] = x; // x
	vlist[3] = y; // y
	vlist[4] = 0; // modifiers
	vlist[5] = 0; // timeStamp
	processEvent(vlist);
}

int MonaMain(List<char*>* pekoe) {
	monaApp = new myApplication();
	return monaApp->main(pekoe);
}
