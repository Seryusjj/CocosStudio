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
	layer->setTag(0);
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

void EditorScene3D::zoom(float delta)
{
	//increase or reduce the length in delta factor
	Vec3 vector = _cameraLookAtTarget - _camera->getPosition3D();
	float cameraDistance = (vector).length();
	Vec3 unitVector = (vector / cameraDistance);
	Vec3 finalPos = _camera->getPosition3D() + (unitVector * delta);
	_camera->setPosition3D(finalPos);
}

void EditorScene3D::pan(float deltaX, float deltaY)
{
	auto currentCamPos = _camera->getPosition3D();
	_camera->setPosition3D(Vec3(currentCamPos.x + deltaX, currentCamPos.y + deltaY, currentCamPos.z));
}

void EditorScene3D::rotateView(float x, float y)
{
	Vec3 newLookAtTarget = Vec3(x, y, 0) + _cameraLookAtTarget;
	_camera->lookAt(newLookAtTarget);
	_cameraLookAtTarget = newLookAtTarget;
}

void EditorScene3D::createAndAddCamera()
{
	CameraFlag cameraMask = CameraFlag::USER1;

	auto s = Director::getInstance()->getWinSize();
	Director::getInstance()->setClearColor(Color4F::WHITE);
	_camera = Camera::createPerspective(60, (GLfloat)s.width / s.height, 1, 1000);

	// set parameters for camera
	_camera->setPosition3D(Vec3(0, 20, 20));
	_cameraLookAtTarget = Vec3(0, 0, 0);
	_camera->lookAt(_cameraLookAtTarget, Vec3(0, 1, 0));

	addChild(_camera); //add camera to the scene
					  //Camera
	_camera->setCameraFlag(cameraMask);

	_currentCameraMask = (unsigned short)cameraMask;
}