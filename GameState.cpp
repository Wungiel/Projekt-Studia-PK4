#include "GameState.h"
#include "ResourceManager.h"
#include "GUI.h"
#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>


int State_Menu::Run(sf::RenderWindow &window)
		{    
			sf::Event Event;
			bool Running = true;
			Changed = 0;
			WhereMove=0;
			sf::Texture bg, bgb, cs;
			sf::Music bgmusic;
			sf::SoundBuffer buffer;
			sf::Font font;
			sf::Text text;
			sf::Event event;

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			sf::IntRect NewGame(110, 340, 350, 200);
			sf::IntRect LoadGame(240, 170, 160, 160);
			sf::IntRect Extras(240, 30, 155, 95);
			sf::IntRect Options(715, 110, 85, 425);
			sf::IntRect Exit(420, 90, 210, 245);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

				if (!font.loadFromFile("data/fonts/mlpfont.ttf"))
				{
				std::cerr << "Error loading font, main menu" << std::endl;
				return (-1);
				}		

				if (!bg.loadFromFile("data/graphics/MainMenu.png"))
				{
				std::cerr << "Error loading presentation.gif" << std::endl;
				return (-1);
				}

				if (!bgb.loadFromFile("data/graphics/MainMenuButtons.png"))
				{
				std::cerr << "Error loading texture, buttons, main menu" << std::endl;
				return (-1);
				}

				if (!cs.loadFromFile("data/graphics/cursor.png"))
				return EXIT_FAILURE;

				if (!bgmusic.openFromFile("data/music/MainMenu.ogg"))
				{
					std::cerr << "Error loading music, main menu" << std::endl;
					return (-1);
				}
	
				if (!buffer.loadFromFile("data/sounds/click.ogg"))
				{
				  std::cerr << "Error loading sound, main menu" << std::endl;
				return (-1);
				}

					//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			text.setFont(font);
			text.setCharacterSize(20);
			text.setColor(sf::Color::Black);
			text.setPosition(490,50);

			sf::Sprite background(bg);

			GUI MainMenu(5, buffer, bgb);
			MainMenu.MenuButtons[0].Load(MainMenu.ButtonsTexture, sf::IntRect(0,0,800,600), NewGame, "Nowa Gra", 0);
			MainMenu.MenuButtons[1].Load(MainMenu.ButtonsTexture, sf::IntRect(800,0,800,600), Exit, "Wyjscie", -1);
			MainMenu.MenuButtons[2].Load(MainMenu.ButtonsTexture, sf::IntRect(1600,0,800,600), LoadGame, "Wczytaj", 0);
			MainMenu.MenuButtons[3].Load(MainMenu.ButtonsTexture, sf::IntRect(2400,0,800,600), Extras, "Extrasy", 1);
			MainMenu.MenuButtons[4].Load(MainMenu.ButtonsTexture, sf::IntRect(3200,0,800,600), Options, "Opcje", 0);

			sf::Sprite cursor(cs);
			window.setFramerateLimit(60);
			bgmusic.play();

    while (Running)
    {
        while (window.pollEvent(event))
        {
			switch(event.type)
			{

				case sf::Event::Closed:
				{
					return (-1);
				}

				case sf::Event::KeyPressed:
				{
					if(event.key.code == sf::Keyboard::Escape) 
					return (-1);
				}

				case sf::Event::MouseButtonPressed:
					{
					if (event.mouseButton.button == sf::Mouse::Left)
					{
					  for (int i=0; i<=((MainMenu.MenuAmount)-1); ++i)
					  {
						if ((MainMenu.MenuButtons[i].activated)==true)
							return (MainMenu.MenuButtons[i].move);
					  }
					}
				}

			 default: break;
			}
        }
   

       cursor.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));


		sf::Vector2i MousePosition=sf::Mouse::getPosition(window);

	    window.clear();	
		window.draw(background);
		
		MainMenu.IsStillActive(MousePosition);
		MainMenu.IsActivated(MousePosition, window, text);

		window.draw(cursor);
		window.draw(text);
        window.display();
    }
	
    return (-1);
	};



int State_Extra::Run(sf::RenderWindow &window)
{    
			sf::Event Event;
			Running = true;
			Changed = 0;
			WhereMove=0;
			sf::Music bgmusic;
			sf::Text text;
			sf::Event event;
			int i;

			EventListeners number1;
			ChangeListeners number2;
			MoveListeners number3(*this);

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			sf::IntRect Encyclopedia(160, 360, 90, 60);
			sf::IntRect Authors(500, 355, 80, 65);
			sf::IntRect Return(595, 390, 80, 50);

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			
			ResourceManager<sf::Texture, Textures::IDT> textures;
			try
			{
				textures.load(Textures::Background, "data/graphics/ExtrasMenu.png");
				textures.load(Textures::BackgroundButtons, "data/graphics/ExtrasMenuButtons.png");
				textures.load(Textures::Cursor, "data/graphics/Cursor.png");
			}

				catch (std::runtime_error& e)
			{
				std::cout << "Exception: " << e.what() << std::endl;
				return 1;
			};

				ResourceManager<sf::SoundBuffer, SoundBuffers::IDS> soundbuffers;
				try
			{
				soundbuffers.load(SoundBuffers::MainSound, "data/sounds/click.ogg");
			}

				catch (std::runtime_error& e)
			{
				std::cout << "Exception: " << e.what() << std::endl;
				return 1;
			};


			ResourceManager<sf::Font, Fonts::IDF> fonts;
			try
			{
				fonts.load(Fonts::MainFont, "data/fonts/mlpfont.ttf");
			}

				catch (std::runtime_error& e)
			{
				std::cout << "Exception: " << e.what() << std::endl;
				return 1;
			};

			
			
					

				if (!bgmusic.openFromFile("data/music/MainMenu.ogg"))
				{
					std::cerr << "Error loading music, extras menu" << std::endl;
					return (-1);
				}
	
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			sf::Sprite background(textures.get(Textures::Background));
			sf::Texture bgb(textures.get(Textures::BackgroundButtons));
			sf::Sprite cursor(textures.get(Textures::Cursor));
			text.setFont(fonts.get(Fonts::MainFont));
			sf::SoundBuffer buffer(soundbuffers.get(SoundBuffers::MainSound));

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
						
			text.setCharacterSize(30);
			text.setColor(sf::Color::Black);
			text.setPosition(290,540);

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



			GUI ExtrasMenu(3, buffer, bgb);
			ExtrasMenu.MenuButtons[0].Load(ExtrasMenu.ButtonsTexture, sf::IntRect(0,0,800,600), Encyclopedia, "Encyklopedia", 1);
			ExtrasMenu.MenuButtons[1].Load(ExtrasMenu.ButtonsTexture, sf::IntRect(800,0,800,600), Authors, "Autorzy", 1);
			ExtrasMenu.MenuButtons[2].Load(ExtrasMenu.ButtonsTexture, sf::IntRect(1600,0,800,600), Return, "Powrot", 0);

			//Dodawanie obserwatorów
			ExtrasMenu.MenuButtons[0].AddObservator(&number1);
			ExtrasMenu.MenuButtons[1].AddObservator(&number2);
			ExtrasMenu.MenuButtons[2].AddObservator(&number3);

			window.setFramerateLimit(60);
			bgmusic.play();

  
    while (Running)
    {
        while (window.pollEvent(event))
        {
			switch(event.type)
			{

				case sf::Event::Closed:
				{
					return (-1);
				}

				case sf::Event::KeyPressed:
				{
					if(event.key.code == sf::Keyboard::Escape) 
					return (-1);
				}

				case sf::Event::MouseButtonPressed:
				{
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						  for (int i=0; i<=((ExtrasMenu.MenuAmount)-1); ++i)
						  {
							if ((ExtrasMenu.MenuButtons[i].activated)==true)
								ExtrasMenu.MenuButtons[i].CallObservators();
								//return (ExtrasMenu.MenuButtons[i].move);
						  }
					}
				}

			 default: break;
			}
        }
   

       cursor.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));


		sf::Vector2i MousePosition=sf::Mouse::getPosition(window);

	    window.clear();	
		window.draw(background);
		
		ExtrasMenu.IsStillActive(MousePosition);
		ExtrasMenu.IsActivated(MousePosition, window, text);

		window.draw(cursor);
		window.draw(text);
        window.display();

		if(this->Changed==1)
			return this->WhereMove; 
    }
	

    //Never reaching this point normally, but just in case, exit the application
    return (-1);
};
