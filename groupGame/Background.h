#ifndef BACKGROUND_H
#define BACKGROUND_H

class Background : public Entity
{
private:
	float deltaTime;
	std::string key;
public:
	Background() : deltaTime(), key() { };
	Background(sf::Texture* newTexture, sf::Vector2f newPos, float scale)
	{
		sprite.setTexture(*newTexture);
		sprite.setOrigin(320, 240);
		sprite.setScale(scale, scale);
		sprite.setPosition(newPos);

		key = "background";
		//1024x768
		//640 480
		animations[key] = new Animation(sprite, *newTexture, 5.f, 0, 0, 7, 0, 640, 480);
		deltaTime = 0;
	}

	void setTime(float & time)
	{
		deltaTime = time;
	}

	void update() override
	{
		animations[key]->play(deltaTime);
	}
};

#endif