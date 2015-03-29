#include "ActionColorTo.h"

#include <new>

using namespace std;
using namespace cocos2d;

namespace framework
{
	ActionColorTo *ActionColorTo::create(float duration, const cocos2d::Color3B &targetColor)
	{
		auto pRet = new (nothrow)ActionColorTo();
		if (pRet && pRet->init(duration, targetColor))
		{
			pRet->autorelease();
			return pRet;
		}
		CC_SAFE_RELEASE(pRet);
		return nullptr;
	}

	bool ActionColorTo::init(float duration, const cocos2d::Color3B &targetColor)
	{
		if (!ActionInterval::initWithDuration(duration))
		{
			return false;
		}

		_targetColor = targetColor;

		return true;
	}

	ActionColorTo *ActionColorTo::clone() const
	{
		auto pCopy = new (nothrow)ActionColorTo();
		if (pCopy && pCopy->init(_duration, _targetColor))
		{
			pCopy->autorelease();
			return pCopy;
		}
		CC_SAFE_RELEASE(pCopy);
		return nullptr;
	}

	ActionColorTo *ActionColorTo::reverse() const
	{
		return ActionColorTo::create(_duration, Color3B::WHITE);
	}

	void ActionColorTo::startWithTarget(cocos2d::Node *target)
	{
		ActionInterval::startWithTarget(target);
		_previousColor = _startColor = target->getColor();
		_deltaColor = Color3B(_targetColor.r - _startColor.r, _targetColor.g - _startColor.g, _targetColor.b - _startColor.b);
	}

	void ActionColorTo::update(float dt)
	{
#if CC_ENABLE_STACKABLE_ACTIONS
		Color3B currentColor = _target->getColor();
		Color3B diff = Color3B(currentColor.r - _previousColor.r, currentColor.g - _previousColor.g, currentColor.b - _previousColor.b);
		_startColor = Color3B(_startColor.r + diff.r, _startColor.g + diff.g, _startColor.b + diff.b);
		Color3B newColor = Color3B(_startColor.r + floor(_deltaColor.r * dt), _startColor.g + floor(_deltaColor.g * dt), _startColor.b + floor(_deltaColor.b * dt));
		_target->setColor(newColor);
		_previousColor = newColor;
#else
		_target->setPosition(_startPosition + _positionDelta * t);
#endif
	}
}