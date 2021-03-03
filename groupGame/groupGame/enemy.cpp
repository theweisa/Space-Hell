#include "enemy.h"

Enemy::Enemy()
{

}

Enemy::Enemy(sf::Texture& newTexture, int newType, float newHp, float damage, float newFireRate, float newMovementSpeed, sf::FloatRect& newHitbox, sf::Vector2f initialPosition, unsigned posInWave)
{
	this->sprite.setTexture(newTexture);
	this->sprite.setOrigin(sprite.getTexture()->getSize().x * 0.5f, sprite.getTexture()->getSize().y * 0.5f);
	this->type = newType;
	this->hp = newHp;
	this->hpMax = newHp;
	this->fireRate = 0;
	this->maxFireRate = newFireRate;
	this->movementSpeed = newMovementSpeed;
	this->destroyed = false;
	this->setHitbox(newHitbox);
	this->sprite.scale(1.5f, 1.5f);
	this->sprite.setPosition(initialPosition);
	this->posInWave = posInWave;
	bulletCounter = 0;
}

Enemy::~Enemy()
{

}

//accessor
const int Enemy::getType() const
{
	return type;
}

const bool Enemy::getDestroyed() const
{
	return destroyed;
}

const unsigned Enemy::getPosInWave() const
{
	return posInWave;
}

const sf::Vector2f Enemy::getEnemyToPlayerDir() const
{
	return this->enemyToPlayerDir;
}

const int Enemy::getBulletCounter() const
{
	return bulletCounter;
}

//functions

//mutator
void Enemy::setDestroyed(bool destroyed_)
{
	destroyed = destroyed_;
}

void Enemy::setEnemyToPlayerDir(sf::Vector2f enemyToPlayerDir)
{
	this->enemyToPlayerDir = enemyToPlayerDir;
}

void Enemy::setBulletCounter(int newBulletCounter)
{
	bulletCounter = newBulletCounter;
}

void Enemy::update()
{
	this->updateFireRate();
	this->updateRotation();
}


