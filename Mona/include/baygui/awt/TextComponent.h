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

#if !defined(_TEXTCOMPONENT_H_INCLUDED_)
#define _TEXTCOMPONENT_H_INCLUDED_

using namespace baygui::awt::event;

namespace baygui {
	namespace awt {
		/** �e�L�X�g��ꕔ�i */
		class TextComponent : public Component {
		private:
			Vector textListenerList;
			
		public:
			/** �f�t�H���g�R���X�g���N�^ */
			TextComponent()
			{
				logprintf("%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__);
			}
			
			/** �f�X�g���N�^ */
			virtual ~TextComponent()
			{
				logprintf("%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__);
			}
			
			/** �N���X�𓾂� */
			virtual int getClass()
			{
				return baygui_awt_TextComponent;
			}
			
			/** AWTEvent���� */
			virtual void processEvent(AWTEvent* e)
			{
				logprintf("%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__);
				if (e->isConsumed() == false) {
					if (e->instanceof(baygui_awt_event_TextEvent)) {
						processTextEvent((TextEvent*)e);
					} else {
						Component::processEvent(e);
					}
				}
				e->consume();
			}
			
			/** TextListener��ǉ� */
			virtual void addTextListener(TextListener* l)
			{
				logprintf("%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__);
				this->textListenerList.add((Object*)l);
			}
			
			/** TextListener���폜 */
			virtual void removeTextListener(TextListener* l)
			{
				logprintf("%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__);
				this->textListenerList.remove((Object*)l);
			}
			
			/** TextEvent���� */
			virtual void processTextEvent(TextEvent* e)
			{
				logprintf("%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__);
				for (int i = 0; i < this->textListenerList.size(); i++) {
					TextListener* l = (TextListener*)this->textListenerList.get(i);
					if (e->isConsumed() == false) {
						l->textValueChanged(e);
					}
				}
				e->consume();
			}
		};
	}
}

#endif // _TEXTCOMPONENT_H_INCLUDED_
