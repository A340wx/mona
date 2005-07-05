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
	void initialize()
	{
		//logprintf("%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__);
		this->elementList = new Object*[defaultCapacity];
		this->_size = 0;
		this->_capacity = defaultCapacity;
	}

public:
	/** �R���X�g���N�^ */
	Vector()
	{
		//logprintf("%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__);
		this->initialize();
	}
	
	/** �f�X�g���N�^ */
	virtual ~Vector()
	{
		//logprintf("%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__);
		delete [] this->elementList;
	}
	
	/** �v�f��ǉ����� */
	void add(Object* item)
	{
		//logprintf("%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__);
		if (this->_size == this->_capacity) {
			// ����Ȃ��Ȃ�����e�ʂ�{�ɑ��₷
			this->_capacity <<= 1;
			Object** ptr = new Object*[this->_capacity];
			for (int i = 0; i < this->_size; i++) ptr[i] = this->elementList[i];
			delete [] this->elementList;
			this->elementList = ptr;
		}
		this->elementList[this->_size] = item;
		this->_size++;
	}
	
	/**
	 �v�f���͂��߂ďo�����鏇�Ԃ𓾂�
	 @return ��x���o�����Ȃ������ꍇ��-1
	*/
	int indexOf(Object* item)
	{
		//logprintf("%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__);
		for (int i = 0; i < this->_size; i++) {
			if (this->elementList[i]->equals(item)) return i;
		}
		return -1;
	}
	
	/** �w�肵�����Ԃ̗v�f���폜���� */
	Object* remove(int index)
	{
		//logprintf("%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__);
		if (index < 0) return NULL;
		this->_size--;
		Object* obj = this->elementList[index];
		for (int i = index; i < this->_size; i++) {
			this->elementList[i] = this->elementList[i + 1];
		}
		return obj;
		//this->elementList[this->_size] = new Object();
	}
	
	/** �w�肵���v�f���폜���� */
	void remove(Object* item)
	{
		//logprintf("%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__);
		int index = this->indexOf(item);
		if (index < 0) return;
		this->remove(index);
	}
	
	/** ���ׂĂ̗v�f���폜���� */
	void removeAll()
	{
		//logprintf("%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__);
		delete [] this->elementList;
		this->initialize();
	}
	
	/** �v�f�ꗗ�𓾂� */
	Object** elements()
	{
		//logprintf("%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__);
		return this->elementList;
	}
	
	/** �w�肵�����Ԃ̗v�f�𓾂� */
	Object* get(int index)
	{
		//logprintf("%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__);
		if (index < 0) return NULL;
		return this->elementList[index];
	}
	
	/** �v�f���𓾂� */
	int size()
	{
		//logprintf("%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__);
		return this->_size;
	}
	
	/** ���݂̗e�ʂ𓾂� */
	int capacity()
	{
		//logprintf("%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__);
		return this->_capacity;
	}
};

#endif // _VECTOR_H_INCLUDED_
