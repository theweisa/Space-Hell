#ifndef HIGHSCORES_H
#define HIGHSCORES_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "score.h"

//want to make a high score class where the points are saved into a file along with the user name.
//the user will also enter their name next to their score

class HighScores
{
private:
	Score scores[5];
	const std::string highScoreFileName = "Scores/highScores.txt";
public:
	HighScores()
	{
		std::string buffer;

		if (!checkIfFileExists())
		{
			std::ofstream fout(highScoreFileName);
			for (int i = 0; i < 5; i++)
			{
				fout << 0 << '\n';
			}
		}

		std::ifstream fin(highScoreFileName);
		if (!fin)
		{
			std::cerr << "Can't find " << highScoreFileName << std::endl;
			exit(1);
		}

		for (int i = 0; i < 5; i++)
		{
			if (std::getline(fin, buffer))
			{
				Score temp(stoi(buffer));
				scores[i] = temp;
			}
		}
		fin.close();
	}
	void updateHighScore(Score& s) {
		for (int i = 0; i < 5; i++)
		{
			if (scores[i] < s)
			{
				Score temp = scores[i];
				scores[i] = s;
				s = temp;
			}
		}

		std::ofstream fout(highScoreFileName);
		if (!fout)
		{
			std::cerr << "Can't find " << highScoreFileName << std::endl;
			exit(2);
		}
		for (int i = 0; i < 5; i++)
			fout << scores[i];
		fout.close();
	}

	//use of overload insertion operator
	friend std::ostream& operator<<(std::ostream& out, HighScores h) {
		out << "High Scores" << std::endl;
		for (auto i = 0; i < 5; i++)
			out << i + 1 << ":  " << h.scores[i];
		return out;
	}
	bool checkIfFileExists()
	{
		std::ifstream fin(highScoreFileName);
		return (static_cast<bool>(fin));
	}
};

#endif 