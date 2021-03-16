#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

#include <iostream>
#include <unordered_map>

#include "Animation.h"

/*
VIRTUAL BASE CLASS ENTITY
	- Entity's contain texture's, sprite, animations, hitbox, movement speed, and rotation
	- has a pure virtual function update that the derived class' use
*/
namespace ent
{
	class Entity
	{
	protected:
		sf::Texture texture;	//base texture of the sprite
		sf::Sprite sprite;		//sprite
		std::unordered_map<std::string, Animation*> animations;	//map containing all the animations the object needs
		sf::FloatRect hitbox;	//hitbox of the entity; collision box
		float movementSpeed;	//movement speed of the entity
		float rotateAngle;		//angle the entitiy rotates
	public:
		~Entity();
		//puret virtual function that update's an entity
		virtual void update() = 0;

		//mutator
		void setPosition(float posX, float posY);
		void setPosition(const sf::Vector2f pos);
		void setRotate(float angle);
		void setHitbox(const sf::FloatRect& newHitbox);
		void setSpriteScale(float scale);
		void setSpriteColor(sf::Color newColor);

		//accessors
		const sf::FloatRect getGlobalHitbox() const;
		const sf::FloatRect getBounds() const;
		const sf::Vector2f& getPos() const;

		//functions
		void updateRotation();
		void addAnimation(std::string key, sf::Texture& spriteSheet, float newSpeed, int startFrameX, int startFrameY, int endFramesX, int endFramesY, int newWidth, int newHeight);
		const bool getEndOfAnimation(const std::string key);

		//render object to the window, or the render target
		void render(sf::RenderTarget& target);
	};
}
#endif