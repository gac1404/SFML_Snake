#include "stdafx.h"
#include "Game.h"


void Game::snakeKeyCommand(Snake &snake)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		snake.setDirection(Direction::Left);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		snake.setDirection(Direction::Right);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		snake.setDirection(Direction::Down);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		snake.setDirection(Direction::Up);
	}

	
}

bool Game::detectFoodCollision(const Snake &snake , const Food &food)
{
	switch (snake.getHeadDirection())
	{
	case Direction::Right:
		if (snake.getHeadPossition().x >= food.getPosition().x &&
			snake.getHeadPossition().x <= food.getPosition().x + FoodSize &&
			snake.getHeadPossition().y == food.getPosition().y)
		{
			return true;
		}
		break;
	case Direction::Left:
		if (snake.getHeadPossition().x <= food.getPosition().x &&
			snake.getHeadPossition().x >= food.getPosition().x - FoodSize &&
			snake.getHeadPossition().y == food.getPosition().y)
		{
			return true;
		}
		break;
	case Direction::Up:
		if (snake.getHeadPossition().y <= food.getPosition().y &&
			snake.getHeadPossition().y >= food.getPosition().y &&
			snake.getHeadPossition().x == food.getPosition().x)
		{
			return true;
		}
		break;
	case Direction::Down:
		if (snake.getHeadPossition().y <= food.getPosition().y &&
			snake.getHeadPossition().y >= food.getPosition().y &&
			snake.getHeadPossition().x == food.getPosition().x)
		{
			return true;
		}
		break;
	default:
		break;
	}

	return false;
}

bool Game::detectWallCollision(const Snake & snake, GameArea & gameArea)
{
	if(snake.getHeadPossition().y < gameArea.peak1.y || 
	   snake.getHeadPossition().x < gameArea.peak1.x ||
	   snake.getHeadPossition().x >= gameArea.peak2.x || 
	   snake.getHeadPossition().y >= gameArea.peak2.y)
	{
		return true;
	}
	return false;
}

bool Game::detectSnakeCollision(const Snake & snake)
{
	const auto vec = snake.getNodeVec();

	for (int i = 1; i < vec.size(); i++)
	{
		if (vec.front().getPosition() == vec[i].getPosition())
		{
			return true;
		}
	}

	return false;
}

void Game::createRandomfood(const Snake &snake, std::vector<Food> &foodVec, const GameArea &gameArea)
{	
	while (true)
	{


		int x = getRandomNumber(gameArea.peak1.x / FoodSize, gameArea.peak2.x / FoodSize - 1) * FoodSize;
		int y = getRandomNumber(gameArea.peak1.y / FoodSize, (gameArea.peak2.y / FoodSize - 1)) * FoodSize;

		//check collision with difrent object
		//food

		for (const auto &food : foodVec)
		{
			if (x == food.getPosition().x && y == food.getPosition().y)
			{
				continue;
			}
		}

		//snake

		for (const auto &node : snake.getNodeVec())
		{
			if (x == node.getPosition().x && y == node.getPosition().y)
			{
				continue;
			}
		}

		//create obj and end functions
		foodVec.push_back(sf::Vector2f( x , y));
		break;
	}
}

int Game::getRandomNumber(int r1 , int r2)
{
	std::random_device rdX;
	std::mt19937 eng(rdX());
	std::uniform_int_distribution<> distr(r1, r2);

	return distr(eng);
}

int Game::loadNumberFromFile(std::string fileName)
{
	std::string line;
	std::ifstream myfile;
	myfile.open(fileName);
	if (myfile.is_open())
	{
		getline(myfile, line);
		myfile.close();
		return std::stoi(line);
	}
	
	return -1;
}

int Game::saveNumberFromFile(std::string fileName, int number)
{
	std::ofstream outfile;
	outfile.open(fileName);

	if (outfile.is_open())
	{
		std::string txt = std::to_string(number);

		char * buffer = new char[txt.size()];
		for (int i = 0; i < txt.size() ; i++)
		{
			buffer[i] = txt[i];
		}
		
		outfile.write(buffer , txt.size());

		delete buffer;
		outfile.close();

		return 1;
	}

	return 0;
}

GameStates Game::runGameWindow()
{
	_window->setFramerateLimit(5);
	_points = 0;

	sf::Font font;
	if (!font.loadFromFile("ARCADECLASSIC.ttf"))
	{
		return GameStates::GAME_ERROR;
	}

	_record = loadNumberFromFile("record.txt");
	if (_record == -1) {
		return GameStates::GAME_ERROR;
	}

	sf::Text text3;
	text3.setString(std::to_string(_record));
	text3.setFont(font);
	text3.setCharacterSize(28);
	text3.setFillColor(sf::Color::Black);
	text3.setPosition(sf::Vector2f(50, 134));

	sf::Text text;
	text.setString(std::to_string(_points));
	text.setFont(font);
	text.setCharacterSize(28);
	text.setFillColor(sf::Color::Black);
	text.setPosition(sf::Vector2f(50, 78));

	sf::Text text1;
	text1.setString("Points");
	text1.setFont(font);
	text1.setCharacterSize(28);
	text1.setFillColor(sf::Color::Black);
	text1.setPosition(sf::Vector2f(50 , 50));

	sf::Text text2;
	text2.setString("Record");
	text2.setFont(font);
	text2.setCharacterSize(28);
	text2.setFillColor(sf::Color::Black);
	text2.setPosition(sf::Vector2f(50, 106));




	sf::Texture texture;

	if (!texture.loadFromFile("Background.png"))
	{
		return GameStates::GAME_ERROR;;
	}

	sf::Sprite sprite;
	sprite.setTexture(texture);

	Snake snake;

	sf::Event event;

	while (true)
	{
		_window->clear(sf::Color::Black);
		_window->pollEvent(event);

		if (event.type == sf::Event::Closed)
		{
			_window->close();
			break;
		}
		if (!_window->isOpen())
		{
			break;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			return GameStates::EXIT;
		}

		snakeKeyCommand(snake);
		snake.move();

		//wall algorithm
		if (detectWallCollision(snake, _gameArea))
		{
			return GameStates::GAME_OVER;
		}

		//snake collision alghoritm
		if (detectSnakeCollision(snake))
		{
			return GameStates::GAME_OVER;
		}

		//food algorithm
		for (auto it = _foodVec.begin(); it != _foodVec.end(); it++)
		{
			if (detectFoodCollision(snake, *it))
			{
				std::swap(*(_foodVec.end() - 1), *it);
				_foodVec.pop_back();
				_points++;
				text.setString(std::to_string(_points));
				snake.addNode();
				break;
			}
		}

		if (_foodVec.size() < _foodAmount)
		{
			createRandomfood(snake, _foodVec, _gameArea);
		}
		////////////////

		_window->draw(sprite);

		for (const auto &food : _foodVec) {
			_window->draw(food);
		}

		
		_window->draw(text);
		_window->draw(text1);
		_window->draw(text2);
		_window->draw(text3);
		_window->draw(snake);
		_window->display();
	}
}

GameStates Game::gameOverWindow()
{
	_window->setFramerateLimit(5);

	sf::Event event;

	sf::Font font;
	if (!font.loadFromFile("ARCADECLASSIC.ttf"))
	{
		return GameStates::GAME_ERROR;
	}

	sf::Text text3;
	text3.setString(std::to_string(_record));
	text3.setFont(font);
	text3.setCharacterSize(28);
	text3.setFillColor(sf::Color::Black);
	text3.setPosition(sf::Vector2f(50, 134));

	sf::Text text4;
	text4.setString(std::to_string(_points));
	text4.setFont(font);
	text4.setCharacterSize(28);
	text4.setFillColor(sf::Color::Black);
	text4.setPosition(sf::Vector2f(50, 78));

	sf::Text text5;
	text5.setString("Points");
	text5.setFont(font);
	text5.setCharacterSize(28);
	text5.setFillColor(sf::Color::Black);
	text5.setPosition(sf::Vector2f(50, 50));

	sf::Text text6;
	text6.setString("Record");
	text6.setFont(font);
	text6.setCharacterSize(28);
	text6.setFillColor(sf::Color::Black);
	text6.setPosition(sf::Vector2f(50, 106));

	sf::Text text;
	text.setString("GAME  OVER");
	text.setFont(font);
	text.setCharacterSize(72);
	text.setFillColor(sf::Color::White);
	text.setStyle(sf::Text::Bold);
	text.setPosition(sf::Vector2f(_gameArea.peak1.x + 225 , _gameArea.peak1.y + 225));

	sf::Text text2;
	text2.setString("Press  the  ESC  key  for  Startup  Menu");
	text2.setFont(font);
	text2.setCharacterSize(28);
	text2.setFillColor(sf::Color::White);
	text2.setPosition(sf::Vector2f(_gameArea.peak1.x +  170, _gameArea.peak1.y + 490));

	sf::Text text7;
	text7.setString("New  record!");
	text7.setFont(font);
	text7.setCharacterSize(28);
	text7.setFillColor(sf::Color::White);
	text7.setPosition(sf::Vector2f(_gameArea.peak1.x + 330, _gameArea.peak1.y + 350));

	if (_points > _record)
	{
		if (!saveNumberFromFile("record.txt", _points))
		{
			return ::GameStates::GAME_ERROR;
		}
	}

	//poc - do funkcji dodac
	sf::Texture texture;

	if (!texture.loadFromFile("Background.png"))
	{
		return GameStates::GAME_ERROR;;
	}

	sf::Sprite sprite;
	sprite.setTexture(texture);

	while (true)
	{
		_window->clear(sf::Color::Black);
		_window->pollEvent(event);

		if (event.type == sf::Event::Closed)
		{
			_window->close();
			break;
		}
		if (!_window->isOpen())
		{
			break;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			return GameStates::MAIN_MENU;
		}
		
		_window->draw(sprite);
		_window->draw(text);
		_window->draw(text2);
		_window->draw(text3);
		_window->draw(text4);
		_window->draw(text5);
		_window->draw(text6);

		if (_points > _record)
		{
			_window->draw(text7);
		}
		
		_window->display();
	}

	return GameStates::GAME_ERROR;
}

GameStates Game::mainMenuWindow()
{
	_window->setFramerateLimit(5);

	sf::Event event;

	sf::Font font;
	sf::Text text;

	if (!font.loadFromFile("ARCADECLASSIC.ttf"))
	{
		return GameStates::GAME_ERROR;
	}

	text.setString("SNAKE");
	text.setFont(font);
	text.setCharacterSize(72);
	text.setFillColor(sf::Color::White);


	text.setPosition(sf::Vector2f(450 , 50));

	
	sf::Text text1;
	text1.setString("START");
	text1.setFont(font);
	text1.setCharacterSize(28);
	text1.setFillColor(sf::Color::White);
	text1.setPosition(sf::Vector2f(520, 200));

	sf::Text text2;
	text2.setString("QUIT");
	text2.setFont(font);
	text2.setCharacterSize(28);
	text2.setFillColor(sf::Color::White);
	text2.setPosition(sf::Vector2f(520, 230));

	std::vector<sf::Vector2f> vecCursorPossition{ sf::Vector2f(490, 210), sf::Vector2f(490, 240)};

	int cursorPossition = 0;

	Node node(vecCursorPossition[cursorPossition]);


	while (true)
	{
		_window->clear(sf::Color::Black);
		_window->pollEvent(event);

		if (event.type == sf::Event::Closed)
		{
			_window->close();
			break;
		}
		if (!_window->isOpen())
		{
			break;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			cursorPossition++;
			node.setPossition(vecCursorPossition[cursorPossition%vecCursorPossition.size()]);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			cursorPossition--;
			node.setPossition(vecCursorPossition[cursorPossition%vecCursorPossition.size()]);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			if (cursorPossition % 2 == 0)
			{
				return GameStates::RUN;
			}
			else if (cursorPossition % 2 == 1 )
			{
				return GameStates::EXIT;
			}
		}


		_window->draw(text);
		_window->draw(text1);
		_window->draw(text2);
		_window->draw(node);
		_window->display();
	}

	return GameStates::GAME_ERROR;
}

Game::Game()
{
	_window = new sf::RenderWindow(sf::VideoMode{ 1100 , 700 }, "Snake");
	//_window->setFramerateLimit(5);

	_gameArea.peak1.x = 200;
	_gameArea.peak1.y = 60;
	_gameArea.peak2.x = 1000;
	_gameArea.peak2.y = 660;
}


Game::~Game()
{
	_window->close();
	delete _window;
}

void Game::run()
{
	//main logic for game
	//switch id retun
	
	GameStates gameState = GameStates::MAIN_MENU;

	while (true)
	{
		switch (gameState)
		{
		case GameStates::MAIN_MENU:
			gameState = mainMenuWindow();
			break;
		case GameStates::RUN:
			gameState = runGameWindow();
			break;
		case GameStates::GAME_OVER:
			gameState = gameOverWindow();
			break;
		case GameStates::EXIT:
			return;
			break;
		default:
			break;
		}
	}
	mainMenuWindow();

	if (runGameWindow() == GameStates::GAME_OVER)
	{
		gameOverWindow();
	}
		
}

