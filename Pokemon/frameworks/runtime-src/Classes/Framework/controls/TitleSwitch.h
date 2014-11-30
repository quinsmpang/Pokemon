/******************************
Description: A control which can switch multiple titles
Author: M.Wan
Date: 11/25/2014
******************************/

#ifndef __CONTROLS_TITLESWITCH__
#define __CONTROLS_TITLESWITCH__

#include "cocos2d.h"

namespace framework
{
	class Win32EventListenerKeyboard;

	class TitleSwitch : public cocos2d::Node
	{
	public:
		static TitleSwitch *create(cocos2d::Node *bg, const std::vector<std::string> &titles, const std::string &ttfFile);

		TitleSwitch();
		virtual ~TitleSwitch();

		void setTitles(const std::vector<std::string> &titles);
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
		void setCurrentIndex(int index);
		inline void setDuration(float duration)
		{
			_duration = duration;
		}

		void onEnter() override;
		void onExit() override;

		// keyboard events
		virtual void onKeyPressed(int keyCode);

		// override to clip the size
		virtual void visit(cocos2d::Renderer *renderer, const kmMat4& parentTransform, bool parentTransformUpdated) override;

	protected:
		bool init(cocos2d::Node *bg, const std::vector<std::string> &titles, const std::string &ttfFile);
		void needUpdate();

		// play shift action
		void shiftLeft();
		void shiftRight();

		void endAction();

		cocos2d::Node *_bg;
		std::vector<std::string> _titles;
		std::string _ttfPath;
		cocos2d::Vector<cocos2d::Label*> _labels;
		bool _allowLoop;
		int _currentIndex;
		cocos2d::Label *_currentTitle;
		cocos2d::Label *_swapTitle;
		bool _inAction;		// whether is playing the action.
		float _duration;

		Win32EventListenerKeyboard *_kbdListener;
		int _leftKey;
		int _rightKey;

		cocos2d::CustomCommand _beforeVisitCmdScissor;
		cocos2d::CustomCommand _afterVisitCmdScissor;

		const int TITLE_TAG = 999;
	};
}

#endif