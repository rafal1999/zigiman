
/** @file */
#ifndef GAME_H_
#define GAME_H_

#include <SFML/Graphics.hpp> 
#include <iostream>
#include <memory>
#include "obj.h"
#include "character.h"
#include "ghost.h"
#include "points.h"
#include "wall.h"
#include "pacman.h"




/**klasa licznika punktów, odpowada za liczenie punktów i wyświetlanie licznika (w prawym górnym rogu*/
class PointsCounter
{
	private:
		int value;///< wartość licznika 
		sf::Text text;///<tekst (punkty) który jest wyświetlny
		sf::Font font;///<font 
		sf::RectangleShape backgroundBox;///<tło licznika
	public:
	/**konstruktor*/
	PointsCounter();
	/**metoda odpowiednio pozycjonuje cyfry zależnie od ich liczebnosci*/
	void resolveSize();

	/**wyświetla punkty w prawym górnym rogu*/
	void showPoints(sf::RenderWindow & _window);

	/**przeciążony operator dodawania 1 pkt*/
	void operator++(int);

	/**przeciążony operator  
	 * @return wartość po dodaniu warości 
	*/
	int operator+=(int a);
	
	/**
	 * @return  wartość licznika*/
	int returnValue();
};
/**struktura mapy, przechowuje sciany i punkty*/
 struct Map
 {
   std::vector <std::unique_ptr<Point>> points;///<przechowuje   wszystkie punkty 
   std::vector<Wall> walls;///<przechowuje wszystkie sciany
 };

/**enum słuząca do obsługi trybu gry*/
enum class GameStatus {
												RUN,///<tryb ucieczki pacmana
												FIGHT///<tryb walki pacmana
											};

/** struktura przechowuje tekstury obiektów*/
 struct Textures
 {
   sf::Texture wall;
   sf::Texture smallPoint;
   sf::Texture bigPoint; 
   sf::Texture pacman;
   sf::Texture ghost;
 };
 /**klasa gry w której są wywoływane wszystkie metody które mają wpływ na grę*/
class Game 
{
  private:
		sf::RenderWindow window;///<okno z SFMLa
		Map gameMap;///<struktra przechowujaca ścian i punkty 
		Textures gameTextures;///<struktura przechowująca textury 
		std::vector<std::unique_ptr<Ghost>> ghosts;
		std::unique_ptr<Pacman> pacman; 
		GameStatus gameStatus;///<status gry czy pacman ucieka czy goni
		PointsCounter pointsCounter; ///<zmienna przechowuje 
		int timer;///<<timer gry po zjedzeniu BigPointa
		
		/**metoda czyta tekstury*/
		void readTextures();
		
		/** czyta i zwraca mape z pliku 
		 * @param _fileName nazwa pliku  mapy*/
		Map returnMap(const char * _fileName);

		/**metoda która jest uruchamian gdy koniec gry*/
		void endGame();
		
		/**metoda wyświetla startowe okno*/
		void startWindow();
		
		/**ustawia status gry na FIGHT i ustaiwa timer*/
		void setGameStatusFight();
		
		/**obsługuje timer*/
		void timerRun();

		/**ustawia kolor duchów na klor ucieczki(niebieski)*/
		void setGhostColorRuning();

		/**ustawia kolor duchów na kolor walki (normalny)*/
		void setGhostColorFighting();

	public:
		/**konstruktor gry czyta mape obiekty, tekstury*/
		Game();
		
		/**główna metoda gry w niej dzieje się cała akcja*/
		void run();
		
		/**rysuje wszyskie obiekty w grze*/
		void drawObjects();
		
		/**rysuje wszyskie ściany*/
		void drawWalls();
		
		/**rysuje wszyskie punkty (małe i duże) w grze*/
		void drawPoints();
		
		/**rysuje Pacmana*/
		void drawPacman();
		
		/**rysuje wszyskie duchy w grze*/
		void drawGhosts();
		
		/**odpowada za miganie duszków jeśli czas super mocy pacmana się kończy*/
		void ChangeGhosts();
		
		/**metoda wykrywa i rozwiazuje kolizje pacmana z punktami*/
		void collisionPacmanPoints();
		
		/**metoda wykrywa i odpowiedni reaguje na  kolizje pacmana z duszkami*/
		bool collisionPacmanGhost();
		
		/**sprawdza kolizje Pacmana z ścianą*/
		bool checkCollisionPacmanWall();
		
		/**metoda wykrywa i rozwiazuje kolizje pacmana z scianą*/
		void collisionPacmanWall();
		
		/**metoda wykrywa i rozwiazuje kolizje duszków  z ścianami*/
		bool CollisionGhostWall();
		
		/** przesuwa i ustawia  wszystkie obiekty*/
		void moveAllObjects();

		/**przesuwa wszystkie duszki*/
		void moveGhost();
};

#endif 
