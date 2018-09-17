#pragma once
#include <SFML/Graphics.hpp>
#include <SFML\Window.hpp>

#include "Node.h"
#include "Snake.h"
#include "Food.h"

#include <numeric>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <random>


enum class GameStates : unsigned int
{
	GAME_ERROR,
	RUN,
	GAME_OVER,
	MAIN_MENU,
	EXIT,
};

class Game
{
private:

	struct GameArea
	{
		sf::Vector2i peak1;
		sf::Vector2i peak2;
	}_gameArea;

	sf::RenderWindow* _window;
	sf::Event _event;
	std::vector<Food> _foodVec;
	
	int _foodAmount = 4;
	int _points = 0;
	int _record = 0;

	void snakeKeyCommand(Snake &snake);
	bool detectFoodCollision(const Snake &snake , const Food &food);
	bool detectWallCollision(const Snake &snake , GameArea &gameArea);
	bool detectSnakeCollision(const Snake &snake);
	void createRandomfood(const Snake &snake, std::vector<Food> &foodVec , const GameArea &gameArea);
	int  getRandomNumber(int r1 , int r2);
	int loadNumberFromFile(std::string fileName);
	int saveNumberFromFile(std::string fileName, int number);

	GameStates runGameWindow();
	GameStates gameOverWindow();
	GameStates mainMenuWindow();

public:
	Game();
	~Game();

	void run();


};

