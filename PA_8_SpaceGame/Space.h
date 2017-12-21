/*<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><*\
Author: William Boston & Ben Elits

Def: This Header File Contains the Classes for the visual background
\*<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><*/

#pragma once
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <iostream>
#include <random>
#include <time.h>


/*<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><*\
		Base Class : Star
Author: William Boston

Def: Star is a base class for the List in class Space


\*<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><*/

class Star
{
	friend class Space;
public:
	Star() {}
	~Star() {}

	void initStar(int seed, int SpeedMin, int SpeedMax, int sizeMax, int sizeMin, sf::Color color);
	void update(int seed, int speedMax, int speedMin, int sizeMin, int sizeMax);

private:
	int X;
	int Y;
	int Speed;
	sf::CircleShape Dot;

};
void Star::initStar(int seed, int SpeedMin, int SpeedMax, int sizeMax, int sizeMin, sf::Color color)
{
	srand(seed);

	Dot.setRadius(rand() % sizeMax + sizeMin);
	Dot.setFillColor(color);
	Dot.setPointCount(50);
	X = (rand() % WIDTH);
	Y = rand() % HEIGHT;
	Speed = rand() % SpeedMax + SpeedMin;
}
void Star::update(int seed, int speedMin, int speedMax, int sizeMin, int sizeMax)
{
	srand(seed);
	if (Y > HEIGHT)
	{
		Dot.setRadius(rand() % sizeMax + sizeMin);
		Y = -10;
		X = rand() % (WIDTH - 25) + 25;
		Speed = rand() % speedMax + speedMin;
	}
	else
	{
		Y += Speed;
	}

	Dot.setPosition(X, Y);
}

/*<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><*\
		Wrapper Class : Space
Author: William Boston

Def: class SPACE is the container class for all the graphics that take place in the background
	

\*<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><*/

class Space
{
public:
	Space();
	~Space() {}

	void makeSpace();
	void UpdateStars(sf::RenderWindow *window);

private:
	Star close[25];
	Star medium[10];
	Star far[30];
};

Space::Space()
{
	srand(time(0));

	int i = 0;
	for (i = 0; i < 25; i++) // init small list
	{					// ( rand Seed , spMin , spMax , szMax , szMin, color)
		sf::Color dust(sf::Color(255, 255, 255, 90));
		close[i].initStar(rand() % 2000, 10, 14, 3, 1, dust);
	}
	for (i = 0; i < 10; i++)
	{
		sf::Color star(sf::Color(200, 200, 200, 200));
		medium[i].initStar(rand() % 2000, 5, 8, 7, 2, star);
	}
	for (i = 0; i < 30; i++)
	{
		sf::Color planet(50,50,50);
		far[i].initStar(rand() % 2000, 2, 7, 3, 1, planet);
	}
}

void Space::makeSpace()
{
	srand(time(0));

	int i = 0;
	for (i = 0; i < 25; i++) // init small list
	{					// ( rand Seed , spMin , spMax , szMax , szMin, color)
		sf::Color dust(sf::Color(255, 255, 255, 90));
		close[i].initStar(rand() % 2000, 10, 14, 3, 1, dust);
	}
	for (i = 0; i < 10; i++)
	{
		sf::Color star(sf::Color(200, 200, 200, 200));
		medium[i].initStar(rand() % 2000, 5, 8, 7, 2, star);
	}
	for (i = 0; i < 30; i++)
	{
		sf::Color planet(50,50,50);
		far[i].initStar(rand() % 2000, 2, 7, 7, 1, planet);
	}

}

void Space::UpdateStars(sf::RenderWindow *window)
{
	srand(time(0));
	/***************** UPDATE ***********************/
	int i = 0;
	for (i = 0; i < 25; i++) // init small list
	{
		close[i].update(rand() % 2000, 10, 14, 1, 4);
	}
	for (i = 0; i < 10; i++)
	{
		medium[i].update(rand() % 2000, 5, 12, 2, 7);
	}
	for (i = 0; i < 30; i++)
	{
		far[i].update(rand() % 2000, 1, 7,2,7);
	}

	/***************** PRINT ***********************/
	for (i = 0; i < 25; i++) // small star list
	{
		window->draw(close[i].Dot);
	}
	for (i = 0; i < 10; i++) // medium star list
	{
		window->draw(medium[i].Dot);
	}
	for (i = 0; i < 30; i++) // big star list
	{
		window->draw(far[i].Dot);
	}
}
