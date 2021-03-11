#include "entity.h"
#include <iostream>


Entity::~Entity()
{
	for (auto& a : animations)
	{
		delete a.second;
	}
}

//mutators
void Entity::setPosition(const float posX, const float posY)
{
	this->sprite.setPosition(posX, posY);
}

void Entity::setPosition(const sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Entity::setHitbox(const sf::FloatRect& newHitbox) {
	hitbox = newHitbox;
}

void Entity::setSpriteScale(float scale)
{
	this->sprite.scale(scale, scale);
}

void Entity::setSpriteColor(sf::Color newColor)
{
	sprite.setColor(newColor);
}

void Entity::setRotate(float angle)
{
	rotateAngle = angle;
}

//accessors

//returns the hitbox of the entity
const sf::FloatRect Entity::getGlobalHitbox() const
{
	return this->sprite.getTransform().transformRect(hitbox);
}

//return sprites global bounds
const sf::FloatRect Entity::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

//return the current position of the sprite
const sf::Vector2f& Entity::getPos() const
{
	return this->sprite.getPosition();
}


//functions
void Entity::updateRotation()
{
	this->sprite.setRotation(rotateAngle);
}

//const std::string key, float newSpeed, int startFrameX, int startFrameY, int endFramesX, int endFramesY, int newWidth, int newHeight
void Entity::addAnimation(std::string key, sf::Texture & spriteSheet, float newSpeed, int startFrameX, int startFrameY, int endFramesX, int endFramesY, int newWidth, int newHeight)
{
	animations[key] = new Animation(sprite, spriteSheet, newSpeed, startFrameX, startFrameY, endFramesX, endFramesY, newWidth, newHeight);
}

const bool Entity::getEndOfAnimation(const std::string key)
{
	return animations[key]->getEndOfAnimation();
}

//draw the constantly updating sprite (animation)
void Entity::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}