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
        /**
         * TableViewEx constructor.
         */
		explicit TableViewEx();
        /**
         * TableViewEx destructor.
         */
		virtual ~TableViewEx();
        
        /**
         * Create a table view.
         */
        CREATE_FUNC(TableViewEx);

        /**
         * Create a TableViewEx control.
         *
         * @param dataSource TableView datasource.
         * @param viewSize TableView visible size.
         *
         * @return A new TableViewEx object.
         */
		static TableViewEx *create(cocos2d::extension::TableViewDataSource *dataSource, cocos2d::Size viewSize);
		
        /**
         * Get delegate used in script.
         *
         * @return Return the script delegate.
         */
		cocos2d::Ref *getScriptDelegate() const;
        /**
         * Set delegate used in script.
         *
         * @param scriptDelegate Target script delegate.
         */
		void setScriptDelegate(cocos2d::Ref *scriptDelegate);

		/**
         * TableView events overrides.
         */
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