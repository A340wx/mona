/*
Copyright (C) 1998, 1999, 2000 Wabasoft

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later version. 

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details. 

You should have received a copy of the GNU General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 675 Mass Ave,
Cambridge, MA 02139, USA. 
*/

/*

If you're looking here, you've probably already looked at (or worked on) the
nm<platform>_a.c file.

�������Ȃ������������Ă���Ȃ�A�����炭 nm<platform>_a.c file �͂��łɌ����ł��傤�B

This file is the second step in porting the VM. In it, you need to place the
main application loop and class loader. If you get through this, you'll have
a basic VM running and from there you can implement the native functions
so you can actually see something on the screen->

���̃t�@�C���� VM ���ڐA���邽�߂̑�Q�X�e�b�v�ł��B���̒��ł��Ȃ��͎�v��
�A�v���P�[�V�������[�v�ƃN���X���[�_�[�������K�v������܂��B������I������΁A
��b�I�� VM ���s�����ł��傤�B�A�܂��A��������A�����ɃX�N���[����̉�����
���邱�Ƃ��ł���悤�ɁA�l�C�e�B�u�֐����������邱�Ƃ��ł��܂�->

The WabaVM, like other applications, needs some type of main application loop
where the OS sends it key clicks, mouse presses, etc. The VM also needs to
load classes from memory or disk or wherever.

WabaVM �͑��̃A�v���P�[�V�����̂悤�ɃA�v���P�[�V�����̎�v�ȃ��[�v��K�v�Ƃ��܂��B
���Ƃ���OS�������Ă���A�L�[�N���b�N��}�E�X�v���X�ȂǁBVM �͂܂���������f�B�X�N
����N���X�����[�h���邱�Ƃ�K�v�Ƃ��܂��B

Different platforms have different main application loops. For example, under
Win32, a program has a WinMain() function. Under PalmOS, applications have
a PilotMain() function.

�قȂ����v���b�g�t�H�[���͈قȂ�����v�ȃ��[�v�������Ă��܂��B���Ƃ��΁A
Win32 �ȉ��ł̓v���O������ WinMain() �֐��������Ă��܂��BPalmOS �ȉ��ł�
�A�v���P�[�V������ PilotMain() �֐��������Ă��܂��B

You'll want to implement a main application loop for the platform you are
porting to. Then, when things start up (initialization), you need to:

���Ȃ�����v�ȃA�v���P�[�V�������[�v�����Ȃ����ڐA�������v���b�g�t�H�[������
�Ɏ����������Ƃ��A�X�^�[�g�i�������j�̂��߂ɂ͈ȉ����K�v�ł�:

- parse the launch command and then call VmInit()
- call VmStartApp passing the class name of the program's main window

You'll also need to figure out how programs will launch the VM. The VM
is normally passed parameters telling it what class heap, class name, etc.
to use. It's usually another program that does this but you could do it
by building a waba launcher that draws a tray of icons and when you click
one, it runs the WabaVM with various parameters as an example of something
different. Whatever you do for this is platform-specific.

����ɁA�v���O�������ǂ̂悤��VM�����s���邩�l����K�v������ł��傤�B
VM�́A�g�p���邽�߂ɉ����N���X�q�[�v�ŁA�����N���X���Ȃǂ���킷
�p�����[�^��ʏ�n����܂��B����͒ʏ킱�������ʂ̃v���O�����ł����A
waba�����`���[�̍\�z�ɂ�肠�Ȃ����s���܂��BWabaVM �͂��܂��܂�
�p�����[�^�𔺂��Ď��s���܂����A����̓v���b�g�t�H�[���ŗL�ł��B

Just before the program exits, you'll should call VmStopApp(mainWinObj);

�v���O�������I������O�ɂ� VmStopApp(mainWinObj) ���ĂԕK�v������ł��傤;

That's it for initialization and exit, then you need to do some work to
hook up key presses, mouse presses, etc. to the VM. When a key is pressed,
you'll want to invoke the main window's onEvent() method. Here's an
example of how to do that:

	mainWinObj = globalMainWin;
	if (!mainWinObj)
		return;
	vclass = WOBJ_class(mainWinObj); // get runtime class
	method = getMethod(vclass, createUtfString("_postEvent"),
		createUtfString("(IIIIII)V"), &vclass);
	if (method != NULL)
		{
		params[0].obj = mainWinObj;
		params[1].intValue = type; // type
		params[2].intValue = key; // key
		params[3].intValue = 0; // x
		params[4].intValue = 0; // y
		params[5].intValue = 0; // modifiers
		params[6].intValue = 0; // timeStamp
		executeMethod(vclass, method, params, 7);
		}

This gets the runtime class of the main window object, gets a
reference to the _postEvent method, fills in an array of parameters
to pass and then calls executeMethod() to execute the method.

There is also a quickbind version of this which is quicker than the
above. You can look at nmpalm_b.c or nmwin32_b.c to get an idea how
that works (look for the #ifdef QUICKBIND) but you should start
without using the quickbind method.

You'll want to hook up mouse or pen click, key presses, calls from
the OS to repaint the window (which should call the main window's
_doPaint routine).

Overall, you need to make sure the following main window functions
get called:

�S�̂Ƃ��āA���̃��C���E�B���h�E�̊֐��Q���Ă΂�邱�Ƃ��m���߂�K�v������܂�:

_onTimerTick()
_postEvent() for key presses and mouse/pen clicks and moves

You'll need to map special keys (escape, etc.) if the device has
them to suitable numbers for waba. To do this, you can see how the
other native implementations do key mapping (a big switch statement).

The _onTimerTick() one can be tricky for devices that don't have
a built in timer (like PalmOS). When using one of those devices,
copy the code from the nmpalm_b.c to deal with timers. Basically,
this consists of getting the current time and looking for an event
up until the time the next timer period expires.

_onTimerTick() �̓p�[��OS�̂悤�Ƀr���g�C���^�C�}�[�������Ă��Ȃ�
�f�o�C�X�ɂ̓g���b�L�[�ɂȂ�܂��B�����̃f�o�C�X�ł�����g���Ƃ��́A
�^�C�}�[����舵�����߂� nmpalm_b.c ����R�[�h���R�s�[���Ă��������B
��{�I�ɁA����́A���݂̎��Ԃ𓾂Ď��̃^�C�}�[���Ԃ��I�����鎞�܂�
�C�x���g��{�����Ƃ��琬��܂��B

The VM only needs a single timer, the waba core classes have the
code to support multiple timers even though the underlying system
only supports a single one.

VM�͒P��̃^�C�}�[��K�v�Ƃ��܂��Bwaba���j�N���X�́A���Ƃ��V�X�e����
�P��̃^�C�}�[�����T�|�[�g���Ă��Ȃ��Ă��A�����̃^�C�}�[���x������
���߂̃R�[�h�������Ă��܂��B

The last code you need to implement is:

nativeLoadClass()

This is the function that load a class from memory, disk or whatever.
It looks like this:

 static uchar *nativeLoadClass(UtfString className, uint32 *size)

and it is passed a class name (not zero terminated, the UtfString
contains the len in:

className.len

and it returns a pointer to the class in memory after it is loaded
and fills in the *size variable with the size of the class in bytes.

The classes loaded are classes that are compiled by a java compiler
or other compiler that can generate code in the subset of java
bytecode that waba supports.

*/

/* static */ WObject mainWinObj;
/* static */ WObject Hashtable_keys[HASHTABLE_SIZE];
/* static */ uint32 Hashtable_elements[HASHTABLE_SIZE];
/* static */ uint32 classRecordOfs1[MAX_CLASS], classRecordOfs2[MAX_CLASS];
/* static */ uint32 classRecordSize1[MAX_CLASS], classRecordSize2[MAX_CLASS];
/* static */ uint32 *image;
/* static */ uchar *jisx0201, *jisx0208;
/* static */ uchar *classesMap1, *classesMap2;
/* static */ int numClassRecords1, numClassRecords2;
/* static */ int globalTimerInterval = 0;
/* static */ int g_mainWinCX0 = 0;
/* static */ int g_mainWinCY0 = 0;
/* static */ int g_mainWinCX1 = g_mainWinWidth;
/* static */ int g_mainWinCY1 = g_mainWinHeight;
#ifdef QUICKBIND
/* static */ int32 postPaintMethodMapNum, postEventMethodMapNum;
#endif

#include "cons00.c"
#include "bpp24lib.c"
#if (defined(MONA) || defined(MONACUI) || defined(PEKOE) || defined(SDL) || defined(NWSOS))
#include "bim2bin.c"
#endif

/* static */ int Hashtable_put(WObject key, uint32 *object) {
/* Hashtable�ɃL�[��ݒ肷�� */
	int i;
	for (i = 0; i < HASHTABLE_SIZE; i++) {
		if (Hashtable_keys[i] == 0) {
			Hashtable_keys[i] = key;
			Hashtable_elements[i] = (uint32)(&object[0]);
			printf("Hashtable_put(%d)\n", key);
			return 1;
		}
	}
	printf("Hashtable_put fault\n");
	return 0;
}

/* static */ int Hashtable_remove(WObject key) {
/* Hashtable����I�u�W�F�N�g���폜���� */
	int i;
	uint32 *list;
	for (i = 0; i < HASHTABLE_SIZE; i++) {
		if (Hashtable_keys[i] == key) {
			Hashtable_keys[i] = 0;
			list = (uint32 *)Hashtable_elements[i];
			xfree(list);
			Hashtable_elements[i] = 0;
			printf("Hashtable_remove(%d)\n", key);
			return 1;
		}
	}
	printf("Hashtable_remove fault\n");
	return 0;
}

/* static */ int Hashtable_get(WObject key, uint32 **object) {
/* Hashtable����I�u�W�F�N�g�𓾂� */
	int i;
	for (i = 0; i < HASHTABLE_SIZE; i++) {
		if (Hashtable_keys[i] == key) {
			*object = (uint32 *)Hashtable_elements[i];
			//printf("Hashtable_get(%d)\n", key);
			return 1;
		}
	}
	*object = NULL;
	printf("Hashtable_get fault\n");
	return 0;
}

/* static */ void processEvent(int* vlist) {
/* �C�x���g���������� */
	WClass *vclass;
	Var param5[5], param7[7];
	WClassMethod *method_paint, *method_event;

#ifdef QUICKBIND
	// ���\�b�h�Ăяo��������
	vclass = (WClass *)WOBJ_class(mainWinObj);
	method_paint = getMethodByMapNum(vclass, &vclass, (uint16)postPaintMethodMapNum);
	method_event = getMethodByMapNum(vclass, &vclass, (uint16)postEventMethodMapNum);
	if (method_paint == NULL || method_event == NULL) {
		waba_exit(0);
		return;
	}
#else
	vclass = (WClass *)WOBJ_class(mainWinObj);
	method_paint = getMethod(vclass, createUtfString("_doPaint"), createUtfString("(IIII)V"), &vclass);
	method_event = getMethod(vclass, createUtfString("_postEvent"), createUtfString("(IIIIII)V"), &vclass);
	if (method_paint == NULL || method_event == NULL) {
		waba_exit(0);
		return;
	}
#endif

	//if (vlist[0] == 303) {
	//	param1[0].obj = mainWinObj;
	//	executeMethod(vclass, method_timer, param1, 1);
	//	printf("_onTimerTick(%d)\n", globalTimerInterval);
	if (vlist[0] == 0) {
		param5[0].obj = mainWinObj;
		param5[1].intValue = vlist[1]; // x
		param5[2].intValue = vlist[2]; // y
		param5[3].intValue = vlist[3]; // w
		param5[4].intValue = vlist[4]; // h
		executeMethod(vclass, method_paint, param5, 5);
	} else if (vlist[0] == 200 || vlist[0] == 201 || vlist[0] == 202) {
		// �͈̓`�F�b�N
		if (0 <= vlist[2] && vlist[2] < g_mainWinOffX + g_mainWinWidth && 
			0 <= vlist[3] && vlist[3] < g_mainWinOffY + g_mainWinHeight) {
			param7[0].obj = mainWinObj;
			param7[1].intValue = vlist[0]; // type
			param7[2].intValue = vlist[1]; // key
			param7[3].intValue = vlist[2]; // x
			param7[4].intValue = vlist[3]; // y
			param7[5].intValue = vlist[4]; // modifiers
			param7[6].intValue = vlist[5]; // timeStamp
			executeMethod(vclass, method_event, param7, 7);
		}
	} else {
		param7[0].obj = mainWinObj;
		param7[1].intValue = vlist[0]; // type
		param7[2].intValue = vlist[1]; // key
		param7[3].intValue = vlist[2]; // x
		param7[4].intValue = vlist[3]; // y
		param7[5].intValue = vlist[4]; // modifiers
		param7[6].intValue = vlist[5]; // timeStamp
		executeMethod(vclass, method_event, param7, 7);
	}
}

//#ifdef WIN32
//#ifndef WINCE
/* static */ void dumpStackTrace()
	{
	WClass *wclass;
	WClassMethod *method;
	UtfString className, methodName, methodDesc;
	uint32 i, n, stackPtr;

	if (vmStackPtr == 0)
		return;
	//AllocConsole();
//#ifdef DUMPERRORTRACE
	{
	char *msg;

	msg = errorMessages[vmStatus.errNum - 1];
	if (msg)
		printf("ERROR - %s\n", msg);
	printf("ERROR arg1: %s\n", vmStatus.arg1);
	printf("ERROR arg2: %s\n", vmStatus.arg2);
	}
//#endif
	stackPtr = vmStackPtr;
	while (stackPtr != 0)
		{
		wclass = (WClass *)vmStack[--stackPtr].refValue;
		method = (WClassMethod *)vmStack[--stackPtr].refValue;
		className = getUtfString(wclass, wclass->classNameIndex);
		methodName = getUtfString(wclass, METH_nameIndex(method));
		methodDesc = getUtfString(wclass, METH_descIndex(method));

		for (i = 0; i < className.len; i++)
			printf("%c", className.str[i]);
		printf(".");
		for (i = 0; i < methodName.len; i++)
			printf("%c", methodName.str[i]);
		for (i = 0; i < methodDesc.len; i++)
			printf("%c", methodDesc.str[i]);
		printf("\n");

		if ((METH_accessFlags(method) & ACCESS_NATIVE) > 0)
			stackPtr -= vmStack[--stackPtr].intValue;
		else
			{
			n = METH_maxLocals(method) + METH_maxStack(method);
			for (i = 0; i < n; i++)
				printf("%d:%d ", i, vmStack[--stackPtr].intValue);
			printf("\n");
			}
		stackPtr -= 3;
		}
	}
//#endif
//#endif

/* static */ void loadWrpWarpFile(char* filename) {
/* WRP�t�@�C�����������[�ɓǂݍ��� */
#if defined(OSASK)
	int i, filesize1, filesize2;
	uchar *fp1, *fp2;
	UtfString fontname1, fontname2;
	uint32 fontsize1 = 0, fontsize2 = 0;

	//
	// Waba Class Load
	//

	// �t�@�C���I�[�v��
	lib_initmodulehandle0(0x0008, 0x0220); /* user-dir�ɏ����� */
	lib_steppath0(0, 0x0220 /* slot */, "WABA    .LIB", 16 /* sig */);
	do {
		i = getsignalw();
	} while (i < 16 || 31 < i);
	if (i != 16){
		printf("base class read error(%d)\n", i);
		return;
	}else{
		//printf("base class open succeed\n");
		filesize1 = lib_readmodulesize(0x0220);
		printf("filesize=%d\n", filesize1);
	}

	// �N���X�}�b�v�p�̈�m��
	//classesMap1 = xmalloc(filesize1); // �������m��

	// �t�@�C���ǂݍ���
	fp1 = (char *) lib_readCSd(0x0010 /* mapping�̈�̎n�܂� */);
	lib_mapmodule(0x0000 /* opt */, 0x0220 /* slot */, 0x5 /* R-mode */, filesize1 /* map-window size */, fp1, 0);
	classesMap1 = fp1;
	numClassRecords1 = getUInt32(classesMap1+4);
	//printf("numClassRecords=%d\n", numClassRecords1);
	for ( i=0 ; i<numClassRecords1 ; i++ ) {
		classRecordOfs1[i] = getUInt32(classesMap1+8+4*i);
		classRecordSize1[i] = getUInt32(classesMap1+12+4*i)-classRecordOfs1[i];
		//printf("classRedordOfs=%d,Size=%d\n", classRecordOfs1[i], classRecordSize1[i]);
	}
	printf("base class read complete\n");

	//
	// User Font Load
	//

	fontname1 = createUtfString("jisx0201.fnt");
	fontname2 = createUtfString("jisx0208.fnt");
	if ((jisx0201 = nativeLoadClass(fontname1, &fontsize1)) != NULL) {
		printf("jis0201.fnt(%dbyte) opened.\n", fontsize1);
	} else {
		printf("cannot load jisx0201.fnt\n");
		waba_exit(0);
		return;
	}
	if ((jisx0208 = nativeLoadClass(fontname2, &fontsize2)) != NULL) {
		printf("jis0208.fnt(%dbyte) opened.\n", fontsize2);
	} else {
		printf("cannot load jisx0208.fnt\n");
		//waba_exit(0);
		//return;
	}

	//
	// User Class Load
	//

	// �N���X�}�b�v�p�̈�m��
	//classesMap2 = xmalloc(filesize2); // �������m��

	// �t�@�C���I�[�v��
	lib_initmodulehandle1(0x0230 /* slot */, 1 /* num */, 16 /* sig */);
	//lib_initmodulehandle0(0x0008, 0x0230); /* user-dir�ɏ����� */
	//lib_steppath0(0, 0x0230 /* slot */, "HELLO   .WRP", 16 /* sig */);
	do {
		i = getsignalw();
	} while (i < 16 || 31 < i);
	if (i != 16){
		printf("main class read error(%d)\n", i);
		waba_exit(0);
		return;
	}else{
		//printf("main class open succeed\n");
		filesize2 = lib_readmodulesize(0x0230);
		printf("filesize=%d\n", filesize2);
	}

	// �t�@�C���ǂݍ���
	//fp2 = (char *) lib_readCSd(0x0010 + filesize /* mapping�̈�̎n�܂� */);
	fp2 = fp1 + ((filesize1 + 0xfff) & ~0xfff); // K�^���w�E [OSASK 6479]
	lib_mapmodule(0x0000 /* opt */, 0x0230 /* slot */, 0x5 /* R-mode */, filesize2 /* map-window size */, fp2, 0);
	classesMap2 = fp2;
	numClassRecords2 = getUInt32(classesMap2+4);
	//printf("numClassRecords2=%d\n", numClassRecords2);
	for ( i=0 ; i<numClassRecords2 ; i++ ) {
		classRecordOfs2[i] = getUInt32(classesMap2+8+4*i);
		classRecordSize2[i] = getUInt32(classesMap2+12+4*i)-classRecordOfs2[i];
		//printf("classRedordOfs2=%d,Size=%d\n", classRecordOfs2[i], classRecordSize2[i]);
	}
	printf("main class read complete\n");
#elif (defined(MONA) || defined(MONACUI))
	int i;
	dword filesize1 = 0, filesize2 = 0, readsize1 = 0, readsize2 = 0;
	uchar *fp1, *fp2;
	UtfString fontname1, fontname2;
	uint32 fontsize1 = 0, fontsize2 = 0;

	//
	// Waba Class Load
	//

	if(syscall_file_open("/APPS/WABA.LIB", 0, &filesize1) != 0){
		printf("%s\n", errorMessages[2]);
		waba_exit(0);
		return;
	}else{
		//printf("filesize=%dbyte.\n", filesize1);
		classesMap1 = (uchar*)xmalloc(filesize1 * 3);
		if(syscall_file_read((char*)classesMap1, filesize1, &readsize1) == 0){
			if (classesMap1[0] != 0x57) {
				// tek0 ��
				restore(classesMap1, &filesize1);
				fp1 = classesMap1;
				printf("tek0 -> wrp converted.\n");
			} else {
				fp1 = classesMap1;
			}
			numClassRecords1 = getUInt32(fp1+4);
			//printf("numClassRecords=%d\n", numClassRecords1);
			for (i = 0 ; i < numClassRecords1 ; i++) {
				classRecordOfs1[i] = getUInt32(fp1+8+4*i);
				classRecordSize1[i] = getUInt32(fp1+12+4*i)-classRecordOfs1[i];
			}
			printf("/APPS/WABA.LIB(%dbyte) opened.\n", filesize1);
		} else {
			waba_exit(0);
			return;
		}
		syscall_file_close();
	}

	//
	// User Font Load
	//

	fontname1 = createUtfString("jisx0201.fnt");
	fontname2 = createUtfString("jisx0208.fnt");
	if ((jisx0201 = nativeLoadClass(fontname1, &fontsize1)) != NULL) {
		printf("jis0201.fnt(%dbyte) opened.\n", fontsize1);
	} else {
		printf("cannot load jisx0201.fnt\n");
		waba_exit(0);
		return;
	}
	if ((jisx0208 = nativeLoadClass(fontname2, &fontsize2)) != NULL) {
		printf("jis0208.fnt(%dbyte) opened.\n", fontsize2);
	} else {
		printf("cannot load jisx0208.fnt\n");
		//waba_exit(0);
		//return;
	}

	//
	// User Class Load
	//

	if (filename == NULL) return;
	if(syscall_file_open(filename, 0, &filesize2) != 0){
		printf("%s\n", errorMessages[3]);
		waba_exit(0);
		return;
	}else{
		//printf("filesize=%dbyte.\n", filesize2);
		classesMap2 = (uchar*)xmalloc(filesize2 * 5);
		if(syscall_file_read((char*)classesMap2, filesize2, &readsize2) == 0){
			if (classesMap2[0] != 0x57) {
				// tek0 ��
				restore(classesMap2, &filesize2);
				fp2 = classesMap2;
				printf("tek0 -> wrp converted.\n");
			} else {
				fp2 = classesMap2;
			}
			numClassRecords2 = getUInt32(fp2+4);
			//printf("numClassRecords=%d\n", numClassRecords2);
			for (i = 0 ; i < numClassRecords2 ; i++) {
				classRecordOfs2[i] = getUInt32(fp2+8+4*i);
				classRecordSize2[i] = getUInt32(fp2+12+4*i)-classRecordOfs2[i];
			}
			printf("%s(%dbyte) opened.\n", filename, filesize2);
		} else {
			waba_exit(0);
			return;
		}
		syscall_file_close();
	}
#elif defined(PEKOE)
	int i;
	int file1, file2;
	uchar *fp1, *fp2;
	int filesize1 = 0, filesize2 = 0;
	int readsize1 = 0, readsize2 = 0;
	UtfString fontname1, fontname2;
	uint32 fontsize1 = 0, fontsize2 = 0;

	//
	// Waba Class Load
	//

	file1 = open("waba.lib", O_RDONLY, 0);
	if (file1 < 0) {
		printf("%s\n", errorMessages[2]);
		waba_exit(0);
		return;
	}
	filesize1 = lseek(file1, 0, 2);
	printf("filesize = %d\n", filesize1);
	lseek(file1, 0, 0); // �擪�ɖ߂�
	classesMap1 = (uchar*)xmalloc(filesize1 * 3);
	readsize1 = read(file1, (char*)classesMap1, filesize1);
	//printf("readsize = %d\n", readsize1);
	close(file1);
	if (classesMap1[0] != 0x57) {
		// tek0 ��
		restore(classesMap1, &filesize1);
		fp1 = classesMap1;
		printf("tek0 -> wrp converted.\n");
	} else {
		fp1 = classesMap1;
	}
	numClassRecords1 = getUInt32(fp1+4);
	//printf("numClassRecords=%d\n", numClassRecords1);
	for (i = 0 ; i < numClassRecords1 ; i++) {
		classRecordOfs1[i] = getUInt32(fp1+8+4*i);
		classRecordSize1[i] = getUInt32(fp1+12+4*i)-classRecordOfs1[i];
	}
	printf("base class read complete\n");

	//
	// User Font Load
	//

	fontname1 = createUtfString("jisx0201.fnt");
	fontname2 = createUtfString("jisx0208.fnt");
	if ((jisx0201 = nativeLoadClass(fontname1, &fontsize1)) != NULL) {
		printf("jis0201.fnt(%dbyte) opened.\n", fontsize1);
	} else {
		printf("cannot load jisx0201.fnt\n");
		waba_exit(0);
		return;
	}
	if ((jisx0208 = nativeLoadClass(fontname2, &fontsize2)) != NULL) {
		printf("jis0208.fnt(%dbyte) opened.\n", fontsize2);
	} else {
		printf("cannot load jisx0208.fnt\n");
		//waba_exit(0);
		//return;
	}

	//
	// User Class Load
	//

	if (filename == NULL) return;
	file2 = open(filename, O_RDONLY, 0);
	if (file2 < 0) {
		printf("%s\n", errorMessages[2]);
		waba_exit(0);
		return;
	}
	filesize2 = lseek(file2, 0, 2);
	printf("filesize = %d\n", filesize2);
	lseek(file2, 0, 0); // �擪�ɖ߂�
	classesMap2 = (uchar*)xmalloc(filesize2 * 5);
	readsize2 = read(file2, (char*)classesMap2, filesize2);
	//printf("readsize = %d\n", readsize2);
	close(file2);
	if (classesMap2[0] != 0x57) {
		// tek0 ��
		restore(classesMap2, &filesize2);
		fp2 = classesMap2;
		printf("tek0 -> wrp converted.\n");
	} else {
		fp2 = classesMap2;
	}
	numClassRecords2 = getUInt32(fp2+4);
	//printf("numClassRecords=%d\n", numClassRecords2);
	for (i = 0 ; i < numClassRecords2 ; i++) {
		classRecordOfs2[i] = getUInt32(fp2+8+4*i);
		classRecordSize2[i] = getUInt32(fp2+12+4*i)-classRecordOfs2[i];
	}
	printf("main class read complete\n");
#elif (defined(SDL) || defined(NWSOS))
	int i;
	FILE *file1, *file2;
	uchar *fp1, *fp2;
	int filesize1 = 0, filesize2 = 0;
	UtfString fontname1, fontname2;
	uint32 fontsize1 = 0, fontsize2 = 0;

	//
	// Waba Class Load
	//

	file1 = fopen("WABA.LIB", "rb");
	if (file1 == NULL) {
		printf("%s\n", errorMessages[2]);
		waba_exit(0);
		return;
	}
	fseek(file1, 0, SEEK_END);
	filesize1 = ftell(file1) + 1;
	if (filesize1 == 0) {
		printf("%s\n", errorMessages[2]);
		waba_exit(0);
		return;
	}
	rewind(file1);
	classesMap1 = (uchar*)xmalloc(filesize1 * 3);
	fread((uchar *)classesMap1, filesize1, 1, file1);
	fclose(file1);
	if (classesMap1[0] != 0x57) {
		// tek0 ��
		restore(classesMap1, &filesize1);
		fp1 = classesMap1;
		printf("tek0 -> wrp converted.\n");
	} else {
		fp1 = classesMap1;
	}
	numClassRecords1 = getUInt32(fp1+4);
	//printf("numClassRecords=%d\n", numClassRecords1);
	for (i = 0 ; i < numClassRecords1 ; i++) {
		classRecordOfs1[i] = getUInt32(fp1+8+4*i);
		classRecordSize1[i] = getUInt32(fp1+12+4*i)-classRecordOfs1[i];
	}
	printf("/APPS/WABA.LIB(%dbyte) opened.\n", filesize1);

	//
	// User Font Load
	//

	fontname1 = createUtfString("jisx0201.fnt");
	fontname2 = createUtfString("jisx0208.fnt");
	if ((jisx0201 = nativeLoadClass(fontname1, &fontsize1)) != NULL) {
		printf("jis0201.fnt(%dbyte) opened.\n", fontsize1);
	} else {
		printf("cannot load jisx0201.fnt\n");
		waba_exit(0);
		return;
	}
	if ((jisx0208 = nativeLoadClass(fontname2, &fontsize2)) != NULL) {
		printf("jis0208.fnt(%dbyte) opened.\n", fontsize2);
	} else {
		printf("cannot load jisx0208.fnt\n");
		//waba_exit(0);
		//return;
	}

	//
	// User Class Load
	//

	if (filename == NULL) return;
	file2 = fopen(filename, "rb");
	if (file2 == NULL) {
		printf("%s\n", errorMessages[3]);
		waba_exit(0);
		return;
	}
	fseek(file2, 0, SEEK_END);
	filesize2 = ftell(file2) + 1;
	if (filesize2 == 0) {
		printf("%s\n", errorMessages[3]);
		waba_exit(0);
		return;
	}
	rewind(file2);
	classesMap2 = (uchar*)xmalloc(filesize2 * 5);
	fread((uchar *)classesMap2, filesize2, 1, file2);
	fclose(file2);
	if (classesMap2[0] != 0x57) {
		// tek0 ��
		restore(classesMap2, &filesize2);
		fp2 = classesMap2;
		printf("tek0 -> wrp converted.\n");
	} else {
		fp2 = classesMap2;
	}
	numClassRecords2 = getUInt32(fp2+4);
	//printf("numClassRecords=%d\n", numClassRecords2);
	for (i = 0 ; i < numClassRecords2 ; i++) {
		classRecordOfs2[i] = getUInt32(fp2+8+4*i);
		classRecordSize2[i] = getUInt32(fp2+12+4*i)-classRecordOfs2[i];
	}
	printf("%s(%dbyte) opened.\n", filename, filesize2);
#endif
}

/* static */ uchar *nativeLoadClass(UtfString className, uint32 *size) {
/* WRP�t�@�C�����̃��\�[�X���擾���� */
	int i, nameLen;
	uchar *fp1, *fp2;

	fp1 = classesMap1;
	for (i = 0; i < numClassRecords1; i++) {
		if ( xstrncmp(className.str, (char *)(fp1+classRecordOfs1[i]+2), className.len) == 0 ) {
			//printf("%s found\n", className.str);
			nameLen = getUInt16(fp1+classRecordOfs1[i]);
			if (size != NULL)
				*size = classRecordSize1[i]-nameLen-2;
			return (fp1+classRecordOfs1[i]+2+nameLen);
		}
	}

	fp2 = classesMap2;
	for (i = 0; i < numClassRecords2; i++) {
		if (xstrncmp (className.str, (char *)(fp2+classRecordOfs2[i]+2), className.len) == 0 ) {
			//printf("%s found\n", className.str);
			nameLen = getUInt16(fp2+classRecordOfs2[i]);
			if (size != NULL)
				*size = classRecordSize2[i]-nameLen-2;
			return (fp2+classRecordOfs2[i]+2+nameLen);
		}
	}

	return NULL;
}

/* static */ void stopApp(WObject mainWinObj) {
/* VM ���s��~ */
	VmStopApp(mainWinObj);
	VmFree();
}

/* static */ WObject startApp(char* filename) {
/* VM ���s�J�n */
	//unsigned long vmStackSize, nmStackSize, classHeapSize, objectHeapSize;
	uint32 objectHeapSize;
	WClass *vclass;
	int vlist[6];
	
	// �ϐ�������
	//vmStackSize = 1500;
	//nmStackSize = 300;
	//classHeapSize = 14000;
	//objectHeapSize = 8000;
	vmStackSize = 15000;
	nmStackSize = 3000;
	classHeapSize = 140000;
	objectHeapSize = 80000;
#ifdef QUICKBIND
	postPaintMethodMapNum = -1;
	postEventMethodMapNum = -1;
#endif
	image = (uint32 *)xmalloc(sizeof(int) * g_mainWinWidth * g_mainWinHeight);
#if defined(NWSOS)
	bitmap = (BYTE *)xmalloc(g_mainWinWidth * g_mainWinHeight * 3);
#endif

	// �N�����b�Z�[�W
	printf("Waba for %s %s\n", VM_OS, WABA_VERSION);
	printf("mainWinWidth %d\n", g_mainWinWidth);
	printf("mainWinHeight %d\n", g_mainWinHeight);
	printf("vmStackSize %d\n", (int)vmStackSize);
	printf("nmStackSize %d\n", (int)nmStackSize);
	printf("classHeapSize %d\n", (int)classHeapSize);
	printf("objectHeapSize %d\n", (int)objectHeapSize);
	printf("className #Main#\n");

	// �N���X�t�@�C���ǂݏo��
	loadWrpWarpFile(filename);

	// VM������
	VmInit(vmStackSize, nmStackSize, classHeapSize, objectHeapSize);

	// VM���s�J�n
	if (filename != NULL) {
		mainWinObj =  VmStartApp("Main");
	} else {
		mainWinObj =  VmStartApp("waba/ui/Welcome");
	}
	if(!mainWinObj){
		stopApp(mainWinObj);
		waba_exit(0);
		return 0;
	}else{
		vclass = (WClass *)WOBJ_class(mainWinObj);
	}

#ifdef QUICKBIND
	// ���\�b�h�Ăяo��������
	postPaintMethodMapNum = getMethodMapNum(vclass, createUtfString("_doPaint"), 
		createUtfString("(IIII)V"), SEARCH_ALL);
	postEventMethodMapNum = getMethodMapNum(vclass, createUtfString("_postEvent"),
		createUtfString("(IIIIII)V"), SEARCH_ALL);
	if (postPaintMethodMapNum == -1 || postEventMethodMapNum == -1) {
		waba_exit(0);
		return 0;
	}
#endif

	// �`��J�n
	vlist[0] = 0;
	vlist[1] = 0;
	vlist[2] = 0;
	vlist[3] = g_mainWinWidth;
	vlist[4] = g_mainWinHeight;
	vlist[5] = 0;
	processEvent(vlist);

	// �_�~�[�C�x���g����
	vlist[0] = 200; // type
	vlist[1] = 0;   // key
	vlist[2] = 0;   // x
	vlist[3] = 0;   // y
	vlist[4] = 0;   // modifiers
	vlist[5] = 0;   // timeStamp
	processEvent(vlist);

	return mainWinObj;
}
