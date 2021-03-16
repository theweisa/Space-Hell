#include "entity.h"
#include <iostream>

namespace ent
{
	Entity::~Entity()
	{
		//delete all the animations; the ranged based for loop would sometime go out of range and cause an error.
		for (auto itr = animations.begin(); itr != animations.end(); itr++)
		{
			delete itr->second;
		}
		/*for (auto& a : animations)
		{
			delete a.second;
		}*/
	}

	//**************MUTATORS**************
	//set the position with an x and y
	void Entity::setPosition(const float posX, const float posY)
	{
		this->sprite.setPosition(posX, posY);
	}

	//set the postiion with a vector
	void Entity::setPosition(const sf::Vector2f pos)
	{
		this->sprite.setPosition(pos);
	}

	//set the hitbox of the entity
	void Entity::setHitbox(const sf::FloatRect& newHitbox)
	{
		hitbox = newHitbox;
	}

	//set the scale of the sprite
	void Entity::setSpriteScale(float scale)
	{
		this->sprite.scale(scale, scale);
	}

	//set the sprite's color
	void Entity::setSpriteColor(sf::Color newColor)
	{
		sprite.setColor(newColor);
	}

	//rotate the sprite
	void Entity::setRotate(float angle)
	{
		rotateAngle = angle;
	}

	//**************ACCESSORS**************
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


	//**************FUNCTIONS**************
	//update the rotation of the entity's sprite
	void Entity::updateRotation()
	{
		this->sprite.setRotation(rotateAngle);
	}

	//add an animation to the entity's animations
	void Entity::addAnimation(std::string key, sf::Texture & spriteSheet, float newSpeed, int startFrameX, int startFrameY, int endFramesX, int endFramesY, int newWidth, int newHeight)
	{
		animations[key] = new Animation(sprite, spriteSheet, newSpeed, startFrameX, startFrameY, endFramesX, endFramesY, newWidth, newHeight);
	}

	//check if a certain animation has reached the last frame
	const bool Entity::getEndOfAnimation(const std::string key)
	{
		return animations[key]->getEndOfAnimation();
	}

	//draw the constantly updating sprite
	void Entity::render(sf::RenderTarget& target)
	{
		target.draw(this->sprite);
	}
}