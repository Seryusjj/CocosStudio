#include "stdafx.h"

#include "EditorScene3D.h"
#include "EditorGrid.h"
USING_NS_CC;

Scene* EditorScene3D::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = EditorScene3D::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool EditorScene3D::init()
{
	//////////////////////////////
	// 1. super init first
	if (!LayerColor::init())
	{
		return false;
	}
	auto s = Director::getInstance()->getWinSize();
	Director::getInstance()->setClearColor(Color4F::WHITE);
	Camera* camera = Camera::createPerspective(60, (GLfloat)s.width / s.height, 1, 1000);

	// set parameters for camera
	camera->setPosition3D(Vec3(0, 10, 20));
	camera->lookAt(Vec3(0, 0, 0), Vec3(0, 1, 0));

	addChild(camera); //add camera to the scene
					  //Camera
	auto light = AmbientLight::create(Color3B::WHITE);
	addChild(light);

	camera->setCameraFlag(CameraFlag::USER1);

	//// add "HelloWorld" splash screen"
	auto sprite = Sprite3D::create("orc.c3b");

	//// position the sprite on the center of the screen
	sprite->setPosition3D(Vec3(0, 0, 0));
	//sprite->setScale(1, 1);

	//// add the sprite as a child to this layer
	this->addChild(sprite, 0);

	this->addChild(EditorGrid::create());
	this->setCameraMask((unsigned short)CameraFlag::USER1, true);
	return true;
}