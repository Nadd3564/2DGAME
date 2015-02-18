#ifndef __RigidSprite__
#define __RigidSprite__

#include "cocos2d.h"
#include <Box2D\Box2D.h>

USING_NS_CC;

const float PTM_RATIO = 32.0;

class RigidSprite : public CCSprite
{
public:

    RigidSprite();
	~RigidSprite();

    void setRigidBody(b2Body* body);
	b2Body* getBody();
	float getPow();
    
private:

	b2Body* m_pBody;
	
};

#endif /* defined(__RigidSprite__) */