#include "enemy.h"

namespace ent
{
	//constructor for enemy
	Enemy::Enemy(sf::Texture& newTexture, int newType, float newHp, float damage, float newFireRate, float newMovementSpeed, sf::FloatRect& newHitbox, sf::Vector2f initialPosition, unsigned posInWave, float scale)
	{
		//initialize the sprite texture
		this->sprite.setTexture(newTexture);
		//set the sprite origin to the center of the texture
		this->sprite.setOrigin(sf::Vector2f(sprite.getTexture()->getSize().x * 0.5f, sprite.getTexture()->getSize().x * 0.5f));
		this->sprite.scale(1.3f * scale, 1.3f * scale);
		this->sprite.setPosition(initialPosition);

		this->type = newType;
		this->hp = newHp;
		this->hpMax = newHp;

		this->fireRate = 0;
		this->maxFireRate = newFireRate;
		this->bulletCounter = 0;

		this->movementSpeed = newMovementSpeed;
		this->setHitbox(newHitbox);
		this->posInWave = posInWave;

		this->destroyed = false;
		this->isDamaged = false;
		this->damageTimer = 0.f;
	}

	//accessors
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

	const float Enemy::getSpeed() const
	{
		return movementSpeed;
	}

	const bool Enemy::getIsDamaged() const
	{
		return isDamaged;
	}

	//mutators
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

	void Enemy::setIsDamaged(bool damaged)
	{
		isDamaged = damaged;
	}

	void Enemy::restartDamageTimer()
	{
		damageTimer = 0.f;
	}


	//functions
	//display the damage "animation"
	void Enemy::showDamaged(float & deltaTime)
	{
		//set enemy to damaged
		isDamaged = true;
		//increment the counter with the time per frame
		damageTimer += deltaTime;

		//for 0.1f seconds, set the sprite's color to a shade of light red to show they are damaged
		if (damageTimer < 0.1f)
		{
			sprite.setColor(sf::Color(239, 138, 138, 255));
		}
		//after the 0.1f seconds, set their color back to white and set is damaged back to false
		else
		{
			isDamaged = false;
			sprite.setColor(sf::Color::White);
		}
	}

	//update the enemy
	void Enemy::update()
	{
		this->updateFireRate();		//update the fire rate
		this->updateRotation();		//update the rotation
	}
}