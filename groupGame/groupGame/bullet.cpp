#include "bullet.h"

Bullet::Bullet()
{

}

Bullet::Bullet(sf::Texture& texture, int bulletType, sf::FloatRect newHitbox, sf::Vector2f pos, float angle, sf::Vector2f dir, float movementSpeed)
{
	this->sprite.setTexture(texture);
	//0 is playerBullet, 10 is basicEnemyBullet, 11 is thinEnemyBullet, 12 is bigEnemyBullet, 13 is bouncingEnemyBullet
	type = bulletType;
	this->sprite.setOrigin(sprite.getTexture()->getSize().x * 0.5f, sprite.getTexture()->getSize().y * 0.5f);
	this->sprite.setPosition(pos);
	this->direction = dir;
	this->movementSpeed = movementSpeed;
	this->sprite.scale(2.f, 2.f);
	this->setHitbox(newHitbox);
	rotateAngle = angle;
	if (type == 13)
		maxBounce = 3;
	else
		maxBounce = 0;
	this->updateRotation();
}

Bullet::~Bullet()
{

}

const int Bullet::getType() const
{
	return type;
}

const sf::Vector2f Bullet::getBasePlayerPos() const
{
	return basePlayerPos;
}

const int Bullet::getMaxBounce() const
{
	return maxBounce;
}

const sf::Vector2f Bullet::getDir() const
{
	return direction;
}

void Bullet::setMaxBounce(int newMaxBounce)
{
	maxBounce = newMaxBounce;
}

void Bullet::setDir(sf::Vector2f newDir)
{
	direction = newDir;
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