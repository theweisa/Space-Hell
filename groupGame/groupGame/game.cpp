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
	for (auto& t : this->textures)
	{
		delete t.second;
	}

	//delete player bullets
	for (auto* b : this->playerBullets)
	{
		delete b;
	}

	//delete enemy bullets
	for (auto* b : this->enemyBullets)
	{
		delete b;
	}

	//delete enemies
	for (auto* e : this->enemies)
	{
		delete e;
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
	this->currentWave = 1;
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

	this->textures["spaceBackground"] = new sf::Texture();
	this->textures["spaceBackground"]->loadFromFile("Textures/space_background.jpg");

	this->textures["enemyTwo"] = new sf::Texture();
	this->textures["enemyTwo"]->loadFromFile("Textures/enemy2.png");

	this->textures["enemyThree"] = new sf::Texture();
	this->textures["enemyThree"]->loadFromFile("Textures/enemy3.png");

	this->textures["enemyFour"] = new sf::Texture();
	this->textures["enemyFour"]->loadFromFile("Textures/enemy4.png");

	this->textures["bossEnemy"] = new sf::Texture();
	this->textures["bossEnemy"]->loadFromFile("Textures/bossEnemy.png");

	this->textures["bigEnemyBullet"] = new sf::Texture();
	this->textures["bigEnemyBullet"]->loadFromFile("Textures/bigEnemyBullet.png");
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
}

/*
*****************************************update functions*****************************************
*/

//update the game 
void Game::update()
{
	this->updateView();
	//updates mouse events
	this->updateMousePos();

	//move player based on input
	this->updatePlayer();

	//update player
	this->player->update();

	//update world collision
	this->updateWorldCollision();

	//update enemies
	this->updateEnemies();

	this->updateBullets();

	this->updatePlayerCollision();

	this->updateEnemyCollision();

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
		this->playerBullets.push_back(new Bullet(*this->textures["playerBullet"], 0, playerBulletHitbox, playerPos, mouseAngle, playerAimDir, 10.f));
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
		bossWave();
		break;
	}

	//move the enemies and have them shoot
	for (auto* enemy : this->enemies)
	{
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
		enemyAimDir = enemyAimDir / sqrt(pow(enemyAimDir.x, 2) + pow(enemyAimDir.y, 2));

		//enemy 1 shoots
		if (enemy->getType() == 0)
		{
			if (enemy->canFire())
			{
				enemyOneFirePattern();
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

		//enemy 3 shoots
		else if (enemy->getType() == 2)
		{
			if (enemy->canFire())
			{
				enemyThreeFirePattern();
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

		else if (enemy->getType() == 10)
		{
			if (enemy->canFire())
			{
				bossFirePattern(enemy);
			}
		}

		//despawn the enemy if it goes outside the window
		/*if ((enemy->getPos().y < 0.f) || (enemy->getPos().y >= this->window->getSize().y) || (enemy->getPos().x < 0.f) || (enemy->getPos().x >= this->window->getSize().x))
		{
			std::cout << "Enemy despawned " << enemy->getType();
			//reset enemy 4's bulletCounter
			if (enemy->getType() == 3)
				bulletCounter = 0;
			delete enemy;
			this->enemies.erase(enemies.begin() + vectPos);
			vectPos--;
		}*/
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
				std::cout << "burst the bullet at pos " << (*itr)->getPos().x << ", " << (*itr)->getPos().y << std::endl;
				itr = enemyBullets.erase(itr);

			}
			else
				itr++;
		}


		else if (((*itr)->getPos().y < 0.f) || ((*itr)->getPos().y >= this->window->getSize().y) || ((*itr)->getPos().x < 0.f) || ((*itr)->getPos().x >= this->window->getSize().x))
		{
			itr = enemyBullets.erase(itr);
		}
		else
			itr++;
	}
	/*
	for (auto *b : this->enemyBullets)
	{
		//move the bullets
		b->update();

		//erase the bullets if out of bounds
		if ((b->getPos().y < 0.f) || (b->getPos().y >= this->window->getSize().y) || (b->getPos().x < 0.f) || (b->getPos().x >= this->window->getSize().x))
		{
			delete this->enemyBullets[vectPos];
			this->enemyBullets.erase(this->enemyBullets.begin() + vectPos);
			std::cout << "Erased bullet at position: " << vectPos << std::endl;
			--vectPos;
		}
		++vectPos;
	}*/
}

//check if character is at edge of world
void Game::updateWorldCollision()
{
	//Top world collision
	if (this->player->getPos().y < 0.f)
	{ 
		this->player->setPosition(this->player->getPos().x, 0.f); 
	}
	//bottom world collision
	if (this->player->getPos().y >= this->window->getSize().y)
	{
		this->player->setPosition(this->player->getPos().x, this->window->getSize().y);
	}
	//left world collision
	if (this->player->getPos().x < 0.f)
	{
		this->player->setPosition(0.f, this->player->getPos().y);
	}
	//right world collision
	if (this->player->getPos().x >= this->window->getSize().x)
	{
		this->player->setPosition(this->window->getSize().x, this->player->getPos().y);
	}
}

//update if hitbox collides with enemy
void Game::updateEnemyCollision()
{
	int unsigned enemyVectPos = 0;
	int unsigned bulletVectPos = 0;
	
	//check if each enemy has collided with a player bullet
	for (auto *e : this->enemies)
	{
		//checks if each bullet has collided with the enemy
		for (auto *b : this->playerBullets)
		{
			//bool that is if enemy hitbox intersects with player bullets
			enemyCollision = this->playerBullets[bulletVectPos]->getGlobalHitbox().intersects(this->enemies[enemyVectPos]->getGlobalHitbox());

			//if collision, enemy takes damage
			if (enemyCollision)
			{
				//enemy takes damage
				this->enemies[enemyVectPos]->takeDamage(player->getDamage());

				//gain points for hitting the enemy
				points += 10 * combo;

				//enemy is set to destroyed if hp bar is below 0
				if (enemies[enemyVectPos]->getHp() <= 0.f)
					enemyDestroyed = true;

				//delete the bullet after it hits the enemy
				delete this->playerBullets[bulletVectPos];
				this->playerBullets.erase(this->playerBullets.begin() + bulletVectPos);
				--bulletVectPos;
			}
			bulletVectPos++;
		}
		//enemy is deleted if it is destroyed
		if (enemyDestroyed)
		{
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

//spawn two basic enemies and have them move left and right
void Game::waveTwo()
{
	sf::Time elapsed = clock.getElapsedTime();
	if (elapsed.asSeconds() >= 2.f && numEnemies == 0)
	{
		numEnemies++;
		sf::Vector2f initialPosition(window->getSize().x * 0.33f, 0);
		spawnEnemyOne(initialPosition, numEnemies);

		numEnemies++;
		initialPosition = sf::Vector2f(window->getSize().x * 0.66f, 0);
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
	if (numEnemiesDestroyed == 2)
	{
		nextWave();
	}
}

//spawn three basic enemies to go around the player
void Game::waveThree()
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

//have a shot gun enemy spawn from the top and move towards the player as well as two basic enemies from the bottom
void Game::waveFour()
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

//have two shot gun enemies moving towards the player, and two basic enemies circling the map
void Game::waveFive()
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
		spawnEnemyOne(initialPosition, numEnemies);
	}

	if (elapsed.asSeconds() >= 4.f && numEnemies == 3)
	{
		//spawn from top
		numEnemies++;
		sf::Vector2f initialPosition(window->getSize().x * 0.5f, 0);
		spawnEnemyOne(initialPosition, numEnemies);
	}

	if (elapsed.asSeconds() >= 5.f && numEnemies == 4)
	{
		//spawn from top
		numEnemies++;
		sf::Vector2f initialPosition(window->getSize().x * 0.5f, 0);
		spawnEnemyOne(initialPosition, numEnemies);
	}

	for (auto *e : enemies)
	{
		if (e->getType() == 0)
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
	if (numEnemiesDestroyed >= 5)
	{	
		nextWave();
	}
}

//three shotgun enemies move towards the player with one sniper enemy in the back
void Game::waveSix()
{
	sf::Time elapsed = clock.getElapsedTime();
	if (elapsed.asSeconds() >= 2.f && numEnemies == 0)
	{
		numEnemies++;
		sf::Vector2f initialPosition(window->getSize().x * 0.5f, 0);
		spawnEnemyTwo(initialPosition, numEnemies);

		numEnemies++;
		initialPosition = sf::Vector2f(window->getSize().x * 0.5f, window->getSize().y);
		spawnEnemyThree(initialPosition, numEnemies);
	}
	if (elapsed.asSeconds() >= 3.f && numEnemies == 2)
	{
		numEnemies++;
		sf::Vector2f initialPosition(window->getSize().x * 0.5f, 0);
		spawnEnemyTwo(initialPosition, numEnemies);
	}
	if (elapsed.asSeconds() >= 4.f && numEnemies == 3)
	{
		numEnemies++;
		sf::Vector2f initialPosition(window->getSize().x * 0.5f, 0);
		spawnEnemyTwo(initialPosition, numEnemies);
	}

	for (auto *e : enemies)
	{
		if (e->getType() == 1)
		{
			e->move(e->getEnemyToPlayerDir().x, e->getEnemyToPlayerDir().y);
		}
		else if (e->getType() == 2)
		{
			if (e->getPos().y > window->getSize().y - 50.f)
			{
				e->move(0, -1);
			}
		}
	}

	if (numEnemiesDestroyed >= 4)
	{
		nextWave();
	}
}

//have two shot gun enemies moving towards the player, one sniper moving left and right, and three basic enemy circling the map
void Game::waveSeven()
{
	sf::Time elapsed = clock.getElapsedTime();
	if (elapsed.asSeconds() >= 2.f && numEnemies == 0)
	{
		numEnemies++;
		sf::Vector2f initialPosition(window->getSize().x * 0.33f, window->getSize().y);
		spawnEnemyTwo(initialPosition, numEnemies);

		numEnemies++;
		initialPosition = sf::Vector2f(window->getSize().x * 0.66f, window->getSize().y);
		spawnEnemyTwo(initialPosition, numEnemies);
	}

	if (elapsed.asSeconds() >= 3.f && numEnemies == 2)
	{
		numEnemies++;
		sf::Vector2f initialPosition(0, window->getSize().y * 0.5f);
		spawnEnemyThree(initialPosition, numEnemies);
	}

	if (elapsed.asSeconds() >= 3.5f && numEnemies == 3)
	{
		numEnemies++;
		sf::Vector2f initialPosition(window->getSize().x * 0.5f, 0);
		spawnEnemyOne(initialPosition, numEnemies);
	}
	if (elapsed.asSeconds() >= 4.5f && numEnemies == 4)
	{
		numEnemies++;
		sf::Vector2f initialPosition(window->getSize().x * 0.5f, 0);
		spawnEnemyOne(initialPosition, numEnemies);
	}
	if (elapsed.asSeconds() >= 5.5f && numEnemies == 5)
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
		else if (e->getType() == 1)
		{
			e->move(e->getEnemyToPlayerDir().x, e->getEnemyToPlayerDir().y);
		}
		else if (e->getType() == 2)
		{
			if (e->getPos().x < 100.f)
				e->move(1, 0);
			else
			{
				if (e->getPos().y < 100.f)
					moveUp = false;
				else if (e->getPos().y > window->getSize().y - 100.f)
					moveUp = true;
				if (moveUp)
					e->move(0, -1);
				else
					e->move(0, 1);
			}
		}
	}
	if (numEnemiesDestroyed >= 6)
	{
		nextWave();
	}
}

//have a spray enemy moving towards the player, two shotgun enemies moving towards the player, and two snipers in the back
void Game::waveEight()
{
	sf::Time elapsed = clock.getElapsedTime();
	if (elapsed.asSeconds() >= 2.f && numEnemies == 0)
	{
		//spawn shotgun enemy from the two veritcal sides of the screen
		numEnemies++;
		sf::Vector2f initialPosition(0, window->getSize().y * 0.5f);
		spawnEnemyTwo(initialPosition, numEnemies);

		numEnemies++;
		initialPosition = sf::Vector2f(window->getSize().x, window->getSize().y * 0.5f);
		spawnEnemyTwo(initialPosition, numEnemies);
	}

	if (elapsed.asSeconds() >= 3.f && numEnemies == 2)
	{
		//spawn sniper enemies from the two bottom corners of the map
		numEnemies++;
		sf::Vector2f initialPosition(window->getSize().x, window->getSize().y);
		spawnEnemyThree(initialPosition, numEnemies);

		numEnemies++;
		initialPosition = sf::Vector2f(0, window->getSize().y);
		spawnEnemyThree(initialPosition, numEnemies);
	}

	if (elapsed.asSeconds() >= 4.f && numEnemies == 4)
	{
		numEnemies++;
		sf::Vector2f initialPosition(window->getSize().x * 0.5f, 0);
		spawnEnemyFour(initialPosition, numEnemies);
	}
	for (auto* enemy : enemies)
	{
		if (enemy->getType() == 1)
		{
			enemy->move(enemy->getEnemyToPlayerDir().x, enemy->getEnemyToPlayerDir().y);
		}
		else if (enemy->getType() == 2)
		{
			if (enemy->getPosInWave() == 3)
			{
				if (enemy->getPos().x > window->getSize().x - 50.f && enemy->getPos().y > window->getSize().y - 50.f)
					enemy->move(-1, -1);
			}
			if (enemy->getPosInWave() == 4)
			{
				if (enemy->getPos().x < 50.f && enemy->getPos().y > window->getSize().y - 50.f)
					enemy->move(1, -1);
			}
		}
		else if (enemy->getType() == 3)
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
	}
	if (numEnemiesDestroyed >= 5)
	{
		nextWave();
	}
}

//have two enemy4s chasing the player around, 3 enemy1s circling the map, a sniper in the back, and a shotgun
void Game::waveNine()
{
	sf::Time elapsed = clock.getElapsedTime();
	if (elapsed.asSeconds() >= 2.f && numEnemies == 0)
	{
		numEnemies++;
		sf::Vector2f initialPosition(window->getSize().x * 0.5f, window->getSize().y);
		spawnEnemyOne(initialPosition, numEnemies);
	}

	if (elapsed.asSeconds() >= 2.5f && numEnemies == 1)
	{

		numEnemies++;
		sf::Vector2f initialPosition(window->getSize().x * 0.4f, 0);
		spawnEnemyFour(initialPosition, numEnemies);

		numEnemies++;
		initialPosition = sf::Vector2f(window->getSize().x * 0.6f, 0);
		spawnEnemyFour(initialPosition, numEnemies);
	}

	if (elapsed.asSeconds() >= 3.f && numEnemies == 3)
	{
		numEnemies++;
		sf::Vector2f initialPosition(window->getSize().x * 0.5f, window->getSize().y);
		spawnEnemyOne(initialPosition, numEnemies);
	}

	if (elapsed.asSeconds() >= 3.5f && numEnemies == 4)
	{
		numEnemies++;
		sf::Vector2f initialPosition(0, window->getSize().y * 0.5f);
		spawnEnemyTwo(initialPosition, numEnemies);

		numEnemies++;
		initialPosition = sf::Vector2f(window->getSize().x, window->getSize().y * 0.5f);
		spawnEnemyThree(initialPosition, numEnemies);
	}

	if (elapsed.asSeconds() >= 4.f && numEnemies == 6)
	{
		numEnemies++;
		sf::Vector2f initialPosition(window->getSize().x * 0.5f, window->getSize().y);
		spawnEnemyOne(initialPosition, numEnemies);
	}

	for (auto* enemy : enemies)
	{
		if (enemy->getType() == 0)
		{
			if (enemy->getPos().y > window->getSize().y - 100.f)
				enemy->move(0, -1);
			else
				moveInRect(enemy);
		}
		else if (enemy->getType() == 1)
		{
			enemy->move(enemy->getEnemyToPlayerDir().x, enemy->getEnemyToPlayerDir().y);
		}
		else if (enemy->getType() == 2)
		{
			if (enemy->getPos().x > window->getSize().x - 100.f)
				enemy->move(-1, 0);
			else
			{
				if (enemy->getPos().y < 100.f)
					moveUp = false;
				else if (enemy->getPos().y > window->getSize().y - 100.f)
					moveUp = true;
				if (moveUp)
					enemy->move(0, -1);
				else
					enemy->move(0, 1);
			}
		}
		else if (enemy->getType() == 3)
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
	}
	if (numEnemiesDestroyed >= 7)
		nextWave();
}

/*
BOSS WAVE
firing patterns:
	- big wave of bullets; covering the whole screen of like 10+ish bullets: 20%
	- multiple waves of bullets, each in slightly different angles: 20%
	- cluster of bullets that explode into all directions: 20%
	- machine gun shots targeting the player for some time: 20%
	- lasers!: 20%
has a % chance of performing these attacks;
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
	for (auto* enemy : enemies)
	{
		if (enemy->getType() == 10)
		{
			if (enemy->getPos().y < 100.f)
				enemy->move(0, 1);
		}
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
	float fireRate = 0.f;
	float movementSpeed = 0.7f;
	int type = 10;
	this->enemies.push_back(new Enemy(*this->textures["bossEnemy"], type, hp, damage, fireRate, movementSpeed, newHitbox, initialPosition, posInWave));
}

void Game::enemyOneFirePattern()
{
	//set the bullet hitbox
	sf::FloatRect  bulletHitbox(1, 1, 6, 6);

	//shoot enemy bullet
	this->enemyBullets.push_back(new Bullet(*this->textures["enemyBullet"], 10, bulletHitbox, enemyPos, enemyAngle, enemyAimDir, 3.f));
}

void Game::enemyTwoFirePattern()
{
	//sf::Vector2f initialEnemyAimDir(enemyAimDir);
	sf::Vector2f newEnemyAimDir;

	sf::FloatRect bulletHitbox(1, 1, 6, 6);
	this->enemyBullets.push_back(new Bullet(*this->textures["enemyBullet"], 10, bulletHitbox, enemyPos, enemyAngle, enemyAimDir, 3.f));

	newEnemyAimDir = sf::Vector2f(
		enemyAimDir.x * (cos(pi / 20.f)) - enemyAimDir.y * (sin(pi / 20.f)),
		enemyAimDir.y * (cos(pi / 20.f)) + enemyAimDir.x * (sin(pi / 20.f))
	);
	this->enemyBullets.push_back(new Bullet(*this->textures["enemyBullet"], 10, bulletHitbox, enemyPos, enemyAngle, newEnemyAimDir, 3.f));

	newEnemyAimDir = sf::Vector2f(
		enemyAimDir.x * (cos(pi / 20.f)) + enemyAimDir.y * (sin(pi / 20.f)),
		enemyAimDir.y * (cos(pi / 20.f)) - enemyAimDir.x * (sin(pi / 20.f))
	);
	this->enemyBullets.push_back(new Bullet(*this->textures["enemyBullet"], 10, bulletHitbox, enemyPos, enemyAngle, newEnemyAimDir, 3.f));
}

void Game::enemyThreeFirePattern()
{
	sf::FloatRect bulletHitbox(6, 0, 4, 16);
	this->enemyBullets.push_back(new Bullet(*this->textures["longEnemyBullet"], 11, bulletHitbox, enemyPos, enemyAngle, enemyAimDir, 10.f));
}

void Game::enemyFourFirePattern(Enemy* enemy)
{
	enemy->setFireRate(10.f);
	enemy->setBulletCounter(enemy->getBulletCounter() + 1);
	int bulletCounter = enemy->getBulletCounter();
	//on the first bullet, set the base direction to shoot at
	if (bulletCounter == 1)
	{
		baseEnemyAimDir = sf::Vector2f(enemyAimDir);
	}

	switch (bulletCounter)
	{
	case 1:
		enemyAimDir = sf::Vector2f(
			baseEnemyAimDir.x * (cos(pi / 5.f)) + baseEnemyAimDir.y * (sin(pi / 5.f)),
			baseEnemyAimDir.y * (cos(pi / 5.f)) - baseEnemyAimDir.x * (sin(pi / 5.f))
		);
		break;
	case 2:
		enemyAimDir = sf::Vector2f(
			baseEnemyAimDir.x * (cos(pi / 10.f)) + baseEnemyAimDir.y * (sin(pi / 10.f)),
			baseEnemyAimDir.y * (cos(pi / 10.f)) - baseEnemyAimDir.x * (sin(pi / 10.f))
		);
		break;
	case 3:
		enemyAimDir = sf::Vector2f(
			baseEnemyAimDir.x * (cos(pi / 20.f)) + baseEnemyAimDir.y * (sin(pi / 20.f)),
			baseEnemyAimDir.y * (cos(pi / 20.f)) - baseEnemyAimDir.x * (sin(pi / 20.f))
		);
		break;
	case 4:
		enemyAimDir = baseEnemyAimDir;
		break;
	case 5:
		enemyAimDir = sf::Vector2f(
			baseEnemyAimDir.x * (cos(pi / 20.f)) - baseEnemyAimDir.y * (sin(pi / 20.f)),
			baseEnemyAimDir.y * (cos(pi / 20.f)) + baseEnemyAimDir.x * (sin(pi / 20.f))
		);
		break;
	case 6:
		enemyAimDir = sf::Vector2f(
			baseEnemyAimDir.x * (cos(pi / 10.f)) - baseEnemyAimDir.y * (sin(pi / 10.f)),
			baseEnemyAimDir.y * (cos(pi / 10.f)) + baseEnemyAimDir.x * (sin(pi / 10.f))
		);
		break;
	case 7:
		enemyAimDir = sf::Vector2f(
			baseEnemyAimDir.x * (cos(pi / 5.f)) - baseEnemyAimDir.y * (sin(pi / 5.f)),
			baseEnemyAimDir.y * (cos(pi / 5.f)) + baseEnemyAimDir.x * (sin(pi / 5.f))
		);
		enemy->setBulletCounter(0);
		enemy->setFireRate(75.f);
		break;
	default:
		enemy->setBulletCounter(0);
	}

	sf::FloatRect  bulletHitbox(1, 1, 6, 6);
	this->enemyBullets.push_back(new Bullet(*this->textures["enemyBullet"], 10, bulletHitbox, enemyPos, enemyAngle, enemyAimDir, 3.f));
}

void Game::bossFirePattern(Enemy * enemy)
{
	enemy->setBulletCounter(enemy->getBulletCounter() + 1);
	bossPatternTwo(enemy);
	/*if (enemy->getBulletCounter() < 10)
		bossPatternOne(enemy);
	else
	{
		enemy->setFireRate(50.f);
		enemy->setBulletCounter(0);
	}*/
}
/*
	- big wave of bullets; covering the whole screen of like 10+ish bullets: 20%
	- multiple waves of bullets, each in slightly different angles: 20%
	- cluster of bullets that explode into all directions: 20%
	- machine gun shots targeting the player for some time: 20%
	- lasers!: 20%
*/

//big wave of bullets; covering the whole screen
void Game::bossPatternOne(Enemy* enemy)
{
	int randTime = time(0) + enemy->getBulletCounter();
	srand(randTime);
	float offset = static_cast<float>(rand() % 20);

	enemy->setFireRate(10.f);
	sf::FloatRect bulletHitbox(1, 1, 6, 6);
	sf::Texture* bulletTexture = this->textures["enemyBullet"];
	fireInCircle(bulletTexture, bulletHitbox, offset);
}

//cluster of bullets that explode into all directions : 20 %
void Game::bossPatternTwo(Enemy* enemy)
{
	enemy->setFireRate(50.f);
	fireClusterShot(enemy);
}

void Game::fireInCircle(sf::Texture* bulletTexture, sf::FloatRect bulletHitbox, float offset)
{
	float degree = offset;
	float radians;

	radians = degree * pi / 180.f; //180
	sf::Vector2f aimDir(cos(radians), sin(radians));
	enemyBullets.push_back(new Bullet(*bulletTexture, 10, bulletHitbox, enemyPos, enemyAngle, aimDir, 3.f));

	/*
	FIRES THE TOP SEMI CIRCLE
	*/
	degree += 30.f; //210
	radians = degree * pi / 180.f;
	aimDir = sf::Vector2f(cos(radians), sin(radians));
	enemyBullets.push_back(new Bullet(*bulletTexture, 10, bulletHitbox, enemyPos, enemyAngle, aimDir, 3.f));

	degree += 30.f; //240
	radians = degree * pi / 180.f;
	aimDir = sf::Vector2f(cos(radians), sin(radians));
	enemyBullets.push_back(new Bullet(*bulletTexture, 10, bulletHitbox, enemyPos, enemyAngle, aimDir, 3.f));

	degree += 30.f; //270
	radians = degree * pi / 180.f;
	aimDir = sf::Vector2f(cos(radians), sin(radians));
	enemyBullets.push_back(new Bullet(*bulletTexture, 10, bulletHitbox, enemyPos, enemyAngle, aimDir, 3.f));

	degree += 30.f; //300
	radians = degree * pi / 180.f;
	aimDir = sf::Vector2f(cos(radians), sin(radians));
	enemyBullets.push_back(new Bullet(*bulletTexture, 10, bulletHitbox, enemyPos, enemyAngle, aimDir, 3.f));

	degree += 30.f; //330
	radians = degree * pi / 180.f;
	aimDir = sf::Vector2f(cos(radians), sin(radians));
	enemyBullets.push_back(new Bullet(*bulletTexture, 10, bulletHitbox, enemyPos, enemyAngle, aimDir, 3.f));

	degree += 30.f; //360
	radians = degree * pi / 180.f;
	aimDir = sf::Vector2f(cos(radians), sin(radians));
	enemyBullets.push_back(new Bullet(*bulletTexture, 10, bulletHitbox, enemyPos, enemyAngle, aimDir, 3.f));

	/*
	FIRES THE BOTTOM SEMI CIRCLE
	*/
	degree += 30.f; //30
	radians = degree * pi / 180.f;
	aimDir = sf::Vector2f(cos(radians), sin(radians));
	enemyBullets.push_back(new Bullet(*bulletTexture, 10, bulletHitbox, enemyPos, enemyAngle, aimDir, 3.f));

	degree += 30.f; //60
	radians = degree * pi / 180.f;
	aimDir = sf::Vector2f(cos(radians), sin(radians));
	enemyBullets.push_back(new Bullet(*bulletTexture, 10, bulletHitbox, enemyPos, enemyAngle, aimDir, 3.f));

	degree += 30.f; //90
	radians = degree * pi / 180.f;
	aimDir = sf::Vector2f(cos(radians), sin(radians));
	enemyBullets.push_back(new Bullet(*bulletTexture, 10, bulletHitbox, enemyPos, enemyAngle, aimDir, 3.f));

	degree += 30.f; //120
	radians = degree * pi / 180.f;
	aimDir = sf::Vector2f(cos(radians), sin(radians));
	enemyBullets.push_back(new Bullet(*bulletTexture, 10, bulletHitbox, enemyPos, enemyAngle, aimDir, 3.f));

	degree += 30.f; //150
	radians = degree * pi / 180.f;
	aimDir = sf::Vector2f(cos(radians), sin(radians));
	enemyBullets.push_back(new Bullet(*bulletTexture, 10, bulletHitbox, enemyPos, enemyAngle, aimDir, 3.f));
}

void Game::fireClusterShot(Enemy* enemy)
{
	sf::FloatRect bulletHitbox(1, 1, 14, 14);
	enemyBullets.push_back(new Bullet(*this->textures["bigEnemyBullet"], 12, bulletHitbox, enemyPos, enemyAngle, enemyAimDir, 2.f));

	Bullet* bullet = enemyBullets.back();
	bullet->setBasePlayerPos(playerPos);
}

//runs the game
void Game::run()
{
	while (running())// && !game.endGame)
	{
		this->updatePollEvents();
		if (player->getHp() > 0.f)
			update();
		else
			gameOver = true;
		render();
	}
}