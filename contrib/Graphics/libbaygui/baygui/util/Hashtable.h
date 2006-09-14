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
	/** 
	 ���̃N���X�́A�n�b�V���e�[�u�����������邽�߂̂��̂ŁA�L�[��l�Ƀ}�b�v���܂��B
	 null �I�u�W�F�N�g�ȊO�ł���΁A�ǂ̃I�u�W�F�N�g�ł��L�[��l�Ɏg�p���邱�Ƃ��ł��܂��B
	*/
	class Hashtable : public Object {
	private:
		/** �L�[�ꗗ */
		Vector keyList;
		/** �l�ꗗ */
		Vector valueList;
		
	public:
		/** �f�t�H���g�̗e�ʂŐV������̃n�b�V���e�[�u���𐶐����܂��B */
		Hashtable();
		
		/** �f�X�g���N�^ */
		virtual ~Hashtable();
		
		/** �l�Ƀ}�b�v����Ă���L�[���A�n�b�V���e�[�u���ɂ��邩�ǂ����𔻒肵�܂��B */
		inline bool isEmpty() { return (this->keyList.size() == 0) ? true : false; }
		
		/** �n�b�V���e�[�u���ɂ���L�[�̃��X�g��Ԃ��܂��B */
		inline Object** keys() { return this->keyList.elements(); }
		
		/** �n�b�V���e�[�u���ɂ���l�̃��X�g��Ԃ��܂��B */
		inline Object** elements() { return this->valueList.elements(); }
		
		/**
		 �w�肳�ꂽ�L�[�Ƀ}�b�v����Ă���A�n�b�V���e�[�u���̒l��Ԃ��܂��B
		 @param key �n�b�V���e�[�u���̃L�[
		 @return �w�肳�ꂽ�L�[�Ƀ}�b�v����Ă���n�b�V���e�[�u���̒l�B�w�肳�ꂽ�L�[�Ƀ}�b�v����Ă���l���Ȃ��ꍇ�� null
		*/
		Object* get(Object* key);
		
		/**
		 �n�b�V���e�[�u���ɂ����āA�w�肳�ꂽ key ���A�w�肳�ꂽ value �Ƀ}�b�v���܂��B
		 @param key �n�b�V���e�[�u���̃L�[
		 @param value �l
		*/
		void put(Object* key, Object* value);

		/**
		 �L�[ (����т���ɑΉ�����l) ���n�b�V���e�[�u������폜���܂��B
		 @param key �폜����L�[
		*/
		void remove(Object* key);

		/** ���ׂĂ̗v�f���폜���� */
		void clear();
		
		/** �v�f���𓾂� */
		int size() { return this->keyList.size(); }
	};
}

#endif // _HASHTABLE_H_INCLUDED_
