/** @file */
#ifndef WALL_H_
#define WALL_H_

#include <SFML/Graphics.hpp> 

#include "obj.h"
#include "character.h"


class Character;//dla kompilatora  
class Wall : public Obj
{
  public:
	/**kontruktor ustawiający ścianę*/
  Wall(const sf::Texture & _texture , const sf::Vector2f & _position);
	void draw(sf::RenderWindow & _window) const;
	/**sprawdza czy wystąpiła kolizja z ścianą*/
	virtual bool  checkCollision(const Character & _character);
};


#endif 