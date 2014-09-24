/* W programie poruszamy się za pomocą myszki. Program obsługuje lewy przycisk myszy oraz klawisz escape. Klawisz escape natychmiast wyłącza grę. 
Poruszając kursorem, podświetlają się obiekty na które można kliknąć. Tylko kliknięcie na:
- Wyjście i Extrasy (drzwi i plakat) w menu głównym
- Powrót (leżący luzem fragment zbroi) w menu extras
Powodują zmianę stanów gry. Pozostałe obiekty, ze względu na brak stanów gry do których mogą prowadzić, nie zmieniają stanu programu */



#include "Button.h"
#include "Listeners.h"
#include "ResourceManager.h"
#include "GUI.h"
#include "GameState.h"

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <map> 
#include <memory> // ze względu na unique pointer,
#include <stdexcept> //do sygnalizowania błędów występujących w czasie pracy programu
#include <cassert> //uby w razie nieudanej próby znaleznienia zasobu o podanym ID przerwać działanie funkcji


int main()
{

	std::vector<GameState*> GameStates;
    int state = 0;

    sf::RenderWindow window(sf::VideoMode(800, 600), "Going Pony: Tycoon", sf::Style::Titlebar | sf::Style::Close);
	window.setMouseCursorVisible(false);

	State_Menu MainMenu;
    GameStates.push_back(&MainMenu);
    State_Extra ExtrasMenu;
    GameStates.push_back(&ExtrasMenu);


	    while (state >= 0)
    {
        state = GameStates[state]->Run(window);
    }

}


