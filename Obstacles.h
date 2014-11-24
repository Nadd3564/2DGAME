#pragma once

#ifndef __Obstacles__
#define __Obstacles__

#include <iostream>
#include "GameObject.h"

USING_NS_CC;

class Obstacles : public GameObject
{
public:
	Obstacles(GameLayer* game);
	~Obstacles();
	virtual void stateUpdate();
	static Obstacles* create(int obstacle, cocos2d::CCPoint pos, float angle);
    b2BodyDef ObsBodyDef(Obstacles* wisp);
	b2FixtureDef ObsFixtureDef(b2Shape* shape);
	virtual void update (float dt);

private:
	Obstacles* initObstacles(int obstacle, cocos2d::CCPoint pos, float angle);
};

#endif /* defined(__Obstacles__) */

