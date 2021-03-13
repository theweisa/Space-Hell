#ifndef UPGRADES_H
#define UPGRADES_H

#include "entity.h"

using namespace sf;

/*
Upgrade class:
-drops where the enemy died
-despawns after x time
-if hitbox interacts with player, player picks it up and fire pattern changes
-that is all!
*/
class Upgrade : public Entity {

private:
	std::string key;
	float deltaTime;
	//float dtMultiplier;
	int type;
	float despawnTimer;
	float despawnTimerMax;

public:

	Upgrade(Texture* texture, Vector2f position, float despawnTimerMax, int type, float & currentTime, float scale);

	inline const int& getType()const { return this->type; }
	inline bool canDelete() { return this->despawnTimer >= this->despawnTimerMax; }

	//bool checkCollision(FloatRect rect);

	void setTime(float & time);

	const float getTime() const;

	void update() override;

	int returnType();

};

#endif