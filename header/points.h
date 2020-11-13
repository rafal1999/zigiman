/** @file */
#ifndef POINTS_H_
#define POINTS_H_

#include <SFML/Graphics.hpp> 

#include "obj.h"
#include "character.h"
#include "pacman.h"



/** klasa bazowa dla punktu*/
class Point: public LiveObj
{
  
  public: 
    Point(const sf::Texture & _texture, const sf::Vector2f & _position);
    virtual void draw(sf::RenderWindow & _window) const;
		/**
		 * @return true jeśli była kolizja i zmienia status obiektu na DEAD
		 * @return false jeśli nie było kolizji i nie zmienia statusu */
 		virtual bool checkCollision(const std::unique_ptr<Pacman> &  _pacman);
		virtual int returnPointValue() const =0;

    virtual ~Point(){};
};

/**klasa małego punktu (na maie oznaczony kolorem zółtym*/
class SmallPoint : public Point 
{
  public:
    SmallPoint(const sf::Texture & _texture , const sf::Vector2f & _position);
		virtual void draw(sf::RenderWindow & _window) const;
    virtual bool checkCollision(const std::unique_ptr<Pacman> &  _pacman);
    /**
     * @return wartość Smallpointa*/
    virtual int returnPointValue() const;
     ~SmallPoint(){};
}; 

class BigPoint : public Point
{
  public:
		BigPoint(const sf::Texture & _texture , const sf::Vector2f & _position);
		virtual void draw(sf::RenderWindow & _window) const;
    virtual bool checkCollision(const std::unique_ptr<Pacman> &  _pacman);
    /**
     * @return wartość Bigpointa*/
    virtual int returnPointValue() const;
		~BigPoint(){};
}; 

#endif 
