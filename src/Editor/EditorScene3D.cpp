#include "stdafx.h"

#include "EditorScene3D.h"
#include "EditorGrid.h"
#include "DrawNode3D.h"
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
	createAndAddCamera();//at first
	_drawAABB = DrawNode3D::create();
	_drawAABB->retain();
	addChild(_drawAABB);
	//add grid
	auto grid = EditorGrid::create();
	this->addChild(grid);
	grid->setCameraMask(_currentCameraMask, true);

	//at end
	createAndAddReferenceArrows();

	this->setCameraMask(_currentCameraMask, true);
	return true;
}

void EditorScene3D::zoom(float delta)
{
	//increase or reduce the length in delta factor
	Vec3 camPosition = _camera->getPosition3D();
	Vec3 direction = _cameraLookAtTarget - camPosition;
	direction.normalize();

	Vec3 finalPos = camPosition + (direction * delta);

	_camera->setPosition3D(_camera->getPosition3D().lerp(finalPos, 0.5f));

	Vec3 diff = _camera->getPosition3D() - camPosition;
	_cameraLookAtTarget += diff;
	_camera->lookAt(_cameraLookAtTarget);
}

void EditorScene3D::pan(float deltaX, float deltaY)
{
	Vec3 currentCamPos = _camera->getPosition3D();
	Vec3 camDirection = _cameraLookAtTarget - currentCamPos;

	camDirection.cross(_cameraUp);
	camDirection.normalize();

	//pan of cam pos
	Vec3 next = currentCamPos + (deltaY * _cameraUp);
	next = next + (deltaX * camDirection);

	//pan look at target to keep this info up to date
	_cameraLookAtTarget += (deltaY * _cameraUp);
	_cameraLookAtTarget += (deltaX * camDirection);

	//camDirection is the pan direction
	_camera->setPosition3D(next);
	_camera->lookAt(_cameraLookAtTarget);
}

void EditorScene3D::rotateView(float deltaX, float deltaY)
{
	Vec3 currentCamPos = _camera->getPosition3D();

	Vec3 camDirection = _cameraLookAtTarget - currentCamPos;
	camDirection.cross(_cameraUp);
	camDirection.normalize();

	_cameraLookAtTarget += (deltaY * _cameraUp);
	_cameraLookAtTarget += (deltaX * camDirection);

	_camera->lookAt(_cameraLookAtTarget);
}

bool  canBeSelected(cocos2d::Node * node)
{
	//If it's not the grid, the node could be selected.
	auto casted = dynamic_cast<EditorGrid*>(node);
	if (casted == nullptr)
		return node->getName() != "ArrowSet";
	return casted == nullptr;
}

cocos2d::Sprite3D * getIntersected(Ray& ray1, Node* parent)
{
	for (int i = 0; i < parent->getChildren().size(); i++)
	{
		Sprite3D* toEval = static_cast<Sprite3D*>(parent->getChildren().at(i));
		const AABB& aabb = toEval->getAABBRecursively();
		if (ray1.intersects(aabb) && canBeSelected(toEval))
		{
			return toEval;
		}
	}

	for (int i = 0; i < parent->getChildren().size(); i++)
	{
		return getIntersected(ray1, parent->getChildren().at(i));
	}

	return nullptr;
}

cocos2d::Node * EditorScene3D::select(float x, float y)
{
	_drawAABB->clear();

	auto lineColor = Color4F(0, 1, 0, 1);
	Node * selection = nullptr;
	Vec3 from = _camera->getPosition3D();
	Vec2 location(x, y);
	Vec3 nearP(location.x, location.y, 0.0f), farP(location.x, location.y, 1.0f);

	auto size = Director::getInstance()->getWinSize();
	_camera->unproject(size, &nearP, &nearP);
	_camera->unproject(size, &farP, &farP);
	Vec3 dir = farP - nearP;
	dir.normalize();
	Ray ray1(nearP, dir);

	Vector<Node*>& children = this->getChildren();
	Vec3 corners[8];
	Sprite3D * selected = getIntersected(ray1, this);
	if (selected != nullptr)
	{
		selected->getAABB().getCorners(corners);
		_drawAABB->drawCube(corners, lineColor);
	}
	selection = selected;

	return selection;
}

void EditorScene3D::removeBoundingBox(Node * node)
{
}

void EditorScene3D::addBoundingBox(Node * node)
{
}

void EditorScene3D::createAndAddCamera()
{
	CameraFlag cameraMask = CameraFlag::USER1;

	auto s = Director::getInstance()->getWinSize();
	Director::getInstance()->setClearColor(Color4F(0.2f, 0.2f, 0.2f, 1));

	_camera = Camera::createPerspective(60, (GLfloat)s.width / s.height, 0.1f, 2000);

	// set parameters for camera
	_camera->setPosition3D(Vec3(0, 1, 20));
	_cameraLookAtTarget = Vec3::ZERO;
	_cameraUp = Vec3::UNIT_Y;
	_camera->lookAt(_cameraLookAtTarget, _cameraUp);

	addChild(_camera); //add camera to the scene

	_camera->setCameraFlag(cameraMask);

	_currentCameraMask = (unsigned short)cameraMask;
}

void EditorScene3D::createAndAddReferenceArrows()
{
	//// add some objects
	auto sprite = Sprite3D::create("boss.obj", "boss.png");
	sprite->setName("boss");
	//sprite->setOpacity(254);
	sprite->setScale(1.00f / sprite->getBoundingBox().size.width);//queremos con size 1
	sprite->setPosition3D(Vec3(0, -sprite->getBoundingBox().size.height*0.5f, 0));
	auto width = sprite->getBoundingBox().size;
	this->addChild(sprite);
	
	auto arrowSet = Sprite3D::create();
	arrowSet->setName("ArrowSet");

	auto arrowX = Sprite3D::create("arrow.obj");
	arrowX->setName("ArrowX");
	auto arrowY = Sprite3D::create("arrow.obj");
	arrowY->setName("Arrow-y");
	auto arrowZ = Sprite3D::create("arrow.obj");
	arrowZ->setName("ArrowZ");

	arrowSet->addChild(arrowX);
	arrowSet->addChild(arrowY);
	arrowSet->addChild(arrowZ);

	arrowSet->setScale(1.00f / arrowZ->getBoundingBox().size.width);

	arrowX->setRotation3D(Vec3(0, 0, 90));
	arrowX->setColor(Color3B::RED);
	arrowX->setPosition3D(Vec3(0, 0, 0));

	arrowY->setRotation3D(Vec3(0, 0, 0));
	arrowY->setColor(Color3B::GREEN);
	arrowY->setPosition3D(Vec3(0, 0, 0));

	arrowZ->setRotation3D(Vec3(90, 0, 0));
	arrowZ->setColor(Color3B::BLUE);
	arrowZ->setPosition3D(Vec3(0, 0, 0));

	arrowSet->setPosition3D(Vec3(0, 0, 0));
	//arrowSet->setGlobalZOrder(-1);
	arrowX->setGlobalZOrder(1);
	arrowY->setGlobalZOrder(2);
	arrowZ->setGlobalZOrder(3);
	sprite->setGlobalZOrder(4);
	//addChild(arrowSet);
}