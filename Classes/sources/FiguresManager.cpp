#include "FiguresManager.h"
#include <CCEventDispatcher.h>

namespace Tetris
{
	MapTetrisFigure* FiguresManager::spawnNextFigure()
	{
		auto shape = FigureShape(_nextFigureType);
		previousFigureTypesCount[shape.getShapeType()]++;
		_nextFigureType = defineNextFigureType();
		auto figure = MapTetrisFigure::create(shape, _startFigurePosition);
		figure->setPosition(_startFigurePosition * Map::CELL_LENGTH);

		return figure;
	}

	FiguresManager::FiguresManager()
	{
		for (int typeInt = static_cast<int>(ShapeType::J); typeInt <= static_cast<int>(ShapeType::S); typeInt++)
		{
			previousFigureTypesCount[static_cast<ShapeType>(typeInt)] = 0;
		}
		_nextFigureType = defineNextFigureType();
	}

	MapTetrisFigure* FiguresManager::swapWithLastSaveFigure(const MapTetrisFigure* figure)
	{
		//auto typeForReturnFigure = _savedShapeType.has_value() ? _savedShapeType.value() : _nextFigureType;
		MapTetrisFigure* outputFigure;
		if (!_savedShapeType.has_value())
		{
			outputFigure = spawnNextFigure();
		}
		else
		{
			outputFigure = MapTetrisFigure::create(FigureShape(_savedShapeType.value()), _startFigurePosition);
			outputFigure->setPosition(_startFigurePosition * Map::CELL_LENGTH);
		}
		_savedShapeType = figure->getShapeType();

		return outputFigure;
	}

	ShapeType FiguresManager::defineNextFigureType()
	{
		auto type = std::min_element(previousFigureTypesCount.begin(), previousFigureTypesCount.end(), [](const auto& l, const auto& r) {return l.second < r.second; });

		EventCustom nextFigureDefinedEvent("nextFigureDefined");
		nextFigureDefinedEvent.setUserData(&*(type));
		Director::getInstance()->getEventDispatcher()->dispatchEvent(&nextFigureDefinedEvent);
		// нет ли ub ? 
		return (*type).first;
	}
}
