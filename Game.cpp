#include "Game.hpp"

Game::Game()
{
	window.create(sf::VideoMode(800,600), "PathFinder!");

	mouse = new Rat(LoadMap("map1.txt"), mMap);

	srand(time(NULL));
}

void Game::Run()
{

	sf::Clock clockdown;
	sf::Time count = sf::Time::Zero;

	while (window.isOpen())
	{

		mMap[mouse->GetCoords().x][mouse->GetCoords().y] = 0;

		sf::Event event;
		while(window.pollEvent(event)) 
		{
		    if(event.type == sf::Event::Closed)
		    	window.close();

		    count += clockdown.restart();

		    while(count.asMilliseconds() >= 150)
		    {
		    	count -= sf::milliseconds(150); 
		    	mouse->Move();
		    }
		    
		    /*
		    else if (event.type == sf::Event::KeyPressed)
		    	if(event.key.code == sf::Keyboard::Space)
		    		mouse->Move();
		    		*/

		    if (mMap[mouse->GetCoords().x][mouse->GetCoords().y] == 2)
		    {
		    	mMap[mouse->GetCoords().x][mouse->GetCoords().y] = 3;
		    	mouse->AteCheese();
		    	int foodH, foodW;
		    	do
		    	{
		    		foodH = rand() % 15;
		    		foodW = rand() % 20;
		    	} while(mMap[foodH][foodW] != 0);

		    	mMap[foodH][foodW] = 2;

		    	mouse->LoadNewMap(mMap);
		    }
		}

		mMap[mouse->GetCoords().x][mouse->GetCoords().y] = 3;

		window.clear();
		DrawMap();
		window.display();
	}

	delete mouse;
}

sf::Vector2i Game::LoadMap(const std::string strMapName)
{
	std::ifstream IN(strMapName);
	if(IN == nullptr)
	{
		std::cout << "Failed to open " + strMapName << std::endl;
		window.close();
		return sf::Vector2i(0,0);
	}

	sf::Vector2i ratPos;

	for (int i = 0 ; i < MAP_HEIGHT ; i++)
		for(int j = 0 ; j < MAP_WIDTH ; j++)
		{
			IN >> mMap[i][j];
			if(mMap[i][j] == 3)
				ratPos = sf::Vector2i(i,j);
		}

	IN.close();

	return ratPos;
}

void Game::DrawMap()
{
	sf::RectangleShape rect(sf::Vector2f(SQUARE_SIZE,SQUARE_SIZE));

	for (int i = 0 ; i < MAP_HEIGHT ; i++)
		for (int j = 0 ; j < MAP_WIDTH ; j++)
		{
			//wall
			if (mMap[i][j] == 1)
			{
				rect.setFillColor(sf::Color::Blue);
			}
			//target
			else if(mMap[i][j] == 2)
			{
				rect.setFillColor(sf::Color::Yellow);
			}
			//seeker
			else if (mMap[i][j] == 3)
			{
				rect.setFillColor(sf::Color::Magenta);
			}
			else
			{
				rect.setFillColor(sf::Color::Black);
			}

			rect.setPosition(sf::Vector2f(SQUARE_SIZE*j, SQUARE_SIZE*i));
			window.draw(rect);
		}
}