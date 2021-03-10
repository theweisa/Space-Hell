#include "character.h"

//character takes damage
void Character::takeDamage(float damage)
{
	this->hp -= damage;
}

//move the character
void Character::move(const float dirX, const float dirY) 
{ 
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY); 
}

//update the fire rate
void Character::updateFireRate()
{
	//fire rate updates by 0.5f
	if (this->fireRate < this->maxFireRate)
		this->fireRate += 0.5f;
}

//accessors
const bool Character::canFire()
{
	//if the fire rate has reached the maximum fire rate, can fire.
	if (this->fireRate >= this->maxFireRate)
	{
		//reset the fire rate
		this->fireRate = 0.f;
		return true;
	}
	//if the fire rate is not at the maximum fire rate, cannot fire
	return false;
}


//returns the damage of the character
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

//mutator
void Character::setFireRate(float newFireRate)
{
	maxFireRate = newFireRate;
	fireRate = 0;
}

void Character::addHP() {

	this->hp++;
}

void Character::addDmg() {

	this->damage = this->damage + 2;
}