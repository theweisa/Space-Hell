#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"

/*
ENEMY CLASS
enemies have a type, cool down on firing, position in a wave, direction towards player, and bullet counter
*/
class Enemy : public Character
{
private:
	int type;							//type of the enemy: 0-3, 10-13, 100
	float fireCooldown;					//cooldown before they can shoot again
	bool destroyed;						//if the enemy is destroyed
	unsigned posInWave;					//when they spawned in a wave
	bool isDamaged;						//if the enemy got damaged
	sf::Vector2f enemyToPlayerDir;		//position of player relative to enemy
	int bulletCounter;					//how many bullets fired in their pattern
	float damageTimer;					//timer to display their damage "animation"

public:
	//constructor / destructor
	Enemy(sf::Texture& newTexture, int type, float newHp, float damage, float newFireRate, float newMovementSpeed, sf::FloatRect& newHitbox, sf::Vector2f initialPosition, unsigned posInWave, float scale);

	//accessor
	const int getType() const;
	const bool getDestroyed() const;
	const unsigned getPosInWave() const;
	const sf::Vector2f getEnemyToPlayerDir() const;
	const int getBulletCounter() const;
	const float getSpeed() const;
	const bool getIsDamaged() const;

	//mutator
	void setDestroyed(bool destroyed_);
	void setEnemyToPlayerDir(sf::Vector2f enemyToPlayerDir);
	void setBulletCounter(int newBulletCounter);
	void setIsDamaged(bool damaged);
	void restartDamageTimer();

	//functions
	void showDamaged(float & deltaTime);		//play the enemies damage "animation"
	void update() override;						//update the enemy
};

#endif