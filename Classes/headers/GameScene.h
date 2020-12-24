#pragma once
#include "cocos2d.h"
#include "TetrisField.h"
#include "InGameUILayer.h"
namespace Tetris
{
	class GameScene : public cocos2d::Layer
	{
	public:
		static cocos2d::Scene* createScene();
		virtual bool init();

		CREATE_FUNC(GameScene);
	private:
		void endGame(const std::size_t score);
		void openMainMenu();
		void exitGame();
		void startNewGame();
		//TetrisField* gameField;
		//cocos2d::Layer* dashBoard;
	};
}
