/** @file */
#ifndef OBJ_H_
#define OBJ_H_

#include <SFML/Graphics.hpp> 

#define WALL_SING '#'
#define SMALL_POINT_SIGN '*'
#define BIG_POINT_SIGN '&'
#define PACMAN_SING 'P'
#define GHOSTGUARDIAN_SING 'G'
#define GHOSTCASPER_SING 'C'
#define GHOSTSPRIGGINIA_SING 'S'
/** enum reprezuntujący status obiektu*/
enum class LiveStatus {
												DEAD,///<gdzy obiekt zniszczony/zjedzony itp
												ALIVE///<gdy obiekt jest wyświetlany 
											};



/**klasa Obj jest klasa abstrakcyją podstawową dla wszyskich obiektów w grze*/
class Obj
{
  protected:
 		sf::Sprite sprite;///< reprezentant obiektu 
  public:
		/**konstruktor tworzy obiekt i umieszcza w wskazanej pozycji
		 * @param _texture tekstura obiektu 
		 * @param _position pozycja obiektu startowa/stała 
		*/
		Obj(const sf::Texture & _texture , const sf::Vector2f & _position);
		
		/**metoda rysuje sprite w oknie 
		 * @param [in,out] _window okno w którym ma być rysowany sprite*/ 
		virtual void draw(sf::RenderWindow & _window) const;

		/**ustawia bezwzględnie pozycje obiektu*/
		void setPosition(const sf::Vector2f & _position);
		
		/**
		 * @return zwraca pozycje obiektu*/
		sf::Vector2f getPosition() const;
};

/**klasa abstrakcyja podstawowa dla wszystkich obiektów które "żyją"*/
class LiveObj : public Obj
{
	private:
		LiveStatus liveStatus;
	public:
		LiveObj(const sf::Texture & _texture , const sf::Vector2f _position);

		/**metoda rysuje sprite w oknie jeśli jest ALIVE 
		 * @param [in.out]  _window */
		virtual void draw(sf::RenderWindow & _window) const;
		
		/**ustawia status obiektu na DEAD
		 * @return true jeśli zminiono stasus na DEAD
		 * @return false jeśli status obiektu był DEAD */
		bool setDead();

		/**ustawia status obiektu na ALIVE
	 	* @return true jeśli zminiono stasus na ALIVE
	 	* @return false jeśli status obiektu był ALIVE */
		bool setAlive();

		/**
		 * @return status obiektu */
		LiveStatus getLiveStatus() const;

		/**destruktor*/
		virtual ~LiveObj() {};
};
#endif 
