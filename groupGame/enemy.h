#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"

class Enemy : public Character
{
private:
	int points;
	int type;
	float fireCooldown;
	bool destroyed;
	unsigned posInWave;
	bool isDamaged;
	sf::Vector2f enemyToPlayerDir;
	int bulletCounter;
	float damageTimer;

public:
	//constructor / destructor
	Enemy();
	Enemy(sf::Texture& newTexture, int type, float newHp, float damage, float newFireRate, float newMovementSpeed, sf::FloatRect& newHitbox, sf::Vector2f initialPosition, unsigned posInWave, float scale);
	virtual ~Enemy();

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
	void showDamaged(float & deltaTime);
	void update() override;
};

#endif