#include "ActionParabola.h"
#include <new>

using namespace cocos2d;
using namespace std;

namespace framework
{
	ActionParabola *ActionParabola::create(float duration, float a, float h, float k, float x1, float x2)
	{
		auto pAction = new (nothrow) ActionParabola();
		if (pAction && pAction->init(duration, a, h, k, x1, x2))
		{
			pAction->autorelease();
			return pAction;
		}
		CC_SAFE_RELEASE(pAction);
		return nullptr;
	}

	bool ActionParabola::init(float duration, float a, float h, float k, float x1, float x2)
	{
		if (abs(a) < 0.001)
		{
			return false;
		}
		if (!ActionInterval::initWithDuration(duration))
		{
			return false;
		}
		_a = a;
		_h = h;
		_k = k;
		_x1 = x1;
		_x2 = x2;
		// calculate perimeter from x1 to x2.
		/* y = a * (x - h) ^ 2 + k
		* dy = 2 * a * x * dx
		* dl = sqrt(dx ^ 2 + dy ^ 2) = sqrt(dx ^ 2 + 4 * a * a * x * x * dx ^ 2) = sqrt(4 * a * a * x * x + 1) * dx
		* l = integration(x1 -> x2) sqrt(4 * a * a * x * x + 1) dx
		*/
		return true;
	}

	ActionParabola *ActionParabola::clone() const
	{
		auto pCopy = new (nothrow) ActionParabola();
		if (pCopy && pCopy->init(_duration, _a, _h, _k, _x1, _x2))
		{
			pCopy->autorelease();
			return pCopy;
		}
		return nullptr;
	}

	ActionParabola *ActionParabola::reverse() const
	{
		return ActionParabola::create(_duration, _a, _h, _k, _x2, _x1);
	}

	void ActionParabola::startWithTarget(Node *target)
	{
		ActionInterval::startWithTarget(target);
		target->setPosition(_x1, _a * (_x1 - _h) * (_x1 - _h) + _k);
		_previousPosition = _startPosition = target->getPosition();
	}

	void ActionParabola::update(float t)
	{
		if (_target)
		{
#if CC_ENABLE_STACKABLE_ACTIONS
			Point currentPos = _target->getPosition();
			Point diff = currentPos - _previousPosition;
			_startPosition = _startPosition + diff;
			Point newPos = _startPosition + (Point(0.01f, 0.01f) * t);
			_target->setPosition(newPos);
			_previousPosition = newPos;
#else
			_target->setPosition(_startPosition + _positionDelta * t);
#endif
		}
	}
}