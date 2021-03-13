#include "Upgrade.h"

Upgrade::Upgrade(sf::Texture* newTexture, Vector2f position, float despawnTimerMax, int type, float & currentTime, float scale) 
{
	sprite.setTexture(*newTexture);
	sprite.setOrigin(4, 4);
	sprite.setPosition(position);
	sprite.scale(2.f * scale, 2.f * scale);
	this->setHitbox(sf::FloatRect(0, 0, 8, 8));
	this->deltaTime = currentTime;

	this->despawnTimer = 0.f;
	this->despawnTimerMax = despawnTimerMax;

	//1 is damage up, 2 is fire rate up, 3 is hp up
	this->type = type;
	key = "upgrade";
	animations[key] = new Animation(sprite, *newTexture, 10.f, 0, 0, 11, 0, 16, 16);
	//sprite.setOrigin()
	/*this->dtMultiplier = 62.5f;
	this->aliveTimerMax = aliveTimerMax;
	this->texture = &t;
	this->type = type;*/
}

void Upgrade::setTime(float & deltaTime)
{
	this->despawnTimer += deltaTime;
	this->deltaTime = deltaTime;
}

const float Upgrade::getTime() const
{
	return deltaTime;
}

void Upgrade::update()
{
	animations[key]->play(deltaTime);
}

int Upgrade::returnType() 
{
	return type;
}