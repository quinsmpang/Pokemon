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
		void setTitleFontName(const std::string &fontName);

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

		// override to clip the size
		virtual void visit(Renderer *renderer, const kmMat4& parentTransform, bool parentTransformUpdated) override;

	protected:
		bool init(cocos2d::Node *bg, const std::vector<const std::string> &titles);
		void needUpdate();

		// play shift action
		void shiftLeft();
		void shiftRight();

		cocos2d::Node *_bg;
		std::vector<const std::string> _titles;
		cocos2d::Vector<cocos2d::Label*> _labels;
		bool _allowLoop;
		int _currentIndex;
		bool _inAction;		// whether is playing the action.
		int _actionDirection;

		Win32EventListenerKeyboard *_kbdListener;
		int _leftKey;
		int _rightKey;

		const int TITLE_TAG = 999;
	};
}

#endif