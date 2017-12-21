/*******************************************
Authors: William Boston & Ben Eilts
      SID: ( 11421575   & 11416913)
*******************************************/

#include <iostream>
#include <fstream>

using std::ifstream;

#include "Source.h"

void main(void)
{
	ifstream inFile;// initial high Score Load
	inFile.open("HighScore.txt");
	std::string Score = "> NULL";
	Score = readScore();

	int selection = 0;// menue selection
	

	std::cout << "Space 101 : Beta 2.4" << std::endl;

	// Window Parameters
	sf::RenderWindow Window(sf::VideoMode(WIDTH, HEIGHT), "Space 101 Beta 2.4", sf::Style::Titlebar | sf::Style::Close);
	Window.setFramerateLimit(60);

	selection = menue(&Window, Score);
	do // APP loop
	{
		switch (selection)
		{
		case 1:
			playgame(&Window);
			Score = readScore();
			break;
		case 3:
			selection = 3;
			break;
		}
	} while (menue(&Window, Score) != 3);

	selection = menue(&Window,Score);
	//system("pause");

	
	inFile.close();
	

}