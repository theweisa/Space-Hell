//create a txt file named "scoretest.txt"

/*
In game.h file
add printScores function in function part
*/
  //functions
  void printScores(unsigned int p);

/*
In game.cpp file
add scoreText
*/ 
addText("scoreText", static_cast<unsigned>(30.f * scale), sf::Color::White, "", sf::Vector2f(0.f, 0.f));
  texts["scoreText"]->setPosition(sf::Vector2f((windowWidth - texts["scoreText"]->getGlobalBounds().width) * 0.35f,
    (windowHeight - texts["scoreText"]->getGlobalBounds().height) * 0.45f));

/*
In game.cpp file
add printScores definition
*/ 
void Game::printScores(unsigned int p) 
{
  //read score file to score array
  const std::string highScoreFileName = "scoretest.txt";
  std::string buffer;
  std::ifstream fin(highScoreFileName);
  if (!fin)
  {
    std::cerr << "Can't find " << highScoreFileName << std::endl;
    exit(1);
  }

  unsigned int scores[5] = {};
  for (int i = 0; i < 5; i++)
  {
    if (fin >> buffer)
      scores[i] = stoi(buffer);
  }
  fin.close();
  
  //update score array
  for (int i = 0; i < 5; i++)
  {
    if (points > scores[i])
    {
      unsigned int temp = scores[i];
      scores[i] = points;
      points = temp;
    }
  }

  //print and wirte the new score array to file 
  std::stringstream ss;
  std::cout << "endof read file" << std::endl;
  ss << "High Scores" << "\n";

  std::ofstream fout(highScoreFileName);
  if (!fout)
  {
    std::cerr << "Can't find " << highScoreFileName << std::endl;
    exit(2);
  }

  for (int i = 0; i < 5; i++)
  {
    fout << scores[i] << ' ';
    ss << "  " << i + 1 << ":  " << scores[i] << "\n";
  }
  fout.close();
  texts["scoreText"]->setString(ss.str());
}

/*
In game.cpp file
call printScores after gameOver = true

the only problem here is 
the console window will print "endof read file" forever
I don't know how to make it stop...
*/
void Game::run()
{
  while (running())
  {
    this->updateDeltaTime();
    this->updatePollEvents();
    this->updatePause();
    if (player->getHp() > 0.f && !pause)
      update();
    else {
      gameOver = true;
      printScores(points);
    }
    render();
  }
}


