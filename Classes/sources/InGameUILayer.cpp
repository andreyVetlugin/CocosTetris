#include "InGameUILayer.h"

namespace Tetris
{
	bool InGameUILayer::init()
	{
		if (!Layer::init())
		{
			return false;
		}

		auto draw = DrawNode::create();
		draw->drawLine({ 320,0 }, { 320,640 }, Color4F::WHITE);
		auto test = Director::getInstance();
		auto test2 = test->getWinSize();
		draw->drawLine({ 640,0 }, { 640,640 }, Color4F::WHITE);
		this->addChild(draw);

		_holdFigure = FigureUIInfo::create("Hold");
		_holdFigure->setPosition(160, 600);
		_nextFigure = FigureUIInfo::create("Next");
		_nextFigure->setPosition(760, 600);
		_scoreForm = TextUIInfo::create("Score", "0");
		_scoreForm->setPosition(160, 320);

		this->addChild(_holdFigure);
		this->addChild(_scoreForm);
		this->addChild(_nextFigure);

		auto onLinesDroped= EventListenerCustom::create("scoreChanged", [=](EventCustom* event)
			{
				const size_t* newScore = static_cast<const size_t*>(event->getUserData());
				if (newScore != nullptr)
					_scoreForm->setValue(std::to_string(*newScore));
			});

		auto onHoldFigure = EventListenerCustom::create("figureHold", [=](EventCustom* event)
			{
				const ShapeType* type = static_cast<ShapeType*>(event->getUserData());
				if (type != nullptr)
					saveFigure(*type);
			});

		auto onNextFigureDefine = EventListenerCustom::create("nextFigureDefined", [=](EventCustom* event)
			{
				const ShapeType* type = static_cast<ShapeType*>(event->getUserData());
				if (type != nullptr)
					_nextFigure->setFigureType(*type);
			});

		_eventDispatcher->addEventListenerWithSceneGraphPriority(onLinesDroped,this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(onHoldFigure, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(onNextFigureDefine, this);
		return true;
	}

	void InGameUILayer::saveFigure(ShapeType figureType)
	{
		_holdFigure->setFigureType(figureType);
	}

	const std::string InGameUILayer::SYSTEM_FONT_TITLE = "Arial";
}

