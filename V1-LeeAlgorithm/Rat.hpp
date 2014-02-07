#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stack>
#include <queue>

#define MAP_WIDTH 20
#define MAP_HEIGHT 15

class Rat
{
public:
	Rat(sf::Vector2i, int map[MAP_HEIGHT][MAP_WIDTH]);
	~Rat();
	void Move();
	void LoadNewMap(int map[MAP_HEIGHT][MAP_WIDTH]);
	sf::Vector2i GetCoords();
	void AteCheese();

private:
	sf::Vector2i mCurrCoord;
	int mCostMap[MAP_HEIGHT][MAP_WIDTH];
	std::stack<sf::Vector2i> mFinalPath;
	unsigned int cheeseEaten;

private:
	void GetPath(int map[MAP_HEIGHT][MAP_WIDTH]);
	bool isNodeOk(sf::Vector2i);
};