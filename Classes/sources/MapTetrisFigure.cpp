#include "MapTetrisFigure.h"
#include "Map.h"
#include "FigureShape.h"

namespace Tetris
{
	bool MapTetrisFigure::blockedUnder(const Map& map) const
	{
		for (const auto& coord : getAbsolutelyMapShapeCoords())
		{
			if (coord.y == 0 || map.getCellValue(Vec2(coord.x, coord.y - 1)) != nullptr)
				return true;
		}
		return false;
	}

	bool MapTetrisFigure::collisionOccurred(const Map& map) const
	{
		for (const auto& coord : getAbsolutelyMapShapeCoords())
		{
			if (!(coord.x >= 0 && coord.x < Map::FIELD_MAP_WIDTH
				&& coord.y >= 0 && coord.y < Map::FIELD_MAP_HEIGHT)) // out of map
				return true;
			if (map.getCellValue(coord) != nullptr)
				return true;
		}
		return false;
	}

	bool MapTetrisFigure::initSprites()
	{
		for (const auto& coord : TetrisFigure::_shape.getCellsCoords())
		{
			//if (!Node::init())//????!?!?!??!?! нужно ли 
			//{
			//	return false;
			//}
			auto sprite = Sprite::create(Map::MAP_CELL_SPRITE_PATH, Rect(0, 0, Map::CELL_LENGTH, Map::CELL_LENGTH));
			sprite->setPosition(coord * Map::CELL_LENGTH);
			sprite->setAnchorPoint({ 0, 0 });
			_spriteMap.push_back(sprite);
			this->addChild(sprite);
		}
		return true;
	}

	const std::vector<Vec2> MapTetrisFigure::getAbsolutelyMapShapeCoords() const
	{
		std::vector<Vec2> output;
		output.reserve(_shape.getCellsCoords().size());
		for (const auto& coord : _shape.getCellsCoords())
		{
			output.push_back(Vec2(coord.x + _coordinate.x, coord.y + _coordinate.y));
		}
		return output;
	}

	bool MapTetrisFigure::tryRotate(const Map& map)
	{
		auto shapeBackUp = _shape;
		TetrisFigure::rotate();
		if (this->collisionOccurred(map))
		{
			_shape = shapeBackUp;
			return false;
		}
		for (int i = 0; i < _spriteMap.size(); i++)
		{
			_spriteMap[i]->setPosition(_shape.getCellsCoords()[i] * Map::CELL_LENGTH);
		}
		return true;
	}

	bool MapTetrisFigure::init()
	{
		return (initSprites());
	}

	bool MapTetrisFigure::tryMove(int dx, int dy, const Map& map)
	{
		_coordinate += Vec2(dx, dy);
		if (collisionOccurred(map))
		{
			_coordinate -= Vec2(dx, dy);
			return false;
		}
		this->setPosition(_coordinate * Map::CELL_LENGTH);
		return true;
	}

	MapTetrisFigure* MapTetrisFigure::create(FigureShape shape,const Vec2& startPosition)
	{
		MapTetrisFigure* pRet = new(std::nothrow) MapTetrisFigure(shape, startPosition);
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

	MapTetrisFigure* MapTetrisFigure::create(const MapTetrisFigure& otherFigure)
	{
		auto shape = FigureShape(otherFigure.getShape().getCellsCoords());
		auto startPosition = otherFigure._coordinate;
		MapTetrisFigure* pRet = new(std::nothrow) MapTetrisFigure(shape, startPosition);
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


	MapTetrisFigure::MapTetrisFigure(FigureShape shape,const Vec2& startPosition) :TetrisFigure(shape)
	{
		_coordinate = startPosition;
		this->setPosition(startPosition);
	}
}
