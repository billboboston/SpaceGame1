/*<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><*\
Author: Ben Elits & William Boston

Def: All classes and functions associated with the Blaster in Game
\*<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><*/#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <string.h>



using sf::Clock;

#define BULLET_SPEED 400

/*************************************
Author: Ben Eilts
def: base class NODE
*************************************/

class NodeBullet
{
	friend class ListBullet;
	friend class AsteroidList;

public:
	NodeBullet()
	{	
		
		bullet.setRadius(5);
		bullet.setFillColor(sf::Color::Red);
		clock.restart().asSeconds();
		pNext = nullptr;
		pPrev = nullptr;// added pPrev so its Doubly Linked *
	}
	~NodeBullet()
	{
	}

protected:
	sf::CircleShape bullet;
	sf::Clock clock;
	NodeBullet *pNext;
	NodeBullet *pPrev;// added pPrev so its Doubly Linked *
};

/*************************************
Author: Ben Eilts
def:  Bullet List Class for NODE BULLET
*************************************/
class ListBullet
{
	friend class AsteroidList;
public:
	ListBullet()
	{
		pHead = nullptr;
		pTail = nullptr;
	}
	~ListBullet();
	void shoot_bullet(float X, float Y);
	bool CanShoot();
	bool Update(sf::RenderWindow *window, float ElapsedTime);

	bool stitch(NodeBullet **pCur);
private:
	NodeBullet *pHead;
	NodeBullet *pTail;
	void deleteList();
};

// Destructor
ListBullet::~ListBullet()
{
	deleteList();
}
 // Does what is says, it Delests the list
void ListBullet::deleteList()
{
	NodeBullet *pTemp = NULL;

	while (pHead != NULL)
	{
		pTemp = pHead;
		pHead = pHead->pNext;
		delete (pTemp);
	}
	std::cout << "List deleted" << std::endl;
	pHead = NULL;
}


/*************************************
Author: Ben Eilts
def:  checks linked list, then inserts into correct
  position 
*************************************/
void ListBullet::shoot_bullet(float X, float Y)
{
	if (pHead == NULL)
	{
		NodeBullet *pMem = new NodeBullet();
		pMem->bullet.setPosition(X + 28, Y);
		pMem->pNext = NULL;
		pMem->pPrev = NULL; // added pPrev so its Doubly Linked *
		pHead = pTail = pMem;
		std::cout << "First Bullet Fired" << std::endl;
	}
	else if (CanShoot() == true) // checking time
	{
		NodeBullet *pMem = new NodeBullet();
		pMem->bullet.setPosition(X + 28, Y);

		pHead->pPrev = pMem;// added pPrev so its Doubly Linked *
		pMem->pNext = pHead;
		pHead = pMem;
		std::cout << "More Bullets Fired" << std::endl;
	}
}

// checks time sense last bullet was shot
bool ListBullet::CanShoot()
{
	bool result = true;

	if (pHead->clock.getElapsedTime().asSeconds() < .1) // this number is the relaod speed *
	{
		result = false; // can't shoot
	}
	return result;
}

/*************************************
Author: William Boston
def: takes input Node and 'stitches' the list
 together so the Node can be deleted.
*************************************/
bool ListBullet::stitch(NodeBullet ** pCur)
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

/***************************************************
Author: Ben Eilts & William Boston
Houses operations to visually update current List
***************************************************/
bool ListBullet::Update(sf::RenderWindow *window, float ElapsedTime)
{
	
	NodeBullet *pCur = pHead;

	while (pCur != NULL)
	{
		pCur->bullet.move(0, -(ElapsedTime * BULLET_SPEED));
		window->draw(pCur->bullet);

		if (pTail == pHead) // one in list
		{
			if (pHead->bullet.getPosition().y < 0)
			{
				NodeBullet *pTemp = pHead;
				pHead = pTail = NULL;
				std::cout << "bullet deleted" << std::endl;
			}
		}
		else if (pCur->pNext == pTail) // pCur is located second to last
		{
			if (pTail->bullet.getPosition().y < 0) // delete bullet
			{
				NodeBullet *pTemp = pTail;
				pCur->pNext = NULL;
				pTail = pCur;
				delete pTemp;
				std::cout << "bullet deleted" << std::endl;
				
			}

		}
		pCur = pCur->pNext;
	}

	return true;
}

