#include "bullet.h"

Bullet::Bullet()
{

}

Bullet::Bullet(sf::Texture& texture, int bulletType, sf::FloatRect newHitbox, sf::Vector2f pos, float angle, sf::Vector2f dir, float newMovementSpeed, float scale)
{
	this->sprite.setTexture(texture);

	//0 is playerBullet, 10 is basicEnemyBullet, 11 is thinEnemyBullet, 12 is bigEnemyBullet, 13 is bouncingEnemyBullet
	type = bulletType;

	//set sprite origin and position
	this->sprite.setOrigin(sprite.getTexture()->getSize().x * 0.5f, sprite.getTexture()->getSize().y * 0.5f);
	this->sprite.setPosition(pos);
	this->sprite.scale(2.f * scale, 2.f * scale);

	//set direction it moves and the speed
	this->direction = dir;
	this->movementSpeed = newMovementSpeed;

	//set the hitbox
	this->setHitbox(newHitbox);

	//set the angle it rotates
	rotateAngle = angle;

	//set if the bullet bounces based on the type passed in
	if (type == 13)
		maxBounce = 3;
	else
		maxBounce = 0;

	//update the rotation
	this->updateRotation();
}

Bullet::~Bullet()
{

}

//accessors

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

//mutators

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

//update the bullets movement
void Bullet::update()
{
	//bullet moves at the set direction
	this->sprite.move(this->movementSpeed * this->direction);
}