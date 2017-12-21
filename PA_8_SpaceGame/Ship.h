/*<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><*\
Linked List : Bullet
Author: William Booston & Ben Elits

Def: File that contains all associated functions to Ship and user values
\*<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><*/
#pragma once

#include <iostream>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
//#include <SFML\System.hpp>



/********************************************
def: this class houses the operations and data
  necessary to display the aray of hearts (Lives)
********************************************/
class HearNode
{
	friend class Ship;
public:
	HearNode() 
	{
		if (!heartPNG.loadFromFile("Health.png"))
		{
			std::cout << "Error Reading 'Health.png'" << std::endl;
		}
		Heart.setTexture(heartPNG);
		
		heartY = HEIGHT - 26;
	}
	~HearNode() {}

private:
	sf::Texture heartPNG;
	sf::Sprite Heart;
	int heartX, heartY;
};

 // is the class that operates the timer shown in game
class inGameTimer
{
public:
	inGameTimer()
	{
		timeString = "";
		if (!font.loadFromFile("consolab.ttf"))
		{
			std::cout << "error Loading text" << std::endl;
		}
		
		TimerText.setFont(font);
		TimerText.setColor(sf::Color(238,226,11));
		TimerText.setString("--:--");
		TimerText.setCharacterSize(23);
		TimerText.setPosition(WIDTH - 90, HEIGHT - 32);
	}
	~inGameTimer() {}

	std::string getString() { return timeString; }

	void updateTimer(int gameClock,sf::RenderWindow * Window)
	{
		int min = 0;
		int sec = 0;

		if (gameClock < 60)
		{
			sec = gameClock;
		}
		else
		{
			min = gameClock / 60;
			sec = gameClock % 60;
		}
		if (min <= 9)
		{
			if (sec <= 9)
			{
				timeString = '0' + std::to_string(min) + ':' + '0' + std::to_string(sec);
				
			}
			else
			{
				timeString = '0' + std::to_string(min) + ':' + std::to_string(sec);
				
			}
		}
		else if (sec <= 9)
		{
			timeString = std::to_string(min) + ':' + '0' + std::to_string(sec);
			
		}
		else
		{
			timeString = std::to_string(min) + ':' + std::to_string(sec);
			
		}
		
		TimerText.setString(timeString);
		Window->draw(TimerText);

	}

private:
	std::string timeString;
	sf::Font font;
	sf::Text TimerText; // Selection 1 Play Game
};





class Ship
{
	friend class AsteroidList;
	friend class AsteroidOBJ;
public:
	Ship();
	~Ship() {}

	bool setShipImg(sf::Image image);
	bool update(sf::RenderWindow *Window);
	
	int getX() { return sSprite.getPosition().x; }
	int getY() { return sSprite.getPosition().y; }
	sf::Sprite &  getSprite() { return sSprite; }

	void setRotate(float degrees);
	void setChange(int NewData) { change = NewData; }


private:
	int X, Y;
	int change;

	int Life;
	HearNode Lives[LIFE];

	sf::Texture baseTexture;
	sf::Sprite baseSprite;

	sf::Texture ShipImg;
	sf::Sprite sSprite;
};

Ship::Ship()
{
	if (!ShipImg.loadFromFile("Ship.png"))
	{
		std::cout << "Error reading from file" << std::endl;
	}
	
	if (!baseTexture.loadFromFile("Base.png"))
	{
		std::cout << "Error Reading 'Base.png'" << std::endl;
	}
	Life = LIFE-1;
	int i = 0;
	for (i = 0; i <= Life; i++)
	{
		Lives[i].heartX = i * 30;
		Lives[i].Heart.setPosition(Lives[i].heartX, Lives[i].heartY);
	}

	baseSprite.setTexture(baseTexture);
	baseSprite.setPosition(0, HEIGHT - 33);

	
	X = 200;
	Y = HEIGHT - 125;
	change = 0;
	sSprite.setPosition(X, Y);
	sSprite.setTexture(ShipImg);
}

bool Ship::setShipImg(sf::Image image)
{
	return false; 
}

void Ship::setRotate(float degrees)
{
	sSprite.rotate(degrees);
}
bool Ship::update(sf::RenderWindow *Window)
{
	
	int x = sSprite.getPosition().x;
	x += change;

	if (x > WIDTH-75)
	{
		x = WIDTH-75;
	}
	else if (x < 0)
	{
		x = 0;
	}
	sSprite.setPosition(x, Y);
	Window->draw(baseSprite);
	int i = 0;
	for (i = 0; i <= Life; i++)
	{
		Window->draw(Lives[i].Heart);
	}
	Window->draw(sSprite);
	return true;
}



