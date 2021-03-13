#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <sstream>
#include <cstdlib>
#include <iterator>

#include "Upgrade.h"
#include "Explosion.h"
#include "Background.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"

class Game
{
private:
	//*******window*******
	sf::RenderWindow* window;
	sf::View* view;
	sf::Event ev;
	sf::VideoMode videoMode;
	float windowWidth;
	float windowHeight;
	float scale;

	//*******player*******
	Player* player;

	//*******world*******
	Background* spaceBackground;

	//*******resources*******
	//std::map<std::string, sf::Texture*> textures;
	std::unordered_map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> playerBullets;
	std::vector<Bullet*> enemyBullets;
	std::vector<Enemy*> enemies;
	std::vector<Explosion*> explosions;
	std::vector<Upgrade*> upgrades;
	std::unordered_map<std::string, sf::Text*> texts;
	sf::Font font;

	//*******Mouse position*******
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	
	//*******Timer*******
	sf::Clock clock;
	sf::Clock deltaClock;
	float deltaTime;

	//*******character positions*******
	sf::Vector2f playerPos;
	sf::Vector2f enemyPos;

	//*******game logic*******

	//enemy variables
	bool moveUp;
	bool moveRight;
	bool enemySpawned;
	bool enemyDestroyed;
	int numEnemies;
	int numEnemiesDestroyed;
	bool enemyFireCluster;
	int bossPattern;
	bool bossEnraged;
	bool bossDestroyed;

	//player variables
	float playerInvulTimer;
	float playerInvulTimerMax;
	bool playerFireCluster;
	int playerFirePattern;
	float totalPlayerDamageUp;
	float totalPlayerFireRateUp;

	//game variables
	int currentWave;
	float mouseAngle;
	float enemyAngle;
	bool pause;
	float pauseBuffer;
	float pauseBufferMax;
	bool gameOver;
	unsigned int points;
	unsigned int combo;
	sf::Vector2f playerAimDir;
	sf::Vector2f enemyAimDir;
	sf::Vector2f baseEnemyAimDir;

	//reset game
	bool resetVal;

	//general private variables
	const float pi = 3.14159f;

	//private functions
	void initVariables();
	void initWindow();
	void initView();
	void initTextures();
	void addTexture(const std::string key, const std::string fileName);
	void initGUI();
	void addText(const std::string key, unsigned charSize, sf::Color color, const std::string initialText, sf::Vector2f initialPos);
	//void initText(sf::Text& text, sf::Font font, sf::Vector2f pos, int size, sf::Color color, std::string initialString);
	void initWorld();
	void initPlayer();
	void initEnemy();

public:
	//constructor/destructor
	Game();
	~Game();

	//update
	void update();
	void updatePause();
	void updateDeltaTime();
	void updateView();
	void updateMousePos();
	void updatePollEvents();
	void updatePlayer();
	void updateEnemies();
	void updateBullets();
	void updateWorldCollision(Entity* entity, float offset);
	void updateEnemyCollision();
	void updatePlayerCollision();
	void updateUpgradeCollision();
	void updateGUI();
	void updateEnemyAnimation(Enemy* enemy);
	void updatePlayerAnimation();
	void updateExplosions();
	void updateUpgrades();
	void updateWorld();

	//render
	void render();
	void renderGUI();

	//accessors
	const bool running() const;

	//functions
	void nextWave();
	void moveInRect(Enemy* enemy);
	void spawnEnemyOne(sf::Vector2f initialPosition, unsigned posInWave);
	void spawnBounceEnemyOne(sf::Vector2f initialPosition, unsigned posInWave);

	void spawnEnemyTwo(sf::Vector2f initialPosition, unsigned posInWave);
	void spawnCircleEnemyTwo(sf::Vector2f initialPosition, unsigned posInWave);

	void spawnEnemyThree(sf::Vector2f initialPosition, unsigned posInWave);
	void spawnBurstEnemyThree(sf::Vector2f initialPosition, unsigned posInWave);

	void spawnEnemyFour(sf::Vector2f initialPosition, unsigned posInWave);
	void spawnBoss(sf::Vector2f initialPosition, unsigned posInWave);

	void spawnRandomEnemy();

	void enemyOneFirePattern();
	void bounceEnemyOneFirePattern();

	void enemyTwoFirePattern();
	void circleEnemyTwoFirePattern();

	void enemyThreeFirePattern();
	void burstEnemyThreeFirePattern();

	void enemyFourFirePattern(Enemy* enemy);
	void bossFirePattern(Enemy* enemy);
	void bossPatternOne(Enemy* enemy);
	void bossPatternTwo(Enemy* enemy);
	void bossPatternThree(Enemy* enemy);
	void bossPatternFour(Enemy* enemy);

	void fireSpread(const std::string character, sf::Texture* bulletTexture, sf::FloatRect bulletHitbox, int bulletType, float bulletSpeed, float spreadDegree);
	void fireWave(sf::Texture* bulletTexture, sf::FloatRect bulletHitbox, int bulletType, float bulletSpeed, float bulletOffset, sf::Vector2f baseAimDir, Enemy* enemy);
	void fireInCircle(const std::string character, sf::Texture* bulletTexture, sf::FloatRect bulletHitbox, int bulletType, float bulletSpeed, sf::Vector2f centerPos, float offSet);
	void fireClusterShot(const std::string character, sf::Texture* bulletTexture, sf::FloatRect bulletHitbox, int bulletType, float bulletSpeed);
	void burstClusterShot(const std::string character, sf::Vector2f burstPos, sf::Texture* bulletTexture, sf::FloatRect bulletHitbox, int bulletType, float bulletSpeed);
	void fireDoubleBullets(const std::string character, sf::Texture* bulletTexture, sf::FloatRect bulletHitbox, int bulletType, float bulletSpeed);

	void waveOne();
	void waveTwo();
	void waveThree();
	void waveFour();
	void waveFive();
	void waveSix();
	void waveSeven();
	void waveEight();
	void waveNine();
	void waveTen();
	void bossWave();

	//void spawnEnemies();
	bool run();
	void run2();


	//upgrades functions
	void dropPowerUp(Enemy* enemy);

	/*void upgradesUpdate(const float& dt);
	void gunUpdate(const float& dt);
	bool gunStatus();

	void fireRTUpdate(const float& dt);
	bool fireRTStatus();*/

	void reset();
	void reset2();

};

#endif