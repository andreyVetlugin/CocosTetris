#include "TetrisField.h"

USING_NS_CC;
namespace Tetris
{
	//Scene* TetrisField::createScene()
	//{
	//	auto scene = Scene::create();
	//	auto layer = TetrisField::create();
	//	scene->addChild(layer);
	//	return scene;
	//}

	bool TetrisField::init()
	{
		if (!Layer::init())
		{
			return false;
		}
		_score = 0;
		this->scheduleUpdate();

		auto eventListener = EventListenerKeyboard::create();
		eventListener->onKeyPressed =
			[=](EventKeyboard::KeyCode code, Event* event) {TetrisField::onPressedKeyboardHandler(code, event); };

		this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);

		return true;
	}

	void TetrisField::bringShadeUpToDate()
	{
		if (!_currentFigure)
		{
			return;
		}
		if (_shadeForCurrentFigure)
		{
			this->removeChild(_shadeForCurrentFigure);
		}
		_shadeForCurrentFigure = MapTetrisFigure::create(*_currentFigure);
		_shadeForCurrentFigure->setPosition(_currentFigure->getPosition());
		while (_shadeForCurrentFigure->tryMove(0, -1, _tetrisMap));
		for (auto& child : _shadeForCurrentFigure->getChildren())
		{
			child->setOpacity(100);
		}
		this->addChild(_shadeForCurrentFigure);
	}

	bool TetrisField::setNewFigure()
	{
		_savedForCurrentFigure = false;
		_currentFigure = _figuresManager.spawnNextFigure();
		this->addChild(_currentFigure);
		if (_currentFigure->collisionOccurred(_tetrisMap))
		{
			endGame();
			return false;
		}
		bringShadeUpToDate();
		return true;
	}

	void TetrisField::makeCurrentFigurePartOfMap()
	{
		for (const auto& coord : _currentFigure->getAbsolutelyMapShapeCoords())
		{
			auto sprite = Sprite::create(Map::FIGURE_CELL_SPRITE_PATH, Rect(0, 0, Map::CELL_LENGTH, Map::CELL_LENGTH));
			sprite->setPosition(coord * Map::CELL_LENGTH);
			sprite->setAnchorPoint({ 0,0 });
			this->addChild(sprite);
			_tetrisMap.setCellValue(coord, sprite);
		}
		this->removeChild(_currentFigure);
		_currentFigure = nullptr;
	}

	void TetrisField::endGame()
	{
		EventCustom endGameEvent("endGame");
		endGameEvent.setUserData(&_score);
		_eventDispatcher->dispatchEvent(&endGameEvent);
	}

	void TetrisField::increaseScoreByLinesDropedCount(int linesCount)
	{
		_score += _increasingScoreByLinesDropedCount[linesCount - 1];

		EventCustom increaseScoreEvent("scoreChanged");
		increaseScoreEvent.setUserData(&_score);
		_eventDispatcher->dispatchEvent(&increaseScoreEvent);
	}

	void TetrisField::onFigureFall()
	{
		makeCurrentFigurePartOfMap();
		auto filledLines = FindFullFillLines();

		if (!filledLines.empty())
		{
			size_t linesCount = filledLines.size();

			increaseScoreByLinesDropedCount(linesCount);
			for (auto lineIndexIt = filledLines.rbegin(); lineIndexIt != filledLines.rend(); lineIndexIt++)
			{
				_tetrisMap.dropLine(*lineIndexIt);
			}
		}
		setNewFigure();
	}

	std::vector<int> TetrisField::FindFullFillLines() const /// проверять только те линии, которые могли быть изменены, т.е. где y из absolyteCoord
	{
		std::vector<int> filledLinesIndexes;
		for (int y = 0; y < Map::FIELD_MAP_HEIGHT; y++)
		{
			for (int x = 0; x < Map::FIELD_MAP_WIDTH; x++)
			{
				if (_tetrisMap.getCellValue(x, y) != nullptr)
				{
					if (x == Map::FIELD_MAP_WIDTH - 1)
						filledLinesIndexes.push_back(y);
				}
				else
				{
					break;
				}
			}
		}
		return filledLinesIndexes;
	}

	void TetrisField::update(float delta)
	{
		_tickTimeElapsed += delta;
		if (_tickTimeElapsed < _timeForTick)
		{
			return;
		}
		if (_currentFigure)
		{
			if (!_currentFigure->tryMove(0, -1, _tetrisMap))
				onFigureFall();
		}
		else
		{
			setNewFigure();
		}
		_tickTimeElapsed = 0;
	}

	void TetrisField::saveCurrentFigureToHold()
	{
		ShapeType saveType = _currentFigure->getShapeType();

		MapTetrisFigure* prevFigure;
		_savedForCurrentFigure = true;
		prevFigure = _currentFigure;
		_currentFigure = _figuresManager.swapWithLastSaveFigure(_currentFigure);
		this->removeChild(prevFigure);
		this->addChild(_currentFigure);

		EventCustom figureHoldEvent("figureHold");
		figureHoldEvent.setUserData(&saveType);
		_eventDispatcher->dispatchEvent(&figureHoldEvent);
	}

	void TetrisField::onPressedKeyboardHandler(EventKeyboard::KeyCode keyCode, Event* event)
	{
		Vec2 loc = event->getCurrentTarget()->getPosition();
		if (!_currentFigure)
			return;
		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		case EventKeyboard::KeyCode::KEY_A:
			_currentFigure->tryMove(-1, 0, _tetrisMap);
			bringShadeUpToDate();
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		case EventKeyboard::KeyCode::KEY_D:
			_currentFigure->tryMove(1, 0, _tetrisMap);
			bringShadeUpToDate();
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		case EventKeyboard::KeyCode::KEY_S:
			_currentFigure->tryMove(0, -1, _tetrisMap);
			bringShadeUpToDate();
			break;
		case EventKeyboard::KeyCode::KEY_C:
			if (!_savedForCurrentFigure)
			{
				saveCurrentFigureToHold();
			}
			break;
		case EventKeyboard::KeyCode::KEY_Z:
			_currentFigure->tryRotate(_tetrisMap);
			bringShadeUpToDate();
			break;
		case EventKeyboard::KeyCode::KEY_ESCAPE:
			endGame();
			break;
		case EventKeyboard::KeyCode::KEY_SPACE:
			while (_currentFigure->tryMove(0, -1, _tetrisMap))
				;
			onFigureFall();
			_tickTimeElapsed = 0;
			break;
		}
	}
}