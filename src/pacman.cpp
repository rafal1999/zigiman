/** @file */
#include <SFML/Graphics.hpp> 


#include "character.h"
#include "pacman.h"

Pacman::Pacman(const sf::Texture & _texture, const sf::Vector2f _position): Character( _texture, _position)
{}

void Pacman::draw(sf::RenderWindow & _window) const
{
	Character::draw(_window);
}

void Pacman::setDirection()
{	
	prevVelocity=velocity;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
	{
		velocity.x=-Speed;
		velocity.y=0;   
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
	{
		velocity.x=Speed;
		velocity.y=0;
  }

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 
	{	
		velocity.x=0;
		velocity.y=-Speed;    
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) 
	{
		velocity.x=0;
		velocity.y=Speed;    
	}
	
}

void Pacman::setRotation()
{	
 if(velocity.x>0 && velocity.y==0)
 {
  	t.loadFromFile("textures/pacmanR.png");
  	sprite.setTexture(t);
 }
 else if(velocity.x<0 && velocity.y==0)
 {
	  t.loadFromFile("textures/pacman.png");
		sprite.setTexture(t);
 }
 else if(velocity.x==0 && velocity.y<0 && prevVelocity.x>0 && prevVelocity.y==0)
 {
	  t.loadFromFile("textures/pacmanUL.png");
		sprite.setTexture(t);
 }
 else if(velocity.x==0 && velocity.y<0 && prevVelocity.x<0 && prevVelocity.y==0)
 {
	  t.loadFromFile("textures/pacmanUR.png");
		sprite.setTexture(t);
 }
 else if(velocity.x==0 && velocity.y>0 && prevVelocity.x>0 && prevVelocity.y==0)
 {
	  t.loadFromFile("textures/pacmanDR.png");
		sprite.setTexture(t);
 }
 else if(velocity.x==0 && velocity.y>0 && prevVelocity.x<0 && prevVelocity.y==0)
 {
	  t.loadFromFile("textures/pacmanDL.png");
		sprite.setTexture(t);
 }
 else if(velocity.x==0 && velocity.y<0 && prevVelocity.x==0 && prevVelocity.y>0)
 {
	  t.loadFromFile("textures/pacmanUR.png");
		sprite.setTexture(t);
 }
 else if(velocity.x==0 && velocity.y>0 && prevVelocity.x==0 && prevVelocity.y<0)
 {
	  t.loadFromFile("textures/pacmanDR.png");
		sprite.setTexture(t);
 }
}

void Pacman::move()
{    
	Character::move();
}
