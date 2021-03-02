#ifndef BULLET_H
#define BULLET_H

#include "entity.h"

class Bullet : public Entity
{
private:
	sf::Vector2f direction;
	sf::Vector2f basePlayerPos;
	int type;
public:
	Bullet();
	Bullet(sf::Texture& texture, int bulletType, sf::FloatRect newHitbox, sf::Vector2f pos, float angle, sf::Vector2f dir, float movementSpeed);
	virtual ~Bullet();

	//accessor
	int getType();
	sf::Vector2f getBasePlayerPos();

	//mutator
	void setBasePlayerPos(sf::Vector2f newPlayerPos);

	void update();
};

#endif