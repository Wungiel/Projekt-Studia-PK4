#pragma once
#include <SFML/Graphics.hpp>

//Polimorfizm i dziedziczenie
class GameState
{
public :

	int Changed;
	int WhereMove;

    virtual int Run (sf::RenderWindow &window) = 0;
};

//State_Menu - nie używa resourcemanager, przechowuje dane potrzebne do wyświetlenia menu głównego
class State_Menu : public GameState
{
	public:
	
    virtual int Run(sf::RenderWindow &window);
};

//State_Extra - używa resourcemanager, przechowuje dane potrzebne do wyświetlenia menu extras; korzysta z właściwości wzorca projektowego obserwator
class State_Extra: public GameState
{
	private:
	bool Running;


	public:
	
    virtual int Run(sf::RenderWindow &window);
};
