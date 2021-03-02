#include "bullet.h"

Bullet::Bullet()
{

}

Bullet::Bullet(sf::Texture& texture, int bulletType, sf::FloatRect newHitbox, sf::Vector2f pos, float angle, sf::Vector2f dir, float movementSpeed)
{
	this->sprite.setTexture(texture);
	//0 is playerBullet, 10 is basicEnemyBullet, 11 is thinEnemyBullet, 12 is bigEnemyBullet, 13 is laserEnemyBullet
	type = bulletType;
	this->sprite.setOrigin(sprite.getTexture()->getSize().x * 0.5f, sprite.getTexture()->getSize().y * 0.5f);
	this->sprite.setPosition(pos);
	this->direction = dir;
	this->movementSpeed = movementSpeed;
	this->sprite.scale(2.f, 2.f);
	this->setHitbox(newHitbox);
	rotateAngle = angle;
	this->updateRotation();
}

Bullet::~Bullet()
{

}

int Bullet::getType()
{
	return type;
}

sf::Vector2f Bullet::getBasePlayerPos()
{
	return basePlayerPos;
}

void Bullet::setBasePlayerPos(sf::Vector2f newPlayerPos)
{
	basePlayerPos = newPlayerPos;
}


void Bullet::update()
{
	//movement
	this->sprite.move(this->movementSpeed * this->direction);
}