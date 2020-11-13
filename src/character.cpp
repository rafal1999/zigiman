/** @file */
#include <SFML/Graphics.hpp> 
#include "character.h"

Character::Character (const sf::Texture & _texture, const sf::Vector2f _position) :LiveObj(_texture,_position)
{
    velocity=sf::Vector2f(0,0);
    prevVelocity=sf::Vector2f(0,0);
}
void Character::draw(sf::RenderWindow & _window) const
{
    LiveObj::draw(_window);
}
sf::FloatRect Character::returnHitBox() const
{
    return sprite.getGlobalBounds();
}

/** metoda rozwiązuje kolizję po przez przyrócenie postaci do porzedniego miejsca 
 * @return nic */
void Character::resolveCollison()
{
  sprite.setPosition(prevPos);
  Character::setPrevVelocity();
}
/**ustawia porzedni kierunek/prędkośc */
void Character::setPrevVelocity()
{
  velocity=prevVelocity;
}
sf::Vector2f Character::getVelocity() const
{
  return velocity;
}
void Character::move()
{    
	prevPos=sprite.getPosition();
	sprite.move(velocity);
}
