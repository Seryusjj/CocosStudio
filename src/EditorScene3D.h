#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "stdafx.h"

class EditorScene3D : public cocos2d::LayerColor
{
private:
	cocos2d::Camera* _camera;
	cocos2d::Vec3 _cameraLookAtTarget;
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void zoom(float delta);
	virtual void pan(float deltaX, float deltaY);
	virtual void rotateView(float x, float y);
	// implement the "static create()" method manually
	CREATE_FUNC(EditorScene3D);

protected:
	virtual void createAndAddCamera();
	unsigned short _currentCameraMask;
};

#endif // __HELLOWORLD_SCENE_H__
