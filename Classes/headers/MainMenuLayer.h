#pragma once
#include "cocos2d.h"

USING_NS_CC;
namespace Tetris
{
	class MainMenuLayer :public Layer
	{
	public:
		bool init() override;
		CREATE_FUNC(MainMenuLayer);
	};
}

