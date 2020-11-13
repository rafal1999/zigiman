/** @file */
#include <SFML/Graphics.hpp> 
#include <cstdlib>
#include <unistd.h>
#include <string>
#include <fstream>
#include "wall.h"
#include "game.h"
#include "pacman.h"

PointsCounter::PointsCounter() 
{
	font.loadFromFile("FreeMono.ttf");
	value=0;
	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Black);
	text.setPosition(765,0);
	backgroundBox.setSize(sf::Vector2f(80,25));
	backgroundBox.setPosition(700,5);
	backgroundBox.setFillColor(sf::Color::White);
	backgroundBox.setOutlineThickness(2);
	backgroundBox.setOutlineColor(sf::Color::Red);
}
void PointsCounter::showPoints(sf::RenderWindow & _window) 
{	
	resolveSize();
	text.setString(std::to_string(value));
	_window.draw(backgroundBox);
	_window.draw(text);
}
void PointsCounter::operator++(int)
{
	value++;
}
void PointsCounter::resolveSize()
{
	if(value>=10 && value <=19)
		text.setPosition(750,0);
	if(value>=100&& value <=999)
		text.setPosition(735,0);
	if(value>=1000)
		text.setPosition(720,0);
	
}
int PointsCounter::operator+=(int a)
{
	return value+=a;
}
int PointsCounter::returnValue()
{
	return value;
}

void Game::readTextures()
{
	std::string s;
	if(!gameTextures.wall.loadFromFile("textures/obj.png"))
	{
		 throw("nie udało się wczytać grafiki obj");
	}
	if(!gameTextures.smallPoint.loadFromFile("textures/Smallpoint.png"))
	{
		throw("nie udało się wczytać grafiki pacmana");
	}
		if(!gameTextures.bigPoint.loadFromFile("textures/bigpoint.png"))
	{
		 throw("nie udało się wczytać grafiki bigpoint");
	}
	if(!gameTextures.pacman.loadFromFile("textures/pacman.png"))
	{
		throw("nie udało się wczytać grafiki pacmana");
	}
	if(!gameTextures.ghost.loadFromFile("textures/ghost.png"))
	{
		throw("nie udało się wczytać grafiki ducha");
	}
	
	return;
}



Map Game::returnMap(const char * _fileName)
{
	readTextures();
	std::ifstream inFile(_fileName);
	if(!inFile.is_open()) 
	{

		throw("Taka mapa nie istnieje");
  }
	Map map;
  char c; //ściana punkt duch 
	for(int j=0;j<15;j++)
  for(int i=0;i<21;i++)
	{
		sf::Vector2f position;
		position.x=i*40;
		position.y=j*40;
		if(inFile.get(c)&& c==WALL_SING)
		{
			Wall w (gameTextures.wall,position);
			map.walls.push_back(w);
		}
    else if(c==SMALL_POINT_SIGN)
    {
      map.points.emplace_back(std::move(new SmallPoint(gameTextures.smallPoint,position)));
    }
		else if(c==PACMAN_SING)
		{
			pacman=std::unique_ptr<Pacman>(new Pacman(gameTextures.pacman,position));
		}
		else if(c==BIG_POINT_SIGN)
		{
			map.points.emplace_back(std::move(new BigPoint(gameTextures.bigPoint,position)));
		}
		else if(c==GHOSTCASPER_SING)
		{
			for(int i=0;i<4;i++)
			ghosts.emplace_back(std::move(new GhostCasper(gameTextures.ghost,position,sf::Color::Red)));
		}
		else if(c==GHOSTGUARDIAN_SING)
		{
			ghosts.emplace_back(std::move(new GhostGuardian(gameTextures.ghost,position,sf::Color::White)));
		}
			else if(c==GHOSTSPRIGGINIA_SING)
		{
			ghosts.emplace_back(std::move(new GhostSprigginia(gameTextures.ghost,position,sf::Color::Green)));
		}
	}
	return map;
}
/**tylko wyświetl napis i coś tan jeszce */
void Game::endGame()
{
  sf::Text text;
	sf::Font font;
	font.loadFromFile("FreeMono.ttf");
	text.setFont(font);
	text.setCharacterSize(35);
	text.setFillColor(sf::Color::Yellow);
	text.setOutlineThickness(5);
	text.setOutlineColor(sf::Color::Black);
	
	if(gameMap.points.begin()!= gameMap.points.end())
	{
		text.setPosition(253,35);
		text.setString("Zigi is Dead");
	}
	else
	{
		text.setPosition(242,35);
		text.setString("Zigi Survived");
	}
	drawObjects();
	window.draw(text);	
  pointsCounter.showPoints(window);
	  while (window.isOpen())
    {
			sf::Event event;
			while (window.pollEvent(event))
			{
					if (event.type == sf::Event::Closed)
							window.close();
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				window.close();			
			window.display();
    }
	window.close();
}
void Game::startWindow()
{
	sf::Text text;
	sf::Font font;
	font.loadFromFile("FreeMono.ttf");
	text.setFont(font);
	text.setCharacterSize(50);
	text.setFillColor(sf::Color::Yellow);
	text.setOutlineThickness(5);
	text.setOutlineColor(sf::Color::Black);
	text.setPosition(275,20);
	text.setString("ZigiMan");
	window.draw(text);
	
	text.setCharacterSize(30);
	text.setPosition(600,560);
	text.setString("FromFroncel");
	window.draw(text);
	window.draw(text);
	text.setCharacterSize(30);
	text.setPosition(3,560);
	text.setString("PoweredByZelu");
	window.draw(text);
}
void Game::setGameStatusFight()
{
	timer=200;
	auto it=ghosts.begin();
  while(it!=ghosts.end())
  { 
	  (*it)->fearReaction();
		it++;
	}	
	gameStatus=GameStatus::FIGHT;
}
void Game::timerRun()
{
	if(gameStatus==GameStatus::RUN)
		return;
	
	timer--;
	if(timer==0)
	{
		gameStatus=GameStatus::RUN;

	}
}
void Game::setGhostColorRuning()
{
	auto it=ghosts.begin();
	while(it!=ghosts.end())
	{ 
		(*it)->fearGhostColor();
		it++;
	}
}
void Game::setGhostColorFighting()
{
		auto it=ghosts.begin();
	while(it!=ghosts.end())
	{ 
		(*it)->angryGhostColor();
		it++;
	}
}
Game::Game() : pointsCounter()
{
	gameStatus=GameStatus::RUN;
	timer=0;
	gameMap=returnMap("mapa");
  window.create(sf::VideoMode(800, 600), "ZigiMan");
	window.setFramerateLimit(40);
  drawObjects();
	startWindow();
		while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
				||	sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
				||	sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
				||	sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
						break;
				}
        window.display();
    }
}


void Game::run()
{

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
		if (event.type == sf::Event::Closed)
		window.close();
		}
		if(gameMap.points.begin()==gameMap.points.end())//if kończący gre 
			endGame();
	
		window.clear();
		timerRun();//odlicza czas jesli tryb gry jest FIGHT
	
		moveAllObjects();
		collisionPacmanPoints();
		collisionPacmanGhost();
		CollisionGhostWall();
		collisionPacmanWall();
		ChangeGhosts();
		drawObjects();

		pointsCounter.showPoints(window);
		window.display();
	}
    
}


void Game::drawObjects()
{
	drawWalls();
	drawPoints();
	drawPacman();
	drawGhosts();
}

void Game::drawWalls()
{
  auto it=gameMap.walls.begin();
  while(it!=gameMap.walls.end())
  {  
    it->draw(window);
	  it++;
	}
}

void Game::drawPoints()
{
	auto it=gameMap.points.begin();
  while(it!=gameMap.points.end())
  {  
   (*it)->draw(window);
	  it++;
	}
}

void Game::drawPacman()
{
	pacman->draw(window);
}

void Game::drawGhosts()
{
	
	auto it=ghosts.begin();
  while(it!=ghosts.end())
  { 
		
  	(*it)->draw(window);
	  (**it)--;// jeslu duch dalej jest martwy to zmniejszenie licznka czasu (o jedną jedostkę czasu) bycia martwy
	  it++;
	}
}
void Game::ChangeGhosts()
{
	if(gameStatus==GameStatus::FIGHT)
	{
		if(timer<=120)
		{
			setGhostColorFighting();
			if(timer%6==0)
				setGhostColorRuning();
		}
		else 
			setGhostColorRuning();
	}
}

void Game::collisionPacmanPoints()
{
	auto it=gameMap.points.begin();
  while(it!=gameMap.points.end())
  {  
   if((*it)->checkCollision(pacman))//jelsi kolizja z pkt
	 {
		  pointsCounter+=(*it)->returnPointValue();
			if(typeid(BigPoint)==typeid(**it))
				Game::setGameStatusFight();
			gameMap.points.erase(std::remove(gameMap.points.begin(),gameMap.points.end(),*it));//usuwanie konkretnego pkt
	 }
	 else//przeciwnie tylko iterator++ 
	 		it++;
	}
}
bool  Game::checkCollisionPacmanWall()
{
	auto it=gameMap.walls.begin();
  while(it!=gameMap.walls.end())
  {  
   if((it->checkCollision(*pacman)))//jelsi kolizja z wall
	 { 
		 return true;
	 }
		it++;
	}
	return false;
}
void Game::collisionPacmanWall()
{
	if(checkCollisionPacmanWall()==true) 
	{
		pacman->resolveCollison();
		pacman->move();
		if(checkCollisionPacmanWall()==true)
			pacman->resolveCollison();
	}
}
bool Game::collisionPacmanGhost()
{
	auto it=ghosts.begin();

  while(it!=ghosts.end())
  {  
   if((*it)->checkCollision(pacman))//jelsi kolizja z pacmanem 
	 {
		if(gameStatus==GameStatus::FIGHT)//jeżeli pacman walczy to duszek zminia status na martwy 
	  {
			(*it)->setDead();
			pointsCounter+=(*it)->returnGhostvalue();
		}
		else if(gameStatus==GameStatus::RUN)
		{
			pacman->setDead();
			endGame();
		}
		return true;
	 }
	 else
	 		it++;
	}
	return false;
}
bool Game::CollisionGhostWall()
{
	auto itGhost=ghosts.begin();
	
	while(itGhost!=ghosts.end())
	{


		auto itWalls=gameMap.walls.begin();

		while(itWalls!=gameMap.walls.end())
		{  
			if((itWalls->checkCollision(**itGhost)))//jelsi kolizja z wall
			{ 
				(*itGhost)->resolveCollison();
				(*itGhost)->setDirection();
			}
				itWalls++;
		}
		itGhost++;
	}
	return true;
}
void Game::moveGhost()
{
	auto it=ghosts.begin();
  while(it!=ghosts.end())
  { 
		if(timer==15)//jesli 15 jednostka czasu to ustawia pozycje do teleportu 
			(*it)->setPositionToTeleport(pacman->getPosition());
		if(timer==1)// jesli 1 jednosta czasu supermocy to duszek się teleportuje nie może być 0 ponieważ zero ozacza ze musiał by sie coągle telportować 
			(*it)->teleportTo(pacman->getVelocity());
   (*it)->move();
		it++;
	 
	}	
}

void Game::moveAllObjects()
{
	pacman->setDirection();	
	pacman->move();
	pacman->setRotation();
	moveGhost();
}