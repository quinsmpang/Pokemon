#include "ListMenu.h"
#include "../lua/LuaUtils.h"

using namespace cocos2d;

namespace framework
{
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
		, _isEnabled(true)
		, _topGlobalIndex(0)
		, _currentShowIndex(0)
		, _kbdListener(nullptr)
	{
	}

	ListMenu::~ListMenu()
	{
		CC_SAFE_DELETE(_recycledItems);
	}

	bool ListMenu::initWithShowCount(ssize_t showCount)
	{
		if (Layer::init())
		{
			this->_recycledItems = new Vector<ListMenuItem*>();
			this->_showCount = showCount;

			return true;
		}
		return false;
	}

	void ListMenu::onEnter()
	{
		auto pKbdListener = EventListenerKeyboard::create();
		pKbdListener->onKeyPressed = std::bind(&ListMenu::onKeyPressed, this, std::placeholders::_1, std::placeholders::_2);
		pKbdListener->onKeyReleased = std::bind(&ListMenu::onKeyReleased, this, std::placeholders::_1, std::placeholders::_2);

		this->_eventDispatcher->addEventListenerWithSceneGraphPriority(pKbdListener, this);
		this->_kbdListener = pKbdListener;
	}

	void ListMenu::onExit()
	{
		this->_eventDispatcher->removeEventListener(_kbdListener);
	}

	void ListMenu::setResponseKeyCodes(int upKeyCode, int downKeyCode)
	{
		this->_upKeyCode = upKeyCode;
		this->_downKeyCode = downKeyCode;
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
				Size itemSize = _dataSource->itemSizeForMenu(this);
				this->setContentSize(Size(itemSize.width, itemCount * itemSize.height));
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
			}
		}
	}

	ListMenuItem *ListMenu::getItemAtIndex(ssize_t index)
	{
		if (index >= 0 && index < _shownItems.size())
		{
			return _shownItems.at(index);
		}
		return nullptr;
	}

	void ListMenu::insertItemAtIndex(ssize_t index)
	{
		if (index < 0 || index >= _shownItems.size())
		{
			return;
		}

		for (int i = index; i < _shownItems.size(); ++i)
		{
			ListMenuItem *pItem = this->getItemAtIndex(i);
			if (i == _showCount - 1)
			{
				// recycle the items.
				if (_delegate)
				{
					_delegate->itemWillRecycle(this, pItem);
				}
				pItem->reset();
				_recycledItems->pushBack(pItem);
				pItem->removeFromParentAndCleanup(false);
				_shownItems.eraseObject(pItem);
				break;
			}
			this->setItemAtIndex(pItem, pItem->getShowIndex() + 1);
		}
		// insert the new item
		ListMenuItem *pItem = _dataSource->itemAtIndex(this, _topGlobalIndex + index);
		this->setItemAtIndex(pItem, index);
	}

	void ListMenu::removeItemAtIndex(ssize_t index)
	{
		if (index < 0 || index >= _shownItems.size())
		{
			return;
		}

		// remove the item first
		ListMenuItem *pItem = this->getItemAtIndex(index);
		// recycle the item.
		if (_delegate)
		{
			_delegate->itemWillRecycle(this, pItem);
		}
		pItem->reset();
		_recycledItems->pushBack(pItem);
		pItem->removeFromParentAndCleanup(false);
		_shownItems.eraseObject(pItem);

		// at the bottom, move above items down
		if (_topGlobalIndex > 0 && _topGlobalIndex + _showCount == _dataSource->countOfItemsInMenu(this) - 1)
		{
			for (int i = index; i >= 0; --i)
			{
				pItem = this->getItemAtIndex(i);
				this->setItemAtIndex(pItem, i + 1);
			}
			pItem = _dataSource->itemAtIndex(this, _topGlobalIndex);
			this->setItemAtIndex(pItem, 0);
			--_topGlobalIndex;
		}
		// otherwise, move below items down
		else
		{
			for (int i = index; i < _shownItems.size(); ++i)
			{
				pItem = this->getItemAtIndex(i);
				this->setItemAtIndex(pItem, i - 1);
			}
			pItem = _dataSource->itemAtIndex(this, _topGlobalIndex + _shownItems.size() - 1);
			this->setItemAtIndex(pItem, _shownItems.size());
		}
	}

	void ListMenu::updateItemAtIndex(ssize_t index)
	{
		if (index < 0 || index >= _shownItems.size())
		{
			return;
		}

		// remove the item first
		ListMenuItem *pItem = this->getItemAtIndex(index);
		// recycle the item.
		if (_delegate)
		{
			_delegate->itemWillRecycle(this, pItem);
		}
		pItem->reset();
		_recycledItems->pushBack(pItem);
		pItem->removeFromParentAndCleanup(false);
		_shownItems.eraseObject(pItem);

		// readd the item
		pItem = _dataSource->itemAtIndex(this, index);
		this->setItemAtIndex(pItem, index);
	}

	ListMenuItem *ListMenu::dequeueItem()
	{
		// get item from the recycled list.
		ListMenuItem *pItem = nullptr;
		if (!_recycledItems->empty())
		{
			pItem = _recycledItems->at(0);
			pItem->retain();
			_recycledItems->erase(0);
			pItem->autorelease();
		}
		return pItem;
	}

	void ListMenu::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event)
	{
		if (!_isEnabled)
		{
			return;
		}

		if ((int)keyCode == _upKeyCode)
		{
			if (_topGlobalIndex == 0)
			{
				return;
			}
			// unfocus the current item
			if (_delegate)
			{
				_delegate->itemBlurred(this, this->getItemAtIndex(_currentShowIndex));
			}
			if (_currentShowIndex > 0)
			{
				--_currentShowIndex;
			}
			else
			{
				ListMenuItem *pItem = nullptr;
				for (int i = 0; i < _shownItems.size(); ++i)
				{
					pItem = this->getItemAtIndex(i);
					if (i == _shownItems.size() - 1)
					{
						// recycle the item.
						if (_delegate)
						{
							_delegate->itemWillRecycle(this, pItem);
						}
						pItem->reset();
						_recycledItems->pushBack(pItem);
						pItem->removeFromParentAndCleanup(false);
						_shownItems.eraseObject(pItem);
						break;
					}
					this->setItemAtIndex(pItem, i + 1);
				}
				--_topGlobalIndex;
				pItem = _dataSource->itemAtIndex(this, _topGlobalIndex);
				this->setItemAtIndex(pItem, 0);
			}
			// focus the current item
			if (_delegate)
			{
				_delegate->itemFocused(this, this->getItemAtIndex(_currentShowIndex));
			}
		}
		else if ((int)keyCode == _downKeyCode)
		{
			if (_topGlobalIndex + _showCount >= _dataSource->countOfItemsInMenu(this) - 1)
			{
				return;
			}
			// unfocus the current item
			if (_delegate)
			{
				_delegate->itemBlurred(this, this->getItemAtIndex(_currentShowIndex));
			}
			if (_currentShowIndex + _topGlobalIndex < _shownItems.size() - 1)
			{
				++_currentShowIndex;
			}
			else
			{
				ListMenuItem *pItem = nullptr;
				for (int i = 0; i < _shownItems.size(); ++i)
				{
					pItem = this->getItemAtIndex(i);
					if (i == 0)
					{
						// recycle the item.
						if (_delegate)
						{
							_delegate->itemWillRecycle(this, pItem);
						}
						pItem->reset();
						_recycledItems->pushBack(pItem);
						pItem->removeFromParentAndCleanup(false);
						_shownItems.eraseObject(pItem);
						continue;
					}
					this->setItemAtIndex(pItem, i - 1);
				}
				--_topGlobalIndex;
				pItem = _dataSource->itemAtIndex(this, _topGlobalIndex + _shownItems.size() - 1);
				this->setItemAtIndex(pItem, _shownItems.size() - 1);
			}
			// focus the current item
			if (_delegate)
			{
				_delegate->itemFocused(this, this->getItemAtIndex(_currentShowIndex));
			}
		}
		else
		{
			return;
		}

#if CC_ENABLE_SCRIPT_BINDING
		if (_scriptType == kScriptTypeLua)
		{
			// params
			Vector<Ref*> pParams(1);
			pParams.pushBack(__Integer::create((int)keyCode));
			// param types
			Vector<Ref*> pTypes(1);
			pTypes.pushBack(__String::create("__Integer"));
			LuaUtils::getInstance()->executePeertableFunction(this, "afterKeyPressed", pParams, pTypes, false);
		}
#endif
	}

	void ListMenu::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event)
	{
		if (!_isEnabled)
		{
			return;
		}

#if CC_ENABLE_SCRIPT_BINDING
		if (_scriptType == kScriptTypeLua)
		{
			// params
			Vector<Ref*> pParams(1);
			pParams.pushBack(__Integer::create((int)keyCode));
			// param types
			Vector<Ref*> pTypes(1);
			pTypes.pushBack(__String::create("__Integer"));
			LuaUtils::getInstance()->executePeertableFunction(this, "afterKeyReleased", pParams, pTypes, false);
		}
#endif
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
}