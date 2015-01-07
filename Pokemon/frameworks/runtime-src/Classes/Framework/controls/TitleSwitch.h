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
        /**
         * Create a TitleSwitch control.
         *
         * @param bg Control background node.
         * @param titles Title collection.
         * @param ttfFile The font family used for the control.
         *
         * @return A new TitleSwitch object.
         */
		static TitleSwitch *create(cocos2d::Node *bg, const std::vector<std::string> &titles, const std::string &ttfFile);

        /**
         * TitleSwitch constructor.
         */
		TitleSwitch();
        /**
         * TitleSwitch destructor.
         */
		virtual ~TitleSwitch();

        /**
         * Title collection setter.
         *
         * @param titles Title collection to replace.
         */
		void setTitles(const std::vector<std::string> &titles);
        /**
         * Update control background.
         *
         * @param bg Background node to replace.
         */
		void setBackgroundNode(cocos2d::Node *bg);

		/**
         * Title font color setter.
         *
         * @param color Font color to replace.
         */
		void setTitleColor(const cocos2d::Color3B &color);
        /**
         * Title font size setter.
         *
         * @param size Font size to replace.
         */
		void setTitleFontSize(int size);
        /**
         * Title font family setter.
         *
         * @param fontName Font family or font path to replace.
         */
		void setTitleFontName(const std::string &fontName);

        /**
         * Whether to allow you swap between the first title and the last one.
         *
         * @param allowLoop A boolean value which indicates you'd like to swap between the first and the last.
         */
		void setAllowLoop(bool allowLoop);		// whether allow transferring from the last to the first, vice versa.

        /**
         * Set the keys which would response to your operations.
         *
         * @param leftKey The key for responsing left operation.
         * @param rightKey The key for responsing right operation.
         */
		void setResponseKeys(int leftKey, int rightKey);
        /**
         * Whether to swallow the keyboard events below.
         *
         * @param isSwallowed A boolean value.
         */
		void setEventsSwallowed(bool isSwallowed);

        /**
         * Get the current showing index.
         *
         * @return The current showing index.
         */
		inline int getCurrentIndex() const
		{
			return this->_currentIndex;
		}
        /**
         * Set the current showing index.
         *
         * @param The showing index you are going to set.
         */
		void setCurrentIndex(int index);
        /**
         * Get the transition animation duration.
         *
         * @param The transition duration.
         */
		inline void setDuration(float duration)
		{
			_duration = duration;
		}

        /**
         * Enter and exit events overrides.
         */
		void onEnter() override;
		void onExit() override;

		/**
         * Keyboard events.
         */
		virtual void onKeyPressed(int keyCode);

		/**
         * Override visit method.
         */
		virtual void visit(cocos2d::Renderer *renderer, const kmMat4& parentTransform, bool parentTransformUpdated) override;

	protected:
		virtual bool init(cocos2d::Node *bg, const std::vector<std::string> &titles, const std::string &ttfFile);
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