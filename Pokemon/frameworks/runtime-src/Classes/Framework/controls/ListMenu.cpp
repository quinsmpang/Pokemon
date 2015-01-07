#include "ListMenu.h"
#include "ListMenuItem.h"
#include "../lua/LuaUtils.h"
#include "../win32/Win32EventListenerKeyboard.h"
#include "../win32/Win32Notifier.h"

using namespace cocos2d;

namespace framework
{
	float ListMenu::LONG_PRESSED_DT = 0.05f;
	float ListMenu::LONG_PRESSED_DELAY = 1.0f;

	ListMenu *ListMenu::create(ssize_t showCount)
	{
		return ListMenu::create(nullptr, showCount);
	}

	ListMenu *ListMenu::create(ListMenuDataSource *dataSource, ssize_t showCount)
	{
		auto pMenu = new ListMenu();
		if (pMenu && pMenu->initWithShowCount(showCount))
		{
			pMenu->setDataSource(dataSource);
			pMenu->reloadData();
			pMenu->autorelease();
			return pMenu;
		}
		CC_SAFE_RELEASE_NULL(pMenu);
		return pMenu;
	}

	ListMenu::ListMenu()
		: Layer()
		, _showCount(0)
		, _delegate(nullptr)
		, _shownItems()
		, _recycledItems(nullptr)
		, _upKeyCode(0)
		, _downKeyCode(0)
		, _confirmKeyCode(0)
		, _isEnabled(true)
		, _topGlobalIndex(0)
		, _currentShowIndex(0)
		, _kbdListener(nullptr)
		, _pressedKey(0)
	{
	}

	ListMenu::~ListMenu()
	{
		CC_SAFE_DELETE(_recycledItems);
		CC_SAFE_RELEASE(_kbdListener);
	}

	bool ListMenu::initWithShowCount(ssize_t showCount)
	{
		if (Layer::init())
		{
			this->_recycledItems = new Vector<ListMenuItem*>();
			this->_showCount = showCount;
			this->setAnchorPoint(Point(0.5, 0.5));
			this->ignoreAnchorPointForPosition(false);

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
			auto pKbdListener = Win32EventListenerKeyboard::createWithTarget(this);
			pKbdListener->onWin32KeyDown = std::bind(&ListMenu::onKeyPressed, this, std::placeholders::_1);
			pKbdListener->onWin32KeyUp = std::bind(&ListMenu::onKeyReleased, this, std::placeholders::_1);
			pKbdListener->setEventsSwallowed(false);
			pKbdListener->retain();
			this->_kbdListener = pKbdListener;
#endif

			return true;
		}
		return false;
	}

	void ListMenu::onEnter()
	{
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
		Win32Notifier::getInstance()->addEventListener(this->_kbdListener);
#endif

		Layer::onEnter();
	}

	void ListMenu::onExit()
	{
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
		if (this->_kbdListener)
		{
			Win32Notifier::getInstance()->removeEventListener(this->_kbdListener);
		}
#endif

		Layer::onExit();
	}

	void ListMenu::select(int index, int showIndex)
	{
		for (const auto &item : _shownItems)
		{
			// recycle the items.
			if (_delegate)
			{
				_delegate->itemWillRecycle(this, item);
			}
			item->reset();
			_recycledItems->pushBack(item);
			item->removeFromParentAndCleanup(false);
		}

		_shownItems.clear();
		if (_dataSource)
		{
			ssize_t itemCount = _dataSource->countOfItemsInMenu(this);
			if (itemCount > 0)
			{
				// init ui
				itemCount = itemCount > _showCount ? _showCount : itemCount;
				Size itemSize = _dataSource->itemSizeForMenu(this);
				this->setContentSize(Size(itemSize.width, _showCount * itemSize.height));
				ListMenuItem *item = nullptr;
				int top = 0;
				int requireIndex = showIndex;
				if (itemCount > _showCount)
				{
					// out of bottom bound
					if (index > _dataSource->countOfItemsInMenu(this) - _showCount - 1)
					{
						top = _dataSource->countOfItemsInMenu(this) - _showCount - 1;
						requireIndex = _dataSource->countOfItemsInMenu(this) - index - 1;
					}
					else
					{
						top = index - showIndex;
						requireIndex = index;
					}
				}
				for (int i = 0; i < itemCount; ++i)
				{
					item = _dataSource->itemAtIndex(this, i + top);
					item->setContentSize(itemSize);
					if (item)
					{
						this->setItemAtIndex(item, i);
					}
				}
				// focus the first item
				if (_delegate)
				{
					_delegate->itemFocused(this, this->getItemAtIndex(requireIndex));
				}
			}
		}
	}

	void ListMenu::setResponseKeyCodes(int upKeyCode, int downKeyCode, int confirmKeyCode)
	{
		this->_upKeyCode = upKeyCode;
		this->_downKeyCode = downKeyCode;
		this->_confirmKeyCode = confirmKeyCode;
	}

	void ListMenu::setEventsSwallowed(bool isSwallowed)
	{
		if (_kbdListener)
		{
			this->_kbdListener->setEventsSwallowed(isSwallowed);
		}
	}

	void ListMenu::reloadData()
	{
		for (const auto &item : _shownItems)
		{
			// recycle the items.
			if (_delegate)
			{
				_delegate->itemWillRecycle(this, item);
			}
			item->reset();
			_recycledItems->pushBack(item);
			item->removeFromParentAndCleanup(false);
		}

		_shownItems.clear();
		if (_dataSource)
		{
			ssize_t itemCount = _dataSource->countOfItemsInMenu(this);
			if (itemCount > 0)
			{
				// init ui
				itemCount = itemCount > _showCount ? _showCount : itemCount;
				Size itemSize = _dataSource->itemSizeForMenu(this);
				this->setContentSize(Size(itemSize.width, _showCount * itemSize.height));
				ListMenuItem *item = nullptr;
				for (int i = 0; i < itemCount; ++i)
				{
					item = _dataSource->itemAtIndex(this, i);
					item->setContentSize(itemSize);
					if (item)
					{
						this->setItemAtIndex(item, i);
					}
				}
				// focus the first item
				if (_delegate)
				{
					_delegate->itemFocused(this, this->getItemAtIndex(0));
				}
			}
		}
	}

	ListMenuItem *ListMenu::getItemAtIndex(ssize_t index)
	{
		if (index >= 0 && index < _shownItems.size())
		{
			for (const auto &item : _shownItems)
			{
				if (item->getShowIndex() == index)
				{
					return item;
				}
			}
		}
		return nullptr;
	}

	ListMenuItem *ListMenu::dequeueItem()
	{
		// get item from the recycled list.
		ListMenuItem *pItem = nullptr;
		if (!_recycledItems->empty())
		{
			pItem = _recycledItems->at(_recycledItems->size() - 1);
			pItem->retain();
			_recycledItems->erase(_recycledItems->size() - 1);
			pItem->autorelease();
		}
		return pItem;
	}

	void ListMenu::onKeyPressed(int keyCode)
	{
		if (!_isEnabled || _dataSource->countOfItemsInMenu(this) <= 0)
		{
			return;
		}

		if ((_pressedKey == _downKeyCode || _pressedKey == _upKeyCode) && (int)keyCode != _confirmKeyCode)
		{
			return;
		}
		_pressedKey = (int)keyCode;

		if ((int)keyCode == _upKeyCode)
		{
			this->moveUp();

			Director::getInstance()->getScheduler()->schedule(CC_CALLBACK_1(ListMenu::onScheduleLongPressed, this), this, LONG_PRESSED_DT, kRepeatForever, LONG_PRESSED_DELAY, false, "long_pressed_delay");
		}
		else if ((int)keyCode == _downKeyCode)
		{
			this->moveDown();

			Director::getInstance()->getScheduler()->schedule(CC_CALLBACK_1(ListMenu::onScheduleLongPressed, this), this, LONG_PRESSED_DT, kRepeatForever, LONG_PRESSED_DELAY, false, "long_pressed_delay");
		}
		else if ((int)keyCode == _confirmKeyCode)
		{
			Director::getInstance()->getScheduler()->unschedule("long_pressed_delay", this);
			_pressedKey = 0;

			// select the current item
			if (_delegate)
			{
				_delegate->itemSelected(this, this->getItemAtIndex(_currentShowIndex));
			}
		}
	}

	void ListMenu::onKeyReleased(int keyCode)
	{
		if (!_isEnabled || _dataSource->countOfItemsInMenu(this) <= 0)
		{
			return;
		}

		if ((int)keyCode == _pressedKey)
		{
			Director::getInstance()->getScheduler()->unschedule("long_pressed_delay", this);
			_pressedKey = 0;
		}
	}

	/***************** protected methods *****************/
	void ListMenu::setItemAtIndex(ListMenuItem *item, ssize_t index)
	{
		if (item)
		{
			item->setShowIndex(index);
			item->setAnchorPoint(Point(0, 1));
			item->setPosition(0, this->getContentSize().height - index * item->getContentSize().height);
			if (!item->getParent())
			{
				this->addChild(item);
				_shownItems.pushBack(item);
			}
		}
	}

	void ListMenu::onScheduleLongPressed(float dt)
	{
		if (_pressedKey == _upKeyCode)
		{
			this->moveUp();
		}
		else if (_pressedKey == _downKeyCode)
		{
			this->moveDown();
		}
	}

	void ListMenu::moveUp()
	{
		if (_topGlobalIndex + _currentShowIndex == 0)
		{
			return;
		}
		// unfocus the current item
		if (_delegate)
		{
			_delegate->itemBlurred(this, this->getItemAtIndex(_currentShowIndex));
		}
		// current show index is not at the beginning, just move up.
		if (_currentShowIndex > 0)
		{
			--_currentShowIndex;
		}
		// show the previous item, index doesn't change
		else
		{
			ListMenuItem *pItem = nullptr;
			ListMenuItem *pLastItem = this->getItemAtIndex(_showCount - 1);
			// move down the rest items.
			for (int i = _showCount - 2; i >= 0; --i)
			{
				pItem = this->getItemAtIndex(i);
				this->setItemAtIndex(pItem, i + 1);
			}
			// recycle the last item
			if (_delegate)
			{
				_delegate->itemWillRecycle(this, pLastItem);
			}
			pLastItem->reset();
			_recycledItems->pushBack(pLastItem);
			pLastItem->removeFromParentAndCleanup(false);
			_shownItems.eraseObject(pLastItem);
			// decrease the top global index.
			--_topGlobalIndex;
			// add the previous item
			pItem = _dataSource->itemAtIndex(this, _topGlobalIndex);
			this->setItemAtIndex(pItem, 0);
		}
		// focus the current item
		if (_delegate)
		{
#if CC_ENABLE_SCRIPT_BINDING
			if (_scriptType == kScriptTypeLua)
			{
				int curIndex = _topGlobalIndex + _currentShowIndex;
				// params
				Vector<Ref*> pParams(1);
				pParams.pushBack(__Integer::create(curIndex + 1));
				pParams.pushBack(__Integer::create(curIndex));
				// param types
				Vector<Ref*> pTypes(1);
				pTypes.pushBack(__String::create("__Integer"));
				pTypes.pushBack(__String::create("__Integer"));
				LuaUtils::getInstance()->executePeertableFunction(this, "onSelectedItemChanged", pParams, pTypes, false);
			}
#endif
			_delegate->itemFocused(this, this->getItemAtIndex(_currentShowIndex));
		}
	}

	void ListMenu::moveDown()
	{
		if (_topGlobalIndex + _currentShowIndex == _dataSource->countOfItemsInMenu(this) - 1)
		{
			return;
		}
		// unfocus the current item
		if (_delegate)
		{
			_delegate->itemBlurred(this, this->getItemAtIndex(_currentShowIndex));
		}
		// current show index is not at the end, just move down.
		if (_currentShowIndex < _shownItems.size() - 1)
		{
			++_currentShowIndex;
		}
		// show the next item, index doesn't change
		else
		{
			ListMenuItem *pItem = nullptr;
			ListMenuItem *pFirstItem = this->getItemAtIndex(0);
			// move up the rest item
			for (int i = 1; i < _shownItems.size(); ++i)
			{
				pItem = this->getItemAtIndex(i);
				this->setItemAtIndex(pItem, i - 1);
			}
			// recycle the first item
			if (_delegate)
			{
				_delegate->itemWillRecycle(this, pFirstItem);
			}
			pFirstItem->reset();
			_recycledItems->pushBack(pFirstItem);
			pFirstItem->removeFromParentAndCleanup(false);
			_shownItems.eraseObject(pFirstItem);
			// add the next item
			pItem = _dataSource->itemAtIndex(this, _topGlobalIndex + _showCount);
			this->setItemAtIndex(pItem, _showCount - 1);
			// increase top global index
			++_topGlobalIndex;
		}
		// focus the current item
		if (_delegate)
		{
#if CC_ENABLE_SCRIPT_BINDING
			if (_scriptType == kScriptTypeLua)
			{
				int curIndex = _topGlobalIndex + _currentShowIndex;
				// params
				Vector<Ref*> pParams(1);
				pParams.pushBack(__Integer::create(curIndex - 1));
				pParams.pushBack(__Integer::create(curIndex));
				// param types
				Vector<Ref*> pTypes(1);
				pTypes.pushBack(__String::create("__Integer"));
				pTypes.pushBack(__String::create("__Integer"));
				LuaUtils::getInstance()->executePeertableFunction(this, "onSelectedItemChanged", pParams, pTypes, false);
			}
#endif
			_delegate->itemFocused(this, this->getItemAtIndex(_currentShowIndex));
		}
	}

	bool ListMenu::isTopOverflowed() const
	{
		return _topGlobalIndex > 0;
	}

	bool ListMenu::isBottomOverflowed()
	{
		return _topGlobalIndex + _showCount < _dataSource->countOfItemsInMenu(this);
	}
}