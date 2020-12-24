#pragma once
#include "TetrisFigure.h"

namespace Tetris
{
	class MapTetrisFigure :
		public Node, public TetrisFigure
	{
	public:
		const std::vector<Vec2> getAbsolutelyMapShapeCoords() const;
		bool tryMove(int dx, int dy, const Map& map);
		bool collisionOccurred(const Map& map) const;
		bool tryRotate(const Map& map);

		bool init() override;
		static MapTetrisFigure* create(FigureShape shape,const Vec2& startPositionin);
		static MapTetrisFigure* create(const MapTetrisFigure& other);
	private:
		bool blockedUnder(const Map& map) const;
		bool initSprites();
		MapTetrisFigure(FigureShape shape, const Vec2& startPosition);
		//SpriteFigureShape _shape; spriteMap
		std::vector<Sprite*> _spriteMap;
		Vec2 _coordinate;
	};
}

