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

	int gunLevel = 0;
	bool enabledRTUpgrade = false;

	//Timer for gunlevel
	float dtMultiplier;
	float aliveTimer = 0;
	float aliveTimerMax;

	//timer for firerate
	float RTaliveTimer = 0;
	float RTaliveTimerMax;

public:
	//constructor/destructor
	Player();
	~Player();

	//update
	void update();

	//functions
	void updateGunLevel(int type, float aliveTimerMax);
	int getGunLevel() { return this->gunLevel; }
	void updateRTUpgrade(bool x, float RTaliveTimerMax);
	void gunUpgradeTimer(const float& dt);
	bool getRTUpgrade() { return enabledRTUpgrade; }
	bool deleteGun() { return aliveTimer >= aliveTimerMax; }
	void aliveTimerReset();

	void fireRTTimer(const float& dt);
	void RTaliveTimerReset() { this->RTaliveTimer = 0; }
	bool deleteRT() { return RTaliveTimer >= RTaliveTimerMax; }
};

#endif
