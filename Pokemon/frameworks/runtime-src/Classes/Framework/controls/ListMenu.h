/******************************
Description: List menu only supports keyboard operations.
Author: M.Wan
Date: 7/5/2014
******************************/

#ifndef __CONTROLS_LISTMENU__
#define __CONTROLS_LISTMENU__

#include "cocos2d.h"

namespace framework
{
	class ListMenuItem;
	class ListMenu;
	class Win32EventListenerKeyboard;

	class ListMenuDelegate
	{
	public:
        /**
         * ListMenuDelegate destructor.
         */
		virtual ~ListMenuDelegate() {}
        /**
         * Called when the item is selected.
         */
		virtual void itemSelected(ListMenu *menu, ListMenuItem *item) = 0;
		/**
         * Called when the item is focused.
         */
		virtual void itemFocused(ListMenu *menu, ListMenuItem *item) = 0;
		/**
         * Called when the item is unfocused.
         */
		virtual void itemBlurred(ListMenu *menu, ListMenuItem *item) = 0;
		/**
         * Called when the item is recycled.
         */
		virtual void itemWillRecycle(ListMenu *menu, ListMenuItem *item) = 0;
	};

	class ListMenuDataSource
	{
	public:
        /**
         * ListMenuDataSource destructor.
         */
		virtual ~ListMenuDataSource() {}
        /**
         * Get the correct item size of the menu.
         *
         * @param menu Sender.
         *
         * @return Return the correct item size of the menu.
         */
		virtual const cocos2d::Size &itemSizeForMenu(ListMenu *menu) = 0;
        
		/**
         * The item of the specified global index.
         *
         * @param menu Sender.
         * @param index The global index.
         *
         * @return Return the item at the specified index.
         */
		virtual ListMenuItem *itemAtIndex(ListMenu *menu, ssize_t index) = 0;
		/**
         * Get the size of the menu items.
         *
         * @param menu Sender.
         *
         * @return Return the size of all items.
         */
		virtual ssize_t countOfItemsInMenu(ListMenu *menu) = 0;
	};

	class ListMenu : public cocos2d::Layer
	{
	public:
        /**
         * Create a new ListMenu with specified maximum shown amount.
         *
         * @param showCount Shown count of the menu.
         *
         * @return Return ListMenu object.
         */
		static ListMenu *create(ssize_t showCount);
        /**
         * Create a new ListMenu with specified data source and maximum shown amount.
         *
         * @param dataSource Data source of the menu.
         * @param showCount Shown count of the menu.
         *
         * @return Return ListMenu object.
         */
		static ListMenu *create(ListMenuDataSource *dataSource, ssize_t showCount);

        /**
         * ListMenu constructor.
         */
		ListMenu();
        /**
         * ListMenu destructor.
         */
		virtual ~ListMenu();

        /**
         * ListMenuDelegate getter and setter.
         */
		CC_SYNTHESIZE(ListMenuDelegate*, _delegate, Delegate);
        /**
         * ListMenuDataSource getter and setter.
         */
		CC_SYNTHESIZE(ListMenuDataSource*, _dataSource, DataSource);

        /**
         * Overrides.
         */
		void onEnter() override;
		void onExit() override;

        /**
         * Check whether the menu is enabled.
         *
         * @return Return boolean which indicates if the menu is enabled.
         */
		inline bool isMenuEnabled() const
		{
			return this->_isEnabled;
		}
        /**
         * Set menu enabled.
         * 
         * @param isEnabled Whether enabled.
         */
		inline void setMenuEnabled(bool isEnabled)
		{
			this->_isEnabled = isEnabled;
		}

        /**
         * Get the top global index if the menu.
         *
         * @return Return the top global index.
         */
		inline ssize_t getTopGlobalIndex() const
		{
			return this->_topGlobalIndex;
		}
        /**
         * Get current shown index of the menu.
         *
         * @return Return current selected shown index.
         */
		inline ssize_t getCurrentShowIndex() const
		{
			return this->_currentShowIndex;
		}
        /**
         * Judge whether the top is overflow.
         *
         * @return Return boolean which indicates the top of the menu is overflow.
         */
		bool isTopOverflowed() const;
        /**
         * Judge whether the bottom is overflow.
         *
         * @return Return boolean which indicates the bottom of the menu is overflow.
         */
		bool isBottomOverflowed();
        /**
         * Get the global index of current selected item.
         *
         * @return Return the global index of current selected item.
         */
		inline ssize_t getIndexInAllItems() const
		{
			return this->_topGlobalIndex + this->_currentShowIndex;
		}

        /**
         * @brief Select the specified index of the menu.
         * If the index doesn't suit the showIndex, then showIndex will have no use.
         * 
         * @param index The index you want to focus.
         * @param showIndex Set the shown index you would like to.
         */
		void select(int index, int showIndex = 0);
        /**
         * Set responsed keys of the menu.
         *
         * @param upKeyCode Up key code.
         * @param downKeyCode Down key code.
         * @param confirmKeyCode Confirm key code.
         */
		void setResponseKeyCodes(int upKeyCode, int downKeyCode, int confirmKeyCode);
        /**
         * Set swallowed of the keyboard event.
         *
         * @param isSwallowed Whether the menu should swallow the items below.
         */
		void setEventsSwallowed(bool isSwallowed);

		// reload data from the data source
		void reloadData();

		ListMenuItem *getItemAtIndex(ssize_t index);
		void insertItemAtIndex(ssize_t index);
		void removeItemAtIndex(ssize_t index);
		void updateItemAtIndex(ssize_t index);

		ListMenuItem *dequeueItem();

		// keyboard events
		virtual void onKeyPressed(int keyCode);
		virtual void onKeyReleased(int keyCode);
		//virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event) override;
		//virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event) override;

	protected:
		virtual bool initWithShowCount(ssize_t showCount);
        
		static float LONG_PRESSED_DT;		// long pressed duration
		static float LONG_PRESSED_DELAY;		// long pressed delay

		void setItemAtIndex(ListMenuItem *item, ssize_t index);
		void moveUp();
		void moveDown();
		void onScheduleLongPressed(float dt);

		ssize_t _showCount;
		cocos2d::Vector<ListMenuItem*> *_recycledItems;
		cocos2d::Vector<ListMenuItem*> _shownItems;
		int _upKeyCode;
		int _downKeyCode;
		int _confirmKeyCode;
		bool _isEnabled;
		ssize_t _topGlobalIndex;
		ssize_t _currentShowIndex;
		//cocos2d::EventListenerKeyboard *_kbdListener;
		Win32EventListenerKeyboard *_kbdListener;
		int _pressedKey;
	};
}

#endif