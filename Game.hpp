#pragma once

#include <SFML/Graphics.hpp>
#include "Rat.hpp"

#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

#define MAP_WIDTH 20
#define MAP_HEIGHT 15
#define SQUARE_SIZE 40

class Rat;

//class that will handle the main logic of the game
class Game
{
public:
	//constructor
	Game();
	//make the game run
	void Run();
private:
	//it loads a map from a file
	sf::Vector2i LoadMap(const std::string);
	void DrawMap();
private:
	//map where the the movement happens
	int mMap[MAP_HEIGHT][MAP_WIDTH];
	//render window
	sf::RenderWindow window;
	//the mouse
	Rat *mouse;
};