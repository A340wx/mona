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

#if !defined(_HASHTABLE_H_INCLUDED_)
#define _HASHTABLE_H_INCLUDED_

/** �L�[�ƒl�̃y�A���i�[�ł���N���X */
class Hashtable : public Object {
private:
	/** �L�[�ꗗ */
	Vector keyList;
	/** �l�ꗗ */
	Vector valueList;
	
public:
	/** �f�t�H���g�R���X�g���N�^ */
	Hashtable()
	{
		//logprintf("%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__);
		//this->keyList = new Vector();
		//this->valueList = new Vector();
	}
	
	/** �f�X�g���N�^ */
	virtual ~Hashtable()
	{
		//logprintf("%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__);
	}
	
	/** �n�b�V���e�[�u�����󂩂ǂ����𓾂� */
	bool isEmpty()
	{
		//logprintf("%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__);
		if (this->keyList.size() == 0) {
			return true;
		} else {
			return false;
		}
	}
	
	/** �L�[�ꗗ�𓾂� */
	Object** keys()
	{
		//logprintf("%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__);
		return this->keyList.elements();
	}
	
	/** �l�ꗗ�𓾂� */
	Object** elements()
	{
		//logprintf("%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__);
		return this->valueList.elements();
	}
	
	/**
	 �w�肵���L�[�ɑΉ�����l�𓾂�
	 @param key �L�[
	 @return �Ή�����l���Ȃ��Ƃ���NULL
	*/
	Object* get(Object* key)
	{
		//logprintf("%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__);
		if (key == NULL) return NULL;
		return this->valueList.get(this->keyList.indexOf(key));
	}
	
	/**
	 �L�[�ƒl�̑΂�ǉ�����
	 @param key �L�[
	 @param value �l
	*/
	void put(Object* key, Object* value)
	{
		//logprintf("%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__);
		if (key == NULL || value == NULL) return;
		int index = this->keyList.indexOf(key);
		if (index >= 0) {
			this->keyList.remove(index);
			this->valueList.remove(index);
		}
		this->keyList.add(key);
		this->valueList.add(value);
	}

	/** �w�肳�ꂽ�L�[���폜���� */
	void remove(Object* key)
	{
		//logprintf("%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__);
		if (key == NULL) return;
		int index = this->keyList.indexOf(key);
		this->keyList.remove(index);
		this->valueList.remove(index);
	}

	/** ���ׂĂ̗v�f���폜���� */
	void clear()
	{
		//logprintf("%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__);
		this->keyList.removeAll();
		this->valueList.removeAll();
	}
	
	/** �v�f���𓾂� */
	int size()
	{
		//logprintf("%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__);
		return this->keyList.size();
	}
};

#endif // _HASHTABLE_H_INCLUDED_
