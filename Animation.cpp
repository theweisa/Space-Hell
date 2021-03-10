#include "Animation.h"

Animation::Animation(sf::Sprite& newSprite, sf::Texture& newSpriteSheet, float newSpeed, int startFrameX, int startFrameY, int endFramesX, int endFramesY, int newWidth, int newHeight)
: sprite(newSprite), spriteSheet(newSpriteSheet), animationTimer(newSpeed), width(newWidth), height(newHeight)
{
	timer = 0.f;
	endOfAnimation = false;

	startRect = sf::IntRect(startFrameX * width, startFrameY * height, width, height);
	currentRect = startRect;
	
	//the last rect is the one at endFramesX * width and height
	endRect = sf::IntRect(endFramesX * width, endFramesY * height, width, height);

	//set the animations sprite to the sprite sheet
	this->sprite.setTexture(spriteSheet, true);

	//set the initial frame of the sprite sheet
	this->sprite.setTextureRect(startRect);
}

void Animation::play(const float & deltaTime)
{
	//update the timer
	timer += 100.f * deltaTime;

	//reset the timer if it goes over the speed of a new frame
	if (timer >= animationTimer)
	{
		//reset the timer
		timer = 0.f;

		//update the animation if the current animation is not the end
		if (currentRect != endRect)
		{
			currentRect.left += width;
		}
		//if the animation reaches the end, set the current frame to the first frame
		else
		{
			currentRect.left = startRect.left;
		}

		//just for the spawn animation to get a more accurate end of animation
		if (currentRect == endRect)
		{
			endOfAnimation = true;
		}
		else
		{
			endOfAnimation = false;
		}

		//set the sprites texture to the current rect
		this->sprite.setTextureRect(currentRect);
	}
}

void Animation::reset()
{
	timer = 0.f;
	currentRect = startRect;
}

const bool Animation::getEndOfAnimation() const
{
	return endOfAnimation;
}

Animation::~Animation()
{
}
