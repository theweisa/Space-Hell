#ifndef CHARACTER_H
#define CHARACTER_H

#include "entity.h"

class Character : virtual public Entity
{
public:
	//functions
	void takeDamage(float damage);
	void move(const float dirX, const float dirY);

	//accessor
	const bool canFire();
	const float getDamage() const;
	const float getHp() const;
	const float getMaxHp() const;
	const float getFireRate() const;
	const std::string getCurrentAnimation() const;
	const std::string getSpawnKey() const;
	const std::string getIdleKey() const;
	const bool endOfSpawnAnimation();

	//mutator
	void setHp(float newHp);
	void setDamage(float newDamage);
	void setFireRate(float newFireRate);
	void setSpawnAnimation(std::string key, sf::Texture* textureSheet, int endFrameX, int endFrameY, int width, int height);
	void setIdleAnimation(std::string key, sf::Texture* textureSheet, int endFrameX, int endFrameY, int width, int height);
	void setCurrentAnimation(std::string newAnimation);

	//update
	void updateAnimation(std::string key, float & deltaTime);
	void updateFireRate();

protected:
	std::string spawnKey;
	std::string idleKey;
	std::string currentAnimation;
	float damage;
	float fireRate, maxFireRate;
	float hp, hpMax;
};

#endif
