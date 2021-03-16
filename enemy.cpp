#include "enemy.h"

namespace ent
{
	//constructor for enemy
	Enemy::Enemy(sf::Texture& newTexture, int newType, float newHp, float damage, float newFireRate, float newMovementSpeed, sf::FloatRect& newHitbox, sf::Vector2f initialPosition, unsigned posInWave, float scale)
	{
		//initialize the sprite texture
		sprite.setTexture(newTexture);
		//set the sprite origin to the center of the texture
		sprite.setOrigin(sf::Vector2f(sprite.getTexture()->getSize().x * 0.5f, sprite.getTexture()->getSize().x * 0.5f));
		sprite.scale(1.3f * scale, 1.3f * scale);
		sprite.setPosition(initialPosition);

		type = newType;
		hp = newHp;
		hpMax = newHp;

		fireRate = 0;
		maxFireRate = newFireRate;
		bulletCounter = 0;

		movementSpeed = newMovementSpeed;
		this->setHitbox(newHitbox);
		posInWave = posInWave;

		destroyed = false;
		isDamaged = false;
		damageTimer = 0.f;
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
		return enemyToPlayerDir;
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
		enemyToPlayerDir = enemyToPlayerDir;
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