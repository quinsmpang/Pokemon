/******************************
Description: A control which can switch multiple titles
Author: M.Wan
Date: 11/25/2014
******************************/

#ifndef __CONTROLS_TITLESWITCH__
#define __CONTROLS_TITLESWITCH__

#include "cocos2d.h"
#include <vector>
#include <string>

namespace framework
{
	class Win32EventListenerKeyboard;

	class TitleSwitch : public cocos2d::Node
	{
	public:
		static TitleSwitch *create(cocos2d::Node *bg, const std::vector<const std::string> &titles);

		TitleSwitch();
		virtual ~TitleSwitch();

		void setTitles(const std::vector<const std::string> &titles);
		void setBackgroundNode(cocos2d::Node *bg);

		// set title display properties
		void setTitleColor(const cocos2d::Color3B &color);
		void setTitleFontSize(int size);
		void setTitleFont(const std::string &font);

		void setAllowLoop(bool allowLoop);		// whether allow transferring from the last to the first, vice versa.

		void setResponseKeys(int leftKey, int rightKey);
		void setEventsSwallowed(bool isSwallowed);

		inline int getCurrentIndex() const
		{
			return this->_currentIndex;
		}

		void onEnter() override;
		void onExit() override;

		// keyboard events
		virtual void onKeyPressed(int keyCode);
		virtual void onKeyReleased(int keyCode);

	protected:
		bool init(cocos2d::Node *bg, const std::vector<const std::string> &titles);

		cocos2d::Node *_bg;
		const std::vector<const std::string> _titles;
		cocos2d::Vector<cocos2d::Label> _labels;
		cocos2d::RenderTexture *_rt;		// to realize transfer animation
		bool _allowLoop;
		int _currentIndex;
		bool _inAction;		// whether is playing the action.

		Win32EventListenerKeyboard *_kbdListener;
		int _leftKey;
		int _rightKey;
	};
}

#endif