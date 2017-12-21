#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <string>
#include <fstream>

#define WIDTH 400 // prProcessor Definition for screen dimensions
#define HEIGHT 800
#define LIFE 5

std::string readScore();
bool updateAList(AsteroidOBJ List[], sf::RenderWindow *Window, Ship *ship);

//bool updateAList(AsteroidOBJ List[], sf::RenderWindow *Window, Ship *ship);

//void storeTime(std::string gameClock);
//bool updateAList(AsteroidOBJ List[], int Size, sf::RenderWindow *Window, Ship *ship);
//bool evaltime(std::string &GameTime);


//when this is included, i get Error when i call in on line 253 in Source.cpp
//void AutoAsteroid(sf::RenderWindow *Window, AsteroidList *List, int gameClock, float Reset, int i, int Seed);

bool playgame(sf::RenderWindow * Window);

int menue(sf::RenderWindow * Window, std::string HighScore);