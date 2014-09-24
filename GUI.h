#pragma once

#include "Button.h"
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class GUI
{
public:
	Button * MenuButtons; //dynamiczna lista obiektów klasy button
	sf::Texture& ButtonsTexture;  //tekstura przechowująca ilustracje wszystkich "podświetlonych" przycisków
	sf::Sound click; //odgłos aktywowany przy najechaniu kursorem
	int MenuAmount; //zmienna przechowująca liczbę przycisków


	void IsStillActive (sf::Vector2i mouse)
	{
		for (int i=0; i<=(MenuAmount-1); ++i) 
		{
			if (!(MenuButtons[i].barea.contains(mouse) && MenuButtons[i].activated==true))
				MenuButtons[i].activated=false;
		}

	};

	void IsActivated (sf::Vector2i mouse, sf::RenderWindow& window, sf::Text& displayed)
	{
		for (int i=0; i<=(MenuAmount-1); ++i) 
			if (MenuButtons[i].barea.contains(mouse))
					{
						if (MenuButtons[i].activated==false) 
							{
								click.play();
								MenuButtons[i].activated=true;
							}
					window.draw(MenuButtons[i].bsprite);
					displayed.setString(MenuButtons[i].bname);
					};
	};




	GUI (int amount, sf::SoundBuffer& buffer, sf::Texture& texture) : ButtonsTexture(texture)
	{
		MenuButtons=new Button[amount];
		MenuAmount=amount;
		click.setBuffer(buffer);

	}

	~GUI ()
	{
		delete [] MenuButtons;
	}
};
