#include "entity.h"
#include <iostream>

//returns the hitbox of the entity
const sf::FloatRect Entity::getGlobalHitbox() const
{
	return this->sprite.getTransform().transformRect(hitbox);
}

//mutator
void Entity::setPosition(const float posX, const float posY)
{
	this->sprite.setPosition(posX, posY);
}

void Entity::setPosition(const sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
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

void Entity::setHitbox(const sf::FloatRect& newHitbox) {
	hitbox = newHitbox;
}

void Entity::setRotate(float angle)
{
	rotateAngle = angle;
}

void Entity::updateRotation()
{
	this->sprite.setRotation(rotateAngle);
}

void Entity::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}