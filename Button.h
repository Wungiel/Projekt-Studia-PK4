#pragma once

//W razie konieczności zmienię nazwę "button" na "clickable", po którym będą dziedziczyć np. pomieszczenia czy postacie

#include <SFML/Graphics.hpp>
#include "Listeners.h"
#include <vector>

class Button
{
public:
	int move; //wartość, jaką zwraca po kliknięciu przycisku klasa
	std::string bname;
	sf::Sprite bsprite; //wygląd naciśniętego przycisku; 
	sf::IntRect barea;
	bool activated;
	std::vector<Listeners*> observators;

	
	void Load (sf::Texture& texture, sf::IntRect areatexture, sf::IntRect area, std::string name, int wheremove);
	void AddObservator (Listeners *Observator);
	void CallObservators (void);
	Button (void);
	Button (sf::Texture& texture, sf::IntRect areatexture, sf::IntRect area, std::string name, int wheremove);
};
