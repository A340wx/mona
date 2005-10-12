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

package java.util;

/**
 �ϒ��f�[�^���X�g�N���X
 */
public final class Vector {
	/** �f�[�^���X�g */
	private Object[] dataList;
	/** ���� */
	private int count = 0;
	/** �W���̃T�C�Y */
	private static final int BUFFER_SIZE = 16;
	
	/** �f�t�H���g�R���X�g���N�^ */
	public Vector() {
		dataList = new Object[BUFFER_SIZE];
	}
	
	/** �v�f��ǉ����� */
	public boolean add(Object obj) {
		if (count == dataList.length) {
			Object[] new_dataList = new Object[dataList.length * 2];
			for (int i = 0; i < count; i++) {
				new_dataList[i] = dataList[i];
			}
			dataList = new_dataList;
		}
		dataList[count++] = obj;
		return true;
	}
	
	/** �T�C�Y�𓾂� */
	public int capacity() {
		return count;
	}
	
	/** ���g����ɂ��� */
	public void clear() {
		for (int i = 0; i < dataList.length; i++) {
			dataList[i] = null;
		}
		dataList = null;
		dataList = new Object[BUFFER_SIZE];
	}
	
	/** �w�肵���v�f���܂܂�Ă��邩�ǂ����𓾂� */
	public boolean contains(Object obj) {
		for (int i = 0; i < dataList.length; i++) {
			if (dataList[i].equals(obj)) return true;
		}
		return false;
	}
	
	/** �w�肵�����Ԃ̗v�f�𓾂� */
	public Object get(int index) {
		if (index < 0 || index >= count) {
			return null;
		} else {
			return dataList[index];
		}
	}
	
	/** �w�肵���v�f�̏��Ԃ𓾂� */
	public int indexOf(Object obj) {
		for (int i = 0; i < dataList.length; i++) {
			if (dataList[i].equals(obj)) return i;
		}
		return -1;
	}
	
	/** ���g���󂩂ǂ����𓾂� */
	public boolean isEmpty() {
		return (count > 0);
	}
	
	/** �w�肵�����Ԃ̗v�f���폜���� */
	public Object remove(int index) {
		if (index < 0 || index >= count) {
			return null;
		} else {
			Object obj = dataList[index];
			count--;
			for (int i = index; i < count; i++) {
				dataList[i] = dataList[i + 1];
			}
			return obj;
		}
	}
	
	/** �w�肵���v�f���폜���� */
	public boolean remove(Object obj) {
		int index = indexOf(obj);
		if (index < 0) {
			return false;
		} else {
			remove(index);
			return true;
		}
	}
}
