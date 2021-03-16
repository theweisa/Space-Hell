#include "highScores.h"

//constructor: read file and get score array
HighScores::HighScores()
{
	std::string buffer;
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

//update the score array with new score and write to file
void HighScores::updateHighScore(Score& s) 
{
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
		fout << scores[i] << ' ';
	fout.close();
}

//overloaded insertion operator
std::ostream& operator<<(std::ostream& out, HighScores h) 
{
	out << "High Scores" << std::endl;
	for (auto i = 0; i < 5; i++)
		out << " " << i+1 << "  " << h.scores[i];
	return out;
}
