#ifndef PLAYER_H
#define PLAYER_H
#include "character.h"

class Player : public Character {
private:
	//private variables
	void initVariables();
	void initTexture();
	void initSprite();
	void initHitbox();

public:
	//constructor/destructor
	Player();
	~Player();

	//update
	void update();

	//functions
};

#endif
