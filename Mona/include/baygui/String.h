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

#if !defined(_STRING_H_INCLUDED_)
#define _STRING_H_INCLUDED_

typedef unsigned int wchar;

/**
 �����񃉃b�p�[�N���X.
 �����`����UCS-4 (4�o�C�g) �ŕێ�����B
 */
class String : public Object
{
private:
	/** ���������� */
	char* charArray;
	/** ���C�h������ (UCS-4) */
	wchar* wcharArray;
	/** ���C�h������̒��� */
	int wlen;
	
private:
	/** �������ݒ肷�� */
	String& set(const char* s);

	/** ���l��ݒ肷�� */
	String& set(const int n);

public:
	/** �R���X�g���N�^ */
	inline String() : charArray(0), wlen(0) {}
	
	/**
	 �R���X�g���N�^
	 @param s ������ (UTF-8)
	*/
	inline String(const char* s) : charArray(0), wlen(0) { set(s); }
	
	/**
	 �R���X�g���N�^
	 @param n ���l
	*/
	inline String(int n) : charArray(0), wlen(0) { set(n); }
	
	/** �f�X�g���N�^ */
	inline ~String(){ delete[] charArray; delete[] wcharArray; }
	
	/** ���C�h��������Ԃ� (wstrlen����) */
	inline int length() const { return wlen; }
	
	/** ���������� (char�z��) ��Ԃ� */
	inline char* getBytes() const { return charArray; }
	
	/** ���C�h�������Ԃ� */
	inline wchar* toCharArray() const { return wcharArray; }
	
	/** i�Ԗڂ̃��C�h�����𓾂� */
	inline wchar operator[](int i) const { return wcharArray[i]; }
	
	/**
	 "="���Z�q�̑��d��`.
	 String s = "hoge"; �̂悤�Ɏg�����Ƃ��ł���B
	*/
	inline const String& operator=(const char* s){ set(s); return *this; }
	
	/**
	 �w�肳�ꂽ������Ɠ��������ǂ����`�F�b�N����
	 */
	inline bool equals(const char *s)
	{
		if (s == NULL) return false;
		if (strcmp(charArray, s) == 0) {
			return true;
		} else {
			return false;
		}
	}
	
	/**
	 �w�肳�ꂽ������Ŏn�܂邩�ǂ����`�F�b�N����
	 @param s ������
	 @return �n�܂��Ă����true�A�����łȂ����false
	*/
	inline bool startsWith(const char* s)
	{
		if (s == 0 || wlen == 0 || (int)strlen(s) > (int)strlen(charArray)) return false;
		for (int i = 0; i < (int)strlen(s); i++) {
			if (s[i] != charArray[i]) return false;
		}
		return true;
	}
	
	/**
	 �w�肳�ꂽ������ŏI���Ă��邩�ǂ����`�F�b�N����
	 @param s ������
	 @return �I���Ă����true�A�����łȂ����false
	*/
	inline bool endsWith(const char*s)
	{
		if (s == 0 || wlen == 0 || (int)strlen(s) > (int)strlen(charArray)) return false;
		for (int i = 0; i < (int)strlen(s); i++) {
			if (s[(int)strlen(s) - i - 1] != 
				charArray[(int)strlen(charArray) - i - 1]) return false;
		}
		return true;
	}
};

#endif // _STRING_H_INCLUDED_
