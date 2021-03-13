#ifndef CHARACTER_H
#define CHARACTER_H

#include "entity.h"

/*
CHARACTER BASE CLASS
inherits from entity; character's have hp, have spawn/idle animations, deal damage, and can fire bullets
*/
class Character : virtual public Entity
{
public:
	//functions
	void move(const float dirX, const float dirY); 	//move the character a direction

	//accessor
	const bool canFire();				//check if the character can fire
	const float getDamage() const;		//get the damage the character deals
	const float getHp() const;			//get the hp of the character
	const float getMaxHp() const;		//get the max hp of the character
	const float getFireRate() const;	//get the fire rate
	const std::string getCurrentAnimation() const;	//get the current animation of the character
	const std::string getSpawnKey() const;	//get the spawn animation key
	const std::string getIdleKey() const;	//get the idle animation key
	const bool endOfSpawnAnimation();		//check if the spawn animation ended

	//mutator
	void setHp(float newHp);				//set hp
	void takeDamage(float damage);			//take damage; lower hp
	void setDamage(float newDamage);		//set the damage dealt
	void setMovementSpeed(float newMS);
	void setFireRate(float newFireRate);	//set the character's fire rates
	void setSpawnAnimation(std::string key, sf::Texture* textureSheet, int endFrameX, int endFrameY, int width, int height);	//set the spawn animation
	void setIdleAnimation(std::string key, sf::Texture* textureSheet, int endFrameX, int endFrameY, int width, int height);		//set the idle animation
	void setCurrentAnimation(std::string newAnimation);			//set the current animation that is playing

	//update
	void updateAnimation(std::string key, float & deltaTime);	//update the character's animation
	void updateFireRate();					//update the fire rate

protected:
	std::string spawnKey;			//key of the spawn animation
	std::string idleKey;			//key of the idle animation
	std::string currentAnimation;	//the currenet animation
	float damage;					//damage dealt
	float fireRate, maxFireRate;	//fire rate and cooldown
	float hp, hpMax;				//hp
};

#endif
