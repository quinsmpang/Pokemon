#include "CursorTextField.h"

using namespace cocos2d;
using namespace std;

namespace framework
{
	const static float DELTA = 0.5f;
	const static float BLINK_SPEED = 0.25f;

	CursorTextField::CursorTextField()
		: TextFieldTTF()
		, _beginPos(Point(0, 0))
		, _cursorSprite(nullptr)
		, _cursorAction(nullptr)
		, _cursorPos(Point(0, 0))
		, _inputText(nullptr)
	{
	}

	CursorTextField::~CursorTextField()
	{
		CC_SAFE_DELETE(this->_inputText);
	}

	void CursorTextField::onEnter()
	{
		TextFieldTTF::onEnter();

		auto pListener = EventListenerTouchOneByOne::create();
		pListener->setSwallowTouches(true);
		pListener->onTouchBegan = CC_CALLBACK_2(CursorTextField::onTouchBegan, this);
		pListener->onTouchEnded = CC_CALLBACK_2(CursorTextField::onTouchEnded, this);
		this->_eventDispatcher->addEventListenerWithSceneGraphPriority(pListener, this);

		this->setDelegate(this);
	}

	void CursorTextField::onExit()
	{
		TextFieldTTF::onExit();
		this->_eventDispatcher->removeAllEventListeners();
	}

	CursorTextField *CursorTextField::create(const std::string &placeholder, const std::string &fontName, float fontSize)
	{
		auto pField = new CursorTextField();

		if (pField && pField->initWithPlaceHolder(placeholder, fontName, fontSize))
		{
			pField->initCursorSprite(fontSize);
			pField->autorelease();

			return pField;
		}

		CC_SAFE_RELEASE_NULL(pField);
		return nullptr;
	}

	void CursorTextField::initCursorSprite(int height)
	{
		// draw cursor sprite
		int column = 4;
		// is (64, 4) a suitable size?
		int pixels[64][4];
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < column; j++)
			{
				pixels[i][j] = 0xffffffff;
			}
		}

		// initialize cursor sprite
		auto pTexture = new Texture2D();
		pTexture->initWithData(pixels, 64 * 4, Texture2D::PixelFormat::RGB888, 1, 1, Size(column, height));
		this->_cursorSprite = Sprite::createWithTexture(pTexture);
		auto fieldSize = this->getContentSize();
		this->_cursorPos = Point(0, fieldSize.height * 0.5);
		this->_cursorSprite->setPosition(_cursorPos);
		this->addChild(_cursorSprite);

		// cursor blink action
		this->_cursorAction = RepeatForever::create((ActionInterval*)Sequence::createWithTwoActions(FadeOut::create(BLINK_SPEED), FadeIn::create(BLINK_SPEED)));

		this->_cursorSprite->runAction(_cursorAction);
		this->_inputText = new string();
	}

	bool CursorTextField::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
	{
		_beginPos = touch->getLocation();

		return true;
	}

	void CursorTextField::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
	{
		Point endPos = touch->getLocation();

		// judge whether it is click event
		if (::abs(endPos.x - _beginPos.x) > DELTA || ::abs(endPos.y - _beginPos.y))
		{
			// not click event
			_beginPos.x = _beginPos.y = -1;

			return;
		}

		// whether to open or close IME
		isInTextField(touch) ? openIME() : closeIME();
	}

	const Rect &CursorTextField::getFieldRegion()
	{
		Size fieldSize = this->getContentSize();

		// is it the same as getBoundingBox()?
		return Rect(-fieldSize.width * 0.5, -fieldSize.height * 0.5, fieldSize.width, fieldSize.height);
	}

	bool CursorTextField::isInTextField(Touch *touch)
	{
		return this->getFieldRegion().containsPoint(convertTouchToNodeSpaceAR(touch));
	}

	bool CursorTextField::onTextFieldAttachWithIME(cocos2d::TextFieldTTF * sender)
	{
		if (_inputText->empty())
		{
			return false;
		}

		_cursorSprite->setPositionX(this->getContentSize().width);

		return false;
	}

	bool CursorTextField::onTextFieldDetachWithIME(cocos2d::TextFieldTTF * sender)
	{
		return false;
	}

	bool CursorTextField::onTextFieldInsertText(cocos2d::TextFieldTTF * sender, const char * text, size_t nLen)
	{
		_inputText->append(text);
		this->setString(*_inputText);

		_cursorSprite->setPositionX(this->getContentSize().width);

		return true;
	}

	bool CursorTextField::onTextFieldDeleteBackward(cocos2d::TextFieldTTF * sender, const char * delText, size_t nLen)
	{
		_inputText->resize(_inputText->size() - nLen);
		this->setString(*_inputText);

		_cursorSprite->setPositionX(this->getContentSize().width);

		if (_inputText->empty())
		{
			_cursorSprite->setPositionX(0);
		}

		return false;
	}

	void CursorTextField::openIME()
	{
		_cursorSprite->setVisible(true);
		this->attachWithIME();
	}

	void CursorTextField::closeIME()
	{
		_cursorSprite->setVisible(false);
		this->detachWithIME();
	}

	void CursorTextField::addChild(Node *child, int zOrder, int tag)
	{
		CCASSERT( child != nullptr, "Argument must be non-nil");
		CCASSERT( child->getParent() == nullptr, "child already added. It can't be added again");

		if (_children.empty())
		{
			this->childrenAlloc();
		}

		this->insertChild(child, zOrder);

		child->setTag(tag);

		child->setParent(this);
		child->setOrderOfArrival(s_globalOrderOfArrival++);

		if( _running )
		{
			child->onEnter();
			// prevent onEnterTransitionDidFinish to be called twice when a node is added in onEnter
			if (_isTransitionFinished) {
				child->onEnterTransitionDidFinish();
			}
		}

		if (_cascadeColorEnabled)
		{
			updateCascadeColor();
		}

		if (_cascadeOpacityEnabled)
		{
			updateCascadeOpacity();
		}
	}
}