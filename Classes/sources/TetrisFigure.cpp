#include "TetrisFigure.h"

void Tetris::TetrisFigure::rotate()
{
	this->_shape.rotate();
}

const FigureShape& Tetris::TetrisFigure::getShape() const 
{
	return _shape;
}

ShapeType Tetris::TetrisFigure::getShapeType() const
{
	return _shape.getShapeType();
}

Tetris::TetrisFigure::TetrisFigure(FigureShape shape):_shape(shape)
{
}

