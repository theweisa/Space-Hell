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

	//mutator
	void setFireRate(float newFireRate);

	//update
	void updateFireRate();

protected:
	float damage;
	float fireRate, maxFireRate;
	float hp, hpMax;
};

#endif
