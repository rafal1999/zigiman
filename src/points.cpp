
/** @file */
#include <SFML/Graphics.hpp> 

#include "obj.h"
#include "points.h"
Point::Point(const sf::Texture & _texture, const sf::Vector2f & _position) : LiveObj(_texture,_position)
{}

void Point::draw(sf::RenderWindow & _window) const
{
	LiveObj::draw(_window);
}

bool Point::checkCollision(const std::unique_ptr<Pacman> &  _pacman)
{
	

	sf::FloatRect pointHitBox=sprite.getGlobalBounds();
	sf::FloatRect pacmanHitBox=_pacman->returnHitBox();
	sf::FloatRect controlBox;
	if(pointHitBox.intersects(pacmanHitBox,controlBox))
	{
		if(controlBox.height*controlBox.width>=40*24)
		if(LiveObj::setDead())
			return true;
	}
	return false;
}

//SmallPoint___________________________________________

SmallPoint::SmallPoint(const sf::Texture & _texture , const sf::Vector2f & _position) : Point( _texture, _position)
{}



void SmallPoint::draw(sf::RenderWindow & _window) const
{
	Point::draw(_window);
}
bool SmallPoint::checkCollision(const std::unique_ptr<Pacman> &  _pacman)
{
	 return Point::checkCollision(_pacman);
}

int SmallPoint::returnPointValue() const
{	
	if(LiveObj::getLiveStatus()==LiveStatus::DEAD)
	{
		return 1;
	}
	return 0;
}


//BigPoint___________________________________________________________________

BigPoint::BigPoint(const sf::Texture & _texture , const sf::Vector2f & _position) :Point( _texture, _position)
{}

void BigPoint::draw(sf::RenderWindow & _window) const
{
	Point::draw(_window);
}

bool BigPoint::checkCollision(const std::unique_ptr<Pacman> &  _pacman)
{
	 return Point::checkCollision(_pacman);
}

int BigPoint::returnPointValue() const
{
	if(LiveObj::getLiveStatus()==LiveStatus::DEAD)
	{
		return 10;
	} 
		return 0;
}




