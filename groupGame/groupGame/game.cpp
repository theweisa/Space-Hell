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
}

/*
*****************************************private functions*****************************************
*/

//initialize variables
void Game::initVariables()
{
	this->window = nullptr;

	this->gameOver = false;

	this->points = 0;
	this->combo = 1;
	this->currentWave = 10;
}

//initialize window
void Game::initWindow()
{
	/**
	// Display the list of all the video modes available for fullscreen
	std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
	for (std::size_t i = 0; i < modes.size(); ++i)
	{
		sf::VideoMode mode = modes[i];
		std::cout << "Mode #" << i << ": "
			<< mode.width << "x" << mode.height << " - "
			<< mode.bitsPerPixel << " bpp" << std::endl;
	}
	// Create a window with the same pixel depth as the desktop
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	*/
	this->videoMode.height = 480;
	this->videoMode.width = 720;
	this->window = new sf::RenderWindow(this->videoMode, "Game", sf::Style::Titlebar | sf::Style::Close); //dynamically allocate mem for window

	//view.setSize(sf::Vector2f(window->getSize()));
	//window->setView(view);

	this->window->setFramerateLimit(60);
}

//initialize the textures
void Game::initTextures()
{
	this->textures["playerBullet"] = new sf::Texture();
	this->textures["playerBullet"]->loadFromFile("Textures/player_bullet.png");

	this->textures["longEnemyBullet"] = new sf::Texture();
	this->textures["longEnemyBullet"]->loadFromFile("Textures/enemy_bullet_long.png");

	this->textures["enemyBullet"] = new sf::Texture();
	this->textures["enemyBullet"]->loadFromFile("Textures/enemy_bullet.png");

	this->textures["enemyOne"] = new sf::Texture();
	this->textures["enemyOne"]->loadFromFile("Textures/enemy1.png");

	this->textures["bounceEnemyOne"] = new sf::Texture();
	this->textures["bounceEnemyOne"]->loadFromFile("Textures/bounceEnemy1.png");

	this->textures["enemyTwo"] = new sf::Texture();
	this->textures["enemyTwo"]->loadFromFile("Textures/enemy2.png");

	this->textures["circleEnemyTwo"] = new sf::Texture();
	this->textures["circleEnemyTwo"]->loadFromFile("Textures/circleEnemy2.png");

	this->textures["enemyThree"] = new sf::Texture();
	this->textures["enemyThree"]->loadFromFile("Textures/enemy3.png");

	this->textures["burstEnemyThree"] = new sf::Texture();
	this->textures["burstEnemyThree"]->loadFromFile("Textures/burstEnemy3.png");

	this->textures["enemyFour"] = new sf::Texture();
	this->textures["enemyFour"]->loadFromFile("Textures/enemy4.png");

	this->textures["bossEnemy"] = new sf::Texture();
	this->textures["bossEnemy"]->loadFromFile("Textures/bossEnemy.png");

	this->textures["bigEnemyBullet"] = new sf::Texture();
	this->textures["bigEnemyBullet"]->loadFromFile("Textures/bigEnemyBullet.png");

	this->textures["bouncingEnemyBullet"] = new sf::Texture();
	this->textures["bouncingEnemyBullet"]->loadFromFile("Textures/bouncingEnemyBullet.png");

	this->textures["spaceBackground"] = new sf::Texture();
	this->textures["spaceBackground"]->loadFromFile("Textures/space_background.jpg");

	//Ian's code(Upgrades)
	this->textures["DBRayupgrades"] = new sf::Texture();
	this->textures["DBRayupgrades"]->loadFromFile("Textures/power_up.png");

	this->textures["SPRayUpgrade"] = new sf::Texture();
	this->textures["SPRayUpgrade"]->loadFromFile("Textures/spread_shot.png");

	this->textures["HPUpgrade"] = new sf::Texture();
	this->textures["HPUpgrade"]->loadFromFile("Textures/hp_upgrade.png");

	this->textures["RTUpgrade"] = new sf::Texture();
	this->textures["RTUpgrade"]->loadFromFile("Textures/star.png");
}

void Game::initGUI()
{
	if (!font.loadFromFile("Fonts/Minecraft.ttf"))
		std::cout << "ERROR: failed to load font.\n";
	
	//init point text
	//initText(pointText, font, sf::Vector2f(20, 400), 20, sf::Color::White, "POINT_TEXT");
	
	pointText.setFont(font);
	pointText.setCharacterSize(20);
	pointText.setFillColor(sf::Color::White);
	pointText.setString("POINT_TEXT");
	pointText.setPosition(20, 400);

	//init combo text
	comboText.setFont(font);
	comboText.setCharacterSize(20);
	comboText.setFillColor(sf::Color::White);
	comboText.setString("COMBO_TEXT");
	comboText.setPosition(580, 430);

	//init player hp text
	playerHpText.setFont(font);
	playerHpText.setCharacterSize(20);
	playerHpText.setFillColor(sf::Color::White);
	playerHpText.setString("HP_TEXT");
	playerHpText.setPosition(20, 430);

	//init game over text
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(40);
	gameOverText.setFillColor(sf::Color::White);
	gameOverText.setString("GAME OVER");
	gameOverText.setPosition((window->getSize().x - gameOverText.getGlobalBounds().width) * 0.5f, (window->getSize().y - gameOverText.getGlobalBounds().height) * 0.5f);
}

/*
void Game::initText(sf::Text& text, sf::Font font, sf::Vector2f pos, int size, sf::Color color, std::string initialString)
{
	text.setFont(font);
	text.setPosition(pos);
	text.setCharacterSize(size);
	text.setFillColor(color);
	text.setString(initialString);
}
*/
//initialize world background
void Game::initWorld()
{
	worldBackground.setTexture(*textures["spaceBackground"]);
}

//initialize player variables
void Game::initPlayer()
{
	//create the player
	this->player = new Player();

	this->playerCollision = false;
	playerBulletHitbox = sf::FloatRect(1, 1, 6, 6);
	this->playerInvulTimerMax = 70.f;
	this->playerInvulTimer = this->playerInvulTimerMax;
	this->player->setRotate(0.f);
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
void Game::update(const float& dt)
{
	this->updateView();
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

	this->updateGUI();

	//update timer for non picked-up upgrades
	this->upgradesUpdate(dt);

	//update timer for pickedup weapon upgrades
	this->gunUpdate(dt);

	//update timer for fire rate
	this->fireRTUpdate(dt);

	this->updateGUI();
}

void Game::updateView()
{
	//window->setView(view);
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
	playerAimDir = playerAimDir / static_cast<float>(sqrt(pow(playerAimDir.x, 2) + pow(playerAimDir.y, 2)));

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
		float fireRT;
		float SPfireRT;//spread firerate

		if (this->fireRTStatus()) {
			fireRT = 20.f;
			SPfireRT = 13.f;
		}
		else {
			fireRT = 10.f;
			SPfireRT = 7.5f;
		}

		//std::cout << mouseAngle << std::endl;
		//std::cout << "Gun level: " << this->player->getGunLevel() << std::endl;
		if (this->gunStatus()) {

			switch (this->player->getGunLevel()) {

			case(0):
				//std::cout << "Player pos :" << this->player->getPos().x << " " << this->player->getPos().y << std::endl;

				//std::cout << "Shoot double ray bullets" << std::endl;
				this->playerBullets.push_back(new Bullet(*this->textures["playerBullet"], 0, playerBulletHitbox, Vector2f(this->player->getPos().x + (25.f * cos(abs(mouseAngle))), this->player->getPos().y + (25.f * sin(abs(mouseAngle)))), mouseAngle, playerAimDir, fireRT));
				this->playerBullets.push_back(new Bullet(*this->textures["playerBullet"], 0, playerBulletHitbox, Vector2f(this->player->getPos().x - (25.f * cos(abs(mouseAngle))), this->player->getPos().y - (25.f * sin(abs(mouseAngle)))), mouseAngle, playerAimDir, fireRT));

				break;

			case(1):
				//std::cout << "Shoot spread bullets" << std::endl;
				Vector2f newPlayerDir;
				this->playerBullets.push_back(new Bullet(*this->textures["playerBullet"], 0, playerBulletHitbox, playerPos, mouseAngle, playerAimDir, SPfireRT));

				newPlayerDir = Vector2f(
					playerAimDir.x * (cos(pi / 20.f)) - playerAimDir.x * (sin(pi / 20.f)),
					playerAimDir.y * (cos(pi / 20.f)) + playerAimDir.x * (sin(pi / 20.f)));

				this->playerBullets.push_back(new Bullet(*this->textures["playerBullet"], 0, playerBulletHitbox, playerPos, mouseAngle, newPlayerDir, SPfireRT));

				newPlayerDir = Vector2f(
					playerAimDir.x * (cos(pi / 20.f)) + playerAimDir.x * (sin(pi / 20.f)),
					playerAimDir.y * (cos(pi / 20.f)) - playerAimDir.x * (sin(pi / 20.f)));

				this->playerBullets.push_back(new Bullet(*this->textures["playerBullet"], 0, playerBulletHitbox, playerPos, mouseAngle, newPlayerDir, SPfireRT));
				break;
			}


		}
		else {
			this->playerBullets.push_back(new Bullet(*this->textures["playerBullet"], 0, playerBulletHitbox, playerPos, mouseAngle, playerAimDir, fireRT));

		}
	}
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

		//move the enemy
		//enemy->move(1.f, 0.f);

		//set the enemy position
		enemyPos = sf::Vector2f(enemy->getPos().x, enemy->getPos().y);

		//gets the cos and sin values of the enemy compared to the player;
		enemyAimDir = playerPos - enemyPos;
		enemyAimDir = enemyAimDir / static_cast<float>(sqrt(pow(enemyAimDir.x, 2) + pow(enemyAimDir.y, 2)));

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
		if ((b->getPos().y < 0.f) || (b->getPos().y >= this->window->getSize().y) || (b->getPos().x < 0.f) || (b->getPos().x >= this->window->getSize().x))
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

		else if (((*itr)->getPos().y < 0.f) || ((*itr)->getPos().y >= this->window->getSize().y) || ((*itr)->getPos().x < 0.f) || ((*itr)->getPos().x >= this->window->getSize().x))
		{
			if ((*itr)->getMaxBounce() > 0)
			{
				//top wall
				if ((*itr)->getPos().y < 0.f)
				{
					(*itr)->setDir(sf::Vector2f((*itr)->getDir().x, (*itr)->getDir().y * -1));
				}
				//bottom wall
				if ((*itr)->getPos().y >= this->window->getSize().y)
				{
					(*itr)->setDir(sf::Vector2f((*itr)->getDir().x, (*itr)->getDir().y * -1));
				}
				//left wall
				if ((*itr)->getPos().x < 0.f)
				{
					(*itr)->setDir(sf::Vector2f((*itr)->getDir().x * -1, (*itr)->getDir().y));
				}
				//right wall
				if ((*itr)->getPos().x >= this->window->getSize().x)
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
	if (entity->getPos().y >= this->window->getSize().y - offset)
	{
		entity->setPosition(entity->getPos().x, this->window->getSize().y - offset);
	}
	//left world collision
	if (entity->getPos().x < offset)
	{
		entity->setPosition(offset, entity->getPos().y);
	}
	//right world collision
	if (entity->getPos().x >= this->window->getSize().x - offset)
	{
		entity->setPosition(this->window->getSize().x - offset, entity->getPos().y);
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

			//drop powerup
			int dropChance = rand() % 100 + 1;

			if (dropChance > 10)
			{
				int type_Generator = rand() % 5;

				switch (type_Generator) {

				case(0):
					this->upgrades.push_back(new Upgrade(*this->textures["DBRayupgrades"], this->enemies[enemyVectPos]->getPosition(), 500.f, type_Generator));
					std::cout << "Inserting a DBRAY powerup!" << std::endl;
					break;

				case(1):
					this->upgrades.push_back(new Upgrade(*this->textures["SPRayUpgrade"], this->enemies[enemyVectPos]->getPosition(), 500.f, type_Generator));
					std::cout << "Inserting a SPRAY powerup!" << std::endl;
					break;

				case(2):
					this->upgrades.push_back(new Upgrade(*this->textures["HPUpgrade"], this->enemies[enemyVectPos]->getPosition(), 500.f, type_Generator));
					std::cout << "Inserting a HP powerup!" << std::endl;
					break;

				case(3):
					this->upgrades.push_back(new Upgrade(*this->textures["RTUpgrade"], this->enemies[enemyVectPos]->getPosition(), 500.f, type_Generator));
					std::cout << "Inserting a FIRERT powerup!" << std::endl;

				}
			}

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
	if (!this->upgrades.empty()) {
		for (auto i = 0; i < this->upgrades.size(); i++)
		{
			if (this->upgrades[i]->checkCollision(this->player->getGlobalHitbox()))
			{
				std::cout << "PowerUp!\n";
				switch (this->upgrades[i]->returnType()) {
				case(0):
					std::cout << "Upgrade Double Ray Gun!" << std::endl;
					this->player->aliveTimerReset();
					this->player->updateGunLevel(0, 500.f);
					break;

				case(1):
					std::cout << "Upgrade Spread Gun!" << std::endl;
					this->player->aliveTimerReset();
					this->player->updateGunLevel(1, 500.f);
					break;

				case(2):
					this->player->addHP();
					break;

				case(3):
					this->player->RTaliveTimerReset();
					this->player->updateRTUpgrade(true, 500.f);
				}
				this->upgrades.erase(this->upgrades.begin() + i);
				std::cout << "Powerup entity deleted!" << std::endl;
				break;

			}
		}
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
	this->renderWorld();

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

	for (auto& e : this->upgrades)
	{
		e->Draw(*this->window);

		e->update();
	}


	//render player
	this->player->render(*this->window); //draw the player

	//render the GUI
	this->renderGUI();
	
	//render game over text if player dies
	if (this->player->getHp() <= 0.f)
	{
		window->draw(gameOverText);
	}

	//render the window
	this->window->display();
}

//render the world
void Game::renderWorld()
{
	this->window->draw(worldBackground);
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
		sf::Vector2f initialPosition(window->getSize().x / 2.f, 0);
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
		sf::Vector2f initialPosition(window->getSize().x * 0.5f, 0);
		spawnEnemyOne(initialPosition, numEnemies);
	}
	if (elapsed.asSeconds() >= 3.f && numEnemies == 1)
	{
		numEnemies++;
		sf::Vector2f initialPosition(window->getSize().x * 0.5f, 0);
		spawnEnemyOne(initialPosition, numEnemies);
	}
	if (elapsed.asSeconds() >= 4.f && numEnemies == 2)
	{
		numEnemies++;
		sf::Vector2f initialPosition(window->getSize().x * 0.5f, 0);
		spawnEnemyOne(initialPosition, numEnemies);
	}
	for (auto* e : enemies)
	{
		if (e->getType() == 0)
		{
			if (e->getPos().y < 100.f)
				e->move(0, 1);
			else 
				moveInRect(e);
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
		sf::Vector2f initialPosition(window->getSize().x * 0.5f, 0);
		spawnEnemyTwo(initialPosition, numEnemies);
	}

	if (elapsed.asSeconds() >= 3.f && numEnemies == 1)
	{
		numEnemies++;
		sf::Vector2f initialPosition(window->getSize().x * 0.5f, window->getSize().y);
		spawnEnemyOne(initialPosition, numEnemies);
	}

	if (elapsed.asSeconds() >= 4.f && numEnemies == 2)
	{
		numEnemies++;
		sf::Vector2f initialPosition(window->getSize().x * 0.5f, window->getSize().y);
		spawnEnemyOne(initialPosition, numEnemies);
	}

	if (elapsed.asSeconds() >= 5.f && numEnemies == 3)
	{
		numEnemies++;
		sf::Vector2f initialPosition(window->getSize().x * 0.5f, window->getSize().y);
		spawnEnemyOne(initialPosition, numEnemies);
	}
	for (auto *e : enemies)
	{
		if (e->getType() == 0)
		{
			if (e->getPos().y > this->window->getSize().y - 100.f)
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
	sf::Vector2f radius(window->getSize().x - 100.f, window->getSize().y - 100.f);
	sf::Time elapsed = clock.getElapsedTime();
	if (elapsed.asSeconds() >= 2.f && numEnemies == 0)
	{
		//spawn two enemies from the top
		numEnemies++;
		sf::Vector2f initialPosition(window->getSize().x * 0.33f, window->getSize().y);
		spawnEnemyTwo(initialPosition, numEnemies);

		numEnemies++;
		initialPosition = sf::Vector2f(window->getSize().x * 0.66f, window->getSize().y);
		spawnEnemyTwo(initialPosition, numEnemies);
	}

	if (elapsed.asSeconds() >= 3.f && numEnemies == 2)
	{
		//spawn from top
		numEnemies++;
		sf::Vector2f initialPosition(window->getSize().x * 0.5f, 0);
		spawnBounceEnemyOne(initialPosition, numEnemies);
	}

	if (elapsed.asSeconds() >= 4.f && numEnemies == 3)
	{
		//spawn from top
		numEnemies++;
		sf::Vector2f initialPosition(window->getSize().x * 0.5f, 0);
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
		sf::Vector2f initialPosition(window->getSize().x * 0.33f, 0);
		spawnEnemyTwo(initialPosition, numEnemies);

		numEnemies++;
		initialPosition = sf::Vector2f(window->getSize().x * 0.66f, 0);
		spawnEnemyTwo(initialPosition, numEnemies);
	}
	//spawn bullet bounce enemy
	if (elapsed.asSeconds() >= 3.f && numEnemies == 2)
	{
		numEnemies++;
		sf::Vector2f initialPosition(window->getSize().x * 0.5f, 0);
		spawnBounceEnemyOne(initialPosition, numEnemies);
	}
	//spawn sniper enemy and normal enemy
	if (elapsed.asSeconds() >= 4.f && numEnemies == 3)
	{
		numEnemies++;
		sf::Vector2f initialPosition(window->getSize().x * 0.5f, window->getSize().y + 50.f);
		spawnEnemyThree(initialPosition, numEnemies);

		numEnemies++;
		initialPosition = sf::Vector2f(window->getSize().x * 0.5f, 0);
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
		sf::Vector2f initialPosition(window->getSize().x * 0.5f, 0);
		spawnEnemyOne(initialPosition, numEnemies);
	}

	//spawn basic enemy two
	if (elapsed.asSeconds() >= 3.f && numEnemies == 1)
	{
		numEnemies++;
		sf::Vector2f initialPosition(window->getSize().x * 0.5f, 0);
		spawnEnemyOne(initialPosition, numEnemies);
	}

	//spawn shot gun enemy and circle shot
	if (elapsed.asSeconds() >= 3.5f && numEnemies == 2)
	{
		numEnemies++;
		sf::Vector2f initialPosition(window->getSize().x * 0.33f, window->getSize().y);
		spawnEnemyTwo(initialPosition, numEnemies);

		numEnemies++;
		initialPosition = sf::Vector2f(window->getSize().x * 0.66f, window->getSize().y);
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
		sf::Vector2f initialPosition(window->getSize().x * 0.33f, 50.f);
		spawnEnemyThree(initialPosition, numEnemies);

		numEnemies++;
		initialPosition = sf::Vector2f(window->getSize().x * 0.66f, 0);
		spawnBounceEnemyOne(initialPosition, numEnemies);
	}

	//spawn circle shot enemy
	if (elapsed.asSeconds() >= 3.f && numEnemies == 2)
	{
		//spawn sniper enemies from the two bottom corners of the map
		numEnemies++;
		sf::Vector2f initialPosition(window->getSize().x, window->getSize().y * 0.5f);
		spawnCircleEnemyTwo(initialPosition, numEnemies);
	}

	//spawn spray enemy
	if (elapsed.asSeconds() >= 4.f && numEnemies == 3)
	{
		numEnemies++;
		sf::Vector2f initialPosition(window->getSize().x * 0.5f, 0);
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
				else if (enemy->getPos().x > window->getSize().x - 50.f)
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
		sf::Vector2f initialPosition(window->getSize().x * 0.33f, 0);
		spawnEnemyTwo(initialPosition, numEnemies);

		numEnemies++;
		initialPosition = sf::Vector2f(window->getSize().x * 0.66f, 0);
		spawnEnemyTwo(initialPosition, numEnemies);
	}

	//spawn basic enemy from bottom
	if (elapsed.asSeconds() >= 3.f && numEnemies == 2)
	{
		numEnemies++;
		sf::Vector2f initialPosition(window->getSize().x * 0.5f, window->getSize().y);
		spawnEnemyOne(initialPosition, numEnemies);
	}

	//spawn circle shot enemy from bottom
	if (elapsed.asSeconds() >= 4.f && numEnemies == 3)
	{
		numEnemies++;
		sf::Vector2f initialPosition(window->getSize().x * 0.5f, window->getSize().y);
		spawnCircleEnemyTwo(initialPosition, numEnemies);
	}

	//spawn burst enemy at top middle
	if (elapsed.asSeconds() >= 5.f && numEnemies == 4)
	{
		numEnemies++;
		sf::Vector2f initialPosition(window->getSize().x * 0.5f, 50.f);
		spawnBurstEnemyThree(initialPosition, numEnemies);
	}

	for (auto* enemy : enemies)
	{
		//move basic enemy in rect
		if (enemy->getType() == 0)
		{
			if (enemy->getPos().y > window->getSize().y - 100.f)
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
		sf::Vector2f initialPosition(window->getSize().x * 0.5f, 0);
		spawnEnemyOne(initialPosition, numEnemies);
	}

	if (elapsed.asSeconds() >= 3.f && numEnemies == 1)
	{
		numEnemies++;
		sf::Vector2f initialPosition(window->getSize().x * 0.5f, 0);
		spawnEnemyOne(initialPosition, numEnemies);
	}

	//spawn two bullet bounce enemies circling too
	//spawn spray and circle enemy from sides
	if (elapsed.asSeconds() >= 4.f && numEnemies == 2)
	{
		numEnemies++;
		sf::Vector2f initialPosition(window->getSize().x * 0.5f, 0);
		spawnBounceEnemyOne(initialPosition, numEnemies);

		numEnemies++;
		initialPosition = sf::Vector2f(0, window->getSize().y * 0.5f);
		spawnCircleEnemyTwo(initialPosition, numEnemies);

		numEnemies++;
		initialPosition = sf::Vector2f(window->getSize().x, window->getSize().y * 0.5f);
		spawnEnemyFour(initialPosition, numEnemies);
	}

	if (elapsed.asSeconds() >= 5.f && numEnemies == 5)
	{
		numEnemies++;
		sf::Vector2f initialPosition(window->getSize().x * 0.5f, 0);
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
		sf::Vector2f initialPosition(window->getSize().x * 0.33f, 0);
		spawnEnemyFour(initialPosition, numEnemies);

		numEnemies++;
		initialPosition = sf::Vector2f(window->getSize().x * 0.66f, 0);
		spawnEnemyFour(initialPosition, numEnemies);
	}

	//spawn burst and circle shot enemy
	if (elapsed.asSeconds() >= 3.f && numEnemies == 2)
	{
		numEnemies++;
		sf::Vector2f initialPosition(window->getSize().x * 0.5f, 50.f);
		spawnBurstEnemyThree(initialPosition, numEnemies);

		numEnemies++;
		initialPosition = sf::Vector2f(window->getSize().x * 0.5f, window->getSize().y);
		spawnCircleEnemyTwo(initialPosition, numEnemies);
	}

	//wait 5 seconds to spawn two shot gun enemies
	if (elapsed.asSeconds() >= 10.f && numEnemies == 4)
	{
		numEnemies++;
		sf::Vector2f initialPosition(window->getSize().x * 0.33f, window->getSize().y);
		spawnEnemyTwo(initialPosition, numEnemies);

		numEnemies++;
		initialPosition = sf::Vector2f(window->getSize().x * 0.66f, window->getSize().y);
		spawnEnemyTwo(initialPosition, numEnemies);
	}

	//spawn two bullet bounce enemies circling 
	if (elapsed.asSeconds() >= 11.f && numEnemies == 6)
	{
		numEnemies++;
		sf::Vector2f initialPosition(window->getSize().x * 0.33f, 0);
		spawnBounceEnemyOne(initialPosition, numEnemies);

		numEnemies++;
		initialPosition = sf::Vector2f(window->getSize().x * 0.66f, 0);
		spawnBounceEnemyOne(initialPosition, numEnemies);
	}

	//spawn circle shot enemy
	if (elapsed.asSeconds() >= 12.f && numEnemies == 8)
	{
		numEnemies++;
		sf::Vector2f initialPosition(window->getSize().x, window->getSize().y * 0.5f);
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
		sf::Vector2f initialPosition(window->getSize().x * 0.5f, 0);
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
			if (enemy->getPos().y < 100.f)
				enemy->move(0, 1);
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
	sf::Vector2f radius(window->getSize().x - 100.f, window->getSize().y - 100.f);
	//move right
	if (enemy->getPos().x < radius.x && enemy->getPos().y <= 100.f)
		enemy->move(1, 0);
	//move down
	if (enemy->getPos().x >= radius.x && enemy->getPos().y < radius.y)
		enemy->move(0, 1);
	//move left
	if (enemy->getPos().x > 100.f && enemy->getPos().y >= radius.y)
		enemy->move(-1, 0);
	//move up
	if (enemy->getPos().x <= 100.f && enemy->getPos().y > 100.f)
		enemy->move(0, -1);
}

void Game::spawnEnemyOne(sf::Vector2f initialPosition, unsigned posInWave)
{
	int type = 0;
	float hp = 15.f;
	float damage = 1.f;
	float fireRate = 30.f;
	float movementSpeed = 1.f;
	sf::FloatRect newHitbox(8, 8, 16, 16);
	this->enemies.push_back(new Enemy(*this->textures["enemyOne"], type, hp, damage, fireRate, movementSpeed, newHitbox, initialPosition, posInWave));
}

void Game::spawnBounceEnemyOne(sf::Vector2f initialPosition, unsigned posInWave)
{
	sf::FloatRect newHitbox(8, 8, 16, 16);

	int type = 10;
	float hp = 20.f;
	float damage = 1.f;
	float fireRate = 50.f;
	float movementSpeed = 1.f;
	this->enemies.push_back(new Enemy(*this->textures["bounceEnemyOne"], type, hp, damage, fireRate, movementSpeed, newHitbox, initialPosition, posInWave));
}

void Game::spawnEnemyTwo(sf::Vector2f initialPosition, unsigned posInWave)
{
	sf::FloatRect newHitbox(8, 8, 16, 16);

	float hp = 20.f;
	float damage = 1.f;
	float fireRate = 50.f;
	float movementSpeed = 0.8f;
	int type = 1;
	this->enemies.push_back(new Enemy(*this->textures["enemyTwo"], type, hp, damage, fireRate, movementSpeed, newHitbox, initialPosition, posInWave));
}

void Game::spawnCircleEnemyTwo(sf::Vector2f initialPosition, unsigned posInWave)
{
	sf::FloatRect newHitbox(8, 8, 16, 16);

	float hp = 30.f;
	float damage = 1.f;
	float fireRate = 75.f;
	float movementSpeed = 0.8f;
	int type = 11;
	this->enemies.push_back(new Enemy(*this->textures["circleEnemyTwo"], type, hp, damage, fireRate, movementSpeed, newHitbox, initialPosition, posInWave));
}

void Game::spawnEnemyThree(sf::Vector2f initialPosition, unsigned posInWave)
{
	sf::FloatRect newHitbox(11, 6, 10, 24);
	float hp = 17.f;
	float damage = 1.f;
	float fireRate = 100.f;
	float movementSpeed = 1.0f;
	int type = 2;
	this->enemies.push_back(new Enemy(*this->textures["enemyThree"], type, hp, damage, fireRate, movementSpeed, newHitbox, initialPosition, posInWave));
}

void Game::spawnBurstEnemyThree(sf::Vector2f initialPosition, unsigned posInWave)
{
	sf::FloatRect newHitbox(11, 6, 10, 24);
	float hp = 20.f;
	float damage = 1.f;
	float fireRate = 80.f;
	float movementSpeed = 1.0f;
	int type = 12;
	this->enemies.push_back(new Enemy(*this->textures["burstEnemyThree"], type, hp, damage, fireRate, movementSpeed, newHitbox, initialPosition, posInWave));
}

void Game::spawnEnemyFour(sf::Vector2f initialPosition, unsigned posInWave)
{
	sf::FloatRect newHitbox(6, 6, 20, 20);
	float hp = 30.f;
	float damage = 1.f;
	float fireRate = 10.f;
	float movementSpeed = 0.4f;
	int type = 3;
	this->enemies.push_back(new Enemy(*this->textures["enemyFour"], type, hp, damage, fireRate, movementSpeed, newHitbox, initialPosition, posInWave));
}

void Game::spawnBoss(sf::Vector2f initialPosition, unsigned posInWave)
{
	sf::FloatRect newHitbox(13, 13, 38, 38);
	float hp = 200.f;
	float damage = 1.f;
	float fireRate = 100.f;
	float movementSpeed = 0.7f;
	int type = 100;
	this->enemies.push_back(new Enemy(*this->textures["bossEnemy"], type, hp, damage, fireRate, movementSpeed, newHitbox, initialPosition, posInWave));
}

void Game::spawnRandomEnemy()
{
	sf::Vector2f initialPosition;
	numEnemies++;
	//get a random number from 0-99
	int spawnRandEnemy = rand() % 100;
	//30% chance to spawn enemy one
	if (spawnRandEnemy < 30)
	{
		initialPosition = sf::Vector2f(window->getSize().x * 0.5f, window->getSize().y);
		spawnEnemyOne(initialPosition, numEnemies);
	}
	//20% chance to spawn enemy two
	else if (spawnRandEnemy < 50)
	{
		initialPosition = sf::Vector2f(window->getSize().x * 0.5f, window->getSize().y);
		spawnEnemyTwo(initialPosition, numEnemies);
	}
	//15% chance to spawn enemy three
	else if (spawnRandEnemy < 65)
	{
		initialPosition = sf::Vector2f(window->getSize().x * 0.5f, window->getSize().y - 50.f);
		spawnEnemyThree(initialPosition, numEnemies);
	}
	//15% chance to spawn bounce enemy one
	else if (spawnRandEnemy < 75)
	{
		initialPosition = sf::Vector2f(window->getSize().x * 0.5f, window->getSize().y);
		spawnBounceEnemyOne(initialPosition, numEnemies);
	}
	//10% chance to spawn enemy four
	else if (spawnRandEnemy < 84)
	{
		initialPosition = sf::Vector2f(window->getSize().x * 0.5f, window->getSize().y);
		spawnEnemyFour(initialPosition, numEnemies);
	}
	//8% chance to spawn burst enemy
	else if (spawnRandEnemy < 93)
	{
		initialPosition = sf::Vector2f(window->getSize().x * 0.5f, window->getSize().y);
		spawnBurstEnemyThree(initialPosition, numEnemies);
	}
	//7% chance to spawn circle enemy
	else if (spawnRandEnemy < 100)
	{
		initialPosition = sf::Vector2f(window->getSize().x * 0.5f, window->getSize().y);
		spawnCircleEnemyTwo(initialPosition, numEnemies);
	}
}

void Game::enemyOneFirePattern()
{
	//set the bullet hitbox
	sf::FloatRect bulletHitbox(1, 1, 6, 6);

	//shoot enemy bullet
	this->enemyBullets.push_back(new Bullet(*this->textures["enemyBullet"], 10, bulletHitbox, enemyPos, enemyAngle, enemyAimDir, 3.f));
}

void Game::bounceEnemyOneFirePattern()
{
	sf::FloatRect bulletHitbox(1, 1, 6, 6);
	sf::Texture* bulletTexture = this->textures["bouncingEnemyBullet"];
	int bulletType = 13;

	this->enemyBullets.push_back(new Bullet(*bulletTexture, bulletType, bulletHitbox, enemyPos, enemyAngle, enemyAimDir, 3.f));
}

void Game::enemyTwoFirePattern()
{
	sf::FloatRect bulletHitbox(1, 1, 6, 6);
	sf::Texture* bulletTexture = this->textures["enemyBullet"];
	int bulletType = 10;

	fireSpread(bulletTexture, bulletHitbox, bulletType, 5.f, pi / 20.f);
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
	this->enemyBullets.push_back(new Bullet(*this->textures["longEnemyBullet"], 11, bulletHitbox, enemyPos, enemyAngle, enemyAimDir, 10.f));
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
	int randTime = time(0) + enemy->getBulletCounter();
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
		enemy->setFireRate(6.4f);
	else
		enemy->setFireRate(8.f);
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
	this->enemyBullets.push_back(new Bullet(*this->textures["enemyBullet"], bulletType, bulletHitbox, enemyPos, enemyAngle, enemyAimDir, bulletSpeed));

	newEnemyAimDir = sf::Vector2f(
		enemyAimDir.x * (cos(spreadDegree)) - enemyAimDir.y * (sin(spreadDegree)),
		enemyAimDir.y * (cos(spreadDegree)) + enemyAimDir.x * (sin(spreadDegree))
	);
	this->enemyBullets.push_back(new Bullet(*this->textures["enemyBullet"], bulletType, bulletHitbox, enemyPos, enemyAngle, newEnemyAimDir, bulletSpeed));

	newEnemyAimDir = sf::Vector2f(
		enemyAimDir.x * (cos(spreadDegree)) + enemyAimDir.y * (sin(spreadDegree)),
		enemyAimDir.y * (cos(spreadDegree)) - enemyAimDir.x * (sin(spreadDegree))
	);
	this->enemyBullets.push_back(new Bullet(*this->textures["enemyBullet"], bulletType, bulletHitbox, enemyPos, enemyAngle, newEnemyAimDir, bulletSpeed));
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

	this->enemyBullets.push_back(new Bullet(*bulletTexture, bulletType, bulletHitbox, enemyPos, enemyAngle, enemyAimDir, 3.f));
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
		enemyBullets.push_back(new Bullet(*bulletTexture, bulletType, bulletHitbox, centerPos, enemyAngle, aimDir, 3.f));
		degree += 30.f;
	}
}

//fire bullets as a cluster
void Game::fireClusterShot(sf::Texture* bulletTexture, sf::FloatRect bulletHitbox, int bulletType)
{
	enemyBullets.push_back(new Bullet(*bulletTexture, bulletType, bulletHitbox, enemyPos, enemyAngle, enemyAimDir, 3.f));

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
	Clock clock2;
	float dt = 0.f;

	while (running())
	{
		this->updatePollEvents();

		dt = clock2.restart().asSeconds();

		if (player->getHp() > 0.f)
			update(dt);
		else
			gameOver = true;
		render();
	}
}

void Game::upgradesUpdate(const float& dt)
{
	bool upgradeRemoved = false;
	bool hasUpgrade = false;

	for (size_t i = 0; i < this->upgrades.size() && !upgradeRemoved; i++)
	{
		this->upgrades[i]->Update(dt);


		if (this->upgrades[i]->canDelete())
		{
			upgradeRemoved = true;
		}

		if (upgradeRemoved)
			this->upgrades.erase(this->upgrades.begin() + i);
	}
}

void Game::gunUpdate(const float& dt)
{
	this->player->gunUpgradeTimer(dt);
}

bool Game::gunStatus() {

	if (this->player->deleteGun())
	{
		return false;
	}
	//std::cout << "Testing func" << std::endl;
	return true;

}

void Game::fireRTUpdate(const float& dt)
{
	this->player->fireRTTimer(dt);
}

bool Game::fireRTStatus() {

	if (this->player->deleteRT())
	{
		return false;
	}
	//std::cout << "Testing func" << std::endl;
	return true;

}