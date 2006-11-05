/**
 *	monaSq �w�b�_
 */
/*
 *	Copyright (c) 2006 okayu punch
 *
 *	Permission is hereby granted, free of charge, to any person
 *	obtaining a copy of this software and associated documentation
 *	files (the "Software"), to deal in the Software without restriction,
 *	including without limitation the rights to use, copy, modify, merge,
 *	publish, distribute, sublicense, and/or sell copies of the Software,
 *	and to permit persons to whom the Software is furnished to do so,
 *	subject to the following conditions:
 *
 *	The above copyright notice and this permission notice shall be
 *	included in all copies or substantial portions of the Software.
 *
 *	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *	MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 *	IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 *	CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 *	TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH
 *	THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#if !defined(MONASQ_H)
#define MONASQ_H

#include "monasq_base.h"

// include monAPI / BayGUI
#include <baygui.h>

// include Squirrel header
#include <squirrel.h>
#include <sqstdblob.h>
#include <sqstdsystem.h>
#include <sqstdio.h>
#include <sqstdmath.h>	
#include <sqstdstring.h>
#include <sqstdaux.h>

// include STL header
#include <vector>
#include <list>
#include <string>
using namespace std;

// include monasq::TextArea
#include "misc/TextArea.h"


// �N���X�O���錾
class SqRunner;
class SqEnvironment;
class MainFrame;
class InputArea;
class ConsoleArea;


//================================================================
// �}�N��
//================================================================

// �z��̗v�f��
#define ARRAY_LENGTH(x)		(sizeof(x) / sizeof(x[0]))

// �ψ������X�g�̓W�J�}�N��
#define GET_VA_ARGS(buf, size, fmt) \
	va_list vl; \
	va_start(vl, fmt); \
	monasq_vsprintf(buf, fmt, vl); \
	va_end(vl);


//================================================================
// �O���[�o���֐�
//================================================================

// Squirrel ���s��
extern SqEnvironment* getSqEnvironment();

//printf �t�H�[�}�b�g���� string �I�u�W�F�N�g����
extern string fmtString(const char* fmt, ...);

//Squirrel �X�N���v�g�����s
extern void exec_sq_script(HSQUIRRELVM v, SQChar* buffer);



//================================================================
// �萔
//================================================================

// ���b�Z�[�W�萔
enum {
	MONASQ_MSG_START = 0x00010000,	// �V�X�e�����b�Z�[�W�Ƃ��Ԃ�Ȃ������ȓK���Ȓl

	// Squirrel �̎��s�J�n�^�I���ʒm���b�Z�[�W
	MONASQ_MSG_SQRUNNER_START = MONASQ_MSG_START,
	MONASQ_MSG_SQRUNNER_END,

	// �R���\�[�����̑���
	MONASQ_MSG_CONSOLE_ADDTEXT,
	MONASQ_MSG_CONSOLE_CLEAR,
};


//================================================================
// �N���X
//================================================================
/**
 *	Squirrel �X���b�h���s�p�N���X
 */
class SqRunner : public Runnable {
	string m_script;
	bool m_bPrintExp;

	bool m_bFinished;
	dword m_threadId;
	MonAPI::Mutex m_mutex;
	
	int tryLock() { return m_mutex.tryLock(); }
	void unlock() { m_mutex.unlock(); }

public:
	SqRunner() : m_bFinished(true), m_threadId(0) {}
	virtual ~SqRunner() {}

	bool readyToRun(const SQChar* script, size_t len, bool bPrintExp);
	
	bool isBreaking() { return !running; }
	bool isFinished() { return m_bFinished; }

	virtual void run();
	void kill();
};


/**
 *	Squirrel ���s��
 *	<br>
 *	�������̎��s���̍쐬�������s�͂ł��܂���
 */
class SqEnvironment {
	Thread* m_scriptThread;
	SqRunner m_runner;
	list<Window*> m_scriptWndList;		// �X�N���v�g���Ǘ����Ă���E�C���h�E���X�g
	
public:
	SqEnvironment() : m_scriptThread(NULL) {}
	virtual ~SqEnvironment() { release(); }

	virtual bool init();
	virtual void release();

	virtual bool isRunning();

	virtual bool run(const SQChar* script, size_t len, bool bPrintExp);
	virtual void stop();
	virtual void stop_anyway();
	
	// Squirrel �X���b�h���s�I�u�W�F�N�g��Ԃ�
	SqRunner* getSqRunner() { return &m_runner; }

	// �E�C���h�E�Ǘ�
	virtual void addScriptWindow(Window* wnd) { m_scriptWndList.push_back(wnd); }
	virtual void removeScriptWindow(Window* wnd) { m_scriptWndList.remove(wnd); }
	virtual void stopAllScriptWindow();
};


/**
 *	�{�^��
 */
class MonasqButton : public Button {
public:
	// �{�^���n���h���֐��̃v���g�^�C�v
	typedef void (*ButtonHandler)(class MonasqButton* sender, void* p);

private:
	ButtonHandler mFunc;
	void* mpData;

public:
	MonasqButton() :
		Button(), mFunc(NULL), mpData(NULL) {}
	MonasqButton(const String& label) :
		Button(label), mFunc(NULL), mpData(NULL) {}

	//�N���b�N���̃n���h����ݒ肷��
	virtual void setHandler(ButtonHandler func, void* pData = NULL);

	//�C�x���g����
	void processEvent(Event *event);
};


/**
 *	�X�N���[���o�[
 */
class MonasqScrollbar : public Scrollbar {
	monasq::TextArea* mLinkedTextArea;

public:
	MonasqScrollbar(int orientation) :
		Scrollbar(orientation), mLinkedTextArea(NULL) {}
	
	void linkTextArea(monasq::TextArea* linkedTextArea) {
		mLinkedTextArea = linkedTextArea;
	}

	//�l��ݒ肷��
	virtual void setValue(int value);
};


/**
 *	���͗��e�L�X�g�G���A
 */
class InputArea : public monasq::TextArea {

	bool mbModified;

protected:
	//�C�x���g����
	void processEvent(Event *event);

public:
	InputArea(int buffer_size, bool draw_line)
 		: monasq::TextArea(buffer_size, draw_line), mbModified(false) {}

	// �ύX�t���O
	bool isModified() { return mbModified; }
	void setModifyFlag() { mbModified = true; }
	void resetModifyFlag() { mbModified = false; }
};


/**
 *	�R���\�[�����G���A
 */
class ConsoleArea : public monasq::TextArea {
	MonAPI::Mutex m_mutex;

protected:
	//�C�x���g����
	void processEvent(Event *event);

public:
	ConsoleArea(int buffer_size, bool draw_line)
 		: monasq::TextArea(buffer_size, draw_line) {}

	int lock() { return m_mutex.lock(); }
	void unlock() { m_mutex.unlock(); }
};


/**
 *	���C���E�C���h�E
 */
class MainFrame : public Frame {

	static MainFrame* s_inst;
	static dword s_mainThreadId;

	// �f�t�h���i
	MonasqButton* mPrevHistoryButton;
	MonasqButton* mNextHistoryButton;
	MonasqButton* mRunStopButton;
	MonasqButton* mClearInputButton;
	MonasqButton* mClearOutputButton;

	MonasqScrollbar* mInputScrollbar;

	InputArea* mInputArea;
	ConsoleArea* mConsoleArea;
	
	
	// �v���O��������
	List<char*>* m_pekoe;
	
	// �����Ǘ�
	vector<string> mHistory;
	unsigned int mHistCursor;
	
	// �R���\�[������
	list<char*> m_outputMsgQue;		// �e�L�X�g�o�̓��b�Z�[�W�p�L���[
	
	// ���̑��t���O
	bool mbCreated;


protected:
	void onCreate();
	void onButtonClick(MonasqButton* sender, void* pData);
	void processEvent(Event *event);
	void updateRunStopButton();

public:
	/**
	 *	���C���E�C���h�E�̃|�C���^���擾
	 */
	static MainFrame* MainFrame::getMainFrame() {
		return s_inst;
	}

	/**
	 *	���C���E�C���h�E�Ƀ��b�Z�[�W���M
	 */
	static int send(dword header, dword arg1 = 0, dword arg2 = 0, dword arg3 = 0, const char* str = NULL) {
		return MonAPI::Message::send(s_mainThreadId, header, arg1, arg2, arg3, str);
	}

	// �R���\�[�����փe�L�X�g�ǉ����b�Z�[�W�𑗂�
	static bool sendConsoleAddText(char* text);


	// ���͗��ɑł����܂ꂽ�X�N���v�g�����s
	void runScript();

	// �X�N���v�g�̎��s���~
	void stopScript();

	// ���ݍs�̃X�N���v�g�����s���Č��ʂ��o��
	void printLineScript();

	// �J�����g�̗�����������Ԃ�
	const string& getCurrentHistoryString() {
		return mHistory[mHistCursor];
	}


	// �O�̗�����
	void prevHistory();

	// ���̗�����
	void nextHistory();


	// ���͗��փt�H�[�J�X
	void focusInput(bool bFocused);

	// �R���\�[�����փt�H�[�J�X
	void focusConsole(bool bFocused);


	// �v���O�����������擾
	List<char*>* getProgramArgs() {
		return m_pekoe;
	}

	// �R���X�g���N�^�E�f�X�g���N�^
	MainFrame(List<char*>* pekoe);
	virtual ~MainFrame();
	
	
public:
	// �{�^�������n���h��
	static void MainFrame::buttonHandler(MonasqButton* sender, void* pData);
};


#endif /* !defined(MONASQ_H) */
