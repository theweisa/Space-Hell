#ifndef HIGHSCORES_H
#define HIGHSCORES_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "score.h"

class HighScores
{
private:
	Score scores[5];
	const std::string highScoreFileName = "scoretest.txt";
public:
	HighScores();
	void updateHighScore(Score& s);
	friend std::ostream& operator<<(std::ostream& out, HighScores h);
};

#endif