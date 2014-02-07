#include "Rat.hpp"

Rat::Rat(sf::Vector2i initialPos, int map[MAP_HEIGHT][MAP_WIDTH]) :
cheeseEaten(0)
{
	for(int i = 0 ; i < MAP_HEIGHT ; i++)
		for(int j = 0 ; j < MAP_WIDTH ; j++)
			mCostMap[i][j] = -1;

	mCurrCoord = initialPos;
	mCostMap[initialPos.x][initialPos.y] = 0;

	GetPath(map); 
}

Rat::~Rat()
{
	std::cout << "Score: " << cheeseEaten << std::endl;
}

void Rat::GetPath(int map[MAP_HEIGHT][MAP_WIDTH])
{
	std::queue<sf::Vector2i> BFS;
	BFS.push(mCurrCoord);

	while (map[BFS.front().x][BFS.front().y] != 2 && !BFS.empty())
	{
		sf::Vector2i node = BFS.front();
		int cost = mCostMap[node.x][node.y];
		BFS.pop();

		if(isNodeOk(sf::Vector2i(node.x + 1, node.y)) && mCostMap[node.x + 1][node.y] == -1 && map[node.x+1][node.y] != 1)
		{
			BFS.push(sf::Vector2i(node.x + 1, node.y));
			mCostMap[node.x + 1][node.y] = cost + 1;
		}

		if(isNodeOk(sf::Vector2i(node.x - 1, node.y)) && mCostMap[node.x - 1][node.y] == -1 && map[node.x-1][node.y] != 1)
		{
			BFS.push(sf::Vector2i(node.x - 1, node.y));
			mCostMap[node.x - 1][node.y] = cost + 1;
		}

		if(isNodeOk(sf::Vector2i(node.x, node.y + 1)) && mCostMap[node.x][node.y + 1] == -1 && map[node.x][node.y+1] != 1)
		{
			BFS.push(sf::Vector2i(node.x, node.y + 1));
			mCostMap[node.x][node.y + 1] = cost + 1;
		}

		if(isNodeOk(sf::Vector2i(node.x, node.y - 1)) && mCostMap[node.x][node.y - 1] == -1 && map[node.x][node.y-1] != 1)
		{
			BFS.push(sf::Vector2i(node.x, node.y - 1));
			mCostMap[node.x][node.y - 1] = cost + 1;
		}
	}

	if(!BFS.empty())
		mFinalPath.push(BFS.front());

	while(!mFinalPath.empty() && mCostMap[mFinalPath.top().x][mFinalPath.top().y] != 0)
	{
		sf::Vector2i node = mFinalPath.top();

		if(isNodeOk(sf::Vector2i(node.x + 1, node.y)) && mCostMap[node.x + 1][node.y] == mCostMap[node.x][node.y] - 1)
		{
			mFinalPath.push(sf::Vector2i(node.x + 1, node.y));
			continue;
		}

		else if(isNodeOk(sf::Vector2i(node.x - 1, node.y)) && mCostMap[node.x - 1][node.y] == mCostMap[node.x][node.y] - 1)
		{
			mFinalPath.push(sf::Vector2i(node.x - 1, node.y));
			continue;
		}

		else if(isNodeOk(sf::Vector2i(node.x, node.y + 1)) && mCostMap[node.x][node.y + 1] == mCostMap[node.x][node.y] - 1)
		{
			mFinalPath.push(sf::Vector2i(node.x, node.y + 1));
			continue;
		}

		else if(isNodeOk(sf::Vector2i(node.x, node.y - 1)) && mCostMap[node.x][node.y - 1] == mCostMap[node.x][node.y] - 1)
		{
			mFinalPath.push(sf::Vector2i(node.x, node.y - 1));
			continue;
		}
	}
}

bool Rat::isNodeOk(sf::Vector2i node)
{
	if(node.x < 15 && node.y < 20 && node.x >= 0 && node.y >= 0)
		return true;
	else
		return false;
}

void Rat::Move()
{
	if(!mFinalPath.empty())
	{
		mCurrCoord = mFinalPath.top();
		mFinalPath.pop();
	}
}

sf::Vector2i Rat::GetCoords()
{
	return mCurrCoord;
}

void Rat::LoadNewMap(int map[MAP_HEIGHT][MAP_WIDTH])
{
	for(int i = 0 ; i < MAP_HEIGHT ; i++)
		for(int j = 0 ; j < MAP_WIDTH ; j++)
			mCostMap[i][j] = -1;

	mCostMap[mCurrCoord.x][mCurrCoord.y] = 0;

	GetPath(map);
}

void Rat::AteCheese()
{
	cheeseEaten++;
}