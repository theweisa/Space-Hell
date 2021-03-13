#ifndef PLAYER_H
#define PLAYER_H
#include "character.h"

/*
PLAYER CLASS
player has a damaged animation, and has preset variables
*/
class Player : public Character 
{
private:
	std::string damagedKey;				//animation key for when a player is damaged
	void initVariables(float scale);	//initialize player variables
	void initTexture();					//initialize the player texture
	void initSprite(sf::Vector2f initialPos, float scale);		//initialize the player sprite
	void initHitbox();					//initialize the player hitbox

public:
	//constructor/destructor
	Player(sf::Vector2f initialPos, float scale);

	//update
	void update() override;

	//set the damaged animation
	void setDamagedAnimation(std::string key, sf::Texture* textureSheet, int endFrameX, int endFrameY, int width, int height);

	//accessor
	const std::string getDamagedKey() const;
};

#endif
