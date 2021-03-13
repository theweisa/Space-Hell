#include "game.h"

/*
*****************************************constructor / destructor*****************************************
*/

//constructor
Game::Game() 
{ 
	//initialize the game variables
	this->initVariables();

	//initialize the window
	this->initWindow();

	//initialize assets
	this->initAssets();

	//initialize the audio
	this->initAudio();

	//initialize the world sprite
	this->initWorld();

	//initialize the GUI
	this->initGUI();
}

//destructor
Game::~Game() 
{
	//delete the window
	delete this->window;

	//delete the player
	delete this->player;

	//delete textures
	for (auto& texture : this->assets)
	{
		delete texture.second;
	}
	
	//delete texts
	for (auto& text : this->texts)
	{
		delete text.second;
	}

	//delete player bullets
	for (auto* bullet : this->playerBullets)
	{
		delete bullet;
	}

	//delete enemy bullets
	for (auto* bullet : this->enemyBullets)
	{
		delete bullet;
	}

	//delete enemies
	for (auto* enemy : this->enemies)
	{
		delete enemy;
	}

	//delete all the explosion animations
	for (auto* explosion : this->explosions)
	{
		delete explosion;
	}

	//delete all the upgrades
	for (auto* upgrade : this->upgrades)
	{
		delete upgrade;
	}

	//delete all the sounds
	for (auto& s : this->sounds)
	{
		delete s.second;
	}

	//delete the background
	delete spaceBackground;
}

/*
*****************************************private functions*****************************************
*/

//initialize game variables
void Game::initVariables()
{
	this->startMusic = false;

	this->startBossMusic = false;

	this->gameStarted = false;

	this->displayCredits = false;
	
	this->displayOptions = false;

	this->window = nullptr;

	this->gameOver = false;

	this->pause = false;
	this->select = -1;		//for moving past the game over screen

	//initialize the pause buffer; one second
	this->pauseBufferMax = 0.5f;
	this->pauseBuffer = pauseBufferMax;
	this->selectBufferMax = 0.1f;
	this->selectBuffer = selectBufferMax;

	//initialize points to 0
	this->points = 0;

	//initialize combo to 1; multiplies the score you gain
	this->combo = 1;

	//set the first wave
	this->currentWave = 11;

	//delta time is 0
	this->deltaTime = 0.f;
}

//initialize window
void Game::initWindow()
{
	// Create a window with the same pixel depth as the desktop
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

	//****games main resolution is in 640 x 480****
	//define the base height and base width to get the scale of the new resolution
	float baseHeight = 480.f;
	float baseWidth = 640.f;

	//set the resolution of the gam
	this->videoMode.height = 768;
	this->videoMode.width = 1024;
	this->window = new sf::RenderWindow(this->videoMode, "Game", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize); //dynamically allocate mem for window


	//height of the window
	windowHeight = static_cast<float>(window->getSize().y);

	//width of the window
	windowWidth = static_cast<float>(window->getSize().x);

	//the scale of all the assets based on the resolution compared to the base resolution
	scale = videoMode.height / baseHeight;

	//set the max frame rate
	this->window->setFramerateLimit(60);
}

//initialize the textures and animations; assets
void Game::initAssets()
{
	//initialize animations
	addAsset("spaceBackground", "Animations/blurredSpaceBackground.png");
	addAsset("destroyedSheet", "Animations/enemyDestroyedSheet.png");
	addAsset("playerSpawn", "Animations/playerSpawnSheet.png");
	addAsset("playerIdle", "Animations/playerIdleSheet.png");
	addAsset("playerDamaged", "Animations/playerDamagedSheet.png");
	addAsset("enemyOneSpawn", "Animations/enemy1SpawnSheet.png");
	addAsset("enemyOneIdle", "Animations/enemy1IdleSheet.png");
	addAsset("bounceEnemyOneSpawn", "Animations/bounceEnemy1SpawnSheet.png");
	addAsset("bounceEnemyOneIdle", "Animations/bounceEnemy1IdleSheet.png");
	addAsset("enemyTwoSpawn", "Animations/enemy2SpawnSheet.png");
	addAsset("enemyTwoIdle", "Animations/enemy2IdleSheet.png");
	addAsset("circleEnemyTwoSpawn", "Animations/circleEnemy2SpawnSheet.png");
	addAsset("circleEnemyTwoIdle", "Animations/circleEnemy2IdleSheet.png");
	addAsset("enemyThreeSpawn", "Animations/enemy3SpawnSheet.png");
	addAsset("enemyThreeIdle", "Animations/enemy3IdleSheet.png");
	addAsset("burstEnemyThreeIdle", "Animations/burstEnemy3IdleSheet.png");
	addAsset("burstEnemyThreeSpawn", "Animations/burstEnemy3SpawnSheet.png");
	addAsset("enemyFourSpawn", "Animations/enemy4SpawnSheet.png");
	addAsset("enemyFourIdle", "Animations/enemy4IdleSheet.png");
	addAsset("bossEnemySpawn", "Animations/bossEnemySpawnSheet.png");
	addAsset("bossEnemyIdle", "Animations/bossEnemyIdleSheet.png");

	//upgrades
	addAsset("damageUpIdle", "Animations/damageUpIdleSheet.png");
	addAsset("hpUpIdle", "Animations/hpUpIdleSheet.png");
	addAsset("fireRateUpIdle", "Animations/fireRateUpIdleSheet.png");
	addAsset("doubleBulletUpIdle", "Animations/doubleBulletUpIdleSheet.png");
	addAsset("spreadBulletUpIdle", "Animations/spreadBulletUpIdleSheet.png");
	addAsset("burstBulletUpIdle", "Animations/burstBulletUpIdleSheet.png");

	//textures
	addAsset("playerBullet", "Textures/player_bullet.png");
	addAsset("bigPlayerBullet", "Textures/bigPlayerBullet.png");
	addAsset("longEnemyBullet", "Textures/enemy_bullet_long.png");
	addAsset("enemyBullet", "Textures/enemy_bullet.png");
	addAsset("enemyOne", "Textures/enemy1.png");
	addAsset("bounceEnemyOne", "Textures/bounceEnemy1.png");
	addAsset("enemyTwo", "Textures/enemy2.png");
	addAsset("circleEnemyTwo", "Textures/circleEnemy2.png");
	addAsset("enemyThree", "Textures/enemy3.png");
	addAsset("burstEnemyThree", "Textures/burstEnemy3.png");
	addAsset("enemyFour", "Textures/enemy4.png");
	addAsset("bossEnemy", "Textures/bossEnemy.png");
	addAsset("bigEnemyBullet", "Textures/bigEnemyBullet.png");
	addAsset("bouncingEnemyBullet", "Textures/bouncingEnemyBullet.png");
	addAsset("displayScreen", "Textures/displayScreen.png");
	addAsset("smallerScreen", "Textures/smallerScreen.png");
}

//small function to add an asset to the assets map
void Game::addAsset(const std::string key, const std::string fileName)
{
	this->assets[key] = new sf::Texture();
	if (!this->assets[key]->loadFromFile(fileName))
	{
		std::cout << "ERROR: failed to load " << fileName << std::endl;
	}
}

//initialize the music and sound effects
void Game::initAudio()
{
	if (!this->normalBGM.openFromFile("Audio/bgm.wav"))
	{
		std::cout << "ERROR: failed to load bgm.wav" << std::endl;
	}
	if (!this->bossBGM.openFromFile("Audio/bossMusic.wav"))
	{
		std::cout << "ERROR: failed to load bossMusic.wav" << std::endl;
	}

	addSound("playerBullet", "Audio/playerBullet.wav");
	addSound("enemyBullet", "Audio/enemyBullet.wav");
	addSound("longEnemyBullet", "Audio/longEnemyBullet.wav");
	addSound("enemySpawn", "Audio/enemySpawn.wav");
	addSound("playerHit", "Audio/playerHit.wav");
	addSound("enemyHit", "Audio/enemyHit.wav");
	addSound("explosion", "Audio/explosion.wav");
	addSound("itemDrop", "Audio/itemDrop.wav");
	addSound("itemPickUp", "Audio/itemPickUp.wav");
	addSound("emergency", "Audio/emergency.wav");
	addSound("gameover", "Audio/gameover.wav");

	this->sounds["emergency"]->setLoop(true);
}

//add sounds
void Game::addSound(const std::string key, const std::string fileName)
{
	this->soundBuffers[key] = new sf::SoundBuffer();
	if (this->soundBuffers[key]->loadFromFile(fileName))
	{
		this->sounds[key] = new sf::Sound();
		this->sounds[key]->setBuffer(*(this->soundBuffers[key]));
	}
	else
		std::cout << "ERROR: failed to load " << fileName << std::endl;
}

void Game::startGame()
{
	std::cout << "start game called\n";
	//initialize player and player variables
	this->initPlayer();
	//initialize the enemy variables
	this->initEnemy();
}

//initialize the GUI elements like text and screens
void Game::initGUI()
{
	if (!font.loadFromFile("Fonts/Minecraft.ttf"))
		std::cout << "ERROR: failed to load font.\n";

	//initialize the text
	addText("pointText", static_cast<unsigned>(20.f * scale), sf::Color::White, "POINT_TEXT", sf::Vector2f(20.f, windowHeight - 50.f));

	//add the combo text
	addText("comboText", static_cast<unsigned>(20.f * scale), sf::Color::White, "COMBO_TEXT", sf::Vector2f(0.f, 0.f));
	texts["comboText"]->setPosition(sf::Vector2f(windowWidth - texts["comboText"]->getGlobalBounds().width, windowHeight - 50.f));

	//add player hp text
	addText("playerHpText", static_cast<unsigned>(20.f * scale), sf::Color::White, "HP_TEXT", sf::Vector2f(20.f, windowHeight - 100.f));

	//add game over text
	addText("gameOverText", static_cast<unsigned>(40.f * scale), sf::Color::White, "GAME OVER", sf::Vector2f(0.f, 0.f));
	texts["gameOverText"]->setPosition(sf::Vector2f((windowWidth - texts["gameOverText"]->getGlobalBounds().width) * 0.5f,
		(windowHeight - texts["gameOverText"]->getGlobalBounds().height) * 0.5f));

	//add level complete text
	addText("levelCompleteText", static_cast<unsigned>(40.f * scale), sf::Color::White, "LEVEL COMPLETE", sf::Vector2f(0.f, 0.f));
	texts["levelCompleteText"]->setPosition(sf::Vector2f((windowWidth - texts["levelCompleteText"]->getGlobalBounds().width) * 0.5f,
		(windowHeight - texts["levelCompleteText"]->getGlobalBounds().height) * 0.5f));

	//add pause text 
	addText("pauseText", static_cast<unsigned>(40.f * scale), sf::Color::White, "PAUSE", sf::Vector2f(0.f, 0.f));
	texts["pauseText"]->setPosition(sf::Vector2f((windowWidth - texts["pauseText"]->getGlobalBounds().width) * 0.5f,
		(windowHeight - texts["pauseText"]->getGlobalBounds().height) * 0.2f));

	//add score text
	addText("scoreText", static_cast<unsigned>(30.f * scale), sf::Color::White, "", sf::Vector2f(0.f, 0.f));

	//add main menu text
	addText("returnToMainMenuText", static_cast<unsigned>(20.f * scale), sf::Color::White, "Return to Main Menu", sf::Vector2f(0.f, 0.f));
	texts["returnToMainMenuText"]->setPosition(sf::Vector2f((windowWidth - texts["returnToMainMenuText"]->getGlobalBounds().width) * 0.5f,
		(windowHeight - texts["returnToMainMenuText"]->getGlobalBounds().height) * 0.45f));

	//add restart level text
	addText("restartLevelText", static_cast<unsigned>(20.f * scale), sf::Color::White, "Restart Level", sf::Vector2f(0.f, 0.f));
	texts["restartLevelText"]->setPosition(sf::Vector2f((windowWidth - texts["restartLevelText"]->getGlobalBounds().width) * 0.5f,
		(windowHeight - texts["restartLevelText"]->getGlobalBounds().height) * 0.55f));

	//add title screen text
	addText("titleScreenText", static_cast<unsigned>(50.f * scale), sf::Color::White, "SPACE HELL", sf::Vector2f(0.f, 0.f));
	texts["titleScreenText"]->setPosition(sf::Vector2f((windowWidth - texts["titleScreenText"]->getGlobalBounds().width) * 0.5f,
		(windowHeight - texts["titleScreenText"]->getGlobalBounds().height) * 0.4f));

	addText("startGameText", static_cast<unsigned>(20.f * scale), sf::Color::White, "Start Game", sf::Vector2f(0.f, 0.f));
	texts["startGameText"]->setPosition(sf::Vector2f((windowWidth - texts["startGameText"]->getGlobalBounds().width) * 0.5f,
		(windowHeight - texts["startGameText"]->getGlobalBounds().height) * 0.6f));

	addText("optionsText", static_cast<unsigned>(20.f * scale), sf::Color::White, "Options", sf::Vector2f(0.f, 0.f));

	addText("creditsText", static_cast<unsigned>(20.f * scale), sf::Color::White, "Credits", sf::Vector2f(0.f, 0.f));
	texts["creditsText"]->setPosition(sf::Vector2f((windowWidth - texts["creditsText"]->getGlobalBounds().width) * 0.5f,
		(windowHeight - texts["creditsText"]->getGlobalBounds().height) * 0.75f));

	const std::string credits = "-----CREDITS-----\n****Developers****\n- Andrew Wei\n- Ku Yi Sien\n- Kena Shi\n- Kaeda Hamada\n\n****Art Direction****\n- Andrew Wei\n\n****Sound Direction****\n- Sebastian Eisenbach\n- Kaeda Hamda";

	addText("displayCredits", static_cast<unsigned>(17.5f * scale), sf::Color::White, credits, sf::Vector2f(0.f, 0.f));
	texts["displayCredits"]->setPosition(sf::Vector2f((windowWidth - texts["displayCredits"]->getGlobalBounds().width) * 0.5f,
		(windowHeight - texts["displayCredits"]->getGlobalBounds().height) * 0.5f));

	addText("goBackText", static_cast<unsigned>(20.f * scale), sf::Color::White, "Go Back", sf::Vector2f(0.f, 0.f));
	texts["goBackText"]->setPosition(sf::Vector2f((windowWidth - texts["goBackText"]->getGlobalBounds().width) * 0.5f,
		(windowHeight - texts["goBackText"]->getGlobalBounds().height) * 0.8f));

	//init the pause screen texture
	displayScreen.setTexture(*assets["displayScreen"]);
	displayScreen.setOrigin(displayScreen.getTexture()->getSize().x * 0.5f, displayScreen.getTexture()->getSize().y * 0.5f);
	displayScreen.scale(16 * scale, 16 * scale);
	displayScreen.setPosition(windowWidth * 0.5f, windowHeight * 0.5f);

	//init the smaller screen texture
	smallerScreen.setTexture(*assets["smallerScreen"]);
	smallerScreen.setOrigin(smallerScreen.getTexture()->getSize().x * 0.5f, smallerScreen.getTexture()->getSize().y * 0.5f);
	smallerScreen.scale(16 * scale, 16 * scale);
	smallerScreen.setPosition(windowWidth * 0.5f, windowHeight * 0.5f);
}

//sets a text's font, size, color, the initial string, and its position
void Game::addText(const std::string key, unsigned charSize, sf::Color color, const std::string initialText, sf::Vector2f initialPos)
{
	texts[key] = new sf::Text;					//create new text
	texts[key]->setFont(font);					//set the font
	texts[key]->setCharacterSize(charSize);		//set the text character size
	texts[key]->setFillColor(color);			//set the text color
	texts[key]->setString(initialText);			//set the string
	texts[key]->setPosition(initialPos);		//set the initial position
}

//initialize world background
void Game::initWorld()
{
	this->spaceBackground = new Background(assets["spaceBackground"], sf::Vector2f(windowWidth * 0.5f, windowHeight * 0.5f), scale);
}

//initialize player variables
void Game::initPlayer()
{
	playerDestroyed = false;
	//set the player]s initial position at the bottom middle of the screen when spawning
	sf::Vector2f initialPos(windowWidth * 0.5f, windowHeight - 100.f);

	//spawn the player
	this->player = new Player(initialPos, scale);

	/*
	FIRE PATTERNS:
	- 0: default
	- 1: double bullets
	- 2: spread shot
	- 3: cluster shot
	*/
	//initialize player patterm to 0; the default fire pattern
	playerFirePattern = 3;

	//initialize the damage and fire rate upgrades they've gotten throughout the game
	totalPlayerDamageUp = 0.f;
	totalPlayerFireRateUp = 0.f;

	playerFireCluster = false;

	//player has invulnerability for 2 seconds when invul
	this->playerInvulTimerMax = 2.f;
	this->playerInvulTimer = this->playerInvulTimerMax;
	this->player->setRotate(0.f);

	//set the spawn animation
	player->setSpawnAnimation("spawnAnimation", this->assets["playerSpawn"], 4, 0, 64, 64);
}

//initialize enemy variables
void Game::initEnemy()
{
	enemyDestroyed = false;
	moveUp = false;
	moveRight = false;
	numEnemiesDestroyed = 0;
	numEnemies = 0;
	enemyFireCluster = false;
	bossEnraged = false;
	bossDestroyed = false;
	spawnTimer = 0.f;
}

/*
*****************************************update functions*****************************************
*/

//update the game 
void Game::update()
{
	//move player based on input
	this->updatePlayer();

	//update player's rotation and fire rate
	this->player->update();

	//update world collision with player
	this->updateWorldCollision(player, 0.f);

	//update enemy firing
	this->updateEnemies();

	//update the bullet movements
	this->updateBullets();

	//update if the player collided with a hitbox
	this->updatePlayerCollision();

	//update if the enemy collided with a hitbox
	this->updateEnemyCollision();

	//update if the upgrade collided with a hitbox
	this->updateUpgradeCollision();

	//update the explosion animations
	this->updateExplosions();

	//update the upgrade animations and despawn timer
	this->updateUpgrades();
	
	//update text
	this->updateGUI();
}

//outside the update function since the game stop's updating when paused
void Game::updatePause()
{
	//increment pause buffer
	pauseBuffer += deltaTime;

	//if user presses P, pause/unpause the game
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
	{
		//if the user can pause/unpause depending on the timer, pause/unpause
		if (pauseBuffer > pauseBufferMax)
		{
			//reset the pause buffer
			pauseBuffer = 0.f;
			if (!pause)
			{
				normalBGM.pause();
				pause = true;
			}
			else
			{
				normalBGM.play();
				pause = false;
			}
		}
	}
}

//select one of the text options
void Game::updateSelect()
{
	selectBuffer += deltaTime;
}

//time it takes to update and render one frame
void Game::updateDeltaTime()
{
	deltaTime = deltaClock.restart().asSeconds();
}

//update mouse position
void Game::updateMousePos()
{
	//updates mouse position relative to window
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

//update player
void Game::updatePlayer()
{
	//updates player position
	playerPos = sf::Vector2f(this->player->getPos().x, this->player->getPos().y);

	//gets the direction the player is aiming based off unit circle; ie.) if facing up, then aimDir = -1, 0; this is for consistent bullet speeds
	//formula for direction: d.x = (m.x - p.x) / sqrt(p.x^2 - m.x^2) + (p.y^2 - m.y^2))
	playerAimDir = mousePosView - playerPos;
	playerAimDir = playerAimDir / sqrt(pow(playerAimDir.x, 2) + pow(playerAimDir.y, 2));

	//get the angle of the mouse relative to the player; will get the angle in terms of degrees
	mouseAngle = -atan2(player->getPos().x - mousePosView.x, player->getPos().y - mousePosView.y) * 180.f / pi;

	//increment invul timer by delta time; time it takes for one frame to update/render
	playerInvulTimer += deltaTime;

	//rotate the player to point towards the mouse
	player->setRotate(mouseAngle);

	//will move the player and do actions depending on key pressed; movement is based on WASD
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->player->move(-1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->player->move(1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->player->move(0.f, 1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->player->move(0.f, -1.f);

	//if player presses space and can fire (fire cooldown < max fire cooldown) , shoot
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->player->canFire())
	{
		//play sound when player shoots
		this->sounds["playerBullet"]->play();

		//if fire pattern 0, shoot default bullets straight
		if (playerFirePattern == 0)
		{
			sf::FloatRect bulletHitbox(1, 1, 6, 6);
			sf::Texture* newTexture = this->assets["playerBullet"];
			int bulletType = 0;
			float bulletSpeed = 8.f * scale;
			this->playerBullets.push_back(new Bullet(*newTexture, bulletType, bulletHitbox, playerPos, mouseAngle, playerAimDir, bulletSpeed, scale));
		}
		//if fire pattern 1, shoot double bullets
		else if (playerFirePattern == 1)
		{
			//double bullets initially do half the damage, but scale very well with damage up
			player->setDamage(0.5f + totalPlayerDamageUp);
			player->setFireRate(5.f - totalPlayerFireRateUp);
			sf::FloatRect bulletHitbox(1, 1, 6, 6);
			sf::Texture* newTexture = this->assets["playerBullet"];
			int bulletType = 0;
			float bulletSpeed = 8.f * scale;

			//shoot two lines of bullets
			fireDoubleBullets("player", newTexture, bulletHitbox, bulletType, bulletSpeed);
		}
		//if fire pattern 2, shoot spread bullets
		else if (playerFirePattern == 2)
		{
			//spread bullets will have a lower fire rate than the default fire rate; still takes into account gathered upgrades
			player->setDamage(0.6f + totalPlayerDamageUp);
			player->setFireRate(10.f - totalPlayerFireRateUp);
			sf::FloatRect bulletHitbox(1, 1, 6, 6);
			sf::Texture* newTexture = this->assets["playerBullet"];
			int bulletType = 0;
			float bulletSpeed = 8.f * scale;

			//shoot spread bullets at a 10 degree angle
			fireSpread("player", newTexture, bulletHitbox, bulletType, bulletSpeed, (pi / 18.f));
		}
		//if fire pattern 3, shoot cluster shot
		else if (playerFirePattern == 3)
		{
			//cluster bullets pierce; do constant damage when in contact with an enemy. so their damage scaling have to be very low to balance the damage. also slower fire rate
			player->setDamage(0.45f + (totalPlayerDamageUp * 0.5f));
			player->setFireRate(20.f - totalPlayerFireRateUp);
			sf::Texture* bulletTexture = this->assets["bigPlayerBullet"];
			sf::FloatRect bulletHitbox(1, 1, 14, 14);
			int bulletType = 12;

			//slower bullets as well
			float bulletSpeed = 2.5f * scale;

			//fire a cluster shot
			fireClusterShot("player", bulletTexture, bulletHitbox, bulletType, bulletSpeed);
		}
	}

	//updates the players current animation
	updatePlayerAnimation();
}

//update enemy wave and firing
void Game::updateEnemies()
{
	//update the wave depending on the current wave
	switch (currentWave)
	{
	case 1:
		waveOne();
		break;
	case 2:
		waveTwo();
		break;
	case 3:
		waveThree();
		break;
	case 4:
		waveFour();
		break;
	case 5:
		waveFive();
		break;
	case 6:
		waveSix();
		break;
	case 7:
		waveSeven();
		break;
	case 8:
		waveEight();
		break;
	case 9:
		waveNine();
		break;
	case 10:
		waveTen();
		break;
	case 11:
		bossWave();
		break;
	}

	//have the enemy shoot
	for (auto* enemy : this->enemies)
	{
		//enemy 2 and 12 will not be able to go past the 50 offset of the border due to having smaller sprites and moving away from the player
		if (enemy->getType() == 2 || enemy->getType() == 12)
			updateWorldCollision(enemy, 50.f);
		//other enemies can't move outside the world border of offset 0
		else
			updateWorldCollision(enemy, 0.f);

		//angle of the player relative to the enemy
		enemyAngle = -atan2(enemy->getPos().x - player->getPos().x, enemy->getPos().y - player->getPos().y) * 180.f / pi;

		//rotate the enemy towards the player
		enemy->setRotate(enemyAngle);
		
		//update enemy fire rate and rotation
		enemy->update();

		//update the enemies current animation
		updateEnemyAnimation(enemy);

		//set the enemy position
		enemyPos = sf::Vector2f(enemy->getPos().x, enemy->getPos().y);

		//gets the cos and sin values of the enemy compared to the player;
		enemyAimDir = playerPos - enemyPos;
		enemyAimDir = enemyAimDir / sqrt(pow(enemyAimDir.x, 2) + pow(enemyAimDir.y, 2));

		//enemy 1 shoots
		if (enemy->getType() == 0)
		{
			//set the aim direction they shoot at
			enemy->setEnemyToPlayerDir(enemyAimDir);
			//if firing not on cooldown, shoot at their designated pattern
			if (enemy->canFire())
			{
				enemyOneFirePattern();
			}
		}

		//bounce enemy 1 shoots
		if (enemy->getType() == 10)
		{
			enemy->setEnemyToPlayerDir(enemyAimDir);
			if (enemy->canFire())
			{
				bounceEnemyOneFirePattern();
			}
		}

		//enemy 2 shoots
		else if (enemy->getType() == 1)
		{
			enemy->setEnemyToPlayerDir(enemyAimDir);
			//enemyToPlayerDir = enemyAimDir;
			if (enemy->canFire())
			{
				enemyTwoFirePattern();
			}
		}

		//circle enemy 2 shoots
		else if (enemy->getType() == 11)
		{
			enemy->setEnemyToPlayerDir(enemyAimDir);
			//enemyToPlayerDir = enemyAimDir;
			if (enemy->canFire())
			{
				circleEnemyTwoFirePattern();
			}
		}

		//enemy 3 shoots
		else if (enemy->getType() == 2)
		{
			enemy->setEnemyToPlayerDir(enemyAimDir);
			if (enemy->canFire())
			{
				enemyThreeFirePattern();
			}
		}

		//circle enemy 3 shoots
		else if (enemy->getType() == 12)
		{
			enemy->setEnemyToPlayerDir(enemyAimDir);
			if (enemy->canFire())
			{
				burstEnemyThreeFirePattern();
			}
		}

		//enemy 4 shoots
		else if (enemy->getType() == 3)
		{
			enemy->setEnemyToPlayerDir(enemyAimDir);
			if (enemy->canFire())
			{
				enemyFourFirePattern(enemy);
			}
		}

		//boss shoots
		else if (enemy->getType() == 100)
		{
			enemy->setEnemyToPlayerDir(enemyAimDir);
			if (enemy->canFire())
			{
				//randomize the boss' fire pattern once their pattern resets (when a pattern is finished)
				if (bossPattern == 0)
					bossPattern = rand() % 4 + 1;
				bossFirePattern(enemy);
			}
		}
	}
}

//update the bullets for the player and the enemy
//use iterators since for some reason, using range based for loops will cause the bullets to glitch and occasionally not update
void Game::updateBullets()
{
	sf::Vector2f playerBulletPos;

	/*
	PLAYER BULLETS: delete bullets that go offscreen; delete cluster bullets once they reach their destination
	*/
	auto itr = playerBullets.begin();
	while (itr != playerBullets.end())
	{
		//update player bullets movements
		(*itr)->update();

		//if the bullet type is 12 (cluster bullet), don't delete the bullet until it reach's the initial position it was aimed at
		if ((*itr)->getType() == 12)
		{
			//make an offset for that base position since its unlikely the bullet will reach that exact position; make a little square where it detonates
			float offsetTop = (*itr)->getBasePos().y + 10.f;
			float offsetBottom = (*itr)->getBasePos().y - 10.f;
			float offsetRight = (*itr)->getBasePos().x - 10.f;
			float offsetLeft = (*itr)->getBasePos().x + 10.f;

			//the cluster bullet deletes once it reaches its destination and bursts
			if (((*itr)->getPos().y < offsetTop && (*itr)->getPos().y > offsetBottom) && ((*itr)->getPos().x < offsetLeft && (*itr)->getPos().x > offsetRight))
			{
				playerBulletPos = (*itr)->getPos();
				itr = playerBullets.erase(itr);
				playerFireCluster = true;
			}
			//if nothing is deleted, increment the iterator
			else
			{
				itr++;
			}
		}

		//remove the bullets when they go off screen
		else if (((*itr)->getPos().y < 0.f) || ((*itr)->getPos().y >= windowHeight) || ((*itr)->getPos().x < 0.f) || ((*itr)->getPos().x >= windowWidth))
			itr = playerBullets.erase(itr);
		//if nothing deleted, increment the iterator
		else
			itr++;
	}
	//if the cluster shot detonated, burst it into small default bullets in a circle
	if (playerFireCluster)
	{
		playerFireCluster = false;
		sf::FloatRect bulletHitbox(1, 1, 6, 6);
		burstClusterShot("player", playerBulletPos, this->assets["playerBullet"], bulletHitbox, 10, 10.f * scale);
	}

	/*
	ENEMY BULLETS: delete them once they go offscreen; cluster bullets deleted if they contact player or reach their destination
	*/
	sf::Vector2f enemyBulletPos;
	itr = enemyBullets.begin();
	while (itr != enemyBullets.end())
	{
		//update bullet's movement
		(*itr)->update();

		//if cluster bullet; detonate at destination
		if ((*itr)->getType() == 12)
		{
			float offsetTop = (*itr)->getBasePos().y + 10.f;
			float offsetBottom = (*itr)->getBasePos().y - 10.f;
			float offsetRight = (*itr)->getBasePos().x - 10.f;
			float offsetLeft = (*itr)->getBasePos().x + 10.f;
			if (((*itr)->getPos().y < offsetTop && (*itr)->getPos().y > offsetBottom) && ((*itr)->getPos().x < offsetLeft && (*itr)->getPos().x > offsetRight))
			{
				enemyBulletPos = (*itr)->getPos();
				itr = enemyBullets.erase(itr);
				enemyFireCluster = true;
			}
			else
				itr++;
		}

		//if bullets reach outside the border, delete them unless they bounce
		else if (((*itr)->getPos().y < 0.f) || ((*itr)->getPos().y >= windowHeight) || ((*itr)->getPos().x < 0.f) || ((*itr)->getPos().x >= windowWidth))
		{
			//if the bullet bounces, bounce it off the wall by changing it's direction
			if ((*itr)->getMaxBounce() > 0)
			{
				//bounce the bullet
				bounceBullet((*itr));
				itr++;
			}
			//if they are not bouncable bullets, erase them once they go offscreen
			else
				itr = enemyBullets.erase(itr);
		}
		else
			itr++;
	}
	
	//if enemy cluster shot detonates, burst it into a circle at the position
	if (enemyFireCluster)
	{
		enemyFireCluster = false;
		sf::FloatRect bulletHitbox(1, 1, 6, 6);
		burstClusterShot("enemy", enemyBulletPos, this->assets["enemyBullet"], bulletHitbox, 10, 3.f * scale);
	}
}

//update if an entity has reached the edge of the window so that it can't move outside the edges
void Game::updateWorldCollision(Entity* entity, float offset)
{
	//Top world collision
	if (entity->getPos().y < offset)
	{
		entity->setPosition(entity->getPos().x, offset);
	}
	//bottom world collision
	if (entity->getPos().y >= windowHeight - offset)
	{
		entity->setPosition(entity->getPos().x, windowHeight - offset);
	}
	//left world collision
	if (entity->getPos().x < offset)
	{
		entity->setPosition(offset, entity->getPos().y);
	}
	//right world collision
	if (entity->getPos().x >= windowWidth - offset)
	{
		entity->setPosition(windowWidth - offset, entity->getPos().y);
	}
}

//update if hitbox collides with enemy
void Game::updateEnemyCollision()
{
	//need to keep track of vect pos to delete from vector
	int unsigned enemyVectPos = 0;
	int unsigned bulletVectPos = 0;

	//check if each enemy has collided with a player bullet
	for (auto *enemy : this->enemies)
	{
		//checks if each bullet has collided with the enemy
		for (auto *bullet : this->playerBullets)
		{
			//returns if enemy hitbox intersects with player bullets
			bool enemyCollision = bullet->getGlobalHitbox().intersects(enemy->getGlobalHitbox());

			//if collision, enemy takes damage
			if (enemyCollision)
			{
				//play sound when enemy takes damage
				if (enemy->getHp() > 0.f && bullet->getType() != 12)
					this->sounds["enemyHit"]->play();

				//if the bullet is hit by a piercing bullet, they take a different damage calculation
				if (bullet->getType() == 12)
				{
					float clusterDamage = 0.2f + (totalPlayerDamageUp * 0.2f);
					enemy->takeDamage(clusterDamage);
				}
				//enemy takes damage equal to player damage
				else
					enemy->takeDamage(player->getDamage());

				//make them flash red for their damaged "animation"
				enemy->restartDamageTimer();

				//set them as damaged
				enemy->setIsDamaged(true);

				//std::cout << "enemy HP: " << enemy->getHp() << std::endl;
				//gain points for hitting the enemy;
				points += 10 * combo;

				//enemy is set to destroyed if hp bar is below 0
				if (enemy->getHp() <= 0.f)
				{
					enemyDestroyed = true;
					//if the enemy is a boss, set the boss to destroyed
					if (enemy->getType() == 100)
						bossDestroyed = true;
				}

				//if player bullet type is 12 (cluster bullet), it doesn't get deleted when it touches an enemy.
				//all other bullets are deleted once they hit an enemy.
				if (bullet->getType() != 12)
				{
					//delete the bullet after it hits the enemy
					delete this->playerBullets[bulletVectPos];
					this->playerBullets.erase(this->playerBullets.begin() + bulletVectPos);
					--bulletVectPos;
				}
			}
			bulletVectPos++;
		}

		//enemy is deleted if it is destroyed, or if the boss has been destroyed all the enemies are destroyed
		if (enemyDestroyed || bossDestroyed)
		{
			//drop a power up
			dropPowerUp(enemy);

			//play sound of explosion
			this->sounds["explosion"]->play();

			//play an explosion animation when an enemy has been destroyed at the position it was destroyed
			explosions.push_back(new Explosion(this->assets["destroyedSheet"], enemy->getPos(), scale));

			//if the boss is destroyed, gain extra points for destroying it
			if (bossDestroyed)
				points += 1000 * combo;
			//destroying the basic enemy gets you 100 points * combo
			else
				points += 100 * combo;

			//increase your combo once you destroy an enemy
			combo += 1;
			numEnemiesDestroyed++;
			enemyDestroyed = false;

			//delete the enemy
			delete this->enemies[enemyVectPos];
			this->enemies.erase(this->enemies.begin() + enemyVectPos);
			--enemyVectPos;
		}
		bulletVectPos = 0;
		enemyVectPos++;
	}
}

//update if hitbox collides with player
void Game::updatePlayerCollision()
{
	unsigned int bulletVectPos = 0;
	unsigned int enemyVectPos = 0;
	bool colliding = false;

	//go through enemy bullets
	for (auto *enemyBullet : this->enemyBullets)
	{
		//if the invul timer is above the set time (not invincible), check for player collision
		if (playerInvulTimer >= playerInvulTimerMax)
		{
			//check if the player collided with an enemy bullet
			bool playerCollision = enemyBullet->getGlobalHitbox().intersects(this->player->getGlobalHitbox());

			//player takes damage, becomes invincible, and combo is reset if hit
			if (playerCollision)
			{
				//play sound when player takes damage
				this->sounds["playerHit"]->play();

				//takes damage if hit
				this->player->takeDamage(1.f);

				//play emergency sound when player's HP gets 1 or less
				if (player->getHp() <= 1.f)
					this->sounds["emergency"]->play();

				//make the player invincible for a time
				playerInvulTimer = 0.f;

				//reset the combo
				combo = 1;

				//delete the enemy bullet that hit the player
				delete enemyBullet;
				this->enemyBullets.erase(this->enemyBullets.begin() + bulletVectPos);

				--bulletVectPos;
				break;
			}

			//go through the enemies
			for (auto *enemy : this->enemies)
			{
				//check if the player collided with the enemy hitbox
				playerCollision = enemy->getGlobalHitbox().intersects(this->player->getGlobalHitbox());

				//player takes damage, becomes invincible, and combo is reset
				if (playerCollision)
				{
					this->player->takeDamage(1.f);
					playerInvulTimer = 0.f;
					combo = 1;
					break;
				}
				enemyVectPos++;
			}
		}
		enemyVectPos = 0;
		bulletVectPos++;
	}
}

//update if upgrade hitbox collided with player
void Game::updateUpgradeCollision()
{
	auto itr = upgrades.begin();
	bool upgradeDeleted = false;
	while (itr != upgrades.end())
	{
		//check if the upgrade collided with the player
		bool upgradeCollision = (*itr)->getGlobalHitbox().intersects(this->player->getGlobalHitbox());
		
		//if the upgrade collides with the player; give the player the upgrade
		if (upgradeCollision)
		{
			//upgrade 1 gives damage boost
			if ((*itr)->getType() == 1)
			{
				//increment damage boost
				totalPlayerDamageUp += 0.2f;

				//additive damage by 0.2
				player->setDamage(player->getDamage() + 0.2f);
				upgradeDeleted = true;
			}
			//upgrade 2 gives one health
			else if ((*itr)->getType() == 2)
			{
				//gives the health only if the player hp is less than the max, else you cannot pick it up
				if (player->getHp() < player->getMaxHp())
				{
					player->setHp(player->getHp() + 1.f);
					upgradeDeleted = true;
				}
			}
			//upgrade 3 gives increased fire rate; decrease fire cooldown
			else if ((*itr)->getType() == 3)
			{
				if (player->getFireRate() > 3.f)
				{
					totalPlayerFireRateUp += 0.2f;
					player->setFireRate(player->getFireRate() - 0.2f);
					upgradeDeleted = true;
				}
			}
			//upgrade 4 gives the player double bullet shots
			else if ((*itr)->getType() == 4)
			{
				//if the player already has double bullet shots, give them increased damage and fire rate instead
				if (playerFirePattern == 1)
				{
					totalPlayerDamageUp += 0.2f;
					totalPlayerFireRateUp += 0.2f;
				}
				playerFirePattern = 1;
				upgradeDeleted = true;
			}
			//upgrade 5 gives player spread shots
			else if ((*itr)->getType() == 5)
			{
				if (playerFirePattern == 2)
				{
					totalPlayerDamageUp += 0.2f;
					totalPlayerFireRateUp += 0.2f;
				}
				playerFirePattern = 2;
				upgradeDeleted = true;
			}
			//upgrade 6 gives player cluster shots
			else if ((*itr)->getType() == 6)
			{
				if (playerFirePattern == 3)
				{
					totalPlayerDamageUp += 0.2f;
					totalPlayerFireRateUp += 0.2f;
				}
				playerFirePattern = 3;
				upgradeDeleted = true;
			}
		}
		//if the upgrade is deleted, give the player 50 * combo points and erase the upgrade
		if (upgradeDeleted)
		{
			//play upgrade picked up sound
			this->sounds["itemPickUp"]->play();

			std::cout << "player damage: " << player->getDamage() << std::endl;
			std::cout << "player fire rate: " << player->getFireRate() << std::endl;
			points += 50 * combo;
			itr = upgrades.erase(itr);
			upgradeDeleted = false;
		}
		else
			itr++;
	}
}

//update the GUI
void Game::updateGUI()
{
	std::stringstream ss;

	//point text
	ss << "POINTS: " << points;
	texts["pointText"]->setString(ss.str());
	ss.str("");

	//combo text
	ss << "COMBO: x" << combo;
	texts["comboText"]->setString(ss.str());
	ss.str("");

	//hp text
	ss << "HP: " << player->getHp();
	texts["playerHpText"]->setString(ss.str());
}

//upgade the enemies animation
void Game::updateEnemyAnimation(Enemy* enemy)
{
	//if the animation is still spawn, update the spawn animation
	if (!enemy->endOfSpawnAnimation())
	{
		enemy->updateAnimation(enemy->getSpawnKey(), deltaTime);
	}
	//if the enemys current animation is spawn, switch to the respective enemies idle animation
	else if (enemy->getCurrentAnimation() == "spawn")
	{
		switch (enemy->getType())
		{
		case 0:
			enemy->setIdleAnimation("idleAnimation", this->assets["enemyOneIdle"], 11, 0, 32, 32);
			break;
		case 10:
			enemy->setIdleAnimation("idleAnimation", this->assets["bounceEnemyOneIdle"], 11, 0, 32, 32);
			break;
		case 1:
			enemy->setIdleAnimation("idleAnimation", this->assets["enemyTwoIdle"], 11, 0, 32, 32);
			break;
		case 11:
			enemy->setIdleAnimation("idleAnimation", this->assets["circleEnemyTwoIdle"], 11, 0, 32, 32);
			break;
		case 2:
			enemy->setIdleAnimation("idleAnimation", this->assets["enemyThreeIdle"], 11, 0, 32, 32);
			break;
		case 12:
			enemy->setIdleAnimation("idleAnimation", this->assets["burstEnemyThreeIdle"], 11, 0, 32, 32);
			break;
		case 3:
			enemy->setIdleAnimation("idleAnimation", this->assets["enemyFourIdle"], 11, 0, 32, 32);
			break;
		case 100:
			enemy->setIdleAnimation("idleAnimation", this->assets["bossEnemyIdle"], 11, 0, 64, 64);
			break;
		}
	}
	//else if the end of the spawn animation, update the animation to be the idle animation
	else if (enemy->getCurrentAnimation() == "idle")
	{
		enemy->updateAnimation(enemy->getIdleKey(), deltaTime);
	}
}

//update the players animation
void Game::updatePlayerAnimation()
{
	//******SET ANIMATION********
	//if the spawn animation ends and current animation is spawn, set the animation to idle
	if (player->endOfSpawnAnimation() && player->getCurrentAnimation() == "spawn")
	{
		player->setIdleAnimation("idleAnimation", this->assets["playerIdle"], 10, 0, 64, 64);
	}

	//if the player is invincible, set the animation to damaged
	else if (playerInvulTimer < playerInvulTimerMax && player->getCurrentAnimation() != "damaged")
	{
		player->setDamagedAnimation("damagedAnimation", this->assets["playerDamaged"], 10, 0, 64, 64);
	}

	//if they are not invincible and the current animation is damaged, set the animation back to idle
	else if (playerInvulTimer >= playerInvulTimerMax && player->getCurrentAnimation() == "damaged")
	{
		player->setIdleAnimation("idleAnimation", this->assets["playerIdle"], 10, 0, 64, 64);
	}

	//*******UPDATE ANIMATION********

	//if the current animation is spawn, update the spawn animation
	if (player->getCurrentAnimation() == "spawn")
	{
		player->updateAnimation(player->getSpawnKey(), deltaTime);
	}

	//if the current animation is idle, update the idle animation
	else if (player->getCurrentAnimation() == "idle")
	{
		player->updateAnimation(player->getIdleKey(), deltaTime);
	}

	//if the current animation is damaged, update the damage animation
	else if (player->getCurrentAnimation() == "damaged")
	{
		player->updateAnimation(player->getDamagedKey(), deltaTime);
	}
}

//update the explosion animation
void Game::updateExplosions()
{
	auto itr = explosions.begin();
	while (itr != explosions.end())
	{
		(*itr)->setTime(deltaTime);
		//update the animation
		(*itr)->update();
		//if the animation is on it's last frame, erase the explosion
		if ((*itr)->getEndOfAnimation("explosion"))
		{
			itr = explosions.erase(itr);
		}
		else
			itr++;
	}
}

//update the upgrade's animation
void Game::updateUpgrades()
{
	auto itr = upgrades.begin();
	while (itr != upgrades.end())
	{
		//update despawn timer
		(*itr)->setTime(deltaTime);
		(*itr)->update();
		//if the upgrade despawns, delete it
		if ((*itr)->isDespawned())
		{
			std::cout << "upgrade deleted" << std::endl;
			itr = upgrades.erase(itr);
		}
		else
			itr++;
	}
}

//update the background animation
void Game::updateWorld()
{
	spaceBackground->setTime(deltaTime);
	spaceBackground->update();
}

//update poll events
void Game::updatePollEvents()
{
	//while you are getting events from the window
	while (this->window->pollEvent(this->ev))
	{
		//check the event type
		switch (this->ev.type)
		{
		//if the event is closed, close the window
		case sf::Event::Closed:
			this->window->close(); 
			break;
		//check for keyboard press
		case sf::Event::KeyPressed:
			//if the key pressed is escape, close the window
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			/*
			if (this->ev.key.code == sf::Keyboard::Space && gameOver)
			{
				//this->reset();
			}
			*/
			break;
		}
	}
}

/*
*****************************************render functions*****************************************
*/

//render the game; the things that are rendered first appear first and last appear last; like layers
void Game::render()
{
	//clear the previous render
	this->window->clear();

	//render the background
	this->spaceBackground->render(*this->window);

	//if the game has not started, render the main menu
	if (!gameStarted && !displayCredits && !displayOptions)
	{
		renderMainMenu();
	}
	//otherwise if the game has started, render the game
	else if (gameStarted)
	{
		renderGame();
	}

	//print the game over screens if the game is over
	if (gameOver)
	{
		renderGameOverScreens();
	}

	if (displayCredits)
	{
		renderCredits();
	}
	else if (displayOptions)
	{
		renderOptions();
	}
	//render the window
	this->window->display();
}

//render the main menu
void Game::renderMainMenu()
{
	window->draw(*texts["titleScreenText"]);
	window->draw(*texts["startGameText"]);

	//move the options text
	texts["optionsText"]->setPosition(sf::Vector2f((windowWidth - texts["optionsText"]->getGlobalBounds().width) * 0.5f,
		(windowHeight - texts["optionsText"]->getGlobalBounds().height) * 0.7f));
	window->draw(*texts["optionsText"]);
	window->draw(*texts["creditsText"]);
	interactMainMenu();
}

//render the options screen
void Game::renderOptions()
{
	window->draw(displayScreen);
	//window->draw(*texts["volumeText"]);
	//window->draw(*texts["resolutionText"]);
	window->draw(*texts["goBackText"]);
}

void Game::renderCredits()
{
	window->draw(displayScreen);
	//window->draw(*texts["creditsText"]);
	window->draw(*texts["displayCredits"]);
	window->draw(*texts["goBackText"]);
	interactCredits();
}

//render the game
void Game::renderGame()
{
	//render enemies
	for (auto &enemy : this->enemies)
	{
		if (enemy->getIsDamaged())
			enemy->showDamaged(deltaTime);
		enemy->render(*this->window);
	}

	//render enemy bullets
	for (auto &bullet : this->enemyBullets)
	{
		bullet->render(*this->window);
	}

	//render player bullets
	for (auto &bullet : this->playerBullets)
	{
		bullet->render(*this->window);
	}

	//render explosions
	for (auto& explosion : this->explosions)
	{
		explosion->render(*this->window);
	}

	//render upgrades
	for (auto& upgrade : this->upgrades)
	{
		upgrade->render(*this->window);
	}

	//render game over text if player dies and delete the player
	if (this->player->getHp() <= 0.f && !playerDestroyed)
	{
		delete player;
		playerDestroyed = true;
		gameOver = true;
	}
	else if (bossDestroyed)
		gameOver = true;

	//render player if player is not destroyed
	if (!playerDestroyed)
		this->player->render(*this->window); //draw the player

	//render the GUI
	this->renderGUI();

	//if pause is on, render the pause text
	if (pause && !gameOver)
	{
		renderPauseMenu();
	}
}


//render the pause menu
void Game::renderPauseMenu()
{
	window->draw(displayScreen);
	window->draw(*texts["restartLevelText"]);
	window->draw(*texts["returnToMainMenuText"]);
	window->draw(*texts["pauseText"]);

	texts["optionsText"]->setPosition(sf::Vector2f((windowWidth - texts["optionsText"]->getGlobalBounds().width) * 0.5f,
		(windowHeight - texts["optionsText"]->getGlobalBounds().height) * 0.65f));
	window->draw(*texts["optionsText"]);
	interactPauseMenu();
}

//rendere the sequence of screens after a game over
void Game::renderGameOverScreens()
{
	if (select == -1)
	{
		select++;
		selectBuffer = 0.f;
		selectBufferMax = 0.5f;
	}
	//update the selection display
	updateSelect();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || (sf::Mouse::isButtonPressed(sf::Mouse::Left)))
	{
		if (selectBuffer >= selectBufferMax)
		{
			selectBuffer = 0.f;
			select++;
		}
	}
	switch (select)
	{
	case 0:
		if (playerDestroyed)
		{
			//stop emergency sound first if it's playing
			if (this->sounds["emergency"]->getStatus() == sf::Sound::Playing)
				this->sounds["emergency"]->stop();

			//play game over sound
			this->sounds["gameover"]->play();

			window->draw(*texts["gameOverText"]);
		}
		else if (bossDestroyed)
			window->draw(*texts["levelCompleteText"]);
		break;
	case 1:
		printScores(points);
		window->draw(displayScreen);
		window->draw(*texts["scoreText"]);
		break;
	default:
		selectBufferMax = 0.1f;
		window->draw(smallerScreen);
		window->draw(*texts["restartLevelText"]);
		window->draw(*texts["returnToMainMenuText"]);
		interactGameOver();
		break;
	}
}

//render the GUI
void Game::renderGUI()
{
	//render all the text except for the text that appears at certain times
	for (auto& text : texts)
	{
		if (text.first == "pointText" || text.first == "comboText" || text.first == "playerHpText")
			window->draw(*text.second);
	}
}

/*
*****************************************functions*****************************************
*/

//return if the game window is still open
const bool Game::running() const {
	return this->window->isOpen();
}

/*
ENEMY WAVES
1: one enemy1
2: three enemy1s in rectangle
3: one shotgun enemy and three enemy1s in rectangle
4: two shot gun enemies and one bullet bounce enemy
5: two shot gun enemy, one bullet bounce enemy, one normal enemy, one sniper enemy
6: one circle shot enemy, two basic enemy, one shotgun enemy
7: one spray enemy, one circle shot enemy, one bounce enemy circling map
8: two shot gun enemies, one circle shot enemy, one bullet bounce enemy, one sniper enemy
9: one circle shot enemy, one spray enemy, two bullet bounce enemy, two normal enemy
10: two spray enemy, one circle shot enemy, one burst enemy; after like 5-7 seconds, two shot gun enemy, two bullet bounce enemy, one burst enemy
11: boss wave!
*/

/*
ENEMY TYPES:
- 0: basic enemy
- 10: bouncing bullet basic enemy
- 1: shot gun enemy
- 11: circle shot variant of shot gun enemy
- 2: sniper enemy
- 12: burst bullet variant of sniper enemy
- 3: wave enemy
- 100: boss enemy
*/
//spawn 1 basic enemy from the top. 
void Game::waveOne()
{
	//check the elapsed time of the wave
	//sf::Time elapsed = spawnClock.getElapsedTime();
	spawnTimer += deltaTime;

	//at 2 seconds, spawn enemy one
	if (spawnTimer >= 2.f && numEnemies == 0)
	{
		//increment current number of enemies in the wave
		numEnemies++;

		//set the initial position of the enemy
		sf::Vector2f initialPosition(windowWidth / 2.f, 0);

		//spawn the enemy
		spawnEnemyOne(initialPosition, numEnemies);
	}

	//move the enemies spawned
	for (auto* e : enemies)
	{
		if (e->getType() == 0)
		{
			if (e->getPos().y < 100.f)
				e->move(0, 1);
		}
	}
	//if all enemies destroyed, next wave
	if (numEnemiesDestroyed == 1)
	{
		nextWave();
	}
}

//spawn three basic enemies to go around the player
void Game::waveTwo()
{
	spawnTimer += deltaTime;

	//spawn enemy one
	if (spawnTimer >= 2.f && numEnemies == 0)
	{
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.5f, 0);
		spawnEnemyOne(initialPosition, numEnemies);
	}
	//spawn enemy two
	if (spawnTimer >= 3.f && numEnemies == 1)
	{
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.5f, 0);
		spawnEnemyOne(initialPosition, numEnemies);
	}
	//spawn enemy three
	if (spawnTimer >= 4.f && numEnemies == 2)
	{
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.5f, 0);
		spawnEnemyOne(initialPosition, numEnemies);
	}

	//enemy one moves in a rectangle
	for (auto* enemy : enemies)
	{
		if (enemy->getType() == 0)
		{
			if (enemy->getPos().y < 100.f)
				enemy->move(0, 1);
			else
			{
				moveInRect(enemy);
			}
		}
	}
	if (numEnemiesDestroyed == 3)
	{
		nextWave();
	}
}

//have a shot gun enemy spawn from the top and move towards the player as well as three basic enemies from the bottom
void Game::waveThree()
{
	spawnTimer += deltaTime;

	//spawn shot gun enemy
	if (spawnTimer >= 2.f && numEnemies == 0)
	{
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.5f, 0);
		spawnEnemyTwo(initialPosition, numEnemies);
	}

	//spawn normal enemies
	if (spawnTimer >= 3.f && numEnemies == 1)
	{
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.5f, windowHeight);
		spawnEnemyOne(initialPosition, numEnemies);
	}
	if (spawnTimer >= 4.f && numEnemies == 2)
	{
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.5f, windowHeight);
		spawnEnemyOne(initialPosition, numEnemies);
	}
	if (spawnTimer >= 5.f && numEnemies == 3)
	{
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.5f, windowHeight);
		spawnEnemyOne(initialPosition, numEnemies);
	}

	//have the shot gun enemy follow the player and the basic enemy move in a rectangle
	for (auto *e : enemies)
	{
		if (e->getType() == 0)
		{
			if (e->getPos().y > windowHeight - 100.f)
				e->move(0, -1);
			else
				moveInRect(e);
		}
		else if (e->getType() == 1)
		{
			e->move(e->getEnemyToPlayerDir().x, e->getEnemyToPlayerDir().y);
		}
	}
	if (numEnemiesDestroyed >= 4)
	{
		nextWave();
	}
}

//have two shot gun enemies moving towards the player, and two bullet bounce enemies
void Game::waveFour()
{
	spawnTimer += deltaTime;

	//spawn two shot gun enemies
	if (spawnTimer >= 2.f && numEnemies == 0)
	{
		//spawn two enemies from the top
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.33f, windowHeight);
		spawnEnemyTwo(initialPosition, numEnemies);

		numEnemies++;
		initialPosition = sf::Vector2f(windowWidth * 0.66f, windowHeight);
		spawnEnemyTwo(initialPosition, numEnemies);
	}

	//spawn one bounce enemies
	if (spawnTimer >= 3.f && numEnemies == 2)
	{
		//spawn from top
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.5f, 0);
		spawnBounceEnemyOne(initialPosition, numEnemies);
	}
	if (spawnTimer >= 4.f && numEnemies == 3)
	{
		//spawn from top
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.5f, 0);
		spawnBounceEnemyOne(initialPosition, numEnemies);
	}

	//bounce enemies move in circle while shot gun enemy moves towards player
	for (auto *e : enemies)
	{
		if (e->getType() == 10)
		{
			if (e->getPos().y < 100.f)
				e->move(0, 1);
			else
				moveInRect(e);
		}
		else if (e->getType() == 1)
		{
			e->move(e->getEnemyToPlayerDir().x, e->getEnemyToPlayerDir().y);
		}
	}
	if (numEnemiesDestroyed >= 4)
	{	
		nextWave();
	}
}

//two shot gun enemy, one bullet bounce enemy, one sniper enemy, and one normal enemy
void Game::waveFive()
{
	spawnTimer += deltaTime;
	//spawn two shot gun enemies
	if (spawnTimer >= 2.f && numEnemies == 0)
	{
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.33f, 0);
		spawnEnemyTwo(initialPosition, numEnemies);

		numEnemies++;
		initialPosition = sf::Vector2f(windowWidth * 0.66f, 0);
		spawnEnemyTwo(initialPosition, numEnemies);
	}

	//spawn bullet bounce enemy
	if (spawnTimer >= 3.f && numEnemies == 2)
	{
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.5f, 0);
		spawnBounceEnemyOne(initialPosition, numEnemies);
	}

	//spawn sniper enemy and normal enemy
	if (spawnTimer >= 4.f && numEnemies == 3)
	{
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.5f, windowHeight + 50.f);
		spawnEnemyThree(initialPosition, numEnemies);

		numEnemies++;
		initialPosition = sf::Vector2f(windowWidth * 0.5f, 0);
		spawnEnemyOne(initialPosition, numEnemies);
	}

	//sniper enemy moves away from player, normal enemy moves in recatangle, and shotgun enemy moves towards player
	for (auto *enemy : enemies)
	{
		if (enemy->getType() == 0)
		{
			if (enemy->getPos().y < 100.f)
				enemy->move(0, 1);
			else
				moveInRect(enemy);
		}
		else if (enemy->getType() == 10)
		{
			if (enemy->getPos().y < 100.f)
				enemy->move(0, 1);
			else
				moveInRect(enemy);
		}
		else if (enemy->getType() == 1)
		{
			enemy->move(enemy->getEnemyToPlayerDir().x, enemy->getEnemyToPlayerDir().y);
		}
		else if (enemy->getType() == 2)
		{
			enemy->move(-enemy->getEnemyToPlayerDir().x, -enemy->getEnemyToPlayerDir().y);
		}
	}

	if (numEnemiesDestroyed >= 5)
	{
		nextWave();
	}
}

//one circle shot enemy, two basic enemy, one shotgun enemy
void Game::waveSix()
{
	spawnTimer += deltaTime;
	//spawn basic enemy one
	if (spawnTimer >= 2.f && numEnemies == 0)
	{
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.5f, 0);
		spawnEnemyOne(initialPosition, numEnemies);
	}

	//spawn basic enemy two
	if (spawnTimer >= 3.f && numEnemies == 1)
	{
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.5f, 0);
		spawnEnemyOne(initialPosition, numEnemies);
	}

	//spawn shot gun enemy and circle shot
	if (spawnTimer >= 3.5f && numEnemies == 2)
	{
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.33f, windowHeight);
		spawnEnemyTwo(initialPosition, numEnemies);

		numEnemies++;
		initialPosition = sf::Vector2f(windowWidth * 0.66f, windowHeight);
		spawnCircleEnemyTwo(initialPosition, numEnemies);
	}

	for (auto* enemy : enemies)
	{
		if (enemy->getType() == 0)
		{
			if (enemy->getPos().y < 100.f)
				enemy->move(0, 1);
			else
				moveInRect(enemy);
		}
		else if (enemy->getType() == 1)
		{
			enemy->move(enemy->getEnemyToPlayerDir().x, enemy->getEnemyToPlayerDir().y);
		}
		else if (enemy->getType() == 11)
		{
			enemy->move(enemy->getEnemyToPlayerDir().x, enemy->getEnemyToPlayerDir().y);
		}
	}
	if (numEnemiesDestroyed >= 4)
	{
		nextWave();
	}
}

//one spray enemy, one circle shot enemy, one sniper and basic enemy circling map
void Game::waveSeven()
{
	spawnTimer += deltaTime;
	//spawn sniper and bounce enemy
	if (spawnTimer >= 2.f && numEnemies == 0)
	{
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.33f, 50.f);
		spawnEnemyThree(initialPosition, numEnemies);

		numEnemies++;
		initialPosition = sf::Vector2f(windowWidth * 0.66f, 0);
		spawnBounceEnemyOne(initialPosition, numEnemies);
	}

	//spawn circle shot enemy
	if (spawnTimer >= 3.f && numEnemies == 2)
	{
		//spawn sniper enemies from the two bottom corners of the map
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth, windowHeight * 0.5f);
		spawnCircleEnemyTwo(initialPosition, numEnemies);
	}

	//spawn spray enemy
	if (spawnTimer >= 4.f && numEnemies == 3)
	{
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.5f, 0);
		spawnEnemyFour(initialPosition, numEnemies);
	}

	for (auto* enemy : enemies)
	{
		//bounce enemy one moves left right
		if (enemy->getType() == 10)
		{
			if (enemy->getPos().y < 50.f)
				enemy->move(0, 1);
			else
			{
				if (enemy->getPos().x < 50.f)
					moveRight = true;
				else if (enemy->getPos().x > windowWidth - 50.f)
					moveRight = false;
				if (moveRight)
					enemy->move(1, 0);
				else
					enemy->move(-1, 0);
			}
		}
		//circle enemy moves towards player
		else if (enemy->getType() == 11)
		{
			enemy->move(enemy->getEnemyToPlayerDir().x, enemy->getEnemyToPlayerDir().y);
		}
		//sniper enemy moves away from player
		else if (enemy->getType() == 2)
		{
			enemy->move(-enemy->getEnemyToPlayerDir().x, -enemy->getEnemyToPlayerDir().y);
		}
		//spray enemy moves towards player
		else if (enemy->getType() == 3)
		{
			enemy->move(enemy->getEnemyToPlayerDir().x, enemy->getEnemyToPlayerDir().y);
		}
	}
	if (numEnemiesDestroyed >= 4)
	{
		nextWave();
	}
}

//two shot gun enemies, one circle shot enemy, one basic enemy, one burst enemy
void Game::waveEight()
{
	spawnTimer += deltaTime;
	//spawn two shot gun enemies from top
	if (spawnTimer >= 2.f && numEnemies == 0)
	{
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.33f, 0);
		spawnEnemyTwo(initialPosition, numEnemies);

		numEnemies++;
		initialPosition = sf::Vector2f(windowWidth * 0.66f, 0);
		spawnEnemyTwo(initialPosition, numEnemies);
	}

	//spawn basic enemy from bottom
	if (spawnTimer >= 3.f && numEnemies == 2)
	{
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.5f, windowHeight);
		spawnEnemyOne(initialPosition, numEnemies);
	}

	//spawn circle shot enemy from bottom
	if (spawnTimer >= 4.f && numEnemies == 3)
	{
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.5f, windowHeight);
		spawnCircleEnemyTwo(initialPosition, numEnemies);
	}

	//spawn burst enemy at top middle
	if (spawnTimer >= 5.f && numEnemies == 4)
	{
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.5f, 50.f);
		spawnBurstEnemyThree(initialPosition, numEnemies);
	}

	for (auto* enemy : enemies)
	{
		//move basic enemy in rect
		if (enemy->getType() == 0)
		{
			if (enemy->getPos().y > windowHeight - 100.f)
				enemy->move(0, -1);
			else
				moveInRect(enemy);
		}
		//shot gun enemy towards player
		else if (enemy->getType() == 1)
		{
			enemy->move(enemy->getEnemyToPlayerDir().x, enemy->getEnemyToPlayerDir().y);
		}
		//circle shot enemy towards player
		else if (enemy->getType() == 11)
		{
			enemy->move(enemy->getEnemyToPlayerDir().x, enemy->getEnemyToPlayerDir().y);
		}
		//burst enemy
		else if (enemy->getType() == 12)
		{
			enemy->move(-enemy->getEnemyToPlayerDir().x, -enemy->getEnemyToPlayerDir().y);
		}
	}
	if (numEnemiesDestroyed >= 5)
		nextWave();
}

//one circle shot enemy, one spray enemy, two bullet bounce enemy, two normal enemy
void Game::waveNine()
{
	spawnTimer += deltaTime;
	//spawn normal enemies from top
	if (spawnTimer >= 2.f && numEnemies == 0)
	{
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.5f, 0);
		spawnEnemyOne(initialPosition, numEnemies);
	}
	if (spawnTimer >= 3.f && numEnemies == 1)
	{
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.5f, 0);
		spawnEnemyOne(initialPosition, numEnemies);
	}

	//spawn one bounce enemy, once circle enemy, and one wave enemy
	if (spawnTimer >= 4.f && numEnemies == 2)
	{
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.5f, 0);
		spawnBounceEnemyOne(initialPosition, numEnemies);

		numEnemies++;
		initialPosition = sf::Vector2f(0, windowHeight * 0.5f);
		spawnCircleEnemyTwo(initialPosition, numEnemies);

		numEnemies++;
		initialPosition = sf::Vector2f(windowWidth, windowHeight * 0.5f);
		spawnEnemyFour(initialPosition, numEnemies);
	}

	//spawn bounce enemy
	if (spawnTimer >= 5.f && numEnemies == 5)
	{
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.5f, 0);
		spawnBounceEnemyOne(initialPosition, numEnemies);
	}

	for (auto* enemy : enemies)
	{
		//move basic enemy in rect
		if (enemy->getType() == 0 || enemy->getType() == 10)
		{
			if (enemy->getPos().y < 100.f)
				enemy->move(0, 1);
			else
				moveInRect(enemy);
		}
		//circle shot enemy towards player
		else if (enemy->getType() == 11)
		{
			enemy->move(enemy->getEnemyToPlayerDir().x, enemy->getEnemyToPlayerDir().y);
		}
		//spray enemy moves towards player
		else if (enemy->getType() == 3)
		{
			enemy->move(enemy->getEnemyToPlayerDir().x, enemy->getEnemyToPlayerDir().y);
		}
	}
	if (numEnemiesDestroyed >= 6)
		nextWave();
}

//two spray enemy, one circle shot enemy, one burst enemy; after like 5 - 7 seconds, two shot gun enemy, two bullet bounce enemy, and one more circle enemy
void Game::waveTen()
{
	spawnTimer += deltaTime;
	//spawn two spray enemies
	if (spawnTimer >= 2.f && numEnemies == 0)
	{
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.33f, 0);
		spawnEnemyFour(initialPosition, numEnemies);

		numEnemies++;
		initialPosition = sf::Vector2f(windowWidth * 0.66f, 0);
		spawnEnemyFour(initialPosition, numEnemies);
	}

	//spawn burst and circle shot enemy
	if (spawnTimer >= 3.f && numEnemies == 2)
	{
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.5f, 50.f);
		spawnBurstEnemyThree(initialPosition, numEnemies);

		numEnemies++;
		initialPosition = sf::Vector2f(windowWidth * 0.5f, windowHeight);
		spawnCircleEnemyTwo(initialPosition, numEnemies);
	}

	//wait 5 seconds to spawn two shot gun enemies
	if (spawnTimer >= 10.f && numEnemies == 4)
	{
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.33f, windowHeight);
		spawnEnemyTwo(initialPosition, numEnemies);

		numEnemies++;
		initialPosition = sf::Vector2f(windowWidth * 0.66f, windowHeight);
		spawnEnemyTwo(initialPosition, numEnemies);
	}

	//spawn two bullet bounce enemies circling 
	if (spawnTimer >= 11.f && numEnemies == 6)
	{
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.33f, 0);
		spawnBounceEnemyOne(initialPosition, numEnemies);

		numEnemies++;
		initialPosition = sf::Vector2f(windowWidth * 0.66f, 0);
		spawnBounceEnemyOne(initialPosition, numEnemies);
	}

	//spawn circle shot enemy
	if (spawnTimer >= 12.f && numEnemies == 8)
	{
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth, windowHeight * 0.5f);
		spawnCircleEnemyTwo(initialPosition, numEnemies);
	}

	for (auto* enemy : enemies)
	{
		//move basic enemy in rect
		if (enemy->getType() == 10)
		{
			if (enemy->getPos().y < 100.f)
				enemy->move(0, 1);
			else
				moveInRect(enemy);
		}
		//circle shot enemy towards player
		else if (enemy->getType() == 1 || enemy->getType() == 11)
		{
			enemy->move(enemy->getEnemyToPlayerDir().x, enemy->getEnemyToPlayerDir().y);
		}
		//burst enemy
		else if (enemy->getType() == 12)
		{
			enemy->move(-enemy->getEnemyToPlayerDir().x, -enemy->getEnemyToPlayerDir().y);
		}
		//spray enemy
		else if (enemy->getType() == 3)
		{
			enemy->move(enemy->getEnemyToPlayerDir().x, enemy->getEnemyToPlayerDir().y);
		}
	}
	if (numEnemiesDestroyed >= 9)
		nextWave();
}

/*
BOSS WAVE
firing patterns:
	- multiple waves of bullets, each in slightly different angles: 
	- cluster of bullets that explode into all directions: 
	- machine gun spread shots targeting the player for some time: 
	- bouncing wave of bullets
*/
void Game::bossWave()
{
	spawnTimer += deltaTime;

	//spawn the boss at 4 seconds
	if (spawnTimer > 4.f && numEnemies == 0)
	{
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.5f, 100.f);
		spawnBoss(initialPosition, numEnemies);
	}

	//spawn an enemy every 7 seconds after the boss is enraged
	if (bossEnraged && spawnTimer >= 7.f)
	{
		spawnRandomEnemy();
		spawnTimer = 0.f;
	}

	for (auto* enemy : enemies)
	{
		//set the boss to enraged if they
		if (enemy->getType() == 100)
		{
			//move slowly towards player
			enemy->move(enemy->getEnemyToPlayerDir().x, enemy->getEnemyToPlayerDir().y);

			//if the boss reaches half hp, they become enraged
			if (enemy->getHp() <= enemy->getMaxHp() * 0.5f)
			{
				enemy->setMovementSpeed(0.3f);
				enemy->setSpriteColor(sf::Color(168, 30, 30, 255));
				bossEnraged = true;
			}
		}
		//the sniper enemies move away from the player while all other enemies move towards the player
		else if (enemy->getType() == 2 || enemy->getType() == 12)
		{
			enemy->move(-enemy->getEnemyToPlayerDir().x, -enemy->getEnemyToPlayerDir().y);
		}
		else
		{
			enemy->move(enemy->getEnemyToPlayerDir().x, enemy->getEnemyToPlayerDir().y);
		}
	}
	if (bossDestroyed)
	{
		std::cout << "boss destroyed!\n";
		bossEnraged = false;
	}
}

//move to the next wave
void Game::nextWave()	
{
	//reset the spawn timer
	spawnTimer = 0.f;

	//set number of enemies and enemies destroyed to 0
	numEnemies = 0;
	numEnemiesDestroyed = 0;
	
	//increment the current wave
	currentWave++;
}

//move an enemy in a rectangle
void Game::moveInRect(Enemy* enemy)
{
	//moves them in a rectangle based on their current positions; have a slight offset so they dont miss the cue to move
	sf::Vector2f radius(windowWidth - 100.f, windowHeight - 100.f);

	//move right
	if (enemy->getPos().x < radius.x + 2.f && enemy->getPos().y <= 100.f + 2.f)
	{
		enemy->move(1, 0);
	}
	//move down
	if (enemy->getPos().x >= radius.x - 2.f && enemy->getPos().y < radius.y + 2.f)
	{
		enemy->move(0, 1);
	}
	//move left
	if (enemy->getPos().x > 100.f - 2.f && enemy->getPos().y >= radius.y - 2.f)
	{
		enemy->move(-1, 0);
	}
	//move up
	if (enemy->getPos().x <= 102.f && enemy->getPos().y > 100.f - 2.f)
	{
		enemy->move(0, -1);
	}
}

void Game::interactMainMenu()
{
	//update the select buffer
	updateSelect();
	bool canSelect = (selectBuffer >= selectBufferMax);

	//user hovers the start game text
	if (texts["startGameText"]->getGlobalBounds().contains(mousePosView))
		texts["startGameText"]->setFillColor(sf::Color::Red);
	else
		texts["startGameText"]->setFillColor(sf::Color::White);

	//user hovers options
	if (texts["optionsText"]->getGlobalBounds().contains(mousePosView))
		texts["optionsText"]->setFillColor(sf::Color::Red);
	else
		texts["optionsText"]->setFillColor(sf::Color::White);

	//user hovers credits
	if (texts["creditsText"]->getGlobalBounds().contains(mousePosView))
		texts["creditsText"]->setFillColor(sf::Color::Red);
	else
		texts["creditsText"]->setFillColor(sf::Color::White);

	//user hovers exit
	if (texts["goBackText"]->getGlobalBounds().contains(mousePosView))
		texts["goBackText"]->setFillColor(sf::Color::Red);
	else
		texts["goBackText"]->setFillColor(sf::Color::White);

	if (canSelect)
	{
		selectBuffer = 0.f;
		//check if the user clicked an option
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (texts["startGameText"]->getGlobalBounds().contains(mousePosView))
			{
				startGame();
				gameStarted = true;
			}
			else if (texts["optionsText"]->getGlobalBounds().contains(mousePosView))
			{
				std::cout << "display options\n";
			}
			else if ((texts["goBackText"]->getGlobalBounds().contains(mousePosView)))
			{
				std::cout << "hit exit\n";
				if (displayCredits)
				{
					std::cout << "close credits\n";
					displayCredits = false;
				}
				else if (displayOptions)
				{
					displayOptions = false;
				}
			}
			else if (texts["creditsText"]->getGlobalBounds().contains(mousePosView))
			{
				std::cout << "display credits\n";
				displayCredits = true;
			}
		}
	}
}

void Game::interactCredits()
{
	updateSelect();
	bool canSelect = (selectBuffer >= selectBufferMax);

	if (texts["goBackText"]->getGlobalBounds().contains(mousePosView))
		texts["goBackText"]->setFillColor(sf::Color::Red);
	else
		texts["goBackText"]->setFillColor(sf::Color::White);

	if (canSelect)
	{
		selectBuffer = 0.f;
		//check if the user clicked an option
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if ((texts["goBackText"]->getGlobalBounds().contains(mousePosView)))
			{
				std::cout << "hit exit\n";
				if (displayCredits)
				{
					std::cout << "close credits\n";
					displayCredits = false;
				}
				else if (displayOptions)
				{
					displayOptions = false;
				}
			}
		}
	}
}

void Game::interactPauseMenu()
{
	updateSelect();
	bool canSelect = (selectBuffer >= selectBufferMax);
	//user hovers the return to main menu text
	if (texts["returnToMainMenuText"]->getGlobalBounds().contains(mousePosView))
		texts["returnToMainMenuText"]->setFillColor(sf::Color::Red);
	else
		texts["returnToMainMenuText"]->setFillColor(sf::Color::White);

	//user hovers the restart level text
	if (texts["restartLevelText"]->getGlobalBounds().contains(mousePosView))
		texts["restartLevelText"]->setFillColor(sf::Color::Red);
	else
		texts["restartLevelText"]->setFillColor(sf::Color::White);

	//user hovers options
	if (texts["optionsText"]->getGlobalBounds().contains(mousePosView))
		texts["optionsText"]->setFillColor(sf::Color::Red);
	else
		texts["optionsText"]->setFillColor(sf::Color::White);

	if (canSelect)
	{
		selectBuffer = 0.f;
		//check if the user clicked an option
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (texts["returnToMainMenuText"]->getGlobalBounds().contains(mousePosView))
			{
				std::cout << "clicked return to main menu\n";
			}
			else if (texts["restartLevelText"]->getGlobalBounds().contains(mousePosView))
			{
				std::cout << "clicked restart level text\n";
			}
			else if (texts["optionsText"]->getGlobalBounds().contains(mousePosView))
			{
				std::cout << "clicked options text\n";
			}
		}
	}
}

void Game::interactGameOver()
{
	updateSelect();
	bool canSelect = (selectBuffer >= selectBufferMax);
	//user hovers the return to main menu text
	if (texts["returnToMainMenuText"]->getGlobalBounds().contains(mousePosView))
		texts["returnToMainMenuText"]->setFillColor(sf::Color::Red);
	else
		texts["returnToMainMenuText"]->setFillColor(sf::Color::White);

	//user hovers the restart level text
	if (texts["restartLevelText"]->getGlobalBounds().contains(mousePosView))
		texts["restartLevelText"]->setFillColor(sf::Color::Red);
	else
		texts["restartLevelText"]->setFillColor(sf::Color::White);

	if (canSelect)
	{
		selectBuffer = 0.f;
		//check if the user clicked an option
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (texts["returnToMainMenuText"]->getGlobalBounds().contains(mousePosView))
			{
				std::cout << "clicked return to main menu\n";
			}
			else if (texts["restartLevelText"]->getGlobalBounds().contains(mousePosView))
			{
				std::cout << "clicked restart level text\n";
			}
		}
	}
}

//spawn enemy one
void Game::spawnEnemyOne(sf::Vector2f initialPosition, unsigned posInWave)
{
	int type = 0;
	float hp = 15.f;
	float damage = 1.f;
	float fireRate = 30.f;
	float movementSpeed = 1.f * scale;
	sf::FloatRect newHitbox(8, 8, 16, 16);

	//play enemy spawn sound
	this->sounds["enemySpawn"]->play();
	this->enemies.push_back(new Enemy(*this->assets["enemyOne"], type, hp, damage, fireRate, movementSpeed, newHitbox, initialPosition, posInWave, scale));
	
	//set the enemies animation to spawn when spawned
	Enemy* enemy = enemies.back();
	sf::Texture* spawnTexture = this->assets["enemyOneSpawn"];
	enemy->setSpawnAnimation("spawnAnimation", spawnTexture, 4, 0, 32, 32);
}

//spawn bounce enemy one
void Game::spawnBounceEnemyOne(sf::Vector2f initialPosition, unsigned posInWave)
{
	sf::FloatRect newHitbox(8, 8, 16, 16);

	int type = 10;
	float hp = 20.f;
	float damage = 1.f;
	float fireRate = 50.f;
	float movementSpeed = 1.f * scale;

	//play enemy spawn sound
	this->sounds["enemySpawn"]->play();
	this->enemies.push_back(new Enemy(*this->assets["bounceEnemyOne"], type, hp, damage, fireRate, movementSpeed, newHitbox, initialPosition, posInWave, scale));

	Enemy* enemy = enemies.back();
	sf::Texture* spawnTexture = this->assets["bounceEnemyOneSpawn"];
	enemy->setSpawnAnimation("spawnAnimation", spawnTexture, 4, 0, 32, 32);
}

//spawn enemy two
void Game::spawnEnemyTwo(sf::Vector2f initialPosition, unsigned posInWave)
{
	sf::FloatRect newHitbox(8, 8, 16, 16);

	float hp = 20.f;
	float damage = 1.f;
	float fireRate = 50.f;
	float movementSpeed = 0.8f * scale;
	int type = 1;

	//play enemy spawn sound
	this->sounds["enemySpawn"]->play();
	this->enemies.push_back(new Enemy(*this->assets["enemyTwo"], type, hp, damage, fireRate, movementSpeed, newHitbox, initialPosition, posInWave, scale));

	Enemy* enemy = enemies.back();
	sf::Texture* spawnTexture = this->assets["enemyTwoSpawn"];
	enemy->setSpawnAnimation("spawnAnimation", spawnTexture, 4, 0, 32, 32);
}

//spawn circle enemy two
void Game::spawnCircleEnemyTwo(sf::Vector2f initialPosition, unsigned posInWave)
{
	sf::FloatRect newHitbox(8, 8, 16, 16);

	float hp = 30.f;
	float damage = 1.f;
	float fireRate = 75.f;
	float movementSpeed = 0.8f * scale;
	int type = 11;
	this->enemies.push_back(new Enemy(*this->assets["circleEnemyTwo"], type, hp, damage, fireRate, movementSpeed, newHitbox, initialPosition, posInWave, scale));

	Enemy* enemy = enemies.back();
	sf::Texture* spawnTexture = this->assets["circleEnemyTwoSpawn"];
	enemy->setSpawnAnimation("spawnAnimation", spawnTexture, 4, 0, 32, 32);
}

//spawn enemy three
void Game::spawnEnemyThree(sf::Vector2f initialPosition, unsigned posInWave)
{
	sf::FloatRect newHitbox(11, 6, 10, 24);
	float hp = 17.f;
	float damage = 1.f;
	float fireRate = 100.f;
	float movementSpeed = 1.0f * scale;
	int type = 2;
	this->enemies.push_back(new Enemy(*this->assets["enemyThree"], type, hp, damage, fireRate, movementSpeed, newHitbox, initialPosition, posInWave, scale));


	Enemy* enemy = enemies.back();
	sf::Texture* spawnTexture = this->assets["enemyThreeSpawn"];
	enemy->setSpawnAnimation("spawnAnimation", spawnTexture, 4, 0, 32, 32);
}

//spawn burst enemy three
void Game::spawnBurstEnemyThree(sf::Vector2f initialPosition, unsigned posInWave)
{
	sf::FloatRect newHitbox(11, 6, 10, 24);
	float hp = 20.f;
	float damage = 1.f;
	float fireRate = 80.f;
	float movementSpeed = 1.0f * scale;
	int type = 12;
	this->enemies.push_back(new Enemy(*this->assets["burstEnemyThree"], type, hp, damage, fireRate, movementSpeed, newHitbox, initialPosition, posInWave, scale));

	Enemy* enemy = enemies.back();
	sf::Texture* spawnTexture = this->assets["burstEnemyThreeSpawn"];
	enemy->setSpawnAnimation("spawnAnimation", spawnTexture, 4, 0, 32, 32);
}

//spawn enemy four
void Game::spawnEnemyFour(sf::Vector2f initialPosition, unsigned posInWave)
{
	sf::FloatRect newHitbox(6, 6, 20, 20);
	float hp = 30.f;
	float damage = 1.f;
	float fireRate = 10.f;
	float movementSpeed = 0.4f * scale;
	int type = 3;
	this->enemies.push_back(new Enemy(*this->assets["enemyFour"], type, hp, damage, fireRate, movementSpeed, newHitbox, initialPosition, posInWave, scale));

	Enemy* enemy = enemies.back();
	sf::Texture* spawnTexture = this->assets["enemyFourSpawn"];
	enemy->setSpawnAnimation("spawnAnimation", spawnTexture, 4, 0, 32, 32);
}

//spawn the boss
void Game::spawnBoss(sf::Vector2f initialPosition, unsigned posInWave)
{
	sf::FloatRect newHitbox(13, 13, 38, 38);
	float hp = 600.f;
	float damage = 1.f;
	float fireRate = 100.f;
	float movementSpeed = 0.2f * scale;
	int type = 100;
	float size = 1.3f * scale; //boss is larger than other enemies
	this->enemies.push_back(new Enemy(*this->assets["bossEnemy"], type, hp, damage, fireRate, movementSpeed, newHitbox, initialPosition, posInWave, size));

	Enemy* enemy = enemies.back();
	sf::Texture* spawnTexture = this->assets["bossEnemySpawn"];
	enemy->setSpawnAnimation("spawnAnimation", spawnTexture, 12, 0, 64, 64);
}

//spawn a random enemy
void Game::spawnRandomEnemy()
{
	//enemy spawns at the bottom center of the screen
	sf::Vector2f initialPosition(windowWidth * 0.5f, windowHeight);
	numEnemies++;

	//get a random number from 0-99
	int spawnRandEnemy = rand() % 100;

	//30% chance to spawn enemy one
	if (spawnRandEnemy < 30)
	{
		spawnEnemyOne(initialPosition, numEnemies);
	}
	//20% chance to spawn enemy two
	else if (spawnRandEnemy < 50)
	{
		spawnEnemyTwo(initialPosition, numEnemies);
	}
	//15% chance to spawn enemy three
	else if (spawnRandEnemy < 65)
	{
		initialPosition = sf::Vector2f(windowWidth * 0.5f, windowHeight - 50.f);
		spawnEnemyThree(initialPosition, numEnemies);
	}
	//15% chance to spawn bounce enemy one
	else if (spawnRandEnemy < 75)
	{
		spawnBounceEnemyOne(initialPosition, numEnemies);
	}
	//10% chance to spawn enemy four
	else if (spawnRandEnemy < 84)
	{
		spawnEnemyFour(initialPosition, numEnemies);
	}
	//8% chance to spawn burst enemy
	else if (spawnRandEnemy < 93)
	{
		spawnBurstEnemyThree(initialPosition, numEnemies);
	}
	//7% chance to spawn circle enemy
	else if (spawnRandEnemy < 100)
	{
		spawnCircleEnemyTwo(initialPosition, numEnemies);
	}
}

//enemy one's fire pattern; fires one bullet at a set interval
void Game::enemyOneFirePattern()
{
	//set the bullet hitbox
	sf::FloatRect bulletHitbox(1, 1, 6, 6);
	int bulletType = 10;
	float bulletSpeed = 3.f * scale;

	//play sound when enemy fires
	this->sounds["enemyBullet"]->play();
	//push back a bullet with the texture, type, hitbox, enemy position, enemy angle, enemy aim direction, bullet speed, and scale
	this->enemyBullets.push_back(new Bullet(*this->assets["enemyBullet"], bulletType, bulletHitbox, enemyPos, enemyAngle, enemyAimDir, bulletSpeed, scale));
}

//bounce enemy one's fire pattern; fires a bouncing bullet at a set interval
void Game::bounceEnemyOneFirePattern()
{
	sf::FloatRect bulletHitbox(1, 1, 6, 6);
	sf::Texture* bulletTexture = this->assets["bouncingEnemyBullet"];
	int bulletType = 13;
	float bulletSpeed = 3.f * scale;

	//play sound when enemy fires
	this->sounds["enemyBullet"]->play();
	this->enemyBullets.push_back(new Bullet(*bulletTexture, bulletType, bulletHitbox, enemyPos, enemyAngle, enemyAimDir, bulletSpeed, scale));
}

//enemy two's fire pattern; fires a spread shot
void Game::enemyTwoFirePattern()
{
	sf::FloatRect bulletHitbox(1, 1, 6, 6);
	sf::Texture* bulletTexture = this->assets["enemyBullet"];
	int bulletType = 10;
	float bulletSpeed = 4.f * scale;
	float spreadAngle = pi / 18.f;

	//play sound when enemy fires
	this->sounds["enemyBullet"]->play();
	//fires a shot gun shot
	fireSpread("enemy", bulletTexture, bulletHitbox, bulletType, bulletSpeed, spreadAngle);
}

//circle enemy two's fire pattern; fires a circle shot
void Game::circleEnemyTwoFirePattern()
{
	sf::FloatRect bulletHitbox(1, 1, 6, 6);
	sf::Texture* bulletTexture = this->assets["enemyBullet"];
	int bulletType = 10;
	float bulletSpeed = 2.f * scale;

	//play sound when enemy fires
	this->sounds["enemyBullet"]->play();
	fireInCircle("enemy", bulletTexture, bulletHitbox, bulletType, bulletSpeed, enemyPos, 0);
}

//enemy three's fire pattern; fires a fast thin shot
void Game::enemyThreeFirePattern()
{
	sf::FloatRect bulletHitbox(6, 0, 4, 16);
	sf::Texture* bulletTexture = this->assets["longEnemyBullet"];
	int bulletType = 11;
	float bulletSpeed = 10.f * scale;

	//play special long bullet sound when enemy fires
	this->sounds["longEnemyBullet"]->play();
	this->enemyBullets.push_back(new Bullet(*bulletTexture, bulletType, bulletHitbox, enemyPos, enemyAngle, enemyAimDir, bulletSpeed, scale));
}

//burst enemy three's fire pattern; fires a slow burst shot
void Game::burstEnemyThreeFirePattern()
{
	sf::Texture* bulletTexture = this->assets["bigEnemyBullet"];
	sf::FloatRect bulletHitbox(1, 1, 14, 14);
	int bulletType = 12;
	float bulletSpeed = 3.f * scale;

	//play sound when enemy fires
	this->sounds["enemyBullet"]->play();
	fireClusterShot("enemy", bulletTexture, bulletHitbox, bulletType, bulletSpeed);
}

//wave enemy four's fire pattern; fires a wave of bullets
void Game::enemyFourFirePattern(Enemy* enemy)
{
	enemy->setFireRate(8.f);
	sf::FloatRect bulletHitbox(1, 1, 6, 6);
	sf::Texture* bulletTexture = this->assets["enemyBullet"];
	int bulletType = 10;
	float bulletSpeed = 3.f * scale;
	float bulletOffset = pi / 9.f;
	baseEnemyAimDir = sf::Vector2f(enemyAimDir);
	
	//keeps track of the bullets fired
	if (enemy->getBulletCounter() < 7)
	{
		//play sound when enemy fires
		this->sounds["enemyBullet"]->play();
		fireWave(bulletTexture, bulletHitbox, bulletType, bulletSpeed, bulletOffset, baseEnemyAimDir, enemy);
	}

	//once 7 bullets fired, they go on cooldown for a bit and bullet counter is reset
	else
	{
		enemy->setBulletCounter(0);
		enemy->setFireRate(75.f);
	}
}

//boss' fire patterns
void Game::bossFirePattern(Enemy * enemy)
{
	//depending on the pattern, do a different attack
	switch (bossPattern)
	{
	//boss pattern one
	case 1:
		//depending on bullets fired, repeat it's pattern
		if (enemy->getBulletCounter() < 10)
		{
			bossPatternOne(enemy);
		}
		//once the pattern is done, reset the fire rate, boss pattern, and bullet counter
		else
		{
			//if the boss is enraged, their fire cooldown is faster
			if (bossEnraged)
				enemy->setFireRate(50.f);
			else
				enemy->setFireRate(75.f);
			enemy->setBulletCounter(0);
			bossPattern = 0;
		}
		break;
	//boss pattern two
	case 2:
		if (enemy->getBulletCounter() < 5)
			bossPatternTwo(enemy);
		else
		{
			if (bossEnraged)
				enemy->setFireRate(50.f);
			else
				enemy->setFireRate(75.f);
			enemy->setBulletCounter(0);
			bossPattern = 0;
		}
		break;
	//boss pattern three
	case 3:
		if (enemy->getBulletCounter() < 20)
		{
			bossPatternThree(enemy);
		}
		else
		{
			if (bossEnraged)
				enemy->setFireRate(50.f);
			else
				enemy->setFireRate(75.f);
			enemy->setBulletCounter(0);
			bossPattern = 0;
		}
		break;
	//boss pattern four
	case 4:
		if (enemy->getBulletCounter() < 7)
			bossPatternFour(enemy);
		else
		{
			if (bossEnraged)
				enemy->setFireRate(50.f);
			else
				enemy->setFireRate(75.f);
			enemy->setBulletCounter(0);
			bossPattern = 0;
		}
		break;
	}
}

//boss pattern one: fires a circle of bullets around the boss 10 times
void Game::bossPatternOne(Enemy* enemy)
{
	//increment the bullet counter
	enemy->setBulletCounter(enemy->getBulletCounter() + 1);

	//constantly randomize the time to get a new offset the circle is fired at
	int randTime = static_cast<int>(time(0) + enemy->getBulletCounter());
	srand(randTime);

	//randomized offset
	float offset = static_cast<float>(rand() % 20);

	//if the boss is enraged, fires faster
	if (bossEnraged)
		enemy->setFireRate(8.f);
	else
		enemy->setFireRate(10.f);
	sf::FloatRect bulletHitbox(1, 1, 6, 6);
	sf::Texture* bulletTexture = this->assets["enemyBullet"];
	int bulletType = 10;
	float bulletSpeed = 3.f * scale;

	this->sounds["enemyBullet"]->play();
	//fires bullets in a circle
	fireInCircle("enemy", bulletTexture, bulletHitbox, bulletType, bulletSpeed, enemyPos, offset);
}

//fires 5 cluster of bullets that explode into all directions once it reaches the initial positions
void Game::bossPatternTwo(Enemy* enemy)
{
	enemy->setBulletCounter(enemy->getBulletCounter() + 1);

	if (bossEnraged)
		enemy->setFireRate(40.f);
	else
		enemy->setFireRate(50.f);

	sf::Texture* bulletTexture = this->assets["bigEnemyBullet"];
	sf::FloatRect bulletHitbox(1, 1, 14, 14);
	int bulletType = 12;
	float bulletSpeed = 2.5f * scale;

	this->sounds["enemyBullet"]->play();
	fireClusterShot("enemy", bulletTexture, bulletHitbox, bulletType, bulletSpeed);
}

//rapid machine gun spread shots targeting the player for twenty shots
void Game::bossPatternThree(Enemy* enemy)
{
	enemy->setBulletCounter(enemy->getBulletCounter() + 1);

	if (bossEnraged)
		enemy->setFireRate(8.f);
	else
		enemy->setFireRate(10.f);

	sf::FloatRect bulletHitbox(1, 1, 6, 6);
	sf::Texture* bulletTexture = this->assets["enemyBullet"];
	float bulletSpeed = 3.f * scale;
	int bulletType = 10;

	this->sounds["enemyBullet"]->play();
	fireSpread("enemy", bulletTexture, bulletHitbox, bulletType, bulletSpeed, pi / 8.f);
}

//shoot a wave of bouncing bullets
void Game::bossPatternFour(Enemy* enemy)
{
	if (bossEnraged)
		enemy->setFireRate(6.4f);
	else
		enemy->setFireRate(8.f);
	
	sf::FloatRect bulletHitbox(1, 1, 6, 6);
	sf::Texture* bulletTexture = this->assets["bouncingEnemyBullet"];
	int bulletType = 13;
	float bulletSpeed = 3.f * scale;
	float bulletOffset = pi / 9.f;
	baseEnemyAimDir = sf::Vector2f(enemyAimDir);

	this->sounds["enemyBullet"]->play();
	fireWave(bulletTexture, bulletHitbox, bulletType, bulletSpeed, bulletOffset, baseEnemyAimDir, enemy);
}

//fire bullets in a spread
void Game::fireSpread(const std::string character, sf::Texture* bulletTexture, sf::FloatRect bulletHitbox, int bulletType, float bulletSpeed, float spreadDegree)
{
	//if the player is firing
	if (character == "player")
	{
		sf::Vector2f newPlayerAimDir;
		//shoots a bullet straight
		this->playerBullets.push_back(new Bullet(*bulletTexture, bulletType, bulletHitbox, playerPos, mouseAngle, playerAimDir, bulletSpeed, scale));

		//shoots a bullet at the spread degree angle (trigonomic identity)
		newPlayerAimDir = sf::Vector2f(
			playerAimDir.x * (cos(spreadDegree)) - playerAimDir.y * (sin(spreadDegree)),
			playerAimDir.y * (cos(spreadDegree)) + playerAimDir.x * (sin(spreadDegree))
		);
		this->playerBullets.push_back(new Bullet(*bulletTexture, bulletType, bulletHitbox, playerPos, mouseAngle, newPlayerAimDir, bulletSpeed, scale));

		//shoots a bullet at the spread degree angle
		newPlayerAimDir = sf::Vector2f(
			playerAimDir.x * (cos(spreadDegree)) + playerAimDir.y * (sin(spreadDegree)),
			playerAimDir.y * (cos(spreadDegree)) - playerAimDir.x * (sin(spreadDegree))
		);
		this->playerBullets.push_back(new Bullet(*bulletTexture, bulletType, bulletHitbox, playerPos, mouseAngle, newPlayerAimDir, bulletSpeed, scale));
	}
	else
	{
		sf::Vector2f newEnemyAimDir;
		this->enemyBullets.push_back(new Bullet(*bulletTexture, bulletType, bulletHitbox, enemyPos, enemyAngle, enemyAimDir, bulletSpeed, scale));

		newEnemyAimDir = sf::Vector2f(
			enemyAimDir.x * (cos(spreadDegree)) - enemyAimDir.y * (sin(spreadDegree)),
			enemyAimDir.y * (cos(spreadDegree)) + enemyAimDir.x * (sin(spreadDegree))
		);
		this->enemyBullets.push_back(new Bullet(*bulletTexture, bulletType, bulletHitbox, enemyPos, enemyAngle, newEnemyAimDir, bulletSpeed, scale));

		newEnemyAimDir = sf::Vector2f(
			enemyAimDir.x * (cos(spreadDegree)) + enemyAimDir.y * (sin(spreadDegree)),
			enemyAimDir.y * (cos(spreadDegree)) - enemyAimDir.x * (sin(spreadDegree))
		);
		this->enemyBullets.push_back(new Bullet(*bulletTexture, bulletType, bulletHitbox, enemyPos, enemyAngle, newEnemyAimDir, bulletSpeed, scale));
	}
}

//fire bullets in a wave
void Game::fireWave(sf::Texture* bulletTexture, sf::FloatRect bulletHitbox, int bulletType, float bulletSpeed, float bulletOffset, sf::Vector2f baseAimDir, Enemy* enemy)
{
	//increment the bullet counter
	enemy->setBulletCounter(enemy->getBulletCounter() + 1);

	int bulletCounter = enemy->getBulletCounter();

	//if the bullet counter is one, then the base firing direction is set
	if (bulletCounter == 1)
	{
		baseEnemyAimDir = sf::Vector2f(baseAimDir);
	}

	//based on the bullet counter, fire at a certain direction
	switch (bulletCounter)
	{
	case 1:
		//shoot at degrees * 3
		enemyAimDir = sf::Vector2f(
			baseEnemyAimDir.x * (cos(bulletOffset * 3)) + baseEnemyAimDir.y * (sin(bulletOffset * 3)),
			baseEnemyAimDir.y * (cos(bulletOffset * 3)) - baseEnemyAimDir.x * (sin(bulletOffset * 3))
		);
		break;
	case 2:
		//shoot at degrees * 2
		enemyAimDir = sf::Vector2f(
			baseEnemyAimDir.x * (cos(bulletOffset * 2)) + baseEnemyAimDir.y * (sin(bulletOffset * 2)),
			baseEnemyAimDir.y * (cos(bulletOffset * 2)) - baseEnemyAimDir.x * (sin(bulletOffset * 2))
		);
		break;
	case 3:
		//shoot at degrees * 1
		enemyAimDir = sf::Vector2f(
			baseEnemyAimDir.x * (cos(bulletOffset)) + baseEnemyAimDir.y * (sin(bulletOffset)),
			baseEnemyAimDir.y * (cos(bulletOffset)) - baseEnemyAimDir.x * (sin(bulletOffset))
		);
		break;
	case 4:
		//shoot at the initial aim direction
		enemyAimDir = baseEnemyAimDir;
		break;
	case 5:
		//shoot at degrees * 1 the other way
		enemyAimDir = sf::Vector2f(
			baseEnemyAimDir.x * (cos(bulletOffset)) - baseEnemyAimDir.y * (sin(bulletOffset)),
			baseEnemyAimDir.y * (cos(bulletOffset)) + baseEnemyAimDir.x * (sin(bulletOffset))
		);
		break;
	case 6:
		//degrees * 2
		enemyAimDir = sf::Vector2f(
			baseEnemyAimDir.x * (cos(bulletOffset * 2)) - baseEnemyAimDir.y * (sin(bulletOffset * 2)),
			baseEnemyAimDir.y * (cos(bulletOffset * 2)) + baseEnemyAimDir.x * (sin(bulletOffset * 2))
		);
		break;
	case 7:
		//degrees * 3
		enemyAimDir = sf::Vector2f(
			baseEnemyAimDir.x * (cos(bulletOffset * 3)) - baseEnemyAimDir.y * (sin(bulletOffset * 3)),
			baseEnemyAimDir.y * (cos(bulletOffset * 3)) + baseEnemyAimDir.x * (sin(bulletOffset * 3))
		);
		break;
	//once the wave is done, bullet counter is reset
	default:
		enemy->setBulletCounter(0);
	}

	//fire the bullet at the new direction
	this->enemyBullets.push_back(new Bullet(*bulletTexture, bulletType, bulletHitbox, enemyPos, enemyAngle, enemyAimDir, bulletSpeed, scale));
}

//fire bullets in a circle
void Game::fireInCircle(const std::string character, sf::Texture* bulletTexture, sf::FloatRect bulletHitbox, int bulletType, float bulletSpeed, sf::Vector2f centerPos, float offset)
{
	//initial degree is the set offset
	float degree = offset;
	float radians;
	sf::Vector2f aimDir;

	//fires bullets in a circle from 30 degree increments 12 times
	for (int i = 0; i < 12; i++)
	{
		radians = degree * pi / 180.f;
		aimDir = sf::Vector2f(cos(radians), sin(radians));
		if (character == "player")
			playerBullets.push_back(new Bullet(*bulletTexture, bulletType, bulletHitbox, centerPos, mouseAngle, aimDir, bulletSpeed, scale));
		else
			enemyBullets.push_back(new Bullet(*bulletTexture, bulletType, bulletHitbox, centerPos, enemyAngle, aimDir, bulletSpeed, scale));
		degree += 30.f;
	}
}

//fire bullets as a cluster
void Game::fireClusterShot(const std::string character, sf::Texture* bulletTexture, sf::FloatRect bulletHitbox, int bulletType, float bulletSpeed)
{
	if (character == "player")
	{
		sf::Vector2f newAimPos(mousePosView.x - playerPos.x, mousePosView.y - playerPos.y);
		playerBullets.push_back(new Bullet(*bulletTexture, bulletType, bulletHitbox, playerPos, mouseAngle, playerAimDir, bulletSpeed, scale));
		//playerBullets.push_back(new Bullet(*bulletTexture, bulletType, bulletHitbox, playerPos, mouseAngle, playerAimDir, bulletSpeed, scale));
		Bullet* bullet = playerBullets.back();
		bullet->setBasePos(mousePosView);
	}
	else
	{
		enemyBullets.push_back(new Bullet(*bulletTexture, bulletType, bulletHitbox, enemyPos, enemyAngle, enemyAimDir, bulletSpeed, scale));
		Bullet* bullet = enemyBullets.back();
		bullet->setBasePos(playerPos);
	}
}

//burst the cluster shot
void Game::burstClusterShot(const std::string character, sf::Vector2f burstPos, sf::Texture* bulletTexture, sf::FloatRect bulletHitbox, int bulletType, float bulletSpeed)
{
	fireInCircle(character, bulletTexture, bulletHitbox, bulletType, bulletSpeed, burstPos, 0);
}

//fires double bullets
void Game::fireDoubleBullets(const std::string character, sf::Texture * bulletTexture, sf::FloatRect bulletHitbox, int bulletType, float bulletSpeed)
{
	//will need to get the angles from the two sides of the player;
	sf::Vector2f leftPos, rightPos;
	sf::Vector2f centerPos;
	sf::Vector2f currentAimDir;
	float currAngle;

	//set the center position, angle being fired at, and aim direction depending on the character firing
	if (character == "player")
	{
		centerPos = playerPos;
		currAngle = mouseAngle;
		currentAimDir = playerAimDir;
	}
	else
	{
		centerPos = enemyPos;
		currAngle = acos(enemyAimDir.x);
		currentAimDir = enemyAimDir;
	}

	//angle is set to 90 degrees - current angle
	float angle = (pi / 2.f) - acos(playerAimDir.x);

	//distance from the center the bullet is fired
	float radius = 20.f;

	//using right triangle identities, find the difference in the x and y position from the initial position
	float deltaX = (radius * cos(angle));
	float deltaY = (radius * sin(angle));

	//if the current aim is aiming upwards, set the left position and right position based on delta x and delta y to fire from left and right
	if (currentAimDir.y < 0)
	{
		leftPos = sf::Vector2f(centerPos.x - deltaX, centerPos.y - deltaY);
		rightPos = sf::Vector2f(centerPos.x + deltaX, centerPos.y + deltaY);
	}
	//if shooting downwards: set the left and right positions differently based on delta x and delta y
	else
	{
		leftPos = sf::Vector2f(centerPos.x - deltaX, centerPos.y + deltaY);
		rightPos = sf::Vector2f(centerPos.x + deltaX, centerPos.y - deltaY);
	}

	//shoot the two bullets from the two positions
	if (character == "player")
	{
		playerBullets.push_back(new Bullet(*bulletTexture, bulletType, bulletHitbox, rightPos, currAngle, currentAimDir, bulletSpeed, scale));
		playerBullets.push_back(new Bullet(*bulletTexture, bulletType, bulletHitbox, leftPos, currAngle, currentAimDir, bulletSpeed, scale));
	}
	else
	{
		enemyBullets.push_back(new Bullet(*bulletTexture, bulletType, bulletHitbox, rightPos, currAngle, currentAimDir, bulletSpeed, scale));
		enemyBullets.push_back(new Bullet(*bulletTexture, bulletType, bulletHitbox, leftPos, currAngle, currentAimDir, bulletSpeed, scale));
	}
}

//bounces a bullet
void Game::bounceBullet(Bullet * bullet)
{
	//top wall
	if (bullet->getPos().y < 0.f)
	{
		bullet->setDir(sf::Vector2f(bullet->getDir().x, bullet->getDir().y * -1));
	}
	//bottom wall
	if (bullet->getPos().y >= windowHeight)
	{
		bullet->setDir(sf::Vector2f(bullet->getDir().x, bullet->getDir().y * -1));
	}
	//left wall
	if (bullet->getPos().x < 0.f)
	{
		bullet->setDir(sf::Vector2f(bullet->getDir().x * -1, bullet->getDir().y));
	}
	//right wall
	if (bullet->getPos().x >= windowWidth)
	{
		bullet->setDir(sf::Vector2f(bullet->getDir().x * -1, bullet->getDir().y));
	}
	//update the world collision so that the bullets dont go off the screen, instead they are set at the border so they don't get deleted
	updateWorldCollision(bullet, 0.f);

	//decrement the bounces the bullet has left
	bullet->setMaxBounce(bullet->getMaxBounce() - 1);
}

//power ups: damage up, hp up, fire rate up; other power ups: double ray, spread shot, sniper (?)
void Game::dropPowerUp(Enemy* enemy)
{
	int dmgUpChance, hpUpChance, fireRateUpChance, doubleBulletUpChance, spreadBulletUpChance, burstBulletUpChance, dropType;
	sf::Texture* newTexture = nullptr;

	//random chance of an enemy dropping a power up
	int randChance = rand() % 100 + 1;
	int dropChance;
	//TEST
	//upgrades.push_back(new Upgrade(this->textures["doubleBulletUpIdle"], enemy->getPos(), 30.f, 4, deltaTime, scale));
	//upgrades.push_back(new Upgrade(this->textures["spreadBulletUpIdle"], enemy->getPos(), 30.f, 5, deltaTime, scale));
	//upgrades.push_back(new Upgrade(this->textures["burstBulletUpIdle"], enemy->getPos(), 30.f, 6, deltaTime, scale));

	//enemy one(s) power up drops
	if (enemy->getType() == 0 || enemy->getType() == 10)
	{
		//base drop chance of a power up
		if (enemy->getType() == 0)
			dropChance = 10;
		else
			dropChance = 20;

		//if a power up drops, this is the chance of the power
		dmgUpChance = 28;
		hpUpChance = 28 + dmgUpChance;
		fireRateUpChance = 28 + hpUpChance;
		doubleBulletUpChance = 5 + fireRateUpChance;
		spreadBulletUpChance = 5 + doubleBulletUpChance;
		burstBulletUpChance = 6 + spreadBulletUpChance;
	}

	//enemy two(s) power up drops
	else if (enemy->getType() == 1 || enemy->getType() == 11)
	{
		//TEST
		if (enemy->getType() == 1)
			dropChance = 25;
		else
			dropChance = 40;
		dmgUpChance = 18;
		hpUpChance = 28 + dmgUpChance;
		fireRateUpChance = 18 + hpUpChance;
		doubleBulletUpChance = 10 + fireRateUpChance;
		spreadBulletUpChance = 18 + doubleBulletUpChance;
		burstBulletUpChance = 8 + spreadBulletUpChance;
	}
	
	//enemy three(s) power up drops
	else if (enemy->getType() == 2 || enemy->getType() == 12)
	{
		if (enemy->getType() == 2)
			dropChance = 25;
		else
			dropChance = 40;
		dmgUpChance = 20;
		hpUpChance = 20 + dmgUpChance;
		fireRateUpChance = 20 + hpUpChance;
		doubleBulletUpChance = 10 + fireRateUpChance;
		spreadBulletUpChance = 10 + doubleBulletUpChance;
		burstBulletUpChance = 20 + spreadBulletUpChance;
	}

	//enemy four(s) power up drops
	else if (enemy->getType() == 3)
	{
		dropChance = 40;
		dmgUpChance = 14;
		hpUpChance = 13 + dmgUpChance;
		fireRateUpChance = 13 + hpUpChance;
		doubleBulletUpChance = 20 + fireRateUpChance;
		spreadBulletUpChance = 20 + doubleBulletUpChance;
		burstBulletUpChance = 20 + spreadBulletUpChance;
	}

	//boss has no drop chance
	else if (enemy->getType() == 100)
	{
		dropChance = 0;
	}

	//if the enemy's drop chance drops, drop a drop
	if (randChance <= dropChance)
	{
		//drop a power up
		this->sounds["itemDrop"]->play();

		//get a random drop based on the chance of powerups dropping
		dropType = rand() % 100 + 1;

		//spawn damage up
		if (dropType <= dmgUpChance)
		{
			newTexture = this->assets["damageUpIdle"];
			dropType = 1;
		}
		//spawn hp up
		else if (dropType <= hpUpChance)
		{
			newTexture = this->assets["hpUpIdle"];
			dropType = 2;
		}
		//spawn fire rate up
		else if (dropType <= fireRateUpChance)
		{
			newTexture = this->assets["fireRateUpIdle"];
			dropType = 3;
		}
		//spawn double bullets
		else if (dropType <= doubleBulletUpChance)
		{
			newTexture = this->assets["doubleBulletUpIdle"];
			dropType = 4;
		}
		//spawn spread bullets
		else if (dropType <= spreadBulletUpChance)
		{
			newTexture = this->assets["spreadBulletUpIdle"];
			dropType = 5;
		}
		//spawn burst bullets
		else if (dropType <= burstBulletUpChance)
		{
			newTexture = this->assets["burstBulletUpIdle"];
			dropType = 6;
		}
		else
			std::cout << "ERROR: NO POWER UP DROPPED" << std::endl;

		upgrades.push_back(new Upgrade(newTexture, enemy->getPos(), 30.f, dropType, deltaTime, scale));
	}
}

//print scores
void Game::printScores(unsigned int p)
{
	//read score file to score array
	const std::string highScoreFileName = "Scores/highScores.txt";
	std::string buffer;
	std::ifstream fin(highScoreFileName);
	if (!fin)
	{
		std::cerr << "Can't find " << highScoreFileName << std::endl;
		exit(1);
	}

	unsigned int scores[5] = {};
	for (int i = 0; i < 5; i++)
	{
		if (fin >> buffer)
			scores[i] = stoi(buffer);
	}
	fin.close();

	//update score array
	for (int i = 0; i < 5; i++)
	{
		if (points > scores[i])
		{
			unsigned int temp = scores[i];
			scores[i] = points;
			points = temp;
		}
	}

	//print and wirte the new score array to file 
	std::stringstream ss;
	ss << "High Scores" << "\n";

	std::ofstream fout(highScoreFileName);
	if (!fout)
	{
		std::cerr << "Can't find " << highScoreFileName << std::endl;
		exit(2);
	}

	for (int i = 0; i < 5; i++)
	{
		fout << scores[i] << ' ';
		ss << "  " << i + 1 << ":  " << scores[i] << "\n";
	}
	fout.close();
	texts["scoreText"]->setString(ss.str());
	texts["scoreText"]->setPosition(sf::Vector2f((windowWidth - texts["scoreText"]->getGlobalBounds().width) * 0.5f,
		(windowHeight - texts["scoreText"]->getGlobalBounds().height) * 0.4f));
}

void Game::playBGM()
{
	//play the bgm while the game is running
	this->normalBGM.play();
}

void Game::playBossBGM()
{
	//stop playing the normal background music if it's playing
	if (normalBGM.getStatus() == sf::Music::Playing)
		this->normalBGM.stop();
	//play the boss background music if it's not playing
	if (bossBGM.getStatus() != sf::Music::Playing)
		this->bossBGM.play();
	/*else
	{
		//stop playing the boss background music if it's playing
		if (bossBGM.getStatus() == sf::Music::Playing)
			this->bossBGM.stop();
		//play the normal background music if it's not playing
		if (normalBGM.getStatus() != sf::Music::Playing)
			this->normalBGM.play();
	}*/
}

/*
*****************************************public functions*****************************************
*/

//runs the game
void Game::run()
{
	//while the game window is not closed, run the game
	while (running())
	{
		//update delta time for seconds for a frame
		this->updateDeltaTime();

		//update poll events
		this->updatePollEvents();

		//update background animation if pause is not on
		if (!pause)
			this->updateWorld();

		//update the mouse position
		this->updateMousePos();

		//if the game is started, check for these events
		if (gameStarted)
		{
			if (!startMusic)
			{
				startMusic = true;
				//play background music
				playBGM();
			}
			//if on the boss wave, play the boss music
			if (currentWave == 11)
			{
				if (!startBossMusic)
				{
					startBossMusic = true;
					playBossBGM();
				}
			}
			//upate the pause timer 
			this->updatePause();
			
			//if the player is not dead, game is not paused, and boss is not destroyed, update the game
			if (!gameOver && !pause && !bossDestroyed)
				update();
			//stop the music if game is over
			else if (gameOver || bossDestroyed)
			{
				if (normalBGM.getStatus() == sf::Music::Playing)
					this->normalBGM.stop();
				if (bossBGM.getStatus() == sf::Music::Playing)
					this->bossBGM.stop();
			}
		}
		//render the game
		render();
	}
}