/*
Copyright (c) 2004 Tino, bayside
All rights reserved.

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

#ifndef __FONTMETRICS_H__
#define __FONTMETRICS_H__

/**
 �t�H���g���N���X
 */
class FontMetrics : public Object
{
private:
	/** �t�H���g�I�t�Z�b�g���X�g���� */
	static int offsetListLength;
	/** �t�H���g�I�t�Z�b�g���X�g */
	static int *offsetList;
	/** �t�H���g�f�[�^ */
	static unsigned char *defaultFontData;
	/** �t�H���g�X�^�C�� */
	int fontStyle;

public:
	/** �R���X�g���N�^ */
	FontMetrics();
	
	/** �f�X�g���N�^ */
	virtual ~FontMetrics();
	
	/**
	 UCS-4�R�[�h���󂯎���ēW�J�ςݕ����f�[�^��Ԃ�
	 @param ucs4 UCS-4�R�[�h�i4�o�C�g�j
	 @param offset [out] �σt�H���g�ł� offset = width�A�Œ�t�H���g�ł� offset > width
	 @param width [out] �����̕�
	 @param height [out] �����̍���
	 @param data [out] �W�J�ςݕ����f�[�^
	*/
	bool decodeCharacter(wchar ucs4, int *offset, int *width, int *height, char *data);
	
	/**
	 ������̕��𓾂�
	 @param str ������i�����s�Ή��j
	 */
	int getWidth(String str);
	
	/**
	 ������̍����𓾂�
	 @param str ������i�����s�Ή��j
	 */
	int getHeight(String str);
	
	/** �t�H���g�X�^�C���𓾂� */
	inline int getFontStyle() { return this->fontStyle; }
	
	/** �t�H���g�X�^�C����ݒ肷�� */
	inline void setFontStyle(int style) { this->fontStyle = style; }
};

#endif // __FONTMETRICS_H__
