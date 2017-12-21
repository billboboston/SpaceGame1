#include "Source.h";
#include "Space.h";
#include "Ship.h";
#include "Projectile.h";
#include "Asteroid.h";

std::string readScore()
{ // 00:00 = Min:Sec
	std::string HighScore; // String var for Highest Score

	std::ifstream inFile; // File Var
	inFile.open("Score.txt", std::ifstream::in);

	if (inFile.fail())
	{
		return "Score Load Error";
	}

	else
	{
		char temp[100] = "";
		inFile.getline(temp, 99, '\n');
		HighScore = temp;
	}

	inFile.close();
	return HighScore;
}

void storeTime(std::string gameClock)
{
	std::ofstream outFile;
	outFile.open("Score.txt", std::ofstream::out);

	if (outFile.fail())
	{
		outFile << "No High Score" << std::endl;
		
	}
	else
	{
		outFile << gameClock << std::endl;
	}

	outFile.close();
}

bool evaltime(std::string &GameTime)
{
	std::string HighScore = readScore();
	int i = 0;
	for (i = 0; i < 5; i++)
	{
		if (HighScore[i] > GameTime[i])
		{
			storeTime(HighScore);
			return false;
		}
		else if (GameTime[i] > HighScore[i])
		{
			storeTime(GameTime);
			return true;
		}
		
		
	}
	return true;
}

/*******************************************************************************************************
def: This funciton houses the auto operations to add dificulty and update the Asteroid List
********************************************************************************************************/

bool updateAList(AsteroidOBJ List[], sf::RenderWindow *Window, Ship *ship)
{
	int i;
	for (i = 0; i < List[0].getSize(); i++)
	{
		if (List[i].getActive() == true)
		{
			if (!List[i].update(Window, ship))
			{
				return false;
			}
		}
	}
	return true;
}

bool initAList2(AsteroidOBJ *List[15], int Size)
{
	int i;
	for (i = 0; i < Size; i++)
	{
		List[i] = new AsteroidOBJ();
	}
	return true;
}

bool AutoAsteroid2(sf::RenderWindow *Window, AsteroidOBJ List[], Ship *ship, int gameClock)
{
	/// gameClock.getElapsedTime().asSeconds()
	if (gameClock <= 5)
	{
		List[0].setActive(true);
		List[0].setSize(1);
	}
	else if (gameClock == 10)
	{
		List[1].setActive(true);
		List[2].setActive(true);
		List[0].setSize(3);
	}
	else if (gameClock == 25)
	{
		List[3].setActive(true);
		List[4].setActive(true);
		List[0].setSize(5);
	}
	else if (gameClock == 50)
	{
		List[5].setActive(true);
		List[6].setActive(true);
		List[0].setSize(7);
	}
	else if (gameClock == 75)
	{
		List[7].setActive(true);
		List[8].setActive(true);
		List[0].setSize(9);
	}
	else if (gameClock == 90)
	{
		List[9].setActive(true);
		List[10].setActive(true);
		List[0].setSize(11);
	}
	else if (gameClock == 120)
	{
		List[11].setActive(true);
		List[12].setActive(true);
		List[0].setSize(13);
	}
	else if (gameClock == 150)
	{
		List[13].setActive(true);
		List[14].setActive(true);
	///	List[14]->setActive(true);
		List[0].setSize(15);
	}
	
	if (!(updateAList(&List[0], Window, ship)))
	{
		return false;
	}
	return true;
}


/******************************************
Authors: William Boston & Ben Eilts
def: GameLoop return false for exit game
******************************************/
bool playgame(sf::RenderWindow *Window)
{
	srand(time(0));
	Clock gameClock; // users time score

	inGameTimer GameTimer;	 
	Clock timer; // timer for blaster reset

	int Seed;
	bool left;
	bool right; // to make ship not "sticky"

	bool play = true;
	Space space; // Star List
	space.makeSpace();

	ListBullet Bullets;// doubly linked Asteroid List
	//AsteroidList Yay;
	AsteroidOBJ Yay2[15]; // Asteroid LIst
	//initAList2(&Yay2[15], 15);

	Ship ship;

	int i =0,o = 0; //asteroid Timers

	gameClock.restart();
	while (play)
	{
		Seed = rand() % 10000 + 1000;

		float timer_time = timer.getElapsedTime().asSeconds();// required for correct implementation of Bullets
		timer.restart();

		sf::Event event;
		while (Window->pollEvent(event)) // check for an Event
		{
			switch (event.type) // check what type Event
			{
			case sf::Event::Closed:
				play = false;
				Window->close();
				break;
				/**************** KEY DOWN **********************/
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Escape: // Quit Game
					return false;
					//Window->close();
					break;

				case sf::Keyboard::Space:
					std::cout << "SpaceBar Down" << std::endl;
					Bullets.shoot_bullet(ship.getX(), ship.getY());
					std::cout << "Sot Fired" << std::endl;
					break;
				case sf::Keyboard::Up:
					std::cout << "SpaceBar Down" << std::endl;
					Bullets.shoot_bullet(ship.getX(), ship.getY());
					std::cout << "Sot Fired" << std::endl;
					break;

				case sf::Keyboard::A: // adds a single extra asteroid to List
					std::cout << "A Down" << std::endl;
					///	Yay.insertAtEnd(Seed);
					break;

				case sf::Keyboard::Left:
					if (left == false) // checks if its already been pressed
					{
						ship.setRotate(-10); //rotate left
					}
					left = true;
					ship.setChange((-(WIDTH)*.02));
					std::cout << "Key Left Down" << std::endl;
					break;

				case sf::Keyboard::Right:
					if (right == false) // should check if its already been pressed
					{
						ship.setRotate(10); //rotate right
					}
					right = true;
					ship.setChange((WIDTH*.02));
					std::cout << "Key Right Down" << std::endl;
					break;
				}
				break;
				/**************** KEY UP *************************/
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Left:
					left = false;
					ship.setRotate(10);
					std::cout << "Key Left Up" << std::endl;
					if (left == false && right == false)
					{
						ship.setChange(0);
					}
					break;

				case sf::Keyboard::Right:
					right = false;
					ship.setRotate(-10);
					std::cout << "Key Right Up" << std::endl;
					if (left == false && right == false)
					{
						ship.setChange(0);

					}
					break;
				}
			}
		}
		i++;
		o++;
		
		Window->clear();// Insert All Draw After

		if (!AutoAsteroid2(Window, &Yay2[15],&ship, gameClock.getElapsedTime().asSeconds()))
		{
			break;
		}
		space.UpdateStars(Window);// background
	///	play = Yay.updateList(Window, &ship, &Bullets); // Asteroids
		Bullets.Update(Window, timer_time);// Bullets
		ship.update(Window); // Ship Status
		GameTimer.updateTimer(gameClock.getElapsedTime().asSeconds(), Window); // game

		Window->display();// Insert All Draw Before
	}

	evaltime(GameTimer.getString());// checks games time to High Score

	return true;
}


/******************************************
Authors: William & Ben
def: Menue Screen with choice & data
******************************************/
int menue(sf::RenderWindow * Window, std::string HighScore)
{
	int menue_result = 0;

	Space space;

	sf::Font font;
	if (!font.loadFromFile("consolab.ttf"))
	{
		std::cout << "error Loading text" << std::endl;
	}
	sf::Text Title; // Header
	Title.setFont(font);
	Title.setColor(sf::Color(200, 200, 200, 200));
	Title.setString("SPACE 101");
	Title.setCharacterSize(40);
	Title.setPosition(30, 30);

	sf::Text Play; // Selection 1 Play Game
	Play.setFont(font);
	Play.setColor(sf::Color::Green);
	Play.setString("> START GAME ");
	Play.setCharacterSize(25);
	Play.setPosition(30, 100);

	sf::Text Score; // Selection 2 High Score
	Score.setFont(font);
	Score.setColor(sf::Color::Yellow);
	Score.setString("> High Score");
	Score.setCharacterSize(25);
	Score.setPosition(30, 150);

	sf::Text Exit; // Selection 3 EXIT
	Exit.setFont(font);
	Exit.setColor(sf::Color::Blue);
	Exit.setString("> EXIT");
	Exit.setCharacterSize(25);
	Exit.setPosition(30, 200);

	bool Yes = true;
	do
	{
		sf::Event event;
		while (Window->pollEvent(event))
		{
			switch (event.type)
			{

			case sf::Event::Closed:
				Yes = false;
				menue_result = 3;
				Window->close();
				break;

				/**************** KEY DOWN **********************/
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Escape: // Quit Game
					return false;
					//Window->close();
					break;
				}
				break;
			}
		


		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))// mouse click Play or Exit
		{
			int X = sf::Mouse::getPosition(*Window).x, Y = sf::Mouse::getPosition(*Window).y;
			if (X >= 56 && X <= 200 && Y >= 104 && Y <= 129)// START
			{
				menue_result = 1;
				std::cout << "play..." << std::endl;
				Yes = false;
			}
			if (X >= 53 && X <= 113 && Y >= 205 && Y <= 230) // EXIT
			{
				menue_result = 3;
				std::cout << "EXIT... " << std::endl;
				Yes = false;
			}

			std::cout << "Click.." << std::endl;
			std::cout << X << " | ";
			std::cout << Y << std::endl;
		}

		// checks if mouse is hovering over high Score
		if (sf::Mouse::getPosition(*Window).x >= 53 && sf::Mouse::getPosition(*Window).x <= 200 &&
			sf::Mouse::getPosition(*Window).y >= 153 && sf::Mouse::getPosition(*Window).y <= 175)
		{
			Score.setString(HighScore);
			Score.setPosition(55, 150);
		}
		else
		{
			Score.setString("> High Score");
			Score.setPosition(30, 150);
		}

		Window->clear();
		space.UpdateStars(Window);
		Window->draw(Title);
		Window->draw(Play);
		Window->draw(Score);
		Window->draw(Exit);
		Window->display();
	} while (Yes);


	return menue_result;
}