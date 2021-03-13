#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include <string>

/*
ANIMATION CLASS
animation animates a sprite sheet and directly updates the sprite in the entity
*/
class Animation
{
private:
	sf::Sprite& sprite;			//sprite being updated
	sf::Texture& spriteSheet;	//the animation sheet
	float animationTimer;		//max timer for the animation
	float timer;				//current timer of the animation
	int width;					//width of the texture being animated
	int height;					//height of the texture being animated
	bool endOfAnimation;		//check for last from of an animation
	sf::IntRect startRect;		//the first frame of the animation
	sf::IntRect currentRect;	//the current frame of the animation
	sf::IntRect endRect;		//the end frame of the animation

public:
	//initialize the animation; sprite, sprite sheet, animation speed, first frame (x, y), last frame (x, y), width and height of one animation
	Animation(sf::Sprite& newSprite, sf::Texture& newSpriteSheet, float newSpeed, int startFrameX, int startFrameY, int endFramesX, int endFramesY, int newWidth, int newHeight);

	//play the animation based on deltaTime
	void play(const float & deltaTime);

	//reset the animation
	void reset();

	//return if an animation ended
	const bool getEndOfAnimation() const;
};

#endif