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

#if !defined(_OBJECT_H_INCLUDED_)
#define _OBJECT_H_INCLUDED_

namespace baygui {
	/** すべてのクラスの元になるクラス */
	class Object {
	private:
		/** 参照カウント */
		int refCount;
		/** スレッドID */
		dword threadID;
		/** GUIサーバーID */
		dword guisvrID;
		
	public:
		/** デフォルトコンストラクタ */
		Object();
		
		/** デストラクタ */
		virtual ~Object();
		
		/**
		 指定されたオブジェクトと等しいかどうかを得る
		 @param obj 比較対象のオブジェクト
		*/
		virtual bool equals(Object* obj);
		
		/** 参照カウントを得る */
		inline int getRefCount() { return this->refCount; }
		
		/** 参照カウントのポインターを得る */
		inline int* getPointer() { return &this->refCount; }
		
		/** スレッドIDを得る */
		inline dword getThreadID() { return this->threadID; }
		
		/** GUIサーバーIDを得る */
		inline dword getGuisvrID() { return this->guisvrID; }
	};
}

#endif // _OBJECT_H_INCLUDED_
