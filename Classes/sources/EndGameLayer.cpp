#include "EndGameLayer.h"
#include "TextUIInfo.h"
#include "ui/CocosGUI.h"
#include "InGameUILayer.h"

USING_NS_CC;
namespace Tetris
{
	bool EndGameLayer::init()
	{
		if (!Layer::init())
		{
			return false;
		}

		auto scoreInfo = TextUIInfo::create("Game Over, finally score:", std::to_string(_finalScore));
		auto okButton = ui::Button::create();
		scoreInfo->setPosition(0, 150);
		okButton->setTitleText("Ok");
		okButton->setPosition({ 0,-80 });
		okButton->setTitleFontSize(InGameUILayer::FONT_SIZE);
		okButton->addClickEventListener
		(
			[=](Ref* ref)
			{
				EventCustom toMainMenu("toMainMenu");
				_eventDispatcher->dispatchEvent(&toMainMenu);
			}
		);

		this->addChild(scoreInfo);
		this->addChild(okButton);
		return true;
	}

	EndGameLayer* EndGameLayer::create(std::size_t score)
	{
		EndGameLayer* pRet = new(std::nothrow) EndGameLayer(score);
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

	EndGameLayer::EndGameLayer(std::size_t score) :_finalScore(score)
	{}
}
