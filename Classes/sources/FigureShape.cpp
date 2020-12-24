#include "FigureShape.h"


void FigureShape::rotate()
{
	if (_shapeType == ShapeType::Undefined)
		return;

	if (_shapeType == ShapeType::O)
	{
		return;
	}
	if (_shapeType == ShapeType::I)
	{
		auto findedCoord = std::find(_cellsCoords.begin(), _cellsCoords.end(), Vec2(0, -2));
		if (findedCoord == _cellsCoords.end())
			findedCoord = std::find(_cellsCoords.begin(), _cellsCoords.end(), Vec2(-2, 0));
		if (findedCoord != _cellsCoords.end())
			*findedCoord = Vec2(findedCoord->y, findedCoord->x);
	}
	for (auto& coord : _cellsCoords)
	{
		auto findedCoord = std::find(rotateOrder.begin(), rotateOrder.end(), coord);
		if (findedCoord != rotateOrder.end())
		{
			auto diff = rotateOrder.end() - findedCoord;
			if (diff <= 2)
				findedCoord = rotateOrder.begin() + 2 - diff;
			else
				findedCoord += 2;
			coord = *findedCoord;
		}
	}
}

ShapeType FigureShape::getShapeType() const
{
	return _shapeType;
}

FigureShape::FigureShape(const ShapeType& type):_shapeType(type)
{
	_cellsCoords = FigureShape::shapesForEachType.at(type);
}

FigureShape::FigureShape(const std::vector<Vec2>& coords):_shapeType(ShapeType::Undefined),_cellsCoords(coords)
{
}

const std::vector<Vec2>& FigureShape::getCellsCoords() const 
{
	return _cellsCoords;
}

const std::vector<Vec2> FigureShape::rotateOrder = { {1,1},{1,0},{1,-1} ,{0,-1},{-1,-1},{-1,0},{-1,1}, {0,1} };
const std::unordered_map<ShapeType, std::vector<Vec2>> FigureShape::shapesForEachType =
{ {ShapeType::J,{{0,1},{0,0},{0,-1},{-1,-1}}},
  {ShapeType::L,{{0,1},{0,0},{0,-1},{1,-1}}},
  {ShapeType::T,{{0,1},{0,0},{-1,0},{1,0}}},
  {ShapeType::S,{{1,1},{0,1},{0,0},{-1,0}}},
  {ShapeType::Z,{{-1,1},{0,1},{0,0},{1,0}}},
  {ShapeType::O,{{1,1},{0,1},{0,0},{1,0}}},
  {ShapeType::I,{{0,-2},{0,1},{0,0},{0,-1}}}};

