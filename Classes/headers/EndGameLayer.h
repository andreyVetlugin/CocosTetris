#pragma once
#include <cocos2d.h>

USING_NS_CC;
namespace Tetris 
{
	class EndGameLayer : public Layer
	{
	public:
		bool init();
		static EndGameLayer* create(std::size_t finalScore);
	private:
		EndGameLayer(std::size_t finalScore);
		std::size_t _finalScore;
	};
}

