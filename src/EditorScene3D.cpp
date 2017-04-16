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
	Vec3 vector = _cameraLookAtTarget - _camera->getPosition3D();
	float cameraDistance = (vector).length();
	Vec3 unitVector = (vector / cameraDistance);
	Vec3 finalPos = _camera->getPosition3D() + (unitVector * delta);

	_camera->setPosition3D(_camera->getPosition3D().lerp(finalPos, 0.5f));
}

void EditorScene3D::pan(float deltaX, float deltaY)
{
	auto currentCamPos = _camera->getPosition3D();
	auto nextPos = Vec3(currentCamPos.x + deltaX, currentCamPos.y + deltaY, currentCamPos.z);

	_camera->setPosition3D(Vec3(currentCamPos.x + deltaX, currentCamPos.y + deltaY, currentCamPos.z));
}

void EditorScene3D::rotateView(float x, float y)
{
	Vec3 newLookAtTarget = Vec3(x, y, 0) + _cameraLookAtTarget;
	newLookAtTarget = newLookAtTarget.lerp(_cameraLookAtTarget, 0.2f);
	_camera->lookAt(newLookAtTarget);
	_cameraLookAtTarget = newLookAtTarget;
}

bool  canBeSelected(cocos2d::Node * node)
{
	//If it's not the grid, the node could be selected.
	auto casted = dynamic_cast<EditorGrid*>(node);
	if (casted == nullptr)
		return node->getName() != "ArrowSet";
	return casted == nullptr;
}

cocos2d::Node * EditorScene3D::select(float x, float y)
{
	_drawAABB->clear();
	auto lineColor = Color4F(0, 1, 0, 1);
	Node * selection = nullptr;
	//from
	Vec3 from = _camera->getPosition3D();

	Vec2 location(x, y);
	//Vec3 nearP(from.x, from.y, from.z), farP(location.x, location.y, -from.z);
	Vec3 nearP(location.x, location.y, 0.0f), farP(location.x, location.y, 1.0f);
	auto size = Director::getInstance()->getWinSize();
	_camera->unproject(size, &nearP, &nearP);
	_camera->unproject(size, &farP, &farP);
	Vec3 dir = farP - nearP;
	dir.normalize();
	Ray ray1(nearP, dir);

	//Ray ray(from, (finalDir).getNormalized());
	Vector<Node*>& children = this->getChildren();
	Vec3 corners[8];
	_drawAABB->drawLine(nearP, farP, lineColor);
	for (const auto& iter : children)
	{
		if (static_cast<Sprite3D*>(iter) != nullptr) {
			const AABB& aabb = static_cast<Sprite3D*>(iter)->getAABBRecursively();
			if (_camera->isVisibleInFrustum(&aabb) && canBeSelected(iter) && ray1.intersects(aabb))
			{
				aabb.getCorners(corners);
				selection = iter;
				_drawAABB->drawCube(corners, lineColor);
			}
		}
	}
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
	_camera->setPosition3D(Vec3(0, 20, 20));
	_cameraLookAtTarget = Vec3(0, 0, 0);
	_camera->lookAt(_cameraLookAtTarget, Vec3(0, 1, 0));

	addChild(_camera); //add camera to the scene
					  //Camera
	_camera->setCameraFlag(cameraMask);

	_currentCameraMask = (unsigned short)cameraMask;
}

void EditorScene3D::createAndAddReferenceArrows()
{
	//// add some objects
	auto sprite = Sprite3D::create("boss.obj", "boss.png");
	sprite->setName("boss");
	sprite->setOpacity(254);
	sprite->setScale(1.00f / sprite->getBoundingBox().size.width);//queremos con size 1
	sprite->setPosition3D(Vec3(0, 0, 0));
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