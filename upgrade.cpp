#include "upgrade.h"

namespace ent
{
	//constructor
	Upgrade::Upgrade(sf::Texture* newTexture, Vector2f position, float despawnTimerMax, int type, float & currentTime, float scale)
	{
		//throw an error if the texture is not initialized
		if (newTexture == nullptr)
		{
			throw std::string("Upgrade texture was not initialized.");
		}
		//initialize textures
		sprite.setTexture(*newTexture);

		//user hard coded origin here since the the middle of the sprite sheet is not the origin
		sprite.setOrigin(4, 4);
		sprite.setPosition(position);
		sprite.scale(2.f * scale, 2.f * scale);
		this->setHitbox(sf::FloatRect(0, 0, 8, 8));

		this->deltaTime = currentTime;

		//set the despawn timers
		this->despawnTimer = 0.f;
		this->despawnTimerMax = despawnTimerMax;

		//1 is damage up, 2 is fire rate up, 3 is hp up, 4 is double bullet, 5 is spread shot, 6 is cluster shot
		this->type = type;

		//idle animation for upgrade
		key = "upgrade";
		animations[key] = new Animation(sprite, *newTexture, 10.f, 0, 0, 11, 0, 16, 16);
	}

	//mutators
	void Upgrade::setTime(float & deltaTime)
	{
		this->despawnTimer += deltaTime;
		this->deltaTime = deltaTime;
	}

	//accessors
	const float Upgrade::getTime() const
	{
		return deltaTime;
	}

	const int Upgrade::getType() const
	{
		return type;
	}

	//functions
	bool Upgrade::isDespawned()
	{
		return this->despawnTimer >= this->despawnTimerMax;
	}

	void Upgrade::update()
	{
		animations[key]->play(deltaTime);
	}
}