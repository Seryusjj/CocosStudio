#include "stdafx.h"
#include "EditorScene.h"

USING_NS_CC;

Scene* EditorScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = EditorScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool EditorScene::init()
{
	//////////////////////////////
	// 1. super init first
    if (!LayerColor::initWithColor(cocos2d::Color4B::RED))
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//// add "HelloWorld" splash screen"
    //auto sprite = Sprite::create("HelloWorld.png");

	//// position the sprite on the center of the screen
    //sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    //sprite->setScale(1, 1);

	//// add the sprite as a child to this layer
    //this->addChild(sprite, 0);

	return true;
}
