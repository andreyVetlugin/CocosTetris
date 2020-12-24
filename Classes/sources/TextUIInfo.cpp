#include "TextUIInfo.h"
#include "InGameUILayer.h"

namespace Tetris
{
	bool TextUIInfo::init()
	{
		this->addChild(_titleLabel);
		this->addChild(_valueLabel);
		_titleLabel->setPosition(0, 0);
		_valueLabel->setPosition(0, -80);
		return true;
	}

	void TextUIInfo::setTitle(const std::string& newTitle)
	{
		_titleLabel->setString(newTitle);
	}

	std::string TextUIInfo::getTitle() const
	{
		return _titleLabel->getString();
	}

	std::string TextUIInfo::getValue() const
	{
		return _valueLabel->getString();
	}

	TextUIInfo::TextUIInfo(const std::string& title, const std::string& startValue)
	{
		_titleLabel = Label::createWithSystemFont(title,InGameUILayer::SYSTEM_FONT_TITLE ,InGameUILayer::FONT_SIZE);
		_valueLabel = Label::createWithSystemFont(startValue, InGameUILayer::SYSTEM_FONT_TITLE,InGameUILayer::FONT_SIZE);
	}

	void TextUIInfo::setValue(const std::string& newValue)
	{
		_valueLabel->setString(newValue);
	}

	TextUIInfo* TextUIInfo::create(const std::string& title, const std::string& startValue)
	{
		TextUIInfo* pRet = new(std::nothrow) TextUIInfo(title, startValue);
		if (pRet && pRet->init())
		{
			pRet->autorelease();
			return pRet;
		}
		else
		{
			delete pRet;
			pRet = nullptr;
			return nullptr;
		}
	}
}
