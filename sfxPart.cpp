// Codes for sfx

// ******************** update 1 ******************** //

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

// In updatePlayer
//play sound when player shoots
this->sounds["playerBullet"]->play();

// In updateEnemyCollision
//play sound when enemy takes damage
if (enemy->getHp() > 0.f)
    this->sounds["enemyHit"]->play();
//play sound when enemy is destroyed
else if (enemy->getHp() <= 0.f)
    this->sounds["explosion"]->play();

// In updatePlayerCollision
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

// In updateUpgradeCollision
//play sound when player picks up an item
this->sounds["itemPickUp"]->play();

// In spawnRandomEnemy
//play spund when enemy is spawned
this->sounds["enemySpawn"]->play();

// In enemyOneFirePattern
// In bounceEnemyOneFirePattern
// In enemyTwoFirePattern
// In circleEnemyTwoFirePattern
// In enemyThreeFirePattern
// In burstEnemyThreeFirePattern
// In enemyFourFirePattern
// In bossPatternOne
// In bossPatternTwo
// In bossPatternThree
// In bossPatternFour
// In burstClusterShot
//play sound when enemy shoots
this->sounds["enemyBullet"]->play();

// In enemyThreeFirePattern
//play sound when enemy shoots
this->sounds["longEnemyBullet"]->play();

//In run
//start playing background music
this->normalBGM.play();

// In run
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

// In run: Line
//stop playing background music
if (normalBGM.getStatus() == sf::Music::Playing)
    this->normalBGM.stop();
if (bossBGM.getStatus() == sf::Music::Playing)
    this->bossBGM.stop();

// In dropPowerUp
//play sound when enemy drops an item
this->sounds["itemDrop"]->play();

// ******************** update 2 ******************** //

// In initAudio: After addSound("longEnemyBullet", "Audio/longEnemyBullet.wav");
addSound("bigEnemyBullet", "Audio/bigEnemyBullet.wav");

// REPLACE this->sounds["enemyBullet"]->play();
// In burstEnemyThreeFirePattern and bossPatternTwo
//play sound when enemy shoots
this->sounds["bigEnemyBullet"]->play();

// ******************** update 3 ******************** //

// For game.h
#include "SliderSFML.h"

float musicVolume;
float soundVolume;
void setMusicVolume(float);
void setSoundVolume(float);

// For game.cpp

// In initAudio
musicVolume = 100;
soundVolume = 100;

// Somewhere in game.cpp (Update function?)
void Game::setMusicVolume(float value)
{
    musicVolume = value;
    normalBGM.setVolume(musicVolume);
    bossBGM.setVolume(musicVolume);
}

void Game::setSoundVolume(float value)
{
    soundVolume = value;
    for (auto &s : this->sounds)
    {
        s.second->setVolume(soundVolume);
    }
}

// Slider
// For initialization
SliderSFML musicSlider(x1, y1);
SliderSFML soundSlider(x2, y2);
// 0 -> Min volume / 100 -> Max volume
musicSlider.create(0, 100);
soundSlider.create(0, 100);

// For update
musicSlider.setSliderValue(musicVolume);
soundSlider.setSliderValue(soundVolume);
musicSlider.draw(*(this->window));
soundSlider.draw(*(this->window));
musicVolume = musicSlider.getSliderValue();
soundVolume = soundSlider.getSliderValue();
setMusicVolume(musicVolume);
setSoundVolume(soundVolume);
