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

#ifndef __FONTMETRICS_H__
#define __FONTMETRICS_H__

#define inGetUInt16(b) (unsigned short)( (unsigned short)((b)[1])<<8 | (unsigned short)((b)[0]) )
#define inGetUInt32(b) (dword)( (dword)((b)[3])<<24 | (dword)((b)[2])<<16 | (dword)((b)[1])<<8 | (dword)((b)[0]) )

#include "BDFParser.h"
namespace baygui {
    /**
     �t�H���g���N���X
     */
    class FontMetrics : public Object
    {
    private:
        /** �t�H���g�I�t�Z�b�g���X�g���� */
        static int offsetListLength;
        /** �t�H���g�I�t�Z�b�g���X�g */
        static int* offsetList;
        /** �t�H���g�f�[�^ */
        static unsigned char* defaultFontData;
        /** �t�H���g�X�^�C�� */
        int fontStyle;

    public:
        /** �R���X�g���N�^ */
        FontMetrics();

        /** �f�X�g���N�^ */
        virtual ~FontMetrics();

        FontImage getFixedFont(ucs4char c);

        /**
         UCS-4�R�[�h���󂯎���ēW�J�ςݕ����f�[�^��Ԃ�
         @param ucs4 UCS-4�R�[�h�i4�o�C�g�j
         @param offset [out] �σt�H���g�ł� offset = width�A�Œ�t�H���g�ł� offset > width
         @param width [out] �����̕�
         @param height [out] �����̍���
         @param data [out] �W�J�ςݕ����f�[�^
        */
        bool decodeCharacter(wchar ucs4, int* offset, int* width, int* height, char* data);

        /**
         ������̕��𓾂�
         @param str ������i�����s�Ή��j
         */
        int getWidth(const String& str);
        int getWidthChar(unsigned int ch);

        /**
         ������̍����𓾂�
         @param str ������i�����s�Ή��j
         */
        int getHeight(const String& str);

        /** �t�H���g�X�^�C���𓾂� */
        inline int getFontStyle() { return this->fontStyle; }

        /** �t�H���g�X�^�C����ݒ肷�� */
        inline void setFontStyle(int style) { this->fontStyle = style; }
    };
}

#endif // __FONTMETRICS_H__
