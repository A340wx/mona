/*
Copyright (c) 2004 bayside
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. The name of the author may not be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
