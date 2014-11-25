#include "TitleSwitch.h"
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
		, _labels()
		, _allowLoop(true)
		, _currentIndex(0)
		, _inAction(false)
		, _actionDirection(0)
		, _kbdListener(nullptr)
		, _leftKey(0)
		, _rightKey(0)
	{
	}

	TitleSwitch::~TitleSwitch()
	{
	}

	TitleSwitch *TitleSwitch::create(cocos2d::Node *bg, const std::vector<const std::string> &titles)
	{
		auto pSwitch = new (std::nothrow) TitleSwitch();
		if (pSwitch && pSwitch->init(bg, titles))
		{
			pSwitch->autorelease();
			return pSwitch;
		}
		CC_SAFE_RELEASE(pSwitch);
		return nullptr;
	}

	bool TitleSwitch::init(cocos2d::Node *bg, const std::vector<const std::string> &titles)
	{
		CCASSERT(bg && titles.size() > 0, "Params error");

		this->addChild(bg);
		this->_titles = titles;

		this->setContentSize(bg->getContentSize());
		bg->setPosition(this->getContentSize().width * 0.5, this->getContentSize().height * 0.5);

		for (int i = 0; i < titles.size(); ++i)
		{
			auto pLabel = Label::createWithTTF(titles[i], "Helvetica", 12);
			pLabel->setColor(Color3B(0, 0, 0));
			// pLabel->setPosition(this->getContentSize().width * (0.5 + i), this->getContentSize().height * 0.5);
			this->_labels.pushBack(pLabel);
		}

		auto pRt = RenderTexture::create(this->getContentSize().width, this->getContentSize().height);
		// pRt->setPosition(bg->getPosition());
		this->addChild(pRt);

		this->needUpdate();
	}

	void TitleSwitch::needUpdate()
	{
		this->removeChildByTag(this->TITLE_TAG);
		Label *pCurrentLabel = _labels.at(_currentIndex);
		pCurrentLabel->setPosition(this->getContentSize().width * 0.5, this->getContentSize().height * 0.5);
		this->addChild(pCurrentLabel);
	}

	void TitleSwitch::onEnter()
	{
		auto pKbdListener = Win32EventListenerKeyboard::createWithTarget(this);
		pKbdListener->onWin32KeyDown = std::bind(&TitleSwitch::onKeyPressed, this, std::placeholders::_1);
		pKbdListener->setEventsSwallowed(true);
		Win32Notifier::getInstance()->addEventListener(pKbdListener);
		this->_kbdListener = pKbdListener;
	}

	void TitleSwitch::onExit()
	{
		if (this->_kbdListener)
		{
			Win32Notifier::getInstance()->removeEventListener(this->_kbdListener);
		}
	}

	void TitleSwitch::setTitles(const std::vector<const std::string> &titles)
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
			auto pLabel = Label::createWithTTF(titles[i], "Helvetica", 12);
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
			if (_currentIndex <= 0)
			{
				_currentIndex = _titles.size() - 1;
			}
			else
			{
				--_currentIndex;
			}
			_actionDirection = 1;
			this->shiftLeft();
		}
		else if (keyCode == _rightKey)
		{
			// loop mode is not open
			if (!_allowLoop && _currentIndex >= _titles.size() - 1)
			{
				return;
			}
			if (_currentIndex >= _titles.size() - 1)
			{
				_currentIndex = 0;
			}
			else
			{
				++_currentIndex;
			}
			_actionDirection = 2;
			this->shiftRight();
		}
	}

	void TitleSwitch::shiftLeft()
	{
		_inAction = true;
	}

	void TitleSwitch::shiftRight()
	{
		_inAction = true;
	}

	void TitleSwitch::visit(Renderer *renderer, const kmMat4& parentTransform, bool parentTransformUpdated)
	{
		glEnable(GL_SCISSOR_TEST);
		auto box = this->getBoundingBox();
		glScissor(box.origin.x, box.origin.y, box.size.width, box.size.height);
		Node::visit(renderer, parentTransform, parentTransformUpdated);
		glDisable(GL_SCISSOR_TEST);
	}
}