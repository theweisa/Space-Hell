#ifndef PLAYER_H
#define PLAYER_H
#include "character.h"

class Player : public Character {
private:
	std::string damagedKey;
	//private variables
	void initVariables(float scale);
	void initTexture();
	void initSprite(sf::Vector2f initialPos, float scale);
	void initHitbox();

public:
	//constructor/destructor
	Player(sf::Vector2f initialPos, float scale);
	~Player();

	//update
	void update() override;

	//functions
	//mutator
	void setDamagedAnimation(std::string key, sf::Texture* textureSheet, int endFrameX, int endFrameY, int width, int height);

	//accesspr
	const std::string getDamagedKey() const;
};

#endif
