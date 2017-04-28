#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "stdafx.h"
#include "DrawNode3D.h"

class EditorScene3D : public cocos2d::LayerColor
{
private:
	cocos2d::Camera* _camera;
	cocos2d::DrawNode3D*             _drawAABB;
	cocos2d::DrawNode3D*             _grid;
	cocos2d::Vec3 _cameraLookAtTarget;
	cocos2d::Vec3 _cameraUp;
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void zoom(float delta);
	virtual void pan(float deltaX, float deltaY);
	virtual void rotateView(float x, float y);
	virtual cocos2d::Node* select(float x, float y);
	virtual void removeBoundingBox(Node* node);
	virtual void addBoundingBox(Node* node);

	// implement the "static create()" method manually
	CREATE_FUNC(EditorScene3D);

protected:
	virtual void createAndAddCamera();
	virtual void createAndAddReferenceArrows();
	unsigned short _currentCameraMask;
};

#endif // __HELLOWORLD_SCENE_H__
