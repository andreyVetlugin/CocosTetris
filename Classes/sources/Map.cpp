#include "Map.h"

const Sprite* Tetris::Map::getCellValue(int x, int y) const
{
	return cells[y * FIELD_MAP_WIDTH + x];
}

const Sprite* Tetris::Map::getCellValue(const Vec2& coord) const
{
	return cells[coord.y * FIELD_MAP_WIDTH + coord.x];
}

void Tetris::Map::setCellValue(int x, int y, Sprite* value)
{
	cells[y * FIELD_MAP_WIDTH + x] = value;
}

void Tetris::Map::setCellValue(const Vec2& coord, Sprite* value)
{
	cells[coord.y * FIELD_MAP_WIDTH + coord.x] = value;
}

void Tetris::Map::dropLine(int lineIndex)
{
	for (int x = 0; x < Map::FIELD_MAP_WIDTH; x++)
	{
		cells[x + lineIndex * FIELD_MAP_WIDTH]->removeFromParent();
	}
	for (int y = lineIndex; y < Map::FIELD_MAP_HEIGHT - 1; y++)
	{
		for (int x = 0; x < Map::FIELD_MAP_WIDTH; x++)
		{
			if (cells[x + (y + 1) * FIELD_MAP_WIDTH] != nullptr)
			{
				cells[x + (y + 1) * FIELD_MAP_WIDTH]->setPosition(x * CELL_LENGTH, y * CELL_LENGTH);
			}
			cells[x + y * FIELD_MAP_WIDTH] = cells[x + (y + 1) * FIELD_MAP_WIDTH];
		}
	}
}


//const Sprite* Tetris::Map::FIGURE_CELL_SPRITE = Sprite::create("HelloWorld.png", Rect(0, 0, 64, 64));
//const Sprite* Tetris::Map::MAP_CELL_SPRITE = Sprite::create("redSquare.png", Rect(0, 0, 64, 64));

const std::string Tetris::Map::FIGURE_CELL_SPRITE_PATH = "greenSquare.png";
const std::string Tetris::Map::MAP_CELL_SPRITE_PATH = "redSquare.png";


