#ifndef SCORE_H
#define SCORE_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <sstream>
#include <cstdlib>
#include <iomanip>

class Score
{
private:
	unsigned int points;
public:
	Score() = default;
	Score(unsigned int p)
	 : points(p){}
	bool operator<(const Score& obj) const { return points < obj.points; }
	friend std::ostream& operator<<(std::ostream& out, const Score& obj) {
		out << obj.points << std::endl;
		return out;
	}
};

#endif