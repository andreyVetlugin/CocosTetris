#include "MainMenuLayer.h"
#include "ui/CocosGUI.h"
#include "InGameUILayer.h"

namespace Tetris
{
	bool MainMenuLayer::init()
	{
		if (!Layer::init())
			return false;

		auto startGameButton = ui::Button::create();
		startGameButton->setPosition({ 0,100 });
		startGameButton->setTitleText("Start game");
		startGameButton->setTitleFontSize(InGameUILayer::FONT_SIZE);
		auto test = ui::Widget();

		startGameButton->addClickEventListener([=](Ref* ref)
			{
				EventCustom startGame("startGame");
				_eventDispatcher->dispatchEvent(&startGame);
			}
		);


		auto endGameButton = ui::Button::create();
		endGameButton->setPosition({ 0,-20 });
		endGameButton->setTitleText("Exit");
		endGameButton->setTitleFontSize(InGameUILayer::FONT_SIZE);

		endGameButton->addClickEventListener([=](Ref* ref)
			{
				EventCustom exitGame("exitGame");
				_eventDispatcher->dispatchEvent(&exitGame);
			}
		);
	
		this->addChild(startGameButton);
		this->addChild(endGameButton);
		return true;
	}
}
