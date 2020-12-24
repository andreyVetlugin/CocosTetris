#pragma once
#include "MapTetrisFigure.h"
#include <optional>

namespace Tetris
{
	class FiguresManager
	{
	public:
		MapTetrisFigure* spawnNextFigure();
		FiguresManager();
		MapTetrisFigure* swapWithLastSaveFigure(const MapTetrisFigure* figure);
	private:
		std::unordered_map<ShapeType, int> previousFigureTypesCount;
		ShapeType defineNextFigureType();
		std::optional<ShapeType> _savedShapeType;
		ShapeType _nextFigureType;
		const Vec2 _startFigurePosition = Vec2(Map::FIELD_MAP_WIDTH / 2, Map::FIELD_MAP_HEIGHT - 2);
		//chances
	};
}
