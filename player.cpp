#include "player.h"

namespace ent
{
	//initialize variables
	void Player::initVariables(float scale)
	{
		movementSpeed = 3.f * scale;
		maxFireRate = 5.f;
		fireRate = maxFireRate;

		hpMax = 10.f;
		hp = 5.f;
		damage = 1.f;

		rotateAngle = 0.f;
	}

	//initialize texture
	void Player::initTexture()
	{
		//load a texture from file
		if (!texture.loadFromFile("Textures/player_ship.png"))
			std::cout << "ERROR: could not open texture. " << std::endl;
	}

	//initialize sprite texture and scale
	void Player::initSprite(sf::Vector2f initialPos, float scale)
	{
		//load a sprite from file
		sprite.setTexture(this->texture);

		sprite.setOrigin(sf::Vector2f(sprite.getTexture()->getSize().x * 0.5f, sprite.getTexture()->getSize().x * 0.5f));
		//resize the sprite
		sprite.scale(1.1f * scale, 1.1f * scale);
		//set the initialize position of the sprite to these coords
		sprite.setPosition(initialPos);
	}

	//initialize hitbox
	void Player::initHitbox()
	{
		hitbox = sf::FloatRect(26, 20, 12, 24);
	}

	/*
	constructor / destructor
	*/
	//initialize needed variables
	Player::Player(sf::Vector2f initialPos, float scale)
	{
		this->initVariables(scale);
		this->initTexture();
		this->initSprite(initialPos, scale);
		this->initHitbox();
	}

	//set the damaged animation
	void Player::setDamagedAnimation(std::string key, sf::Texture * textureSheet, int endFrameX, int endFrameY, int width, int height)
	{
		damagedKey = key;
		animations[key] = new Animation(sprite, *textureSheet, 10.f, 0, 0, endFrameX, endFrameY, width, height); //11, 0, 32, 32
		currentAnimation = "damaged";
	}

	const std::string Player::getDamagedKey() const
	{
		return damagedKey;
	}

	//update character
	void Player::update()
	{
		this->updateFireRate();
		this->updateRotation();
	}
}