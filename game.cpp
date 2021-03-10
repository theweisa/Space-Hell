#include "game.h"

/*
*****************************************constructor / destructor*****************************************
*/

//constructor
Game::Game() 
{ 
	//initialize all variables
	this->initVariables();
	this->initWindow();
	this->initView();
	this->initTextures();
	this->initGUI();
	this->initWorld();
	this->initPlayer();
	this->initEnemy();
}

//destructor
Game::~Game() 
{
	//delete the window
	delete this->window;

	delete this->view;

	//delete the player
	delete this->player;

	//delete textures
	for (auto& texture : this->textures)
	{
		delete texture.second;
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
	for (auto* d : this->explosions)
	{
		delete d;
	}
	delete spaceBackground;
}

/*
*****************************************private functions*****************************************
*/

//initialize variables
void Game::initVariables()
{
	this->window = nullptr;

	this->gameOver = false;

	this->pause = false;

	this->pauseBufferMax = 20.f;
	this->pauseBuffer = pauseBufferMax;

	//initialize points to 0
	this->points = 0;

	//initialize combo to 1
	this->combo = 1;

	//set the first wave
	this->currentWave = 1;

	//delta time is 0
	this->deltaTime = 0.f;
}

//initialize window
void Game::initWindow()
{
	std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
	for (const auto& videoMode : sf::VideoMode::getFullscreenModes())
	{
		std::cout << "resolution: " << videoMode.width << "x" << videoMode.height;
		std::cout << ", bits per pixel: " << videoMode.bitsPerPixel << std::endl;
	}

	// Create a window with the same pixel depth as the desktop
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	//games main resolution is in 640 x 480
	this->videoMode.height = 768;
	this->videoMode.width = 1024;
	this->window = new sf::RenderWindow(this->videoMode, "Game", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize); //dynamically allocate mem for window

	if (!videoMode.isValid())
	{
		std::cout << "NEW MODE: " << videoMode.width << ", " << videoMode.height << std::endl;
	}


	//height of the window
	windowHeight = static_cast<float>(window->getSize().y);

	//width of the window
	windowWidth = static_cast<float>(window->getSize().x);

	//define the base height and base width to get the scale of the new resolution
	float baseHeight = 480.f;
	float baseWidth = 640.f;

	scale = videoMode.height / baseHeight;

	//set the max frame rate
	this->window->setFramerateLimit(60);
}

void Game::initView()
{
	view = new sf::View(sf::Vector2f(windowWidth * 0.5f, windowHeight * 0.5f), sf::Vector2f(windowWidth, windowHeight));
	//view->zoom(0.5);
	window->setView(*view);
	//window->setView(view);
}

//initialize the textures and animations
void Game::initTextures()
{
	addTexture("spaceBackground", "Animations/blurredSpaceBackground.png");
	addTexture("destroyedSheet", "Animations/enemyDestroyedSheet.png");
	addTexture("playerSpawn", "Animations/playerSpawnSheet.png");
	addTexture("playerIdle", "Animations/playerIdleSheet.png");
	addTexture("playerDamaged", "Animations/playerDamagedSheet.png");
	addTexture("enemyOneSpawn", "Animations/enemy1SpawnSheet.png");
	addTexture("enemyOneIdle", "Animations/enemy1IdleSheet.png");
	addTexture("bounceEnemyOneSpawn", "Animations/bounceEnemy1SpawnSheet.png");
	addTexture("bounceEnemyOneIdle", "Animations/bounceEnemy1IdleSheet.png");
	addTexture("enemyTwoSpawn", "Animations/enemy2SpawnSheet.png");
	addTexture("enemyTwoIdle", "Animations/enemy2IdleSheet.png");
	addTexture("circleEnemyTwoSpawn", "Animations/circleEnemy2SpawnSheet.png");
	addTexture("circleEnemyTwoIdle", "Animations/circleEnemy2IdleSheet.png");
	addTexture("enemyThreeSpawn", "Animations/enemy3SpawnSheet.png");
	addTexture("enemyThreeIdle", "Animations/enemy3IdleSheet.png");
	addTexture("burstEnemyThreeIdle", "Animations/burstEnemy3IdleSheet.png");
	addTexture("burstEnemyThreeSpawn", "Animations/burstEnemy3SpawnSheet.png");
	addTexture("enemyFourSpawn", "Animations/enemy4SpawnSheet.png");
	addTexture("enemyFourIdle", "Animations/enemy4IdleSheet.png");
	addTexture("bossEnemySpawn", "Animations/bossEnemySpawnSheet.png");
	addTexture("bossEnemyIdle", "Animations/bossEnemyIdleSheet.png");

	addTexture("playerBullet", "Textures/player_bullet.png");
	addTexture("longEnemyBullet", "Textures/enemy_bullet_long.png");
	addTexture("enemyBullet", "Textures/enemy_bullet.png");
	addTexture("enemyOne", "Textures/enemy1.png");
	addTexture("bounceEnemyOne", "Textures/bounceEnemy1.png");
	addTexture("enemyTwo", "Textures/enemy2.png");
	addTexture("circleEnemyTwo", "Textures/circleEnemy2.png");
	addTexture("enemyThree", "Textures/enemy3.png");
	addTexture("burstEnemyThree", "Textures/burstEnemy3.png");
	addTexture("enemyFour", "Textures/enemy4.png");
	addTexture("bossEnemy", "Textures/bossEnemy.png");
	addTexture("bigEnemyBullet", "Textures/bigEnemyBullet.png");
	addTexture("bouncingEnemyBullet", "Textures/bouncingEnemyBullet.png");
}

void Game::addTexture(const std::string key, const std::string fileName)
{
	this->textures[key] = new sf::Texture();
	if (!this->textures[key]->loadFromFile(fileName))
	{
		std::cout << "ERROR: failed to load " << fileName << std::endl;
	}
}

//initialize the GUI elements like text
void Game::initGUI()
{	
	if (!font.loadFromFile("Fonts/Minecraft.ttf"))
		std::cout << "ERROR: failed to load font.\n";
	
	//init point text
	//initText(pointText, font, sf::Vector2f(20, 400), 20, sf::Color::White, "POINT_TEXT");
	
	pointText.setFont(font);
	pointText.setCharacterSize(static_cast<unsigned>(20.f * scale));
	pointText.setFillColor(sf::Color::White);
	pointText.setString("POINT_TEXT");
	pointText.setPosition(20, windowHeight - 50.f);

	//init combo text
	comboText.setFont(font);
	comboText.setCharacterSize(static_cast<unsigned>(20.f * scale));
	comboText.setFillColor(sf::Color::White);
	comboText.setString("COMBO_TEXT");
	comboText.setPosition(windowWidth - comboText.getGlobalBounds().width, windowHeight - 50.f);

	//init player hp text
	playerHpText.setFont(font);
	playerHpText.setCharacterSize(static_cast<unsigned>(20.f * scale));
	playerHpText.setFillColor(sf::Color::White);
	playerHpText.setString("HP_TEXT");
	playerHpText.setPosition(20, windowHeight - 100.f);

	//init game over text
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(static_cast<unsigned>(40.f * scale));
	gameOverText.setFillColor(sf::Color::White);
	gameOverText.setString("GAME OVER");
	gameOverText.setPosition((windowWidth - gameOverText.getGlobalBounds().width) * 0.5f, (windowHeight - gameOverText.getGlobalBounds().height) * 0.5f);

	pauseText.setFont(font);
	pauseText.setCharacterSize(static_cast<unsigned>(40.f * scale));
	pauseText.setFillColor(sf::Color::White);
	pauseText.setString("PAUSE");
	pauseText.setPosition((windowWidth - pauseText.getGlobalBounds().width) * 0.5f, (windowHeight - pauseText.getGlobalBounds().height) * 0.5f);
}

//initialize world background
void Game::initWorld()
{
	this->spaceBackground = new Background(textures["spaceBackground"], sf::Vector2f(windowWidth * 0.5f, windowHeight * 0.5f), scale);
}

//initialize player variables
void Game::initPlayer()
{
	//create the player
	sf::Vector2f initialPos(windowWidth * 0.5f, windowHeight - 100.f);
	this->player = new Player(initialPos, scale);
	//player->setSpriteScale(scale);

	this->playerCollision = false;
	playerBulletHitbox = sf::FloatRect(1, 1, 6, 6);
	this->playerInvulTimerMax = 70.f;
	this->playerInvulTimer = this->playerInvulTimerMax;
	this->player->setRotate(0.f);

	player->setSpawnAnimation("spawnAnimation", this->textures["playerSpawn"], 4, 0, 64, 64);
}

//initialize enemy variables
void Game::initEnemy()
{
	this->enemyCollision = false;
	enemySpawned = false;
	enemyDestroyed = false;
	moveUp = false;
	moveRight = false;
	numEnemiesDestroyed = 0;
	numEnemies = 0;
	fireCluster = false;
	bossEnraged = false;
	bossDestroyed = false;
}

/*
*****************************************update functions*****************************************
*/

//update the game 
void Game::update()
{
	//updates mouse events
	this->updateMousePos();

	//move player based on input
	this->updatePlayer();

	//update player
	this->player->update();

	//update world collision with player
	this->updateWorldCollision(player, 0.f);

	//update enemies
	this->updateEnemies();

	this->updateBullets();

	this->updatePlayerCollision();

	this->updateEnemyCollision();

	this->updateExplosion();

	this->updateWorld();

	this->updateGUI();
}

void Game::updatePause()
{
	pauseBuffer++;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
	{
		if (pauseBuffer > pauseBufferMax)
		{
			pauseBuffer = 0.f;
			if (!pause)
				pause = true;
			else
				pause = false;
		}
	}
}

//time it takes to update and render one frame
void Game::updateDeltaTime()
{
	deltaTime = deltaClock.restart().asSeconds();
}

void Game::updateView()
{
	/*sf::Vector2f prevWindowSize(windowWidth, windowHeight);
	windowWidth = window->getSize().x;
	windowHeight = window->getSize().y;

	float scale = prevWindowSize.x / windowWidth;
	std::cout << "scale: " << scale << std::endl;

	view->setSize(sf::Vector2f(window->getSize()));
	view->setCenter(windowWidth * 0.5f, windowHeight * 0.5f);
	view->zoom(scale);
	window->setView(*view);*/
}

//update mouse position
void Game::updateMousePos()
{
	//updates mouse position relative to window
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);

	//updates player position
	playerPos = sf::Vector2f(this->player->getPos().x, this->player->getPos().y);
	//formula for direction: d.x = (m.x - p.x) / sqrt(p.x^2 - m.x^2) + (p.y^2 - m.y^2))
	playerAimDir = mousePosView - playerPos;
	playerAimDir = playerAimDir / sqrt(pow(playerAimDir.x, 2) + pow(playerAimDir.y, 2));

	//get the angle of the mouse relative to the player
	mouseAngle = -atan2(player->getPos().x - mousePosView.x, player->getPos().y - mousePosView.y) * 180.f / pi;
}

//update player
void Game::updatePlayer()
{
	//increment invul timer
	playerInvulTimer += 1.f;

	//rotate the player to point towards the mouse
	player->setRotate(mouseAngle);

	//will move the player and do actions depending on key pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->player->move(-1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->player->move(1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->player->move(0.f, 1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->player->move(0.f, -1.f);

	//if player presses space and can fire, shoot
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->player->canFire())
	{
		this->playerBullets.push_back(new Bullet(*this->textures["playerBullet"], 0, playerBulletHitbox, playerPos, mouseAngle, playerAimDir, 10.f, scale));
	}

	//should also update the player animation
	updatePlayerAnimation();
}

//update enemy
/*
make a wave constantly update on a timer; reset the timer at the end(?) of the wave
*/
void Game::updateEnemies()
{
	unsigned int vectPos = 0;

	//update wave one
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

	//move the enemies and have them shoot
	for (auto* enemy : this->enemies)
	{
		if (enemy->getType() == 2 || enemy->getType() == 12)
			updateWorldCollision(enemy, 50.f);
		else
			updateWorldCollision(enemy, 0.f);
		//angle of the player relative to the enemy
		enemyAngle = -atan2(enemies[vectPos]->getPos().x - player->getPos().x, enemies[vectPos]->getPos().y - player->getPos().y) * 180.f / 3.14159f;

		//rotate the enemy towards the player
		enemy->setRotate(enemyAngle);
		
		//update enemy fire rate and rotation
		enemy->update();

		//UPDATE ANIMATION
		updateEnemyAnimation(enemy);

		//set the enemy position
		enemyPos = sf::Vector2f(enemy->getPos().x, enemy->getPos().y);

		//gets the cos and sin values of the enemy compared to the player;
		enemyAimDir = playerPos - enemyPos;
		enemyAimDir = enemyAimDir / sqrt(pow(enemyAimDir.x, 2) + pow(enemyAimDir.y, 2));

		//enemy 1 shoots
		if (enemy->getType() == 0)
		{
			enemy->setEnemyToPlayerDir(enemyAimDir);
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
				if (bossPattern == 0)
					bossPattern = rand() % 4 + 1;
				bossFirePattern(enemy);
			}
		}
		vectPos++;
	}
}

//update bullets
void Game::updateBullets()
{
	unsigned vectPos = 0;

	//upade player bullets
	for (auto *b : this->playerBullets)
	{
		//move the bullets
		b->update();

		//remove the bullets when they go off screen
		if ((b->getPos().y < 0.f) || (b->getPos().y >= windowHeight) || (b->getPos().x < 0.f) || (b->getPos().x >= windowWidth))
		{
			delete this->playerBullets[vectPos];
			this->playerBullets.erase(this->playerBullets.begin() + vectPos);
			--vectPos;
		}
		++vectPos;
	}
	vectPos = 0;

	//update enemy bullets; move and delete them
	std::vector<Bullet*>::iterator itr = enemyBullets.begin();
	sf::Vector2f bulletPos;
	while (itr != enemyBullets.end())
	{
		(*itr)->update();

		if ((*itr)->getType() == 12)
		{
			float offsetTop = (*itr)->getBasePlayerPos().y + 10.f;
			float offsetBottom = (*itr)->getBasePlayerPos().y - 10.f;
			float offsetRight = (*itr)->getBasePlayerPos().x - 10.f;
			float offsetLeft = (*itr)->getBasePlayerPos().x + 10.f;
			if (((*itr)->getPos().y < offsetTop && (*itr)->getPos().y > offsetBottom) && ((*itr)->getPos().x < offsetLeft && (*itr)->getPos().x > offsetRight))
			{
				bulletPos = (*itr)->getPos();
				itr = enemyBullets.erase(itr);
				fireCluster = true;
			}
			else
				itr++;
		}

		else if (((*itr)->getPos().y < 0.f) || ((*itr)->getPos().y >= windowHeight) || ((*itr)->getPos().x < 0.f) || ((*itr)->getPos().x >= windowWidth))
		{
			if ((*itr)->getMaxBounce() > 0)
			{
				//top wall
				if ((*itr)->getPos().y < 0.f)
				{
					(*itr)->setDir(sf::Vector2f((*itr)->getDir().x, (*itr)->getDir().y * -1));
				}
				//bottom wall
				if ((*itr)->getPos().y >= windowHeight)
				{
					(*itr)->setDir(sf::Vector2f((*itr)->getDir().x, (*itr)->getDir().y * -1));
				}
				//left wall
				if ((*itr)->getPos().x < 0.f)
				{
					(*itr)->setDir(sf::Vector2f((*itr)->getDir().x * -1, (*itr)->getDir().y));
				}
				//right wall
				if ((*itr)->getPos().x >= windowWidth)
				{
					(*itr)->setDir(sf::Vector2f((*itr)->getDir().x * -1, (*itr)->getDir().y));
				}
				updateWorldCollision((*itr), 0.f);
				(*itr)->setMaxBounce((*itr)->getMaxBounce() - 1);
				itr++;
			}
			else
				itr = enemyBullets.erase(itr);
		}
		else
			itr++;
	}
	if (fireCluster)
	{
		fireCluster = false;
		burstClusterShot(bulletPos);
	}
}

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
	int unsigned enemyVectPos = 0;
	int unsigned bulletVectPos = 0;
	
	//check if each enemy has collided with a player bullet
	for (auto *enemy : this->enemies)
	{
		//checks if each bullet has collided with the enemy
		for (auto *bullet : this->playerBullets)
		{
			//bool that is if enemy hitbox intersects with player bullets
			enemyCollision = this->playerBullets[bulletVectPos]->getGlobalHitbox().intersects(this->enemies[enemyVectPos]->getGlobalHitbox());

			//if collision, enemy takes damage
			if (enemyCollision)
			{
				//enemy takes damage
				enemy->takeDamage(player->getDamage());

				//gain points for hitting the enemy
				points += 10 * combo;

				//enemy is set to destroyed if hp bar is below 0
				if (enemy->getHp() <= 0.f)
				{
					enemyDestroyed = true;
					if (enemy->getType() == 100)
						bossDestroyed = true;
				}

				//delete the bullet after it hits the enemy
				delete this->playerBullets[bulletVectPos];
				this->playerBullets.erase(this->playerBullets.begin() + bulletVectPos);
				--bulletVectPos;
			}
			bulletVectPos++;
		}
		//enemy is deleted if it is destroyed, or if the boss has been destroyed all the enemies are destroyed
		if (enemyDestroyed || bossDestroyed)
		{
			explosions.push_back(new Explosion(this->textures["destroyedSheet"], enemy->getPos(), scale));

			if (bossDestroyed)
			{
				points += 1000 * combo;
			}
			else
			//gain points for destroying the enemy
				points += 100 * combo;

			//increase your combo
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
	for (auto *b : this->enemyBullets)
	{
		//if the invul timer is above the set time (not invincible), check for player collision
		//if the invul timer is above the set time (not invincible), check for player collision
		if (playerInvulTimer >= playerInvulTimerMax)
		{
			//check if the player collided with an enemy bullet
			playerCollision = b->getGlobalHitbox().intersects(this->player->getGlobalHitbox());

			//player takes damage, becomes invincible, and combo is reset if hit
			if (playerCollision)
			{
				//takes damage if hit
				this->player->takeDamage(1.f);

				//make the player invincible for a time
				playerInvulTimer = 0.f;

				//reset the combo
				combo = 1;

				//delete the enemy bullet that hit the player
				delete b;
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

//update the GUI
void Game::updateGUI()
{
	std::stringstream ss;
	ss << "POINTS: " << points;
	pointText.setString(ss.str());
	ss.str("");

	ss << "COMBO: x" << combo;
	comboText.setString(ss.str());
	ss.str("");

	ss << "HP: " << player->getHp();
	playerHpText.setString(ss.str());
}

void Game::updateEnemyAnimation(Enemy* enemy)
{
	if (!enemy->endOfSpawnAnimation())
	{
		enemy->updateAnimation(enemy->getSpawnKey(), deltaTime);
	}
	else if (enemy->getCurrentAnimation() == "spawn")
	{
		switch (enemy->getType())
		{
		case 0:
			enemy->setIdleAnimation("idleAnimation", this->textures["enemyOneIdle"], 11, 0, 32, 32);
			break;
		case 10:
			enemy->setIdleAnimation("idleAnimation", this->textures["bounceEnemyOneIdle"], 11, 0, 32, 32);
			break;
		case 1:
			enemy->setIdleAnimation("idleAnimation", this->textures["enemyTwoIdle"], 11, 0, 32, 32);
			break;
		case 11:
			enemy->setIdleAnimation("idleAnimation", this->textures["circleEnemyTwoIdle"], 11, 0, 32, 32);
			break;
		case 2:
			enemy->setIdleAnimation("idleAnimation", this->textures["enemyThreeIdle"], 11, 0, 32, 32);
			break;
		case 12:
			enemy->setIdleAnimation("idleAnimation", this->textures["burstEnemyThreeIdle"], 11, 0, 32, 32);
			break;
		case 3:
			enemy->setIdleAnimation("idleAnimation", this->textures["enemyFourIdle"], 11, 0, 32, 32);
			break;
		case 100:
			enemy->setIdleAnimation("idleAnimation", this->textures["bossEnemyIdle"], 11, 0, 64, 64);
			break;
		}
	}
	//else if the end of the spawn animation, update the animation to be the idle animation
	else if (enemy->getCurrentAnimation() == "idle")
	{
		enemy->updateAnimation(enemy->getIdleKey(), deltaTime);
	}
}

void Game::updatePlayerAnimation()
{
	//******SET ANIMATION********
	//if the spawn animation ends and current animation is spawn, set the animation to idle
	if (player->endOfSpawnAnimation() && player->getCurrentAnimation() == "spawn")
	{
		player->setIdleAnimation("idleAnimation", this->textures["playerIdle"], 10, 0, 64, 64);
	}

	//if the player is invincible, set the animation to damaged
	else if (playerInvulTimer < playerInvulTimerMax && player->getCurrentAnimation() != "damaged")
	{
		player->setDamagedAnimation("damagedAnimation", this->textures["playerDamaged"], 10, 0, 64, 64);
	}

	//if they are not invincible and the current animation is damaged, set the animation back to idle
	else if (playerInvulTimer >= playerInvulTimerMax && player->getCurrentAnimation() == "damaged")
	{
		player->setIdleAnimation("idleAnimation", this->textures["playerIdle"], 10, 0, 64, 64);
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

	//else if the end of the spawn animation, update the animation to be the idle animation
}

void Game::updateExplosion()
{
	auto itr = explosions.begin();
	while (itr != explosions.end())
	{
		(*itr)->setTime(deltaTime);
		(*itr)->update();
		if ((*itr)->getEndOfAnimation("explosion"))
		{
			itr = explosions.erase(itr);
		}
		else
			itr++;
	}
}

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
		case sf::Event::Closed:
			this->window->close(); 
			break;
		case sf::Event::KeyPressed:
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

//render the game
void Game::render()
{
	//clear the previous render
	this->window->clear();

	//render the background
	this->spaceBackground->render(*this->window);

	//render enemies
	for (auto &e : this->enemies)
	{
		e->render(*this->window);
	}

	//render enemy bullets
	for (auto &b : this->enemyBullets)
	{
		b->render(*this->window);
	}

	//render player bullets
	for (auto &b : this->playerBullets) //render all the bullets to window
	{
		b->render(*this->window);
	}

	for (auto& d : this->explosions)
	{
		d->render(*this->window);
	}

	//render player
	this->player->render(*this->window); //draw the player

	//render the GUI
	this->renderGUI();
	
	if (pause)
	{
		window->draw(pauseText);
	}
	//render game over text if player dies
	if (this->player->getHp() <= 0.f)
	{
		window->draw(gameOverText);
	}

	//render the window
	this->window->display();
}

//render the GUI
void Game::renderGUI()
{
	window->draw(pointText);
	window->draw(comboText);
	window->draw(playerHpText);
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

//spawn 1 basic enemy from the top. 
void Game::waveOne()
{
	sf::Time elapsed = clock.getElapsedTime();
	if (elapsed.asSeconds() >= 2.f && numEnemies == 0)
	{
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth / 2.f, 0);
		spawnEnemyOne(initialPosition, numEnemies);
	}
	for (auto* e : enemies)
	{
		if (e->getType() == 0)
		{
			if (e->getPos().y < 100.f)
				e->move(0, 1);
		}
	}
	if (numEnemiesDestroyed == 1)
	{
		nextWave();
	}
}

//spawn three basic enemies to go around the player
void Game::waveTwo()
{
	sf::Time elapsed = clock.getElapsedTime();

	if (elapsed.asSeconds() >= 2.f && numEnemies == 0)
	{
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.5f, 0);
		spawnEnemyOne(initialPosition, numEnemies);
	}
	if (elapsed.asSeconds() >= 3.f && numEnemies == 1)
	{
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.5f, 0);
		spawnEnemyOne(initialPosition, numEnemies);
	}
	if (elapsed.asSeconds() >= 4.f && numEnemies == 2)
	{
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.5f, 0);
		spawnEnemyOne(initialPosition, numEnemies);
	}
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
	sf::Time elapsed = clock.getElapsedTime();
	if (elapsed.asSeconds() >= 2.f && numEnemies == 0)
	{
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.5f, 0);
		spawnEnemyTwo(initialPosition, numEnemies);
	}

	if (elapsed.asSeconds() >= 3.f && numEnemies == 1)
	{
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.5f, windowHeight);
		spawnEnemyOne(initialPosition, numEnemies);
	}

	if (elapsed.asSeconds() >= 4.f && numEnemies == 2)
	{
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.5f, windowHeight);
		spawnEnemyOne(initialPosition, numEnemies);
	}

	if (elapsed.asSeconds() >= 5.f && numEnemies == 3)
	{
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.5f, windowHeight);
		spawnEnemyOne(initialPosition, numEnemies);
	}
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
	sf::Vector2f radius(windowWidth - 100.f, windowHeight - 100.f);
	sf::Time elapsed = clock.getElapsedTime();
	if (elapsed.asSeconds() >= 2.f && numEnemies == 0)
	{
		//spawn two enemies from the top
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.33f, windowHeight);
		spawnEnemyTwo(initialPosition, numEnemies);

		numEnemies++;
		initialPosition = sf::Vector2f(windowWidth * 0.66f, windowHeight);
		spawnEnemyTwo(initialPosition, numEnemies);
	}

	if (elapsed.asSeconds() >= 3.f && numEnemies == 2)
	{
		//spawn from top
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.5f, 0);
		spawnBounceEnemyOne(initialPosition, numEnemies);
	}

	if (elapsed.asSeconds() >= 4.f && numEnemies == 3)
	{
		//spawn from top
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.5f, 0);
		spawnBounceEnemyOne(initialPosition, numEnemies);
	}

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
	sf::Time elapsed = clock.getElapsedTime();
	//spawn two shot gun enemies
	if (elapsed.asSeconds() >= 2.f && numEnemies == 0)
	{
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.33f, 0);
		spawnEnemyTwo(initialPosition, numEnemies);

		numEnemies++;
		initialPosition = sf::Vector2f(windowWidth * 0.66f, 0);
		spawnEnemyTwo(initialPosition, numEnemies);
	}
	//spawn bullet bounce enemy
	if (elapsed.asSeconds() >= 3.f && numEnemies == 2)
	{
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.5f, 0);
		spawnBounceEnemyOne(initialPosition, numEnemies);
	}
	//spawn sniper enemy and normal enemy
	if (elapsed.asSeconds() >= 4.f && numEnemies == 3)
	{
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.5f, windowHeight + 50.f);
		spawnEnemyThree(initialPosition, numEnemies);

		numEnemies++;
		initialPosition = sf::Vector2f(windowWidth * 0.5f, 0);
		spawnEnemyOne(initialPosition, numEnemies);
	}

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
	sf::Time elapsed = clock.getElapsedTime();
	//spawn basic enemy one
	if (elapsed.asSeconds() >= 2.f && numEnemies == 0)
	{
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.5f, 0);
		spawnEnemyOne(initialPosition, numEnemies);
	}

	//spawn basic enemy two
	if (elapsed.asSeconds() >= 3.f && numEnemies == 1)
	{
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.5f, 0);
		spawnEnemyOne(initialPosition, numEnemies);
	}

	//spawn shot gun enemy and circle shot
	if (elapsed.asSeconds() >= 3.5f && numEnemies == 2)
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
	sf::Time elapsed = clock.getElapsedTime();
	//spawn sniper and bounce enemy
	if (elapsed.asSeconds() >= 2.f && numEnemies == 0)
	{
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.33f, 50.f);
		spawnEnemyThree(initialPosition, numEnemies);

		numEnemies++;
		initialPosition = sf::Vector2f(windowWidth * 0.66f, 0);
		spawnBounceEnemyOne(initialPosition, numEnemies);
	}

	//spawn circle shot enemy
	if (elapsed.asSeconds() >= 3.f && numEnemies == 2)
	{
		//spawn sniper enemies from the two bottom corners of the map
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth, windowHeight * 0.5f);
		spawnCircleEnemyTwo(initialPosition, numEnemies);
	}

	//spawn spray enemy
	if (elapsed.asSeconds() >= 4.f && numEnemies == 3)
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
	sf::Time elapsed = clock.getElapsedTime();
	//spawn two shot gun enemies from top
	if (elapsed.asSeconds() >= 2.f && numEnemies == 0)
	{
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.33f, 0);
		spawnEnemyTwo(initialPosition, numEnemies);

		numEnemies++;
		initialPosition = sf::Vector2f(windowWidth * 0.66f, 0);
		spawnEnemyTwo(initialPosition, numEnemies);
	}

	//spawn basic enemy from bottom
	if (elapsed.asSeconds() >= 3.f && numEnemies == 2)
	{
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.5f, windowHeight);
		spawnEnemyOne(initialPosition, numEnemies);
	}

	//spawn circle shot enemy from bottom
	if (elapsed.asSeconds() >= 4.f && numEnemies == 3)
	{
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.5f, windowHeight);
		spawnCircleEnemyTwo(initialPosition, numEnemies);
	}

	//spawn burst enemy at top middle
	if (elapsed.asSeconds() >= 5.f && numEnemies == 4)
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
	sf::Time elapsed = clock.getElapsedTime();
	//spawn normal enemies from top
	if (elapsed.asSeconds() >= 2.f && numEnemies == 0)
	{
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.5f, 0);
		spawnEnemyOne(initialPosition, numEnemies);
	}

	if (elapsed.asSeconds() >= 3.f && numEnemies == 1)
	{
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.5f, 0);
		spawnEnemyOne(initialPosition, numEnemies);
	}

	//spawn two bullet bounce enemies circling too
	//spawn spray and circle enemy from sides
	if (elapsed.asSeconds() >= 4.f && numEnemies == 2)
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

	if (elapsed.asSeconds() >= 5.f && numEnemies == 5)
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
		//spray enemy
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
	sf::Time elapsed = clock.getElapsedTime();
	//spawn two spray enemies
	if (elapsed.asSeconds() >= 2.f && numEnemies == 0)
	{
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.33f, 0);
		spawnEnemyFour(initialPosition, numEnemies);

		numEnemies++;
		initialPosition = sf::Vector2f(windowWidth * 0.66f, 0);
		spawnEnemyFour(initialPosition, numEnemies);
	}

	//spawn burst and circle shot enemy
	if (elapsed.asSeconds() >= 3.f && numEnemies == 2)
	{
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.5f, 50.f);
		spawnBurstEnemyThree(initialPosition, numEnemies);

		numEnemies++;
		initialPosition = sf::Vector2f(windowWidth * 0.5f, windowHeight);
		spawnCircleEnemyTwo(initialPosition, numEnemies);
	}

	//wait 5 seconds to spawn two shot gun enemies
	if (elapsed.asSeconds() >= 10.f && numEnemies == 4)
	{
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.33f, windowHeight);
		spawnEnemyTwo(initialPosition, numEnemies);

		numEnemies++;
		initialPosition = sf::Vector2f(windowWidth * 0.66f, windowHeight);
		spawnEnemyTwo(initialPosition, numEnemies);
	}

	//spawn two bullet bounce enemies circling 
	if (elapsed.asSeconds() >= 11.f && numEnemies == 6)
	{
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.33f, 0);
		spawnBounceEnemyOne(initialPosition, numEnemies);

		numEnemies++;
		initialPosition = sf::Vector2f(windowWidth * 0.66f, 0);
		spawnBounceEnemyOne(initialPosition, numEnemies);
	}

	//spawn circle shot enemy
	if (elapsed.asSeconds() >= 12.f && numEnemies == 8)
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
	sf::Time elapsed = clock.getElapsedTime();
	if (elapsed.asSeconds() > 4.f && numEnemies == 0)
	{
		numEnemies++;
		sf::Vector2f initialPosition(windowWidth * 0.5f, 100.f);
		spawnBoss(initialPosition, numEnemies);
	}

	//spawn an enemy every 7 seconds after the boss is enraged
	if (bossEnraged && elapsed.asSeconds() >= 10.f)
	{
		spawnRandomEnemy();
		clock.restart();
	}

	for (auto* enemy : enemies)
	{
		if (enemy->getType() == 100)
		{
			/*if (enemy->getPos().y < 100.f)
				enemy->move(0, 1);*/
			if (enemy->getHp() <= enemy->getMaxHp() * 0.5f)
				bossEnraged = true;
		}
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
		bossDestroyed = false;
		nextWave();
	}
}

void Game::nextWave()	
{
	clock.restart();
	numEnemies = 0;
	numEnemiesDestroyed = 0;
	currentWave++;
}

void Game::moveInRect(Enemy* enemy)
{
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

void Game::spawnEnemyOne(sf::Vector2f initialPosition, unsigned posInWave)
{
	int type = 0;
	float hp = 15.f;
	float damage = 1.f;
	float fireRate = 30.f;
	float movementSpeed = 1.f * scale;
	sf::FloatRect newHitbox(8, 8, 16, 16);
	this->enemies.push_back(new Enemy(*this->textures["enemyOne"], type, hp, damage, fireRate, movementSpeed, newHitbox, initialPosition, posInWave, scale));
	
	Enemy* enemy = enemies.back();
	sf::Texture* spawnTexture = this->textures["enemyOneSpawn"];
	enemy->setSpawnAnimation("spawnAnimation", spawnTexture, 4, 0, 32, 32);
}

void Game::spawnBounceEnemyOne(sf::Vector2f initialPosition, unsigned posInWave)
{
	sf::FloatRect newHitbox(8, 8, 16, 16);

	int type = 10;
	float hp = 20.f;
	float damage = 1.f;
	float fireRate = 50.f;
	float movementSpeed = 1.f * scale;
	this->enemies.push_back(new Enemy(*this->textures["bounceEnemyOne"], type, hp, damage, fireRate, movementSpeed, newHitbox, initialPosition, posInWave, scale));

	Enemy* enemy = enemies.back();
	sf::Texture* spawnTexture = this->textures["bounceEnemyOneSpawn"];
	enemy->setSpawnAnimation("spawnAnimation", spawnTexture, 4, 0, 32, 32);
}

void Game::spawnEnemyTwo(sf::Vector2f initialPosition, unsigned posInWave)
{
	sf::FloatRect newHitbox(8, 8, 16, 16);

	float hp = 20.f;
	float damage = 1.f;
	float fireRate = 50.f;
	float movementSpeed = 0.8f * scale;
	int type = 1;
	this->enemies.push_back(new Enemy(*this->textures["enemyTwo"], type, hp, damage, fireRate, movementSpeed, newHitbox, initialPosition, posInWave, scale));

	Enemy* enemy = enemies.back();
	sf::Texture* spawnTexture = this->textures["enemyTwoSpawn"];
	enemy->setSpawnAnimation("spawnAnimation", spawnTexture, 4, 0, 32, 32);
}

void Game::spawnCircleEnemyTwo(sf::Vector2f initialPosition, unsigned posInWave)
{
	sf::FloatRect newHitbox(8, 8, 16, 16);

	float hp = 30.f;
	float damage = 1.f;
	float fireRate = 75.f;
	float movementSpeed = 0.8f * scale;
	int type = 11;
	this->enemies.push_back(new Enemy(*this->textures["circleEnemyTwo"], type, hp, damage, fireRate, movementSpeed, newHitbox, initialPosition, posInWave, scale));

	Enemy* enemy = enemies.back();
	sf::Texture* spawnTexture = this->textures["circleEnemyTwoSpawn"];
	enemy->setSpawnAnimation("spawnAnimation", spawnTexture, 4, 0, 32, 32);
}

void Game::spawnEnemyThree(sf::Vector2f initialPosition, unsigned posInWave)
{
	sf::FloatRect newHitbox(11, 6, 10, 24);
	float hp = 17.f;
	float damage = 1.f;
	float fireRate = 100.f;
	float movementSpeed = 1.0f * scale;
	int type = 2;
	this->enemies.push_back(new Enemy(*this->textures["enemyThree"], type, hp, damage, fireRate, movementSpeed, newHitbox, initialPosition, posInWave, scale));


	Enemy* enemy = enemies.back();
	sf::Texture* spawnTexture = this->textures["enemyThreeSpawn"];
	enemy->setSpawnAnimation("spawnAnimation", spawnTexture, 4, 0, 32, 32);
}

void Game::spawnBurstEnemyThree(sf::Vector2f initialPosition, unsigned posInWave)
{
	sf::FloatRect newHitbox(11, 6, 10, 24);
	float hp = 20.f;
	float damage = 1.f;
	float fireRate = 80.f;
	float movementSpeed = 1.0f * scale;
	int type = 12;
	this->enemies.push_back(new Enemy(*this->textures["burstEnemyThree"], type, hp, damage, fireRate, movementSpeed, newHitbox, initialPosition, posInWave, scale));

	Enemy* enemy = enemies.back();
	sf::Texture* spawnTexture = this->textures["burstEnemyThreeSpawn"];
	enemy->setSpawnAnimation("spawnAnimation", spawnTexture, 4, 0, 32, 32);
}

void Game::spawnEnemyFour(sf::Vector2f initialPosition, unsigned posInWave)
{
	sf::FloatRect newHitbox(6, 6, 20, 20);
	float hp = 30.f;
	float damage = 1.f;
	float fireRate = 10.f;
	float movementSpeed = 0.4f * scale;
	int type = 3;
	this->enemies.push_back(new Enemy(*this->textures["enemyFour"], type, hp, damage, fireRate, movementSpeed, newHitbox, initialPosition, posInWave, scale));

	Enemy* enemy = enemies.back();
	sf::Texture* spawnTexture = this->textures["enemyFourSpawn"];
	enemy->setSpawnAnimation("spawnAnimation", spawnTexture, 4, 0, 32, 32);
}

void Game::spawnBoss(sf::Vector2f initialPosition, unsigned posInWave)
{
	sf::FloatRect newHitbox(13, 13, 38, 38);
	float hp = 300.f;
	float damage = 1.f;
	float fireRate = 100.f;
	float movementSpeed = 0.7f * scale;
	int type = 100;
	this->enemies.push_back(new Enemy(*this->textures["bossEnemy"], type, hp, damage, fireRate, movementSpeed, newHitbox, initialPosition, posInWave, scale));

	Enemy* enemy = enemies.back();
	sf::Texture* spawnTexture = this->textures["bossEnemySpawn"];
	enemy->setSpawnAnimation("spawnAnimation", spawnTexture, 12, 0, 64, 64);
}

void Game::spawnRandomEnemy()
{
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

void Game::enemyOneFirePattern()
{
	//set the bullet hitbox
	sf::FloatRect bulletHitbox(1, 1, 6, 6);
	float bulletSpeed = 3.f * scale;
	//shoot enemy bullet
	this->enemyBullets.push_back(new Bullet(*this->textures["enemyBullet"], 10, bulletHitbox, enemyPos, enemyAngle, enemyAimDir, bulletSpeed, scale));
}

void Game::bounceEnemyOneFirePattern()
{
	sf::FloatRect bulletHitbox(1, 1, 6, 6);
	sf::Texture* bulletTexture = this->textures["bouncingEnemyBullet"];
	int bulletType = 13;
	float bulletSpeed = 3.f * scale;

	this->enemyBullets.push_back(new Bullet(*bulletTexture, bulletType, bulletHitbox, enemyPos, enemyAngle, enemyAimDir, bulletSpeed, scale));
}

void Game::enemyTwoFirePattern()
{
	sf::FloatRect bulletHitbox(1, 1, 6, 6);
	sf::Texture* bulletTexture = this->textures["enemyBullet"];
	int bulletType = 10;
	float bulletSpeed = 4.f * scale;
	float spreadAngle = pi / 18.f;

	fireSpread(bulletTexture, bulletHitbox, bulletType, bulletSpeed, spreadAngle);
}

void Game::circleEnemyTwoFirePattern()
{
	sf::FloatRect bulletHitbox(1, 1, 6, 6);
	sf::Texture* bulletTexture = this->textures["enemyBullet"];
	int bulletType = 10;

	fireInCircle(bulletTexture, bulletHitbox, bulletType, enemyPos, 0);
}

void Game::enemyThreeFirePattern()
{
	sf::FloatRect bulletHitbox(6, 0, 4, 16);
	this->enemyBullets.push_back(new Bullet(*this->textures["longEnemyBullet"], 11, bulletHitbox, enemyPos, enemyAngle, enemyAimDir, 10.f, scale));
}

void Game::burstEnemyThreeFirePattern()
{
	sf::Texture* bulletTexture = this->textures["bigEnemyBullet"];
	sf::FloatRect bulletHitbox(1, 1, 14, 14);
	int bulletType = 12;

	fireClusterShot(bulletTexture, bulletHitbox, bulletType);
}

void Game::enemyFourFirePattern(Enemy* enemy)
{
	enemy->setFireRate(8.f);
	sf::FloatRect bulletHitbox(1, 1, 6, 6);
	sf::Texture* bulletTexture = this->textures["enemyBullet"];
	int bulletType = 10;
	float bulletOffset = pi / 9.f;
	baseEnemyAimDir = sf::Vector2f(enemyAimDir);
	if (enemy->getBulletCounter() < 7)
		fireWave(bulletTexture, bulletHitbox, bulletType, bulletOffset, baseEnemyAimDir, enemy);
	else
	{
		enemy->setBulletCounter(0);
		enemy->setFireRate(75.f);
	}
}

void Game::bossFirePattern(Enemy * enemy)
{
	switch (bossPattern)
	{
	case 1:
		if (enemy->getBulletCounter() < 10)
			bossPatternOne(enemy);
		else
		{
			if (bossEnraged)
				enemy->setFireRate(60.f);
			else
				enemy->setFireRate(100.f);
			enemy->setBulletCounter(0);
			bossPattern = 0;
		}
		break;
	case 2:
		if (enemy->getBulletCounter() < 5)
			bossPatternTwo(enemy);
		else
		{
			if (bossEnraged)
				enemy->setFireRate(60.f);
			else
				enemy->setFireRate(100.f);
			enemy->setBulletCounter(0);
			bossPattern = 0;
		}
		break;
	case 3:
		if (enemy->getBulletCounter() < 20)
		{
			bossPatternThree(enemy);
		}
		else
		{
			if (bossEnraged)
				enemy->setFireRate(60.f);
			else
				enemy->setFireRate(100.f);
			enemy->setBulletCounter(0);
			bossPattern = 0;
		}
		break;
	case 4:
		if (enemy->getBulletCounter() < 7)
			bossPatternFour(enemy);
		else
		{
			if (bossEnraged)
				enemy->setFireRate(60.f);
			else
				enemy->setFireRate(100.f);
			enemy->setBulletCounter(0);
			bossPattern = 0;
		}
		break;
	}
}

//big wave of bullets; covering the whole screen
void Game::bossPatternOne(Enemy* enemy)
{
	enemy->setBulletCounter(enemy->getBulletCounter() + 1);
	int randTime = static_cast<int>(time(0) + enemy->getBulletCounter());
	srand(randTime);
	float offset = static_cast<float>(rand() % 20);

	if (bossEnraged)
		enemy->setFireRate(8.f);
	else
		enemy->setFireRate(10.f);
	sf::FloatRect bulletHitbox(1, 1, 6, 6);
	sf::Texture* bulletTexture = this->textures["enemyBullet"];
	int bulletType = 10;
	fireInCircle(bulletTexture, bulletHitbox, bulletType, enemyPos, offset);
}

//cluster of bullets that explode into all directions : 20 %
void Game::bossPatternTwo(Enemy* enemy)
{
	if (bossEnraged)
		enemy->setFireRate(40.f);
	else
		enemy->setFireRate(50.f);
	sf::Texture* bulletTexture = this->textures["bigEnemyBullet"];
	sf::FloatRect bulletHitbox(1, 1, 14, 14);
	int bulletType = 12;

	enemy->setBulletCounter(enemy->getBulletCounter() + 1);
	fireClusterShot(bulletTexture, bulletHitbox, bulletType);
}

//machine gun shots targeting the player for some time : 20 %
void Game::bossPatternThree(Enemy* enemy)
{
	if (bossEnraged)
		enemy->setFireRate(8.f);
	else
		enemy->setFireRate(10.f);
	enemy->setBulletCounter(enemy->getBulletCounter() + 1);

	sf::FloatRect bulletHitbox(1, 1, 6, 6);
	sf::Texture* bulletTexture = this->textures["enemyBullet"];
	int bulletType = 10;

	fireSpread(bulletTexture, bulletHitbox, bulletType, 3.f, pi / 8.f);
}

//shoot a wave that bounces three times
void Game::bossPatternFour(Enemy* enemy)
{
	if (bossEnraged)
		enemy->setFireRate(6.4f);
	else
		enemy->setFireRate(8.f);
	sf::FloatRect bulletHitbox(1, 1, 6, 6);
	sf::Texture* bulletTexture = this->textures["bouncingEnemyBullet"];
	int bulletType = 13;
	float bulletOffset = pi / 9.f;
	baseEnemyAimDir = sf::Vector2f(enemyAimDir);

	fireWave(bulletTexture, bulletHitbox, bulletType, bulletOffset, baseEnemyAimDir, enemy);
}

//fire bullets in a spread
void Game::fireSpread(sf::Texture* bulletTexture, sf::FloatRect bulletHitbox, int bulletType, float bulletSpeed, float spreadDegree)
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

//fire bullets in a wave
void Game::fireWave(sf::Texture* bulletTexture, sf::FloatRect bulletHitbox, int bulletType, float bulletOffset, sf::Vector2f baseAimDir, Enemy* enemy)
{
	//on the first bullet, set the base direction to shoot at
	enemy->setBulletCounter(enemy->getBulletCounter() + 1);
	int bulletCounter = enemy->getBulletCounter();

	if (bulletCounter == 1)
	{
		baseEnemyAimDir = sf::Vector2f(baseAimDir);
	}

	switch (bulletCounter)
	{
	case 1:
		//shoot 36 degrees
		enemyAimDir = sf::Vector2f(
			baseEnemyAimDir.x * (cos(bulletOffset * 3)) + baseEnemyAimDir.y * (sin(bulletOffset * 3)),
			baseEnemyAimDir.y * (cos(bulletOffset * 3)) - baseEnemyAimDir.x * (sin(bulletOffset * 3))
		);
		break;
	case 2:
		//shoot 18 degrees
		enemyAimDir = sf::Vector2f(
			baseEnemyAimDir.x * (cos(bulletOffset * 2)) + baseEnemyAimDir.y * (sin(bulletOffset * 2)),
			baseEnemyAimDir.y * (cos(bulletOffset * 2)) - baseEnemyAimDir.x * (sin(bulletOffset * 2))
		);
		break;
	case 3:
		//shoot 9 degrees
		enemyAimDir = sf::Vector2f(
			baseEnemyAimDir.x * (cos(bulletOffset)) + baseEnemyAimDir.y * (sin(bulletOffset)),
			baseEnemyAimDir.y * (cos(bulletOffset)) - baseEnemyAimDir.x * (sin(bulletOffset))
		);
		break;
	case 4:
		//shoot at the players initial position (90 degrees)
		enemyAimDir = baseEnemyAimDir;
		break;
	case 5:
		//shoot
		enemyAimDir = sf::Vector2f(
			baseEnemyAimDir.x * (cos(bulletOffset)) - baseEnemyAimDir.y * (sin(bulletOffset)),
			baseEnemyAimDir.y * (cos(bulletOffset)) + baseEnemyAimDir.x * (sin(bulletOffset))
		);
		break;
	case 6:
		enemyAimDir = sf::Vector2f(
			baseEnemyAimDir.x * (cos(bulletOffset * 2)) - baseEnemyAimDir.y * (sin(bulletOffset * 2)),
			baseEnemyAimDir.y * (cos(bulletOffset * 2)) + baseEnemyAimDir.x * (sin(bulletOffset * 2))
		);
		break;
	case 7:
		enemyAimDir = sf::Vector2f(
			baseEnemyAimDir.x * (cos(bulletOffset * 3)) - baseEnemyAimDir.y * (sin(bulletOffset * 3)),
			baseEnemyAimDir.y * (cos(bulletOffset * 3)) + baseEnemyAimDir.x * (sin(bulletOffset * 3))
		);
		break;
	default:
		enemy->setBulletCounter(0);
	}

	this->enemyBullets.push_back(new Bullet(*bulletTexture, bulletType, bulletHitbox, enemyPos, enemyAngle, enemyAimDir, 3.f, scale));
}

//fire bullets in a circle
void Game::fireInCircle(sf::Texture* bulletTexture, sf::FloatRect bulletHitbox, int bulletType, sf::Vector2f centerPos, float offset)
{
	float degree = offset;
	float radians;
	sf::Vector2f aimDir;
	for (int i = 0; i < 12; i++)
	{
		radians = degree * pi / 180.f;
		aimDir = sf::Vector2f(cos(radians), sin(radians));
		enemyBullets.push_back(new Bullet(*bulletTexture, bulletType, bulletHitbox, centerPos, enemyAngle, aimDir, 3.f, scale));
		degree += 30.f;
	}
}

//fire bullets as a cluster
void Game::fireClusterShot(sf::Texture* bulletTexture, sf::FloatRect bulletHitbox, int bulletType)
{
	enemyBullets.push_back(new Bullet(*bulletTexture, bulletType, bulletHitbox, enemyPos, enemyAngle, enemyAimDir, 3.f, scale));

	Bullet* bullet = enemyBullets.back();
	bullet->setBasePlayerPos(playerPos);
}

//burst the cluster shot
void Game::burstClusterShot(sf::Vector2f burstPos)
{
	sf::FloatRect bulletHitbox(1, 1, 6, 6);
	sf::Texture* bulletTexture = this->textures["enemyBullet"];
	int bulletType = 10;
	fireInCircle(bulletTexture, bulletHitbox, bulletType, burstPos, 0);
}

//runs the game
void Game::run()
{
	while (running())
	{
		this->updateDeltaTime();
		this->updatePollEvents();
		this->updatePause();
		if (player->getHp() > 0.f && !pause)
			update();
		else
			gameOver = true;
		render();
	}
}