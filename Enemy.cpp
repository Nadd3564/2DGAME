//
//  Enemy.cpp
//
//  Created by athenaeum on 2014/11/18.
//
//

#include "Enemy.h"
#include "ObjectManager.h"
#include "GameLayer.h"


Enemy::Enemy(GameLayer * game) : GameObject(game){}

Enemy::~Enemy(){
	CC_SAFE_RELEASE(this);
}

Enemy* Enemy::create(CCPoint position, const char* fileName)
{
	//エネミー生成
	Enemy* enemy = new Enemy(GameLayer::Instance());
	if (enemy) {
        enemy->initEnemy(position, fileName);
		enemy->autorelease();
		GameLayer::Instance()->setEnemy(enemy);
		return enemy;
	}
	//autoreleaseを使用しているため、deleteの代わりに使用、メモリを開放
	//何度も生成しないようにガードをかける
	CC_SAFE_DELETE(enemy);
	return NULL;
}

Enemy* Enemy::initEnemy(CCPoint position, const char* FileName)
{
	this->initWithFile(FileName);
	this->setPosition(position);
	this->setTag(_gameL->kTag_Enemy);

	//物理ボディ生成
	_body = _gameL->getWorld()->CreateBody(&enemyBodyDef(this));
	_body->SetSleepingAllowed(true);
	_body->SetLinearDamping(0.2);
	_body->SetAngularDamping(0.8);
    
	//物理エンジン上の物質の形と大きさ
    b2CircleShape spriteShape;
   spriteShape.m_radius = this->getContentSize().width * 0.4 / PTM_RATIO;

    //物理性質
	_body->CreateFixture(&enemyFixtureDef(&spriteShape));
	
	this->setRigidBody(_body);
	Game::Instance()->addGameObjectMap("enemy", this);
	Game::Instance()->addGameObject(this);
	return this;
}

void Enemy::addEnemy(){
	create(ccp(636, 335), "enemy1.png");
	create(ccp(536, 125), "enemy1.png");
}

void Enemy::stateUpdate(float dt){
	if (this == NULL)
		return;
    std::cout << "Update for the enemy.";
	setPositionX(_body->GetPosition().x * PTM_RATIO);
	setPositionY(_body->GetPosition().y * PTM_RATIO);
	setRotation(CC_RADIANS_TO_DEGREES(-1 * _body->GetAngle()));
}

//物理ボディ生成
b2BodyDef Enemy::enemyBodyDef(Enemy* enemy){
	b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(enemy->getPositionX() / PTM_RATIO,
                               enemy->getPositionY() / PTM_RATIO);
	bodyDef.userData = enemy; 
	return bodyDef;
}

//物理性質
b2FixtureDef Enemy::enemyFixtureDef(b2Shape* shape){
	b2FixtureDef fixtureDef;
    fixtureDef.shape = shape;
	fixtureDef.filter.categoryBits = 0x0010;
    fixtureDef.density = 0.5;
    fixtureDef.restitution = 0.5;
	fixtureDef.friction = 0.3;
	return fixtureDef;
}

void Enemy::update (float dt) {
    
    if (_body && isVisible()) {
		setPositionX(_body->GetPosition().x * PTM_RATIO);
		setPositionY(_body->GetPosition().y * PTM_RATIO);
		setRotation(CC_RADIANS_TO_DEGREES(-1 * _body->GetAngle()));
    }
}
