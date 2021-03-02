#include "player.h"

//initialize variables
void Player::initVariables()
{
	this->movementSpeed = 3.f;
	this->maxFireRate = 5.f;
	this->fireRate = this->maxFireRate;
	
	this->hpMax = 5.f;
	this->hp = this->hpMax;
	this->damage = 1.f;

	this->rotateAngle = 0.f;
}

//initialize texture
void Player::initTexture()
{
	//load a texture from file
	if (!this->texture.loadFromFile("Textures/player_ship.png")) 
		std::cout << "ERROR: could not open texture. " << std::endl;
}

//initialize sprite texture and scale
void Player::initSprite()
{
	//load a sprite from file
	this->sprite.setTexture(this->texture);

	this->sprite.setOrigin(sf::Vector2f(sprite.getTexture()->getSize().x * 0.5f, sprite.getTexture()->getSize().x * 0.5f));
	//resize the sprite
	this->sprite.scale(1.2f, 1.2f);

	//set the initialize position of the sprite to these coords
	this->sprite.setPosition(360.f, 400.f);	
}

//initialize hitbox
void Player::initHitbox()
{
	this->hitbox = sf::FloatRect(26, 20, 12, 24);
}

/*
constructor / destructor
*/
//initialize needed variables
Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initHitbox();
}

Player::~Player()
{
	
}

//update character
void Player::update()
{
	this->updateFireRate();
	this->updateRotation();
}

