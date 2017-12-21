#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <random>
#include <time.h>

#include "Projectile.h"

/*<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><*\
Object class : Asteroid
Author: William Boston

Def: class SPACE is the container class for all the graphics that take place in the background

\*<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><*/
class AsteroidOBJ
{
public:
	AsteroidOBJ() 
	{
		x = 0;
		y = -50;
		Size = 0;
		Active = false;

		if (!Img.loadFromFile("LargeAsteroid.png"))
		{
			std::cout << "Error Reading Asteroid IMG" << std::endl;
		}
		else
		{
			Sprte.setTexture(Img);
		}

	}
	~AsteroidOBJ() {}
	bool update(sf::RenderWindow *Window, Ship *ship /*ListBullet * bullet*/);
	void reset();

	int getSize() { return Size; }
	void setSize(int newData) { Size = newData; }
	bool getActive() { return Active; }
	void setActive(bool newData) { Active = newData; }

	void setImg(sf::Texture NewImg) { Img = NewImg; }

private:
	int Size;
	int x, y;
	int speed;
	bool Active;
	sf::Texture Img;
	sf::Sprite Sprte;
	
};

void AsteroidOBJ::reset()
{
	y = rand() % 200;
	speed = rand() % 5 + 8;
	x = rand() % (WIDTH - 45);
}

bool AsteroidOBJ::update(sf::RenderWindow *Window, Ship *ship /*ListBullet * bullet*/)
{
	y += speed;
	if ((x + 40) >= (ship->sSprite.getPosition().x) // checking horisontal collision
		&& (x + 5 <= (ship->sSprite.getPosition().x + 40)))
	{
		if (y + 40 >= ship->sSprite.getPosition().y  // checking virtical collision
			&& y <= ship->sSprite.getPosition().y + 75)
		{
			reset();
			ship->Life -= 1;
			std::cout << "<< :Lost 1 life! : >>" << std::endl;
			if (ship->Life < 0) // last life
			{
				return false; // end game
			}
		}
	}
	Window->draw(Sprte);
	return true;
}

/*<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><*\
			Node class : Asteroid
Author: William Boston

Def: class SPACE is the container class for all the graphics that take place in the background

\*<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><*/

class Asteroid
{
	friend class AsteroidList;
public:
	Asteroid(int seed) 
	{
		srand(seed);

		AsteroidImg.loadFromFile("LargeAsteroid.png");
		AsteroidSprite.setTexture(AsteroidImg);
		Y = -20;
		Speed = rand() % 7 + 5;
		X = rand() % (WIDTH-45);

		pPrev = nullptr;
		pNext = nullptr;

	}
	~Asteroid() {}
	bool updateAsteroid();

private:
	int X, Y, Speed;
	sf::Texture AsteroidImg;
	sf::Sprite AsteroidSprite;
	Asteroid *pPrev;
	Asteroid *pNext;
};

bool Asteroid::updateAsteroid()
{

	Y += Speed;
	AsteroidSprite.setPosition(X, Y);
	if(Y > HEIGHT)
	{
		return false;
	}
	return true;
}


/*<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><*\
			Node Wrapper : AsteroidList
Author: William Boston & Ben Elits

Def: class SPACE is the container class for all the graphics that take place in the background
\*<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><*/

class AsteroidList
{
public:
	AsteroidList()
	{
		pHead = nullptr;
		pTail = nullptr;
	}
	~AsteroidList() {}
	void setSeed(int newData) { seed = newData; }

	void insertAtEnd(int seed);
	bool deleteAsteroid(Asteroid **pCur);
	bool updateList(sf::RenderWindow *Window, Ship *ship, ListBullet * bullet); // checks for all collisions

private:
	int seed;
	Asteroid *pHead;
	Asteroid *pTail;
};

/******************************************
def: creates new Asteroid and adds it to the 
  End of the linked list
******************************************/
void AsteroidList::insertAtEnd(int seed)
{
	srand(seed);
	if (pHead == nullptr)
	{
		Asteroid *NewData = new Asteroid(rand() % 10000 + 100);
		pHead = NewData;
		pTail = NewData;
	}
	else
	{
		Asteroid *NewData = new Asteroid(rand() % 10000 + 100);
		pTail->pNext = NewData;
		NewData->pPrev = pTail;
		pTail = NewData;

	}
}

/************************************************
def: takes input Node & 'stiches' previous 
  and next Nodes together so it can be Deleted
************************************************/
bool AsteroidList::deleteAsteroid(Asteroid **pCur)
{
	if ((*pCur)->pPrev == nullptr) // head Node?
	{
		if ((*pCur)->pNext == nullptr)
		{
			pHead = nullptr;
			pTail = nullptr;
		}
		else
		{
			pHead = (*pCur)->pNext;
			pHead->pPrev = nullptr;
		}
	}
	else if ((*pCur)->pNext == nullptr)// Tail Node?
	{
		pTail = (*pCur)->pPrev;
		pTail->pNext = nullptr;
	}
	else // Node in the Middle
	{
		(*pCur)->pNext->pPrev = (*pCur)->pPrev;
		(*pCur)->pPrev->pNext = (*pCur)->pNext;
	}

	return true;
}

/**************************************************************************************
def: When Update List is called, it iterates through the Asteroid list and moves the asteroid
  then it checks for collisions
**************************************************************************************/
bool AsteroidList::updateList(sf::RenderWindow *Window, Ship *ship, ListBullet * bullet)
{

	Asteroid *pCur = pHead;
	NodeBullet * b_pCur = bullet->pHead;

	while (pCur != nullptr)
	{
		if (!(pCur->updateAsteroid()))
		{
			deleteAsteroid(&pCur); // clear asteroid
			Asteroid *temp = pCur;
			pCur = pCur->pNext;
			delete temp;
			return true;
		}
		// Ship Collision
		else if ((pCur->AsteroidSprite.getPosition().x + 40) >= (ship->sSprite.getPosition().x) // checking horisontal collision
			&& (pCur->AsteroidSprite.getPosition().x + 5 <= (ship->sSprite.getPosition().x + 40)))
		{
			if (pCur->AsteroidSprite.getPosition().y + 40 >= ship->sSprite.getPosition().y  // checking virtical collision
				&& pCur->AsteroidSprite.getPosition().y <= ship->sSprite.getPosition().y + 75)
			{
				deleteAsteroid(&pCur); // clear asteroid
				Asteroid *temp = pCur;
				pCur = pCur->pNext;
				delete temp;

				ship->Life -= 1; // decreasing life
				std::cout << "<< :Lost 1 life! : >>" << std::endl;
				if (ship->Life < 0) // last life
				{
					return false; // end game
				}

			}
		}
		if (pCur == nullptr)
		{
			break;
		}
		else
		{
			Window->draw(pCur->AsteroidSprite);
			pCur = pCur->pNext;
		}
	}

	pCur = pHead;


	// Blaster Collision
	while (pCur != nullptr)
	{
		while (b_pCur != nullptr)
		{
			if (pCur == nullptr)
			{
				break;
			}

			if ((pCur->AsteroidSprite.getPosition().x + 45) >= (b_pCur->bullet.getPosition().x) // checking horisontal collision
				&& (pCur->AsteroidSprite.getPosition().x <= (b_pCur->bullet.getPosition().x + 6)))
			{
				if (pCur->AsteroidSprite.getPosition().y + 42 >= b_pCur->bullet.getPosition().y // checking virticle collision
					&& pCur->AsteroidSprite.getPosition().y <= b_pCur->bullet.getPosition().y + 5)
				{
					deleteAsteroid(&pCur); // clear asteroid
					Asteroid *temp = pCur;
					pCur = pCur->pNext;
					delete temp;

					bullet->stitch(&b_pCur); // clear bullet
					NodeBullet * b_temp = b_pCur;
					b_pCur = b_pCur->pNext;
					delete b_temp;
				}
			}
			if (b_pCur == nullptr) // checks for new updatd null list
			{
				break;
			}
			else
			{
				b_pCur = b_pCur->pNext;
			}

		}
		if (pCur != nullptr)
		{
			Window->draw(pCur->AsteroidSprite);
			pCur = pCur->pNext;
		}
	}


	return true;
}


