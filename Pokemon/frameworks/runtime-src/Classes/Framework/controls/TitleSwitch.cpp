#include "TitleSwitch.h"
#include "../lua/LuaUtils.h"
#include "../Win32/Win32EventListenerKeyboard.h"
#include "../win32/Win32Notifier.h"
#include <new>

using namespace cocos2d;
using namespace std;

namespace framework
{
	TitleSwitch::TitleSwitch()
		: _bg(nullptr)
		, _titles()
		, _ttfPath()
		, _labels()
		, _allowLoop(true)
		, _currentIndex(0)
		, _currentTitle(nullptr)
		, _swapTitle(nullptr)
		, _inAction(false)
		, _duration(0.5f)
		, _kbdListener(nullptr)
		, _leftKey(0)
		, _rightKey(0)
	{
	}

	TitleSwitch::~TitleSwitch()
	{
	}

	TitleSwitch *TitleSwitch::create(cocos2d::Node *bg, const std::vector<std::string> &titles, const std::string &ttfFile)
	{
		auto pSwitch = new (std::nothrow) TitleSwitch();
		if (pSwitch && pSwitch->init(bg, titles, ttfFile))
		{
			pSwitch->autorelease();
			return pSwitch;
		}
		CC_SAFE_RELEASE(pSwitch);
		return nullptr;
	}

	bool TitleSwitch::init(cocos2d::Node *bg, const std::vector<std::string> &titles, const std::string &ttfFile)
	{
		CCASSERT(bg && titles.size() > 0, "Params error");

		this->addChild(bg);
		this->_bg = bg;
		this->_titles = titles;
		this->_ttfPath = ttfFile;

		this->setContentSize(bg->getContentSize());
		bg->setPosition(this->getContentSize().width * 0.5, this->getContentSize().height * 0.5);

		for (int i = 0; i < titles.size(); ++i)
		{
			auto pLabel = Label::createWithTTF(titles[i], ttfFile, 12);
			pLabel->setColor(Color3B(0, 0, 0));
			// pLabel->setPosition(this->getContentSize().width * (0.5 + i), this->getContentSize().height * 0.5);
			this->_labels.pushBack(pLabel);
		}

		this->needUpdate();

		return true;
	}

	void TitleSwitch::needUpdate()
	{
		if (this->_currentTitle)
		{
			this->removeChildByTag(this->TITLE_TAG);
		}
		Label *pCurrentLabel = _labels.at(_currentIndex);
		pCurrentLabel->setPosition(this->getContentSize().width * 0.5, this->getContentSize().height * 0.5);
		this->addChild(pCurrentLabel, 0, this->TITLE_TAG);
		this->_currentTitle = pCurrentLabel;
	}

	void TitleSwitch::onEnter()
	{
		auto pKbdListener = Win32EventListenerKeyboard::createWithTarget(this);
		pKbdListener->onWin32KeyDown = std::bind(&TitleSwitch::onKeyPressed, this, std::placeholders::_1);
		pKbdListener->setEventsSwallowed(true);
		Win32Notifier::getInstance()->addEventListener(pKbdListener);
		this->_kbdListener = pKbdListener;

		Node::onEnter();
	}

	void TitleSwitch::onExit()
	{
		if (this->_kbdListener)
		{
			Win32Notifier::getInstance()->removeEventListener(this->_kbdListener);
		}

		Node::onExit();
	}

	void TitleSwitch::setTitles(const std::vector<std::string> &titles)
	{
		CCASSERT(titles.size() > 0, "Params error");

		this->_titles = titles;
		for (const auto &lbl : _labels)
		{
			lbl->removeFromParent();
		}
		_labels.clear();

		for (int i = 0; i < titles.size(); ++i)
		{
			auto pLabel = Label::createWithTTF(titles[i], _ttfPath, 12);
			pLabel->setColor(Color3B(0, 0, 0));
			// pLabel->setPosition(this->getContentSize().width * (0.5 + i), this->getContentSize().height * 0.5);
			this->_labels.pushBack(pLabel);
		}

		this->needUpdate();
	}

	void TitleSwitch::setBackgroundNode(cocos2d::Node *bg)
	{
		CCASSERT(bg, "Params error");

		if (this->_bg)
		{
			this->_bg->removeFromParent();
		}
		this->_bg = bg;
		bg->setPosition(this->getContentSize().width * 0.5, this->getContentSize().height * 0.5);
		this->needUpdate();
	}

	void TitleSwitch::setTitleColor(const cocos2d::Color3B &color)
	{
		for (const auto &lbl : _labels)
		{
			lbl->setColor(color);
		}

		this->needUpdate();
	}

	void TitleSwitch::setTitleFontSize(int size)
	{
		for (const auto &lbl : _labels)
		{
			lbl->setSystemFontSize(size);
		}

		this->needUpdate();
	}

	void TitleSwitch::setTitleFontName(const std::string &fontName)
	{
		for (const auto &lbl : _labels)
		{
			lbl->setSystemFontName(fontName);
		}

		this->needUpdate();
	}

	void TitleSwitch::setAllowLoop(bool allowLoop)
	{
		this->_allowLoop = allowLoop;
	}

	void TitleSwitch::setResponseKeys(int leftKey, int rightKey)
	{
		this->_leftKey = leftKey;
		this->_rightKey = rightKey;
	}

	void TitleSwitch::setEventsSwallowed(bool isSwallowed)
	{
		if (this->_kbdListener)
		{
			this->_kbdListener->setEventsSwallowed(isSwallowed);
		}
	}

	void TitleSwitch::onKeyPressed(int keyCode)
	{
		if (_inAction || _titles.size() < 2)
		{
			return;
		}
		if (keyCode == _leftKey)
		{
			// loop mode is not open
			if (!_allowLoop && _currentIndex <= 0)
			{
				return;
			}
			int newIndex = (_currentIndex - 1 + _titles.size()) % _titles.size();
#if CC_ENABLE_SCRIPT_BINDING
			if (_scriptType == kScriptTypeLua)
			{
				// params
				Vector<Ref*> pParams(2);
				pParams.pushBack(__Integer::create(_currentIndex));
				pParams.pushBack(__Integer::create(newIndex));
				// param types
				Vector<Ref*> pTypes(2);
				pTypes.pushBack(__String::create("__Integer"));
				pTypes.pushBack(__String::create("__Integer"));
				LuaUtils::getInstance()->executePeertableFunction(this, "onShiftLeft", pParams, pTypes, false);
			}
#endif
			_currentIndex = newIndex;
			this->shiftLeft();
		}
		else if (keyCode == _rightKey)
		{
			// loop mode is not open
			if (!_allowLoop && _currentIndex >= _titles.size() - 1)
			{
				return;
			}
			int newIndex = (_currentIndex + 1) % _titles.size();
#if CC_ENABLE_SCRIPT_BINDING
			if (_scriptType == kScriptTypeLua)
			{
				// params
				Vector<Ref*> pParams(2);
				pParams.pushBack(__Integer::create(_currentIndex));
				pParams.pushBack(__Integer::create(newIndex));
				// param types
				Vector<Ref*> pTypes(2);
				pTypes.pushBack(__String::create("__Integer"));
				pTypes.pushBack(__String::create("__Integer"));
				LuaUtils::getInstance()->executePeertableFunction(this, "onShiftRight", pParams, pTypes, false);
			}
#endif
			_currentIndex = newIndex;
			this->shiftRight();
		}
	}

	void TitleSwitch::shiftLeft()
	{
		Label *pLeft = nullptr, *pCurrentTitle = nullptr;
		pLeft = _labels.at(_currentIndex);
		pLeft->setPosition(-this->getContentSize().width * 0.5, this->getContentSize().height * 0.5);
		this->addChild(pLeft);
		pCurrentTitle = _labels.at((_currentIndex + 1) % _titles.size());
		this->_swapTitle = pCurrentTitle;
		auto spawnAction = Spawn::create(TargetedAction::create(pLeft, MoveBy::create(_duration, Point(this->getContentSize().width, 0))), TargetedAction::create(pCurrentTitle, MoveBy::create(_duration, Point(this->getContentSize().width, 0))), nullptr);
		auto action = Sequence::create(spawnAction, CallFunc::create(std::bind(&TitleSwitch::endAction, this)), nullptr);
		_inAction = true;
		this->runAction(action);
		_currentTitle = pLeft;
	}

	void TitleSwitch::shiftRight()
	{
		Label *pRight = nullptr, *pCurrentTitle = nullptr;
		pRight = _labels.at(_currentIndex);
		pRight->setPosition(this->getContentSize().width * 1.5, this->getContentSize().height * 0.5);
		this->addChild(pRight);
		pCurrentTitle = _labels.at((_currentIndex - 1 + _titles.size()) % _titles.size());
		this->_swapTitle = pCurrentTitle;
		auto spawnAction = Spawn::create(TargetedAction::create(pRight, MoveBy::create(_duration, Point(-this->getContentSize().width, 0))), TargetedAction::create(pCurrentTitle, MoveBy::create(_duration, Point(-this->getContentSize().width, 0))), nullptr);
		auto action = Sequence::create(spawnAction, CallFunc::create(std::bind(&TitleSwitch::endAction, this)), nullptr);
		_inAction = true;
		this->runAction(action);
		_currentTitle = pRight;
	}

	void TitleSwitch::endAction()
	{
		if (this->_swapTitle)
		{
			this->_swapTitle->removeFromParent();
			this->_swapTitle = nullptr;
		}
		this->_inAction = false;
	}

	void TitleSwitch::visit(Renderer *renderer, const kmMat4& parentTransform, bool parentTransformUpdated)
	{
		// old style
		/*glEnable(GL_SCISSOR_TEST);
		auto box = this->getBoundingBox();
		glScissor(box.origin.x, box.origin.y, box.size.width, box.size.height);
		Node::visit(renderer, parentTransform, parentTransformUpdated);
		glDisable(GL_SCISSOR_TEST);*/

		_beforeVisitCmdScissor.init(_globalZOrder);
		_beforeVisitCmdScissor.func = [this] {
			glEnable(GL_SCISSOR_TEST);
			auto box = this->getBoundingBox();
			Director::getInstance()->getOpenGLView()->setScissorInPoints(box.origin.x, box.origin.y, box.size.width, box.size.height);
		};
		renderer->addCommand(&_beforeVisitCmdScissor);

		Node::visit(renderer, parentTransform, parentTransformUpdated);

		_afterVisitCmdScissor.init(_globalZOrder);
		_afterVisitCmdScissor.func = [this] {
			glDisable(GL_SCISSOR_TEST);
		};
		renderer->addCommand(&_afterVisitCmdScissor);
	}
}