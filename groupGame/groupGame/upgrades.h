#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <iostream>


#include "entity.h"

using namespace sf;

class Upgrade : public Entity{

private:
	Texture *texture;
	float dtMultiplier;
	int type;
	float aliveTimer;
	float aliveTimerMax;

	Sprite sprite;

public:
	
	Upgrade(Texture&, Vector2f position, float aliveTimerMax, int type);

	~Upgrade();

	inline const int& getType()const { return this->type; }
	inline bool canDelete() { return this->aliveTimer >= this->aliveTimerMax; }

	bool checkCollision(FloatRect rect);

	void Update(const float& dt);
	void Draw(RenderTarget& target);
	void update();
	int returnType();

};