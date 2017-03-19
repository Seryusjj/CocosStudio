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
	createAndAddCamera();

	//add grid
	auto grid = EditorGrid::create();
	grid->setGlobalZOrder(-1);
	this->addChild(grid);
	grid->setCameraMask(_currentCameraMask, true);

	//// add some objects
	auto sprite = Sprite3D::create("boss.obj", "boss.png");
	sprite->setName("boss");
	sprite->setOpacity(254);
	sprite->setScale(1.00f / sprite->getBoundingBox().size.width);//queremos con size 1
	sprite->setPosition3D(Vec3(0, 0, 0));
	auto width = sprite->getBoundingBox().size;
	this->addChild(sprite);

	sprite->setCameraMask(_currentCameraMask, true);
	this->setCameraMask(_currentCameraMask, true);
	return true;
}

void EditorScene3D::createAndAddCamera()
{
	CameraFlag cameraMask = CameraFlag::USER1;

	auto s = Director::getInstance()->getWinSize();
	Director::getInstance()->setClearColor(Color4F::WHITE);
	Camera* camera = Camera::createPerspective(60, (GLfloat)s.width / s.height, 1, 1000);

	// set parameters for camera
	camera->setPosition3D(Vec3(0, 3, 3));
	camera->lookAt(Vec3(0, 0, 0), Vec3(0, 1, 0));

	addChild(camera); //add camera to the scene
					  //Camera
	camera->setCameraFlag(cameraMask);

	_currentCameraMask = (unsigned short)cameraMask;
}