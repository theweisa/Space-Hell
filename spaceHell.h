#ifndef GAME_H			
#define GAME_H

//include sfml libraries
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <iostream>			//standard library
#include <ctime>			//time
#include <string>			//strings
#include <vector>			//vectors
#include <unordered_map>	//unordered maps
#include <sstream>			//string stream
#include <cstdlib>			//rand
#include <iterator>			//iterators
#include <fstream>			//files

#include "Upgrade.h"
#include "Explosion.h"
#include "Background.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "highScores.h"

#include "Slider.h"

using namespace ent;

/*
GAME CLASS
the entirety of the game
*/
class Game
{
private:
	//general private variables
	const float pi = 3.14159f; //pi!

	//*******window*******
	sf::RenderWindow* window; //the window that the game appears in
	sf::Event ev; //events that occur in the window
	sf::VideoMode videoMode;
	float windowWidth; //width of the window
	float windowHeight; //height of the window
	float scale; //scale the 

	//*******player*******
	Player* player;

	//*******world*******
	Background* spaceBackground;

	//*******resources*******
	//visual assets
	std::unordered_map<std::string, sf::Texture*> assets;	//contains all of the game's textures and animations
	std::unordered_map<std::string, sf::Text*> texts;		//contains all the texts for the game

	//sounds
	sf::Music normalBGM;									//back ground ost
	sf::Music bossBGM;										//boss ost
	std::map<std::string, sf::SoundBuffer*> soundBuffers;	//sound buffers
	std::map<std::string, sf::Sound*> sounds;				//sounds
	float musicVolume;	
	float soundVolume;

	//vectors for stuff
	std::vector<Bullet*> playerBullets;						//vector containing the players bullets
	std::vector<Bullet*> enemyBullets;						//vector containing the enemys bullets
	std::vector<Enemy*> enemies;							//vector containing all the enemies
	std::vector<Explosion*> explosions;						//vector containing all the explosion objects
	std::vector<Upgrade*> upgrades;							//vector containing all the upgrade objects
	sf::Font font;											//font the game uses
	sf::Sprite displayScreen;								//sprite of the display
	sf::Sprite smallerScreen;

	//*******Mouse position*******
	sf::Vector2i mousePosWindow;	//gets mouse position relative to window
	sf::Vector2f mousePosView;		//gets mouse position relative to screen

	//*******Timer*******
	sf::Clock deltaClock;	//clock to get the time of one frame
	float deltaTime;		//time it takes for one frame
	float spawnTimer;		//the timer of when events happen in a wave
	float spawnTimerMax;	//max timer of which things spawn

	//*******positions*******
	sf::Vector2f playerPos;			//the players current position
	sf::Vector2f enemyPos;			//position of an enemy
	float mouseAngle;				//angle of the player relative to the mouse position; for rotating
	float enemyAngle;				//angle of the enemy relative to the player; for rotating
	sf::Vector2f playerAimDir;		//the direction that the player is aiming
	sf::Vector2f enemyAimDir;		//the direction that the enemy is aiming
	sf::Vector2f baseEnemyAimDir;	//the base direction an enemy is aiming 

	//*******game logic*******

	//enemy variables
	bool moveUp;			//will move the enemy up, down, right, or left
	bool moveRight;
	bool enemyDestroyed;	//check if an enemy has been destroyed
	int numEnemies;			//the number of enemies spawned in a wave
	int numEnemiesDestroyed; //the number of enemies destroyed in a wave
	bool enemyFireCluster;	//bool to detonate the enemy's cluster shot
	int bossPattern;		//the bosses current firing pattern
	bool bossEnraged;		//bool to see if the boss is enraged
	bool bossDestroyed;		//bool to see if the boss has been destroyed

	//player variables
	bool playerDestroyed;
	float playerInvulTimer;		//timer that determines if player is invulnerable
	float playerInvulTimerMax;	//the length of the players invincibility
	bool playerFireCluster;		//bool to detonate player's cluster shot
	int playerFirePattern;		//int to decide the players firing pattern
	float totalPlayerDamageUp;	//keeps track of the players damage upgrades to transfer 
	float totalPlayerFireRateUp; //keeps track of the players fire rate upgrades to transfer

	//debug mode variables
	bool printDebugCommands;
	bool playerInvincible;
	bool debugMode;

	//game variables
	bool startMusic;
	bool startBossMusic;
	bool displayCredits;
	bool displayOptions;
	bool displayVolume;
	bool displayPause;
	bool gameStarted;			//check if the game has been started yet from the main menu
	int currentWave;		//the current wave the game is on
	bool pause;				//if the game is paused
	int select;
	float pauseBuffer;		//buffer before you can pause again
	float pauseBufferMax;	//buffer for when you can unpause
	float selectBuffer;		//buffer for when you can select
	float selectBufferMax;	//max buffer
	bool gameOver;			//determines if game is over
	unsigned int points;	//the player's points
	unsigned int combo;		//the player's current combo

	//private functions
	void initVariables();	//initialize the game variables and clock
	void initWindow();		//initialize the window
	void initAssets();		//initialize the assets
	void addAsset(const std::string key, const std::string fileName); //add an asset to the assets vector
	void initGUI();			//initialize the GUI; text and fonts
	void addText(const std::string key, unsigned charSize, sf::Color color, const std::string initialText, sf::Vector2f initialPos); //add text to the texts vector
	void initWorld();		//initialize the background
	void initPlayer();		//initialize the player and player variables
	void initEnemy();		//initialize the enemy and enemy variables
	void resetGame(bool returnToMainMenu);		//reset the game; if returnToMainMenu is true, go to main menu; else reset the level

	//audio
	void initAudio();
	void addSound(const std::string key, const std::string fileName, float volume);

	//*************************FUNCTIONS***************************
	//update functions
	void update();				//update all the other updates
	void updatePause();			//update if the game is paused
	void updateSelect();		//update the select timer
	void updateDeltaTime();		//update delta time to check the time for one frame
	void updateMousePos();		//update the mouse's position
	void updatePollEvents();	//update events like key presses
	void updatePlayer();		//update the player's movement, key presses, and fire patterns
	void updateEnemies();		//update the enemies firing and the current wave
	void updateBullets();		//update the bullets movement
	void updateWorldCollision(Entity* entity, float offset);	//update if the entity hit the world and stop it from going outside the border
	void updateEnemyCollision();	//update entity's colliding with the enemy
	void updatePlayerCollision();	//update entity's colliding with the player
	void updateUpgradeCollision();	//update entitiy's colliding with the upgrades
	void updateGUI();				//update the GUI; interface
	void updateEnemyAnimation(Enemy* enemy);	//update the enemy's animation
	void updatePlayerAnimation();	//update the player's animations
	void updateExplosions();		//update the explosion's animations
	void updateUpgrades();			//update the upgrade's animations and despawn
	void updateWorld();				//update the background's animation
	void setMusicVolume(float value);
	void setSoundVolume(float value);

	//render
	void render();			//render everything to the screen.
	void renderMainMenu();
	void renderOptions();
	void renderVolumeSlider();
	void renderCredits();
	void renderGame();
	void renderPauseMenu();
	void renderGameOverScreens();
	void renderGUI();		//render the texts

	//accessors
	const bool running() const;	//check if the game is running

	//functions
	void startGame();
	void dropPowerUp(Enemy* enemy); //enemy drops a power up
	void nextWave();				//move to the next wave
	void moveInRect(Enemy* enemy);	//move an enemy in a rectangle

	//menu functions
	void interactMainMenu();
	void interactOptions();
	void interactCredits();
	void interactPauseMenu();
	void interactGameOver();
	void interactVolume();

	//***************ENEMY SPAWNS***************
	//spawn an enemy at a position, as the nth enemy in a wave
	void spawnEnemyOne(sf::Vector2f initialPosition, unsigned posInWave);			//spawn enemy one
	void spawnBounceEnemyOne(sf::Vector2f initialPosition, unsigned posInWave);		//spawn bounce enemy one
	void spawnEnemyTwo(sf::Vector2f initialPosition, unsigned posInWave);			//spawn enemy two
	void spawnCircleEnemyTwo(sf::Vector2f initialPosition, unsigned posInWave);		//spawn circle shot enemy two
	void spawnEnemyThree(sf::Vector2f initialPosition, unsigned posInWave);			//spawn enemy three
	void spawnBurstEnemyThree(sf::Vector2f initialPosition, unsigned posInWave);	//spawn burst shot enemy three
	void spawnEnemyFour(sf::Vector2f initialPosition, unsigned posInWave);			//spawn enemy four
	void spawnBoss(sf::Vector2f initialPosition, unsigned posInWave);				//spawn the boss
	void spawnRandomEnemy();														//spawn a random enemy

	//***************ENEMY FIRE PATTERNS***************
	void enemyOneFirePattern();					//enemy one's fire pattern
	void bounceEnemyOneFirePattern();			//bounce shot enemy one's fire pattern
	void enemyTwoFirePattern();					//enemy two's fire pattern
	void circleEnemyTwoFirePattern();			//circle shot enemy two's fire pattern
	void enemyThreeFirePattern();				//enemy three's fire pattern
	void burstEnemyThreeFirePattern();			//burst shot enemy three's fire pattern
	void enemyFourFirePattern(Enemy* enemy);	//enemy four's fire pattern
	void bossFirePattern(Enemy* enemy);			//boss' fire patterns
	void bossPatternOne(Enemy* enemy);			//boss' first fire pattern
	void bossPatternTwo(Enemy* enemy);			//boss' second fire pattern
	void bossPatternThree(Enemy* enemy);		//boss' third fire pattern
	void bossPatternFour(Enemy* enemy);			//boss; fourth fire pattern

	//***************TYPES OF FIRE PATTERNS***************
	//a character fires a shot gun spread show
	void fireSpread(const std::string character, sf::Texture* bulletTexture, sf::FloatRect bulletHitbox, int bulletType, float bulletSpeed, float spreadDegree);
	//an enemy fires in a wave (no use making players fire this way)
	void fireWave(sf::Texture* bulletTexture, sf::FloatRect bulletHitbox, int bulletType, float bulletSpeed, float bulletOffset, sf::Vector2f baseAimDir, Enemy* enemy);
	//a character fires 16 bullets in a circle
	void fireInCircle(const std::string character, sf::Texture* bulletTexture, sf::FloatRect bulletHitbox, int bulletType, float bulletSpeed, sf::Vector2f centerPos, float offSet);
	//a character fires a cluster shot bullet that bursts once it reaches the position it was initially aimed at when fired
	void fireClusterShot(const std::string character, sf::Texture* bulletTexture, sf::FloatRect bulletHitbox, int bulletType, float bulletSpeed);
	//burst the cluster shot once it reaches it's destination
	void burstClusterShot(const std::string character, sf::Vector2f burstPos, sf::Texture* bulletTexture, sf::FloatRect bulletHitbox, int bulletType, float bulletSpeed);
	//a character fires two streams of bullets next to them
	void fireDoubleBullets(const std::string character, sf::Texture* bulletTexture, sf::FloatRect bulletHitbox, int bulletType, float bulletSpeed);
	//bounce an enemy bullet
	void bounceBullet(Bullet* bullet);

	//DEBUG MODE
	void gameDebugMode();

	//***************WAVE TYPES***************
	//waves that spawn enemies and move them in a certain pattern varying with waves
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

	//***************SCORE***************
	void printHighScores();

	//play music
	void playBGM();
	void playBossBGM();

	//*******PUBLIC MEMBERS*******
public:
	//constructor/destructor
	Game();		//constructor that initializes all the game's variables
	~Game();	//destructor that frees all the used memory
	void run();	//runs the game when called in main
};

#endif