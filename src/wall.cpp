/** @file */
#include <SFML/Graphics.hpp> 


#include "wall.h"


Wall::Wall(const sf::Texture & _texture , const sf::Vector2f & _position) :Obj(_texture,_position)
{}

void Wall::draw(sf::RenderWindow & _window) const
{
  Obj::draw(_window);
}

bool Wall::checkCollision(const Character&  _character)
{
  sf::FloatRect wallHitBox=sprite.getGlobalBounds();
	sf::FloatRect characterHitBox=_character.returnHitBox();
  
	if(wallHitBox.intersects(characterHitBox))//jesli hitoxy się nakładają
     return true;
 
  return false;
}

