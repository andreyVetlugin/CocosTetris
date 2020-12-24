#include "AppDelegate.h"
#include "GameScene.h"
USING_NS_CC;

AppDelegate::AppDelegate() {
}
AppDelegate::~AppDelegate()
{
}
bool AppDelegate::applicationDidFinishLaunching() {
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
		glview = GLViewImpl::create("Cocos Tetris");
		glview->setFrameSize(960,640);
		director->setOpenGLView(glview);
	}
	auto scene = Tetris::GameScene::createScene();
	director->runWithScene(scene);
	return true;
}
void AppDelegate::applicationDidEnterBackground() {
}
void AppDelegate::applicationWillEnterForeground() {
}