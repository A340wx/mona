#include <monapi.h>
using namespace MonAPI;

extern "C" {
#include "waba.cpp"
}

class myApplication : public MonaApplication
/* MONA�A�v���P�[�V�������^ */
	{
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
	dword targetID = Message::lookupMainThread("MOUSE.SVR");
	if (targetID == 0xFFFFFFFF)
	{
		printf("Reversi:MouseServer not found\n");
		exit(1);
	}

	// �}�E�X�T�[�o�[�Ƀ}�E�X���������悤�Ɏ������g��o�^���郁�b�Z�[�W�𑗐M
	MessageInfo info;
	Message::create(&info, MSG_MOUSE_REGIST_TO_SERVER, myPid, 0, 0, NULL);
	if (Message::send(targetID, &info)) {
		printf("[ERROR] mouse server not found\n");
	}

	// �X�N���[��������
	screen = Screen();
	}

int myApplication::main(List<char*>* pekoe)
	{
	WClass *vclass;
	Var param5[5];
	Var param7[7];
	//int i, type, key, x, y, mod;
	//int32 timer_interval;

	// �A�v���P�[�V�����X�^�[�g
	printf("Waba for %s %s\n", VM_OS, WABA_VERSION);
	mainWinObj = startApp();
	if(!mainWinObj){
		stopApp(mainWinObj);
		return 0;
	}else{
		vclass = (WClass *)WOBJ_class(mainWinObj);
	}

	// ���\�b�h�Ăяo��������
#ifdef QUICKBIND
	// cache method map numbers for commonly called methods
	postPaintMethodMapNum = getMethodMapNum(vclass, createUtfString("_doPaint"),
		createUtfString("(IIII)V"), SEARCH_ALL);
	postEventMethodMapNum = getMethodMapNum(vclass, createUtfString("_postEvent"),
		createUtfString("(IIIIII)V"), SEARCH_ALL);
	method_paint = getMethodByMapNum(vclass, &vclass, (uint16)postPaintMethodMapNum);
	method_event = getMethodByMapNum(vclass, &vclass, (uint16)postEventMethodMapNum);
	if (postPaintMethodMapNum == -1 || postEventMethodMapNum == -1)
		return 0;
#else
	method_paint = getMethod(vclass, createUtfString("_doPaint"), createUtfString("(IIII)V"), &vclass);
	method_event = getMethod(vclass, createUtfString("_postEvent"), createUtfString("(IIIIII)V"), &vclass);
#endif

	// �`��J�n
	if (method_paint != NULL){
		param5[0].obj = mainWinObj;
		param5[1].intValue = 0;
		param5[2].intValue = 0;
		param5[3].intValue = g_mainWinWidth;
		param5[4].intValue = g_mainWinHeight;
		printf("Main.doPaint()\n");
		executeMethod(vclass, method_paint, param5, 1);
	}

	// �_�~�[�C�x���g����
	if (method_event != NULL){
		param7[0].obj = mainWinObj;
		param7[1].intValue = 100; // event_type
		param7[2].intValue = 0; // key
		param7[3].intValue = 0; // x
		param7[4].intValue = 0; // y
		param7[5].intValue = 0; // modifiers
		param7[6].intValue = 0; // timeStamp
		executeMethod(vclass, method_event, param7, 7);
	}

	// �C�x���g��҂�
	run();
	return 0;
	}

void myApplication::onKeyDown(int keycode, int modifiers)
	{
	WClass *vclass;
	Var param7[7];

	//printf("keycode %d\n", keycode);
	if(mainWinObj && method_event != NULL){
		vclass = (WClass *)WOBJ_class(mainWinObj);
		param7[0].obj = mainWinObj;
		param7[1].intValue = 100; // type
		param7[2].intValue = keycode; // key
		param7[3].intValue = 0; // x
		param7[4].intValue = 0; // y
		param7[5].intValue = modifiers; // modifiers
		param7[6].intValue = 0; // timeStamp
		executeMethod(vclass, method_event, param7, 7);
	}
	}

void myApplication::onMouseClick(int x, int y)
	{
	WClass *vclass;
	Var param7[7];

	//printf("x, y %d,%d\n", x, y);
	if(mainWinObj && method_event != NULL){
		vclass = (WClass *)WOBJ_class(mainWinObj);
		param7[0].obj = mainWinObj;
		param7[1].intValue = 200; // type
		param7[2].intValue = 0; // key
		param7[3].intValue = x; // x
		param7[4].intValue = y; // y
		param7[5].intValue = 0; // modifiers
		param7[6].intValue = 0; // timeStamp
		executeMethod(vclass, method_event, param7, 7);
	}
	}

int MonaMain(List<char*>* pekoe)
	{
	monaApp = new myApplication();
	return monaApp->main(pekoe);
	}
