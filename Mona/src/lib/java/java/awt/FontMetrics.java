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

/**
 �t�H���g���N���X
 */
public class FontMetrics {
	/** �t�H���g�I�t�Z�b�g���X�g���� */
	private static int offsetListLength;
	/** �t�H���g�I�t�Z�b�g���X�g */
	private static int[] offsetList;
	/** �t�H���g�f�[�^ */
	private static byte[] defaultFontData;
	/** �t�H���g�X�^�C�� */
	private int fontStyle;
	/** GUI�T�[�o�[ID */
	private int guisvrID;

	/** �R���X�g���N�^ */
	public FontMetrics() {
		this.fontStyle = Font.PLAIN;
		if (defaultFontData != null) return;
		
		/*// GUI�T�[�o�[��T��
		dword guisvrID = monapi_get_server_thread_id(ID_GUI_SERVER);
		if (this.guisvrID == THREAD_UNKNOWN) {
			System.out.print("%s:%d:ERROR: can not connect to GUI server!\n", __FILE__, __LINE__);
			System.exit(1);
		}
		// �t�H���g�擾���b�Z�[�W�𓊂���
		MessageInfo info;
		MonAPI.Message.sendReceive(&info, guisvrID, MSG_GUISERVER_GETFONT, 0, 0, 0, null);
		unsigned char* font_data = null;
		font_data = MonAPI.MemoryMap.map(info.arg2);
		if (font_data == null) {
			System.out.print("%s:%d:ERROR: can not get font!\n", __FILE__, __LINE__);
			System.exit(1);
		}
		defaultFontData = (unsigned char *)malloc(info.arg3);
		memcpy(defaultFontData, font_data, info.arg3);
		MonAPI.MemoryMap.unmap(info.arg2);
		
		// ���i�[�t�H���g�̍\��
		// 3 - 0 �t�H���g��
		// ? - 3 �t�H���g�\���� ( ? = �t�H���g�� )
		// 
		// �t�H���g�\����
		// 3 - 0 UCS-4 (UTF-16)
		//     4 �� (fw)
		//     5 ���� (fh)
		// ? - 6 �r�b�g�p�^�[�� ( ? = (fw * fh + 7) / 8 )
		
		offsetListLength = inGetUInt16(&defaultFontData[0]);
		
		// �����܂ł̃I�t�Z�b�g(byte)
		offsetList = (int *)malloc(65536 * sizeof(int));
		memset(offsetList, 0, 65536 * sizeof(int));
		
		// �I�t�Z�b�g���X�g�����
		int pos = 4;
		for (int i = 0; i < offsetListLength; i++) {
			offsetList[inGetUInt16(&defaultFontData[pos])] = pos;
			pos += 4;
			int fw = defaultFontData[pos++];
			int fh = defaultFontData[pos++];
			pos += (int)((fw * fh + 7) / 8);
		}*/
	}
	
	/**
	 UCS-4�R�[�h���󂯎���ēW�J�ςݕ����f�[�^��Ԃ�
	 @param ucs4 UCS-4�R�[�h�i4�o�C�g�j
	 @param offset [out] �σt�H���g�ł� offset = width�A�Œ�t�H���g�ł� offset > width
	 @param width [out] �����̕�
	 @param height [out] �����̍���
	 @param data [out] �W�J�ςݕ����f�[�^
	*/
	/*public boolean decodeCharacter(wchar ucs4, int* offset, int* width, int* height, char* data) {
		if (ucs4 <= 0xFFFF && defaultFontData != null && offsetList[ucs4] != 0) {
			int fw = defaultFontData[offsetList[ucs4] + 4];
			int fh = defaultFontData[offsetList[ucs4] + 5];
			//System.out.print("fontStyle = %d,", this.fontStyle);
			if ((this.fontStyle & 0x100) == Font.FIXED) {
				if (ucs4 < 128 || 0xff60 < ucs4) {
					*offset = 6;
				} else {
					*offset = 12;
				}
			} else {
				*offset = fw;
			}
			*width  = fw;
			*height = fh;
			memcpy(data, &defaultFontData[offsetList[ucs4] + 6], (int)((fw * fh + 7) / 8));
			return true;
		} else {
			return false;
		}
		return false;
	}*/
	
	/**
	 ������̕��𓾂�
	 @param str ������i�����s�Ή��j
	 */
	public int getWidth(String str) {
		/*// null�`�F�b�N
		if (str.length() == 0 || defaultFontData == null) return 0;
		
		int w = 0;
		for (int i = 0; i < str.length(); i++) {
			wchar c = str.charAt(i);
			if (c == '\n') {
				break;
			}
			if (c <= 0xFFFF) {
				if ((this.fontStyle & 0x100) == Font.FIXED) {
					if (c < 128 || 0xff60 < c) {
						w += 6;
					} else {
						w += 12;
					}
				} else {
					w += defaultFontData[offsetList[c] + 4];
				}
			}
		}
		
		return w;*/
		return 0;
	}
	
	/**
	 ������̍����𓾂�
	 @param str ������i�����s�Ή��j
	 */
	public int getHeight(String str) {
		/*int h = 12;
		for (int i = 0; i < str.length(); i++) {
			if (str.charAt(i) == '\n') {
				h += 12; // ���i�[�t�H���g�͍�����12�h�b�g
			}
		}
		
		return h;*/
		return 0;
	}
	
	/** �t�H���g�X�^�C���𓾂� */
	public int getFontStyle() { return this.fontStyle; }
	
	/** �t�H���g�X�^�C����ݒ肷�� */
	public void setFontStyle(int style) { this.fontStyle = style; }
}
