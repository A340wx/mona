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

#if !defined(_COLOR_H_INCLUDED_)
#define _COLOR_H_INCLUDED_

namespace monagui {
	/**
	 �F�\���́i�V�X�e���W��16�F�ɏ����j
	 */
	struct Color {
	public:
		/** ���F */
		static const int black     = 0xff000000;
		/** �Z�����F */
		static const int maroon    = 0xff800000;
		/** �Z���ΐF */
		static const int green     = 0xff008000;
		/** �Z�����F */
		static const int olive     = 0xff808000;
		/** �Z���F */
		static const int navy      = 0xff000080;
		/** ���F */
		static const int purple    = 0xff800080;
		/** �Â��F */
		static const int teal      = 0xff008080;
		/** ���邢�D�F */
		static const int lightGray = 0xffC0C0C0;
		/** �D�F */
		static const int gray      = 0xff808080;
		/** �ԐF */
		static const int red       = 0xffff0000;
		/** ���邢�ΐF */
		static const int lime      = 0xff00ff00;
		/** ���F */
		static const int yellow    = 0xffffff00;
		/** �F */
		static const int blue      = 0xff0000ff;
		/** ���邢�ԐF */
		static const int magenta   = 0xffff00ff;
		/** ���F */
		static const int cyan      = 0xff00ffff;
		/** ���F */
		static const int white     = 0xffffffff;
	};
}

#endif /* _COLOR_H_INCLUDED_ */
