/** @file */
#include <SFML/Graphics.hpp> 

#include <iostream>
#include <random>


#include"game.h"

int main()
{ 
	std::srand(time(0));
	try
	{
    Game game;
		game.run();
  }
	catch(const char * errorInfo)
	{
		std::cout<<errorInfo<<std::endl;
	}
  catch(...)
	{
		std::cout<<"INNY WYJĄTEK"<<std::endl; 
	}
 	return 0;
}
