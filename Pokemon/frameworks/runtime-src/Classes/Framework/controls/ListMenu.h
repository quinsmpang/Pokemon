/******************************
Description: List menu only supports keyboard operations.
Author: M.Wan
Date: 7/5/2014
******************************/

#ifndef __CONTROLS_LISTMENU__
#define __CONTROLS_LISTMENU__

#include "cocos2d.h"
#include "ListMenuItem.h"

namespace framework
{
	class ListMenu;

	class ListMenuDelegate
	{
	public:
		virtual ~ListMenuDelegate() {}
		// called when the item is selected.
		virtual void itemSelected(ListMenu *menu, ListMenuItem *item) = 0;
		// called when the item is focused.
		virtual void itemFocused(ListMenu *menu, ListMenuItem *item) = 0;
		// called when the item is unfocused.
		virtual void itemBlurred(ListMenu *menu, ListMenuItem *item) = 0;
		// called when the item is to be recycled.
		virtual void itemWillRecycle(ListMenu *menu, ListMenuItem *item) = 0;
	};

	class ListMenuDataSource
	{
	public:
		virtual ~ListMenuDataSource() {}
		// return the correct item size of the menu
		virtual const cocos2d::Size &itemSizeForMenu(ListMenu *menu) = 0;
		// set your item at the specified global index here
		virtual ListMenuItem *itemAtIndex(ListMenu *menu, ssize_t index) = 0;
		// return the count of items
		virtual ssize_t countOfItemsInMenu(ListMenu *menu) = 0;
	};

	class ListMenu : public cocos2d::Layer
	{
	public:
		static ListMenu *create(ssize_t showCount);
		static ListMenu *create(ListMenuDataSource *dataSource, ssize_t showCount);

		ListMenu();
		virtual ~ListMenu();

		virtual bool initWithShowCount(ssize_t showCount);

		CC_SYNTHESIZE(ListMenuDelegate*, _delegate, Delegate);
		CC_SYNTHESIZE(ListMenuDataSource*, _dataSource, DataSource);

		void onEnter() override;
		void onExit() override;

		inline bool isMenuEnabled() const
		{
			return this->_isEnabled;
		}
		inline void setMenuEnabled(bool isEnabled)
		{
			this->_isEnabled = isEnabled;
		}

		inline ssize_t getTopGlobalIndex() const
		{
			return this->_topGlobalIndex;
		}
		inline ssize_t getCurrentShowIndex() const
		{
			return this->_currentShowIndex;
		}

		void setResponseKeyCodes(int upKeyCode, int downKeyCode, int confirmKeyCode);

		// reload data from the data source
		void reloadData();

		ListMenuItem *getItemAtIndex(ssize_t index);
		void insertItemAtIndex(ssize_t index);
		void removeItemAtIndex(ssize_t index);
		void updateItemAtIndex(ssize_t index);

		ListMenuItem *dequeueItem();

		// keyboard events
		virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event) override;
		virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event) override;

	protected:
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
		cocos2d::EventListenerKeyboard *_kbdListener;
		int _pressedKey;
	};
}

#endif