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
 �L�[�ƒl���Z�b�g�Ŏ����X�g�N���X
*/
public class Hashtable {
	/** �L�[���X�g */
	private Vector keyList;
	/** �l���X�g */
	private Vector valueList;

	/** �f�t�H���g�R���X�g���N�^ */
	public Hashtable() {
		keyList = new Vector();
		valueList = new Vector();
	}

	/** ���g����ɂ��� */
	public void clear() {
		keyList.clear();
		valueList.clear();
	}

	/** �L�[�ɑ�������l�𓾂� */
	public Object get(Object key) {
		return (key == null) ? null : valueList.get(keyList.indexOf(key));
	}

	/** �L�[�ƒl�̑g��ǉ����� */
	public void put(Object key, Object value) {
		if (key == null || value == null) return;
		int index = keyList.indexOf(key);
		if (index >= 0) {
			keyList.remove(index);
			valueList.remove(index);
		}
		keyList.add(key);
		valueList.add(value);
	}

	/** �L�[�ɑ�������l���폜���� */
	public void remove(Object key)
	{
		if (key == null) return;
		int index = keyList.indexOf(key);
		keyList.remove(index);
		valueList.remove(index);
	}
}
