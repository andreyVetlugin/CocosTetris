#pragma once
#include <cocos/2d/CCDrawNode.h>
#include "cocos2d.h"
USING_NS_CC;
namespace Tetris {
	class Map
	{
	public:
		const Sprite* getCellValue(int x, int y) const;
		const Sprite* getCellValue(const Vec2& coord)const;
		void setCellValue(int x, int y, Sprite* value);
		void setCellValue(const Vec2& coord, Sprite* value);
		void dropLine(int lineIndex);
		//std::unique_ptr<const Vec2> getMapCellRectangle(int x, int y);
		//std::unique_ptr<const Vec2> getMapCellRectangle(Vec2 coords);
		static const std::string FIGURE_CELL_SPRITE_PATH;
		static const std::string MAP_CELL_SPRITE_PATH;
		static const int FIELD_MAP_WIDTH = 10;
		static const int FIELD_MAP_HEIGHT = 20;
		static const int CELL_LENGTH = 16;

	private:
		std::array<Sprite*, Map::FIELD_MAP_WIDTH* Map::FIELD_MAP_HEIGHT>cells;
	};
}

