#include "TableViewEx.h"
#include "../lua/LuaUtils.h"
#include <string>

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace std;

namespace framework
{
	TableViewEx::TableViewEx()
		: TableView()
		, _tableViewScriptDelegate(nullptr)
	{
	}

	TableViewEx::~TableViewEx()
	{
		CC_SAFE_RELEASE_NULL(this->_tableViewScriptDelegate);
	}

	TableViewEx *TableViewEx::create(TableViewDataSource *dataSource, Size viewSize)
	{
		auto pTableView = new TableViewEx();
		if (pTableView && pTableView->initWithViewSize(viewSize))
		{
			pTableView->autorelease();
			pTableView->setDataSource(dataSource);
			pTableView->_updateCellPositions();
			pTableView->_updateContentSize();

			return pTableView;
		}
		CC_SAFE_RELEASE_NULL(pTableView);
		return nullptr;
	}

	Ref *TableViewEx::getScriptDelegate() const
	{
		return this->_tableViewScriptDelegate;
	}

	void TableViewEx::setScriptDelegate(Ref *scriptDelegate)
	{
		this->_tableViewScriptDelegate = scriptDelegate;
	}

	/***************** ScrollViewDelegate events override *****************/
	void TableViewEx::scrollViewDidScroll(cocos2d::extension::ScrollView* view)
	{
		long countOfItems = _dataSource->numberOfCellsInTableView(this);
		if (0 == countOfItems)
		{
			return;
		}

		if (_isUsedCellsDirty)
		{
			_isUsedCellsDirty = false;
			std::sort(_cellsUsed.begin(), _cellsUsed.end(), [](TableViewCell *a, TableViewCell *b) -> bool{
				return a->getIdx() < b->getIdx();
			});
		}

		if(_tableViewDelegate != NULL) {
			_tableViewDelegate->scrollViewDidScroll(this);
		}
		// add lua peertable function
#if CC_ENABLE_SCRIPT_BINDING
		if (_tableViewScriptDelegate) {
			Vector<Ref*> pParams(1);
			pParams.pushBack(this);
			Vector<Ref*> pParamTypes(1);
			pParams.pushBack(__String::create("cc.TableView"));
			LuaUtils::getInstance()->executePeertableFunction(this->_tableViewScriptDelegate, "scrollViewDidScroll", pParams, pParamTypes, false);
		}
#endif

		ssize_t startIdx = 0, endIdx = 0, idx = 0, maxIdx = 0;
		Point offset = this->getContentOffset() * -1;
		maxIdx = MAX(countOfItems-1, 0);

		if (_vordering == VerticalFillOrder::TOP_DOWN)
		{
			offset.y = offset.y + _viewSize.height/this->getContainer()->getScaleY();
		}
		startIdx = this->_indexFromOffset(offset);
		if (startIdx == CC_INVALID_INDEX)
		{
			startIdx = countOfItems - 1;
		}

		if (_vordering == VerticalFillOrder::TOP_DOWN)
		{
			offset.y -= _viewSize.height/this->getContainer()->getScaleY();
		}
		else
		{
			offset.y += _viewSize.height/this->getContainer()->getScaleY();
		}
		offset.x += _viewSize.width/this->getContainer()->getScaleX();

		endIdx   = this->_indexFromOffset(offset);
		if (endIdx == CC_INVALID_INDEX)
		{
			endIdx = countOfItems - 1;
		}

		if (!_cellsUsed.empty())
		{
			auto cell = _cellsUsed.at(0);
			idx = cell->getIdx();

			while(idx < startIdx)
			{
				this->_moveCellOutOfSight(cell);
				if (!_cellsUsed.empty())
				{
					cell = _cellsUsed.at(0);
					idx = cell->getIdx();
				}
				else
				{
					break;
				}
			}
		}
		if (!_cellsUsed.empty())
		{
			auto cell = _cellsUsed.back();
			idx = cell->getIdx();

			while(idx <= maxIdx && idx > endIdx)
			{
				this->_moveCellOutOfSight(cell);
				if (!_cellsUsed.empty())
				{
					cell = _cellsUsed.back();
					idx = cell->getIdx();
				}
				else
				{
					break;
				}
			}
		}

		for (long i = startIdx; i <= endIdx; i++)
		{
			if (_indices->find(i) != _indices->end())
			{
				continue;
			}
			this->updateCellAtIndex(i);
		}
	}

	/*********************** Touch events override ***********************/
	bool TableViewEx::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
	{
		if (!this->isVisible())
		{
			return false;
		}

		bool touchResult = ScrollView::onTouchBegan(pTouch, pEvent);

		if(_touches.size() == 1)
		{
			long index;
			Point point;

			point = this->getContainer()->convertTouchToNodeSpace(pTouch);

			index = this->_indexFromOffset(point);
			if (index == CC_INVALID_INDEX)
			{
				_touchedCell = NULL;
			}
			else
			{
				_touchedCell  = this->cellAtIndex(index);
			}

			if (_touchedCell && _tableViewDelegate != NULL)
			{
				_tableViewDelegate->tableCellHighlight(this, _touchedCell);
			}

			// add lua peertable function
#if CC_ENABLE_SCRIPT_BINDING
			if (_touchedCell && _tableViewScriptDelegate) {
				Vector<Ref*> pParams(2);
				pParams.pushBack(this);
				pParams.pushBack(_touchedCell);
				Vector<Ref*> pParamTypes(2);
				pParams.pushBack(__String::create("cc.TableView"));
				pParams.pushBack(__String::create("cc.TableViewCell"));
				LuaUtils::getInstance()->executePeertableFunction(this->_tableViewScriptDelegate, "tableCellHighlight", pParams, pParamTypes, false);
			}
#endif
		}
		else if (_touchedCell)
		{
			if(_tableViewDelegate != NULL)
			{
				_tableViewDelegate->tableCellUnhighlight(this, _touchedCell);
			}

			// add lua peertable function
#if CC_ENABLE_SCRIPT_BINDING
			if (_tableViewScriptDelegate) {
				Vector<Ref*> pParams(2);
				pParams.pushBack(this);
				pParams.pushBack(_touchedCell);
				Vector<Ref*> pParamTypes(2);
				pParams.pushBack(__String::create("cc.TableView"));
				pParams.pushBack(__String::create("cc.TableViewCell"));
				LuaUtils::getInstance()->executePeertableFunction(this->_tableViewScriptDelegate, "tableCellUnhighlight", pParams, pParamTypes, false);
			}
#endif

			_touchedCell = NULL;
		}

		return touchResult;
	}

	void TableViewEx::onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
	{
		ScrollView::onTouchMoved(pTouch, pEvent);

		if (_touchedCell && isTouchMoved())
		{
			if(_tableViewDelegate != NULL)
			{
				_tableViewDelegate->tableCellUnhighlight(this, _touchedCell);
			}
			// add lua peertable function
#if CC_ENABLE_SCRIPT_BINDING
			if (_tableViewScriptDelegate) {
				Vector<Ref*> pParams(2);
				pParams.pushBack(this);
				pParams.pushBack(_touchedCell);
				Vector<Ref*> pParamTypes(2);
				pParams.pushBack(__String::create("cc.TableView"));
				pParams.pushBack(__String::create("cc.TableViewCell"));
				LuaUtils::getInstance()->executePeertableFunction(this->_tableViewScriptDelegate, "tableCellUnhighlight", pParams, pParamTypes, false);
			}
#endif

			_touchedCell = NULL;
		}
	}

	void TableViewEx::onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
	{
		if (!this->isVisible()) {
			return;
		}

		if (_touchedCell){
			Rect bb = this->getBoundingBox();
			bb.origin = _parent->convertToWorldSpace(bb.origin);

			if (bb.containsPoint(pTouch->getLocation()) && _tableViewDelegate != NULL)
			{
				_tableViewDelegate->tableCellUnhighlight(this, _touchedCell);
				_tableViewDelegate->tableCellTouched(this, _touchedCell);
			}
			else if (bb.containsPoint(pTouch->getLocation()) && _tableViewScriptDelegate)
			{
				// add lua peertable function
#if CC_ENABLE_SCRIPT_BINDING
				if (_tableViewScriptDelegate) {
					Vector<Ref*> pParams(2);
					pParams.pushBack(this);
					pParams.pushBack(_touchedCell);
					Vector<Ref*> pParamTypes(2);
					pParams.pushBack(__String::create("cc.TableView"));
					pParams.pushBack(__String::create("cc.TableViewCell"));
					LuaUtils::getInstance()->executePeertableFunction(this->_tableViewScriptDelegate, "tableCellUnhighlight", pParams, pParamTypes, false);
					LuaUtils::getInstance()->executePeertableFunction(this->_tableViewScriptDelegate, "tableCellTouched", pParams, pParamTypes, false);
				}
#endif
			}

			_touchedCell = NULL;
		}

		ScrollView::onTouchEnded(pTouch, pEvent);
	}

	void TableViewEx::onTouchCancelled(Touch *pTouch, Event *pEvent)
	{
		ScrollView::onTouchCancelled(pTouch, pEvent);

		if (_touchedCell)
		{
			if(_tableViewDelegate != NULL)
			{
				_tableViewDelegate->tableCellUnhighlight(this, _touchedCell);
			}

			// add lua peertable function
#if CC_ENABLE_SCRIPT_BINDING
			if (_tableViewScriptDelegate) {
				Vector<Ref*> pParams(2);
				pParams.pushBack(this);
				pParams.pushBack(_touchedCell);
				Vector<Ref*> pParamTypes(2);
				pParams.pushBack(__String::create("cc.TableView"));
				pParams.pushBack(__String::create("cc.TableViewCell"));
				LuaUtils::getInstance()->executePeertableFunction(this->_tableViewScriptDelegate, "tableCellUnhighlight", pParams, pParamTypes, false);
			}
#endif

			_touchedCell = NULL;
		}
	}
}