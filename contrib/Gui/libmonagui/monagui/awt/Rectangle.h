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

#if !defined(_RECTANGLE_H_INCLUDED_)
#define _RECTANGLE_H_INCLUDED_

#include <algorithm>

namespace monagui {
    /**
     ��`�N���X
    */
    class Rectangle : public Object {
    public:
        /** x�i��΍��W�j*/
        int x;
        /** y�i��΍��W�j*/
        int y;
        /** ���� */
        int height;
        /** �� */
        int width;

    public:
        /** �f�t�H���g�R���X�g���N�^ */
        Rectangle() {
            this->x = this->y = this->width = this->height = 0;
        }

        /** �R���X�g���N�^ */
        Rectangle(int x, int y, int w, int h)
        {
            this->x = x;
            this->y = y;
            this->width = w;
            this->height = h;
        }

        /** �f�X�g���N�^ */
        virtual ~Rectangle() {}

        Rectangle createUnion(const Rectangle& r)
        {
            int nx = std::min(x, r.x);
            int ny = std::min(y, r.y);
            int nx_max = std::max(x + width, r.x + r.width);
            int ny_max = std::max(y + height, r.y + r.height);
            return Rectangle(nx, ny, nx_max - nx, ny_max - ny);
        }

        bool isEmpty() const {
            return width == 0 && height == 0;
        }

        /** �ʒu�Ƒ傫����ݒ肷�� */
        inline void setBounds(int x, int y, int w, int h)
        {
            setLocation(x, y);
            setSize(w, h);
        }

        /** �ʒu��ݒ肷�� */
        inline void setLocation(int x, int y) { this->x = x; this->y = y; }

        /** �傫����ݒ肷�� */
        inline void setSize(int w, int h) { this->width = w; this->height = h; }
    };
}

#endif // _RECTANGLE_H_INCLUDED_
