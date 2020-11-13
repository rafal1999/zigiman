/** @file */
#include <SFML/Graphics.hpp> 
#include <cstdlib>
#include "obj.h"
#include "character.h"
#include "pacman.h"
#include "ghost.h"




Ghost::Ghost(const sf::Texture & _texture, const sf::Vector2f _position,sf::Color _color):Character(_texture,_position)
{
  ghostColor =_color;
	sprite.setColor(ghostColor);
	startPosition=_position;
}
void Ghost::setRandomDirection()
{
	int i=rand()  % 4;
	switch(i)
	{
	case 0:
		velocity.x=-Speed;
		velocity.y=0;
			break;
		
	case 1:
		velocity.x=Speed;
		velocity.y=0;
		break;
		
	case 2:
		velocity.x=0;
		velocity.y=-Speed;
			break;

	case 3:
		velocity.x=0;
		velocity.y=Speed; 
			break;
	}
}

void Ghost::draw(sf::RenderWindow & _window) const
{
  Character::draw(_window);
}
bool Ghost::checkCollision(const std::unique_ptr<Pacman> &  _pacman)
{
	if(LiveObj::getLiveStatus()==LiveStatus::DEAD)
		return false;


	sf::FloatRect ghostHitBox=sprite.getGlobalBounds();
	sf::FloatRect pacmanHitBox=_pacman->returnHitBox();
	sf::FloatRect controlBox;//zmiena przechowująca wartości (wysokoć szerokość itp) obszaru/prostokątu który jest wypadkowym naożeniem się dwóch obszarów 
	if(ghostHitBox.intersects(pacmanHitBox,controlBox))
	{
		if(controlBox.height*controlBox.width>=40*10)
			return true;
	}
	return false;
}
void Ghost::fearGhostColor()
{
	sprite.setColor(sf::Color::Blue);
}
void Ghost::angryGhostColor()
{
	sprite.setColor(ghostColor);
}
int Ghost::operator--(int)
{
	if(LiveObj::getLiveStatus()==LiveStatus::DEAD)
	{
		timeLeftInDead--;
		if(timeLeftInDead==0)
		{
			LiveObj::setAlive();
			sprite.setPosition(startPosition);
		}
	}
	return timeLeftInDead;
}
void Ghost::setDead()
{
	timeLeftInDead=200;
	LiveObj::setDead();
}
void Ghost::move()
{
	if(LiveObj::getLiveStatus()==LiveStatus::ALIVE)
		Character::move();
}
void Ghost::fearReaction()
{
	velocity.x*=-1;
	velocity.y*=-1;
}
int Ghost::returnGhostvalue()
{
	return 100;
}
///////GhostGuardian_______________________________________
GhostGuardian::GhostGuardian(const sf::Texture & _texture, const sf::Vector2f _position,sf::Color _color):
														Ghost(_texture,_position,_color)
{
	velocity=sf::Vector2f(Speed,0);
	controlMove=0;
}
void GhostGuardian::setDirection()
{
	
	if(controlMove==1)
	{
		velocity=sf::Vector2f(Speed,0);
		controlMove=0;
	}
	else if(controlMove==0)
	{
		velocity=sf::Vector2f(-Speed,0);
		controlMove=1;
	}
}

GhostCasper::GhostCasper(const sf::Texture & _texture, const sf::Vector2f _position,sf::Color _color):
													Ghost(_texture,_position,_color)
{
	Ghost::setRandomDirection();
}


void GhostCasper::setDirection()
{

	Ghost::setRandomDirection();	
}
//GhostSprigginia____________________________________________________

GhostSprigginia::GhostSprigginia (sf::Texture & _texture, const sf::Vector2f _position,sf::Color _color):
																						GhostCasper(_texture, _position,_color)
{}



void GhostSprigginia::setDirection()
{
	GhostCasper::setDirection();
}
void GhostSprigginia::teleportTo(const sf::Vector2f &  _velocity)
{
	this->setPosition(positionToTeleport);
	velocity=_velocity;
}
void GhostSprigginia::setPositionToTeleport(const sf::Vector2f & _position)
{
	positionToTeleport=_position;
}
