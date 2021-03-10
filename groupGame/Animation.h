#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include <string>
#include <map>

class Animation
{
private:
	sf::Sprite& sprite;
	sf::Texture& spriteSheet;
	float animationTimer;
	float timer;
	int width;
	int height;
	bool endOfAnimation;
	sf::IntRect startRect;
	sf::IntRect currentRect;
	sf::IntRect endRect;

public:
	~Animation();
	//initialize the animation
	Animation(sf::Sprite& newSprite, sf::Texture& newSpriteSheet, float newSpeed, int startFrameX, int startFrameY, int endFramesX, int endFramesY, int newWidth, int newHeight);

	//play the animation based on deltaTime
	void play(const float & deltaTime);

	//reset the animation
	void reset();

	const bool getEndOfAnimation() const;
};

#endif