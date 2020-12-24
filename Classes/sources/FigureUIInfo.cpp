#include "FigureUIInfo.h"
#include "InGameUILayer.h"

namespace Tetris {
	bool FigureUIInfo::init()
	{
		this->addChild(_titleLabel);
		_titleLabel->setPosition(0, 0);
		return true;
	}

	void FigureUIInfo::setTitle(const std::string& newTitle)
	{
		_titleLabel->setString(newTitle);
	}

	std::string FigureUIInfo::getTitle() const
	{
		return _titleLabel->getString();
	}

	void FigureUIInfo::setFigureType(ShapeType type)
	{
		if (_figure)
		{
			this->removeChild(_figure);
		}

		_figure = MapTetrisFigure::create(FigureShape(type), { 0, 0 });
		_figure->setPosition(0, -100);
		this->addChild(_figure);
	}

	std::optional<ShapeType> FigureUIInfo::getFigureType() const
	{
		return _figure != nullptr ? _figure->getShapeType() : std::optional<ShapeType>();
	}

	FigureUIInfo* FigureUIInfo::create(std::string title)
	{
		FigureUIInfo* pRet = new(std::nothrow) FigureUIInfo(title);
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

	FigureUIInfo::FigureUIInfo(std::string title)
	{
		_titleLabel = Label::createWithSystemFont(title, InGameUILayer::SYSTEM_FONT_TITLE, InGameUILayer::FONT_SIZE);
	}
}
