/* For test */

#ifndef __TEST_H__
#define __TEST_H__

#include "cocos2d.h"

class TestScene : public cocos2d::Layer
{
public:
	CREATE_FUNC(TestScene);

	static cocos2d::Scene *scene();

	virtual bool init();

	void onBtnClick(void *pParam);
	void onKbdPressed(cocos2d::EventKeyboard::KeyCode keyCode, void *pParam);
};

#endif