#include "GameScene.h"
#include "EndGameLayer.h"
#include "MainMenuLayer.h"

USING_NS_CC;
namespace Tetris
{
	Scene* GameScene::createScene()
	{
		auto scene = Scene::create();
		auto layer = GameScene::create();
		scene->addChild(layer);
		return scene;
	}

	bool GameScene::init()
	{
		if (!Layer::init())
			return false;

		openMainMenu();

		auto toMainMenuListener = EventListenerCustom::create("toMainMenu", [=](EventCustom* event)
			{
				openMainMenu();
			});

		auto endGameListener = EventListenerCustom::create("endGame", [=](EventCustom* event)
			{
				auto score = static_cast<const std::size_t*>(event->getUserData());
				endGame(*score);
			});

		auto startNewGameListener = EventListenerCustom::create("startGame", [=](EventCustom* event)
			{
				startNewGame();
			}
		);

		auto exitGameEvent = EventListenerCustom::create("exitGame", [=](EventCustom* event)
			{
				exitGame();
			});

		_eventDispatcher->addEventListenerWithSceneGraphPriority(toMainMenuListener, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(endGameListener, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(startNewGameListener, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(exitGameEvent, this);

		return true;
	}

	void GameScene::endGame(const std::size_t score)
	{
		this->removeAllChildren();

		auto endGameLayer = EndGameLayer::create(score);
		endGameLayer->setPosition(Director::getInstance()->getWinSize()/2);
		this->addChild(endGameLayer);
	}
	void GameScene::openMainMenu()
	{
		this->removeAllChildren();

		auto menu = MainMenuLayer::create();
		menu->setPosition(Director::getInstance()->getWinSize() / 2);
		this->addChild(menu);
	}
	void GameScene::exitGame()
	{
		Director::getInstance()->end();
	}
	void GameScene::startNewGame()
	{
		this->removeAllChildren();

		auto gameField = TetrisField::create();
		auto uiLayer = InGameUILayer::create();
		this->addChild(uiLayer);
		this->addChild(gameField);

		gameField->setScale(2);
		gameField->setAnchorPoint({ 0,0 });
		gameField->setPosition(320, 0);
	}
}
