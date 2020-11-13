/** @file */
#include "obj.h"

Obj::Obj(const sf::Texture & _texture , const sf::Vector2f & _position): sprite(_texture)
{
	sprite.setPosition(_position.x,_position.y);//korekta względem środka sprita 
}




void Obj::draw(sf::RenderWindow & _window) const
{
	_window.draw(sprite);
}

void Obj::setPosition(const sf::Vector2f & _position)
{
	sprite.setPosition(_position);	
}

sf::Vector2f Obj::getPosition() const	
{
	return sprite.getPosition();
}

LiveObj::LiveObj(const sf::Texture & _texture, const sf::Vector2f _position): Obj(_texture,_position), liveStatus(LiveStatus::ALIVE)
{}



void LiveObj::draw(sf::RenderWindow & _window) const
{
	if(liveStatus==LiveStatus::ALIVE)
		Obj::draw(_window);
}
LiveStatus LiveObj::getLiveStatus() const
{
	return liveStatus;
}

bool LiveObj::setDead()
{
	if(liveStatus==LiveStatus::ALIVE)
	{
			liveStatus=LiveStatus::DEAD;
			return true;
	}
	else if(liveStatus==LiveStatus::DEAD)
	{
		return false;
	}
	return false;
}
bool LiveObj::setAlive()
{
	if(liveStatus==LiveStatus::DEAD)
	{
			liveStatus=LiveStatus::ALIVE;
			return true;
	}
	else if(liveStatus==LiveStatus::ALIVE)
	{
		return false;
	}
	return false;
}