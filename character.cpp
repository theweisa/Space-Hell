#include "character.h"

//character takes damage
namespace ent
{
	void Character::takeDamage(float damage)
	{
		hp -= damage;
	}

	//move the character
	void Character::move(const float dirX, const float dirY)
	{
		sprite.move(movementSpeed * dirX, movementSpeed * dirY);
	}

	//update the animations
	void Character::updateAnimation(std::string key, float & deltaTime)
	{
		animations[key]->play(deltaTime);
	}

	//update the fire rate
	void Character::updateFireRate()
	{
		//fire rate updates by 0.5f
		if (fireRate < maxFireRate)
			fireRate += 0.5f;
	}

	//accessors
	const bool Character::canFire()
	{
		//if the fire rate has reached the maximum fire rate, can fire.
		if (fireRate >= maxFireRate)
		{
			//reset the fire rate
			fireRate = 0.f;
			return true;
		}
		//if the fire rate is not at the maximum fire rate, cannot fire
		return false;
	}


	const float Character::getDamage() const
	{
		return damage;
	}

	const float Character::getHp() const
	{
		return hp;
	}

	const float Character::getMaxHp() const
	{
		return hpMax;
	}

	const float Character::getFireRate() const
	{
		return maxFireRate;
	}

	const std::string Character::getCurrentAnimation() const
	{
		return currentAnimation;
	}

	const std::string Character::getSpawnKey() const
	{
		return spawnKey;
	}

	const std::string Character::getIdleKey() const
	{
		return idleKey;
	}

	const bool Character::endOfSpawnAnimation()
	{
		return animations[spawnKey]->getEndOfAnimation();
	}

	//mutators
	void Character::setHp(float newHp)
	{
		hp = newHp;
	}

	void Character::setDamage(float newDamage)
	{
		damage = newDamage;
	}

	void Character::setMovementSpeed(float newMS)
	{
		movementSpeed = newMS;
	}

	//mutator
	void Character::setFireRate(float newFireRate)
	{
		maxFireRate = newFireRate;
		fireRate = 0;
	}

	void Character::setSpawnAnimation(std::string key, sf::Texture * textureSheet, int endFrameX, int endFrameY, int width, int height)
	{
		spawnKey = key;
		//animation name, speed, startFrameX, startFrameY, endFrameX, endFrameY, width, height
		animations[key] = new Animation(sprite, *textureSheet, 10.f, 0, 0, endFrameX, endFrameY, width, height); //4, 0, 32, 32
		currentAnimation = "spawn";
	}

	void Character::setIdleAnimation(std::string key, sf::Texture * textureSheet, int endFrameX, int endFrameY, int width, int height)
	{
		idleKey = key;
		animations[key] = new Animation(sprite, *textureSheet, 10.f, 0, 0, endFrameX, endFrameY, width, height); //11, 0, 32, 32
		currentAnimation = "idle";
	}

	void Character::setCurrentAnimation(std::string newAnimation)
	{
		currentAnimation = newAnimation;
	}
}