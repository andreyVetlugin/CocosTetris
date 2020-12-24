#pragma once
#include "FiguresManager.h"
#include <cocos/2d/CCDrawNode.h>
#include "Map.h"

USING_NS_CC;
namespace Tetris
{
	class TetrisField : public cocos2d::Layer
	{
	public:
		//static Scene* createScene();
		bool init() override;
		void update(float) override;

		CREATE_FUNC(TetrisField);

	private:
		FiguresManager _figuresManager;
		MapTetrisFigure* _currentFigure;
		MapTetrisFigure* _shadeForCurrentFigure;
		std::size_t _score = 0;
		Map _tetrisMap;
		std::array<size_t, 4>_increasingScoreByLinesDropedCount = { 200,500,900,1400 };


		void bringShadeUpToDate();
		bool setNewFigure();
		void makeCurrentFigurePartOfMap();
		void increaseScoreByLinesDropedCount(int linesCount);
		void onFigureFall();

		std::vector<int> FindFullFillLines() const;
		void endGame();
		void saveCurrentFigureToHold();
		void onPressedKeyboardHandler(EventKeyboard::KeyCode keyCode, Event* event);

		int _figureSpeed = 1;
		float _tickTimeElapsed = 0;
		const float _timeForTick = 0.5;
		bool _savedForCurrentFigure = false;
	};
}

