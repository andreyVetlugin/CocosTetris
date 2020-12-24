#pragma once
#include "cocos2d.h"

USING_NS_CC;
enum class ShapeType 
{
	J = 0,
	I,
	O,
	L,
	Z,
	T,
	S,
	Undefined
};
class FigureShape
{
public:
	void rotate();
	ShapeType getShapeType() const;
	FigureShape(const ShapeType& type);
	FigureShape(const std::vector<Vec2>& coords);
	const std::vector<Vec2>& getCellsCoords()const;
	// visitor ??
private:
	std::vector<Vec2> _cellsCoords; /// изменить на свой класс intPoint ? 
	ShapeType _shapeType;
	static const std::vector<Vec2> rotateOrder;
	static const std::unordered_map<ShapeType, std::vector<Vec2>> shapesForEachType;
}; 