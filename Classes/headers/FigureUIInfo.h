#pragma once
#include <cocos2d.h>
#include "MapTetrisFigure.h"
#include <optional>
USING_NS_CC;

namespace Tetris
{
	class FigureUIInfo : public Node
	{
	public:
		bool init() override;
		void setTitle(const std::string& newTitle);
		std::string getTitle()const;
		void setFigureType(ShapeType type);
		std::optional<ShapeType> getFigureType() const;
		FigureUIInfo(std::string title);
		static FigureUIInfo* create(std::string title);
	private:
		Label* _titleLabel;
		MapTetrisFigure* _figure;
	};
}

