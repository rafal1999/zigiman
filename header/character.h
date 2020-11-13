
/** @file */
#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <SFML/Graphics.hpp> 
#include <iostream>

#include "obj.h"
#include "wall.h"

/**klasa postaci bazowa dla Ghost i  Pacman*/
class Character : public LiveObj 
{
	private:
		sf::Vector2f prevPos;///<przechowuje poprzednia pozycję postaci 
	protected:
		static const  int  Speed=4.0;	
		sf::Vector2f velocity;///<prędkośc/kierunek
		sf::Vector2f prevVelocity;///<przechowuję poprzednia prędkość/kierunek 
  public:
	
	/**konstruktor 
	 * @param _texture tekstura 
	 * @param _position pozycja startowa postaci*/
  	Character (const sf::Texture & _texture, const sf::Vector2f _position);
		
		virtual void draw(sf::RenderWindow & _window) const;
		
		/**
		 * @return gloablBoudns-"ramki obiektu"*/
		virtual sf::FloatRect returnHitBox() const;
		
		/**rozwiązuje kolizje */
		virtual void resolveCollison();

		/**metoda czysto wirtualna */
		virtual void setDirection()=0;
		
		/**powoduje zmianę położenia obiektu*/
		virtual void  move();
		/**
		 * @return prędkość/kierunek*/
		virtual sf::Vector2f getVelocity() const;
		/**ustawia poprzedni kierunek/prędkość*/
		void setPrevVelocity();
		virtual ~Character() {};
	
};




#endif 
