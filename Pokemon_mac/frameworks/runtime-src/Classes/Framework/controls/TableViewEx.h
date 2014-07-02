/******************************
Description: TableView extension, to support some lua functions
Author: M.Wan
Date: 6/20/2014
******************************/

#ifndef __CONTROLS_TABLEVIEWEX__
#define __CONTROLS_TABLEVIEWEX__

#include "cocos2d.h"
#include "cocos-ext.h"

namespace framework
{
	class TableViewEx : public cocos2d::extension::TableView
	{
	public:
		explicit TableViewEx();
		virtual ~TableViewEx();

		static TableViewEx *create(cocos2d::extension::TableViewDataSource *dataSource, cocos2d::Size viewSize);
		
		cocos2d::Ref *getScriptDelegate() const;
		void setScriptDelegate(cocos2d::Ref *scriptDelegate);

		/* override some events, to add some peertable executions */
		virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view) override;
		virtual bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) override;
		virtual void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) override;
		virtual void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) override;
		virtual void onTouchCancelled(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) override;

	protected:
		cocos2d::Ref *_tableViewScriptDelegate;
	};
}

#endif