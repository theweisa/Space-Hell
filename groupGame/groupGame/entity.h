#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

#include <iostream>

class Entity
{
protected:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::FloatRect hitbox;
	float movementSpeed;
	float rotateAngle;
public:
	virtual void update() = 0;

	//mutator
	void setPosition(float posX, float posY);
	void setPosition(const sf::Vector2f pos);
	void setRotate(float angle);
	void updateRotation();

	//accessors
	const sf::FloatRect getGlobalHitbox() const;

	const sf::FloatRect getBounds() const;
	const sf::Vector2f& getPos() const;

	//functions
	void setHitbox(const sf::FloatRect& newHitbox);
	void render(sf::RenderTarget& target);
};

#endif
