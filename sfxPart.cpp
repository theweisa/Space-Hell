// Codes for sfx

// For game.h
// In resources section
sf::Music normalBGM;
sf::Music bossBGM;
std::map<std::string, sf::SoundBuffer*> soundBuffers;
std::map<std::string, sf::Sound*> sounds;

// In private functions section
void initAudio();
void addSound(const std::string key, const std::string fileName);


// For game.cpp
// In constructor
this->initAudio();

// In destructor
//delete sounds
for (auto& s : this->sounds)
{
    delete s.second;
}

// Line 192-249
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

// Line 251-259
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

// In updatePlayer: Line 435-436
//play sound when player shoots
this->sounds["playerBullet"]->play();

// In updateEnemyCollision: Line 775-780
//play sound when enemy takes damage
if (enemy->getHp() > 0.f)
    this->sounds["enemyHit"]->play();
//play sound when enemy is destroyed
else if (enemy->getHp() <= 0.f)
    this->sounds["explosion"]->play();

// In updatePlayerCollision: Line 850-866 AND 884-900
//play sound when player takes damage
if (this->player->getHp() > 0.f)
{
    this->sounds["playerHit"]->play();
    
    //play emergency sound when player's HP gets 1 or less
    if (player->getHp() <= 1.f)
        this->sounds["emergency"]->play();
}
//play sound when player is destroyed = game over
else if (this->player->getHp() <= 0.f)
{
    //stop emergency sound first if it's playing
    if (this->sounds["emergency"]->getStatus() == sf::Sound::Playing)
        this->sounds["emergency"]->stop();
    this->sounds["gameover"]->play();
}

// In updateUpgradeCollision: Line 985-986
//play sound when player picks up an item
this->sounds["itemPickUp"]->play();

// In spawnRandomEnemy: Line 2113-2114
//play spund when enemy is spawned
this->sounds["enemySpawn"]->play();

// In enemyOneFirePattern: Line 2125-2126
// In bounceEnemyOneFirePattern: Line 2138-2139
// In enemyTwoFirePattern: Line 2152-2153
// In circleEnemyTwoFirePattern: Line 2165-2166
// In enemyThreeFirePattern: Line 2174-2175
// In burstEnemyThreeFirePattern: Line 2187-2188
// In enemyFourFirePattern: Line 2208-2209
// In bossPatternOne: Line 2291-2292
// In bossPatternTwo: Line 2310-2311
// In bossPatternThree: Line 2330-2331
// In bossPatternFour: Line 2350-2351
// In burstClusterShot: Line 2497-2498
//play sound when enemy shoots
this->sounds["enemyBullet"]->play();

// In enemyThreeFirePattern: Line 2174-2175
//play sound when enemy shoots
this->sounds["longEnemyBullet"]->play();

//In run: Line: 2553-2554
//start playing background music
this->normalBGM.play();

// In run: Line 2561-2578
if (currentWave == 11)
{
    //stop playing the normal background music if it's playing
    if (normalBGM.getStatus() == sf::Music::Playing)
        this->normalBGM.stop();
    //play the boss background music if it's not playing
    if (bossBGM.getStatus() != sf::Music::Playing)
        this->bossBGM.play();
}
else
{
    //stop playing the boss background music if it's playing
    if (bossBGM.getStatus() == sf::Music::Playing)
        this->bossBGM.stop();
    //play the normal background music if it's not playing
    if (normalBGM.getStatus() != sf::Music::Playing)
        this->normalBGM.play();
}

// In run: Line: 2586-2590
//stop playing background music
if (normalBGM.getStatus() == sf::Music::Playing)
    this->normalBGM.stop();
if (bossBGM.getStatus() == sf::Music::Playing)
    this->bossBGM.stop();

// In dropPowerUp: Line 2701-2702
//play sound when enemy drops an item
this->sounds["itemDrop"]->play();
