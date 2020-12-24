#pragma once
#include <cocos2d.h>

USING_NS_CC;
namespace Tetris{
	class TextUIInfo : public Node
	{
	public:
		bool init() override;
		void setTitle(const std::string& newTitle);
		std::string getTitle()const;
		std::string getValue()const;
		void setValue(const std::string& newValue);
		static TextUIInfo* create(const std::string& title, const std::string& startValue);

	private:
		TextUIInfo(const std::string& title, const std::string& startValue);
		Label* _titleLabel;
		Label* _valueLabel;
	};

}
