#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include "Animation.h"

#include <iostream>

class Entity
{
protected:
	sf::Texture texture;
	sf::Sprite sprite;
	std::map<std::string, Animation*> animations;
	sf::FloatRect hitbox;
	float movementSpeed;
	float rotateAngle;
public:
	~Entity();
	virtual void update() = 0;

	//mutator
	void setPosition(float posX, float posY);
	void setPosition(const sf::Vector2f pos);
	void setRotate(float angle);
	void setHitbox(const sf::FloatRect& newHitbox);
	void setSpriteScale(float scale);

	//accessors
	const sf::FloatRect getGlobalHitbox() const;
	const sf::FloatRect getBounds() const;
	const sf::Vector2f& getPos() const;
		
	//functions
	void updateRotation();
	void addAnimation(std::string key, sf::Texture& spriteSheet, float newSpeed, int startFrameX, int startFrameY, int endFramesX, int endFramesY, int newWidth, int newHeight);
	const bool getEndOfAnimation(const std::string key);

	void render(sf::RenderTarget& target);
};

#endif
