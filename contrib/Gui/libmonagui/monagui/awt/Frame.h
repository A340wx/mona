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

#if !defined(_FRAME_H_INCLUDED_)
#define _FRAME_H_INCLUDED_

namespace monagui {
    /**
     �t���[���N���X
    */
    class Frame : public Window {
    protected:
        /** �^�C�g�� */
        String title;

    protected:

        virtual void drawCloseButton(Graphics* g);

        /** ����{�^�����N���b�N���ꂽ���ǂ��� */
        virtual bool getCloseButtonClicked(int px, int py)
        {
            return (4 <= px && px < 17 && 4 <= py && py < 17) ? true : false;
        }

        /** �^�C�g���o�[���N���b�N���ꂽ���ǂ��� */
        virtual bool getTitlebarClicked(int px, int py)
        {
            return (0 <= px && px < getWidth() && 0 <= py && py < getInsets()->top);
        }

        Graphics* getFrameGrapics() const
        {
            return __g;
        }

    public:
        /** �f�t�H���g�R���X�g���N�^ */
        Frame();

        /**
         * �R�s�[�R���X�g���N�^
         * @param title �^�C�g��
        */
        Frame(const String& title);

        /** �f�X�g���N�^ */
        virtual ~Frame();

        /** �^�C�g���𓾂� */
        inline const char* getTitle() { return this->title.getBytes(); }

        /**
         �^�C�g���ݒ�
         @param title �^�C�g��
         */
        virtual void setTitle(const String& title);

        /** �ĕ`�� */
        virtual void repaint();
    };
}

#endif // _FRAME_H_INCLUDED_
