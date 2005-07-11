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

namespace baygui {
	/** �L�[�ƒl�̃y�A���i�[�ł���N���X */
	class Hashtable : public Object {
	private:
		/** �L�[�ꗗ */
		Vector keyList;
		/** �l�ꗗ */
		Vector valueList;
		
	public:
		/** �f�t�H���g�R���X�g���N�^ */
		Hashtable();
		
		/** �f�X�g���N�^ */
		virtual ~Hashtable();
		
		/** �n�b�V���e�[�u�����󂩂ǂ����𓾂� */
		inline bool isEmpty() { return (this->keyList.size() == 0) ? true : false; }
		
		/** �L�[�ꗗ�𓾂� */
		inline Object** keys() { return this->keyList.elements(); }
		
		/** �l�ꗗ�𓾂� */
		inline Object** elements() { return this->valueList.elements(); }
		
		/**
		 �w�肵���L�[�ɑΉ�����l�𓾂�
		 @param key �L�[
		 @return �Ή�����l���Ȃ��Ƃ���NULL
		*/
		Object* get(Object* key);
		
		/**
		 �L�[�ƒl�̑΂�ǉ�����
		 @param key �L�[
		 @param value �l
		*/
		void put(Object* key, Object* value);

		/** �w�肳�ꂽ�L�[���폜���� */
		void remove(Object* key);

		/** ���ׂĂ̗v�f���폜���� */
		void clear();
		
		/** �v�f���𓾂� */
		int size() { return this->keyList.size(); }
	};
}

#endif // _HASHTABLE_H_INCLUDED_
