// SFML1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <SFML\Window.hpp>
#include <Windows.h>

#include "Game.h"




int main()
{
	::ShowWindow(GetConsoleWindow(), SW_HIDE);
	Game game;
	game.run();

	return 0;
}