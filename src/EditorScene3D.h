#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "stdafx.h"

class EditorScene3D : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(EditorScene3D);

protected:
	virtual void createAndAddCamera();
	unsigned short _currentCameraMask;
};

#endif // __HELLOWORLD_SCENE_H__
