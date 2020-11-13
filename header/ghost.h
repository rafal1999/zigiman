/** @file */
#ifndef GOHSTS_H_
#define GOHSTS_H_

#include <SFML/Graphics.hpp> 

#include "character.h"
#include "pacman.h"
/**klasa abstrkcyjna  ducha */
class Ghost : public Character 
{
  private:
    sf::Color ghostColor;///<kolor duszka 
    sf::Vector2f startPosition;///<miejsce rodzenia się duszka 
    int timeLeftInDead;///<Czas podczas którego duszek jest martwy*/
  protected:
  /**metoda losuje kierunek poruszania się*/
    void setRandomDirection();
  public:
    /**konstruktor ustawia pozycję, teksturę i kolor duszka*/
    Ghost(const sf::Texture & _texture, const sf::Vector2f _position,sf::Color _color);
    /**ustawia kolor duszka gdy pacman walczy*/
    void fearGhostColor();
    /**ustawia kolor duszka gdy pacman ucieka*/
    void angryGhostColor();
    virtual void draw(sf::RenderWindow & _window) const;
    /**sprawdza kolizje z pacmanem 
     * @return true jesli nastapiła kolizja 
     * @return false jesli kolizja nie wystąpiła */
    virtual bool checkCollision(const std::unique_ptr<Pacman> &  _pacman);
    /**przesuwa duszka */
    virtual void  move();
    virtual void setDirection()=0; 
    /**metoda konieczna aby zachować hierarchię klas  */
    virtual void setPositionToTeleport(const sf::Vector2f & _position){};
    /**metoda konieczna aby zachować hierarchię klas */
    virtual void teleportTo(const sf::Vector2f &  _velocity){};
    /**dekrementuje czas, kiedy duszek jest martwy*/
    int operator--(int);
    /**ustawia status na DEAD i ustawia czas bycia martwym*/
    void  setDead();
    /**reakcja duszków na zjedzenie BigPointa przez pacmana*/
    void fearReaction();
    int returnGhostvalue();

};
/**duszek który patroluje w kółko okreslony teren*/
class GhostGuardian : public Ghost
{
  private:
    bool controlMove;
	public:
	  GhostGuardian(const sf::Texture & _texture, const sf::Vector2f _position,sf::Color _color);
    
    /**ustawia kierunek ruchu zależnie od kolizja tylko w prawa bądz w lewo */
    virtual void setDirection(); 
};

/**klasyczy duszek który sie porusza po mapie */
class GhostCasper : public Ghost
{
	public:
	  GhostCasper(const sf::Texture & _texture, const sf::Vector2f _position,sf::Color _color);
    /**ustawia kierunek ruchu*/
    virtual void setDirection(); 
};
/**klasa duszka Sprigginia duszek posiada moc teleportowania sie w miejse które odwiedził pacman pod koniec czasu trwania supermocy (czyli gdy zjadł BigPointa) pacmana*/ 
class GhostSprigginia : public GhostCasper 
{
  private:
    sf::Vector2f positionToTeleport;///<pozycja do telporcaji która jest wybierana kilka jednkstek czasu przed teleportacją

  public:
    GhostSprigginia(sf::Texture & _texture, const sf::Vector2f _position,sf::Color _color);
    /**ustawia kierunek*/
    virtual void setDirection();
    /**ustawia pozycje do teleportu
     * @param _position pozycja do której duszek bedzie się teleportował*/
    virtual void setPositionToTeleport(const sf::Vector2f & _position);

    /**teleportuje duszka do wskazywanego miejsca 
     * @param _velocity prędkośc/kierunek  jaką przyjmuje duszek po teleportacji i jest to kierunek/predkosc pacmana*/ 
    virtual void teleportTo(const sf::Vector2f &  _velocity); 
};






#endif 