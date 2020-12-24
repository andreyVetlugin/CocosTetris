#pragma once
#include "TetrisFigure.h"
#include "FigureUIInfo.h"
#include "TextUIInfo.h"

namespace Tetris
{
	class InGameUILayer : public Layer
	{
	public:
		bool init();
		CREATE_FUNC(InGameUILayer);
		static const int FONT_SIZE = 40;
		static const std::string SYSTEM_FONT_TITLE;
	private:
		//InGameUILayer();
		void saveFigure(ShapeType figureType);
		FigureUIInfo* _holdFigure;
		FigureUIInfo* _nextFigure;
		TextUIInfo* _scoreForm;
	};
}
