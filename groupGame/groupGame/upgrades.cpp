#include "upgrades.h"


Upgrade::Upgrade(sf::Texture &t,Vector2f position, float aliveTimerMax, int type) {
	
	this->dtMultiplier = 62.5f;
	this->aliveTimerMax = aliveTimerMax;
	this->texture = &t;
	this->type = type;
	
	this->sprite.setTexture(*(this->texture));
	this->sprite.setScale(0.05f, 0.05f);

	this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().width / 2);
	this->sprite.setPosition(position);
}

bool Upgrade::checkCollision(FloatRect rect) {

	if (this->sprite.getGlobalBounds().intersects(rect)) {
		return true;
	}
	return false;
}

void Upgrade::Update(const float& dt) {

	if (this->aliveTimer < this->aliveTimerMax) {
		this->aliveTimer += 1.f * dt * this->dtMultiplier;
		//std::cout << this->aliveTimer << std::endl;
	}

	this->sprite.rotate(5.f * dt * this->dtMultiplier);
}

void Upgrade::update() {

	this->sprite.move(0, 0);
}

void Upgrade::Draw(RenderTarget& target) {

	target.draw(this->sprite);
}

int Upgrade::returnType() {

	return type;
}
