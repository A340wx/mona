/*
Copyright (c) 2005 bayside

Permission is hereby granted, free of charge, to any person 
obtaining a copy of this software and associated documentation files 
(the "Software"), to deal in the Software without restriction, 
including without limitation the rights to use, copy, modify, merge, 
publish, distribute, sublicense, and/or sell copies of the Software, 
and to permit persons to whom the Software is furnished to do so, 
subject to the following conditions:

The above copyright notice and this permission notice shall be 
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY 
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

package java.awt;

import org.monaos.*;

/**
 �摜�N���X
 */
public class Image {
	private static final int THREAD_UNKNOWN = 0xffffffff;
	private static final int MSG_GUISERVER_DECODEIMAGE   = 0x4001;
	private static final int MSG_GUISERVER_CREATEBITMAP  = 0x4007;
	private static final int MSG_GUISERVER_DISPOSEBITMAP = 0x4008;
	
	/** �� */
	private int width;
	/** ���� */
	private int height;
	
	/** �R���X�g���N�^ */
	public Image(int width, int height) {
		this.width = this.height = 0;
		//this.bitmap = null; // TODO
		
		// GUI�T�[�o�[��T��
		int guisvrID = Message.getServerThreadId(Message.ID_GUI_SERVER);
		if (guisvrID == 0xffffffff) {
			System.out.print("ERROR: can not connect to GUI server!\n");
			System.exit(1);
		}
		
		// GUI�T�[�o�[��Ƀr�b�g�}�b�v�𐶐�����
		MessageInfo msg = new MessageInfo();
		if (Message.sendReceive(msg, guisvrID, MSG_GUISERVER_CREATEBITMAP, width, height, Color.lightGray) == 1)
		{
			System.out.print("ERROR: can not connect to GUI server!\n");
			return;
		}
		if (msg.arg2 == 0) return;

		// TODO
		// GUI�T�[�o�[��̃r�b�g�}�b�v�I�u�W�F�N�g�𐶐�����
		//this.bitmap = (guiserver_bitmap*)MonAPI::MemoryMap::map(msg.arg2);
		//if (this.bitmap == null)
		//{
		//	System.out.print("%s:%d:ERROR: can not get image data!\n");
		//	return;
		//}
		
		this.width = width;
		this.height = height;
	}

	/** �R���X�g���N�^ */
	public Image(String path) {
		this.width = this.height = 0;
		//this.bitmap = null;
		
		// GUI�T�[�o�[��T��
		int guisvrID = Message.getServerThreadId(Message.ID_GUI_SERVER);
		if (guisvrID == THREAD_UNKNOWN) {
			System.out.print("%s:%d:ERROR: can not connect to GUI server!\n");
			System.exit(1);
		}
		
		// GUI�T�[�o�[��Ńr�b�g�}�b�v���f�R�[�h����
		MessageInfo msg = new MessageInfo();
		if (Message.sendReceive(msg, guisvrID, MSG_GUISERVER_DECODEIMAGE, 0, 0, 0/*, path.getBytes()*/) == 1) {
			System.out.print("%s:%d:ERROR: can not connect to GUI server!\n");
			return;
		}
		if (msg.arg2 == 0) return;
		
		// TODO
		// GUI�T�[�o�[��̃r�b�g�}�b�v�I�u�W�F�N�g�𐶐�����
		//this.bitmap = (guiserver_bitmap*)MonAPI::MemoryMap::map(msg.arg2);
		//if (this.bitmap == null)
		//{
		//	System.out.print("%s:%d:ERROR: can not get image data!\n");
		//	return;
		//}
		
		this.width = 0;//this.bitmap->Width;
		this.height = 0;//this.bitmap->Height;
	}

	/** �摜��j������ */
	public void flush() {
		// GUI�T�[�o�[��T��
		int guisvrID = Message.getServerThreadId(Message.ID_GUI_SERVER);
		if (guisvrID == THREAD_UNKNOWN) {
			System.out.print("%s:%d:ERROR: can not connect to GUI server!\n");
			System.exit(1);
		}
		
		// �r�b�g�}�b�v�j���v��
		if (Message.send(guisvrID, MSG_GUISERVER_DISPOSEBITMAP, 0/*getHandle()*/, 0, 0) == 1) {
			System.out.print("%s:%d:ERROR: can not connect to GUI server!\n");
		}
	}

	/** ���𓾂� */
	public int getWidth() {
		return this.width;
	}

	/** �����𓾂� */
	public int getHeight() {
		return this.height;
	}

	/** �_�𓾂� */
	public int getPixel(int x, int y) {
		if (x < 0 || this.width <= x || y < 0 || this.height <= y) {
			return 0;
		} else {
			return 0;//this.bitmap->Data[x + this.width * y]; // TODO
		}
	}

	/** �_��ł� */
	public void setPixel(int x, int y, int color) {
		if (0 <= x && x < this.width && 0 <= y && y < this.height) {
			//this.bitmap->Data[x + this.width * y] = color; // TODO
		}
	}
}
