/** @file */
#ifndef PACMAN_H_
#define PACMAN_H_

#include <SFML/Graphics.hpp> 

#include "character.h"
/**klasa pacmana odpowiada za rysowanie, poruszanie, ustawianie kierunku i rotacji tekstury*/ 
class Pacman : public Character
{
	private:
	sf::Texture t;///<tekstura pomocnicza wykorzystywana przy rotacji pacmana
	public:
		/**konstruktor ustawia pozycję i teksture*/
		Pacman(const sf::Texture & _texture, const sf::Vector2f _position);
		
		virtual void draw(sf::RenderWindow & _window) const;
		
		/**ustawia kieunek ruchu */
		virtual void setDirection();
		/**metoda ustwia rotacje pacmana zaleznie od predkosci/kierunku obecnej i poprzedniej*/
		void setRotation(); 

		/**metoda realizuje ruch pacmana oraz zapamiętuje poprzednią pozycję*/
		virtual void move();
};


#endif 
