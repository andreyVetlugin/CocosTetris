#pragma once
#include "FigureShape.h"
#include "Map.h"

namespace Tetris
{

	class TetrisFigure
	{
	public:
		void rotate();
		TetrisFigure(FigureShape shape);
		TetrisFigure() = delete;
		const FigureShape& getShape() const;
		ShapeType getShapeType() const;
	protected:
		FigureShape _shape;
	};

}
