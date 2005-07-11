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

#if !defined(_VECTOR_H_INCLUDED_)
#define _VECTOR_H_INCLUDED_

namespace baygui {
	/** �I�u�W�F�N�g�̉ϒ��z����i�[�ł���N���X */
	class Vector : public Object {
	protected:
		/** �f�t�H���g�e�� */
		static const int defaultCapacity = 5;
		/** �v�f�ꗗ */
		Object** elementList;
		/** �v�f�� */
		int _size;
		/** ���݂̗e�� */
		int _capacity;

	private:
		/** ������ */
		void initialize();

	public:
		/** �R���X�g���N�^ */
		Vector();
		
		/** �f�X�g���N�^ */
		virtual ~Vector();
		
		/** �v�f��ǉ����� */
		void add(Object* item);
		
		/**
		 �v�f���͂��߂ďo�����鏇�Ԃ𓾂�
		 @return ��x���o�����Ȃ������ꍇ��-1
		*/
		int indexOf(Object* item);
		
		/** �w�肵�����Ԃ̗v�f���폜���� */
		Object* remove(int index);
		
		/** �w�肵���v�f���폜���� */
		void remove(Object* item);
		
		/** ���ׂĂ̗v�f���폜���� */
		void removeAll();
		
		/** �v�f�ꗗ�𓾂� */
		inline Object** elements() { return this->elementList; }
		
		/** �w�肵�����Ԃ̗v�f�𓾂� */
		inline Object* get(int index) { return (index < 0) ? NULL : this->elementList[index]; }
		
		/** �v�f���𓾂� */
		inline int size() { return this->_size; }
		
		/** ���݂̗e�ʂ𓾂� */
		inline int capacity() { return this->_capacity; }
	};
}

#endif // _VECTOR_H_INCLUDED_
