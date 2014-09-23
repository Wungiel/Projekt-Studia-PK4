/* W programie poruszamy się za pomocą myszki. Program obsługuje lewy przycisk myszy oraz klawisz escape. Klawisz escape natychmiast wyłącza grę. 
Poruszając kursorem, podświetlają się obiekty na które można kliknąć. Tylko kliknięcie na:
- Wyjście i Extrasy (drzwi i plakat) w menu głównym
- Powrót (leżący luzem fragment zbroi) w menu extras
Powodują zmianę stanów gry. Pozostałe obiekty, ze względu na brak stanów gry do których mogą prowadzić, nie zmieniają stanu programu */



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


	namespace Textures
		{
		enum IDT
			{
			Background,
			BackgroundButtons,
			Cursor
			};
		}

	namespace Fonts
		{
		enum IDF
			{
			MainFont
			};
		}

	namespace SoundBuffers
		{
		enum IDS
			{
			MainSound
			};
		}


//w klasie zawarto: obsługę wyjątków oraz szablony
template <typename Resource, typename Identifier>
class ResourceManager
{
	public:
		void load(Identifier id, const std::string& filename)
		{
			// Create and load resource
			std::unique_ptr<Resource> resource(new Resource());
			if (!resource->loadFromFile(filename))
				throw std::runtime_error("Manager zasobów - nieudane ładowanie pliku" + filename);

			// If loading successful, insert resource to map
			insertResource(id, std::move(resource));
		};

		template <typename Parameter>

		Resource& get(Identifier id)
		{
			auto found = mResourceMap.find(id);
			assert(found != mResourceMap.end());

			return *found->second;
		};

		const Resource& get(Identifier id) const
			{
				auto found = mResourceMap.find(id);
				assert(found != mResourceMap.end());

				return *found->second;
			};


	private:
		void insertResource(Identifier id, std::unique_ptr<Resource> resource)
			{
				// Insert and check success
				auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
				assert(inserted.second);
			};


		std::map<Identifier, std::unique_ptr<Resource>>	mResourceMap;
};

class Button
{
public:
	int move; //wartość, jaką zwraca po kliknięciu przycisku klasa
	std::string bname;
	sf::Sprite bsprite; //wygląd naciśniętego przycisku; 
	sf::IntRect barea;
	bool activated;
	
	
	void Load (sf::Texture& texture, sf::IntRect areatexture, sf::IntRect area, std::string name, int wheremove)
	{
		this->move=wheremove;
		this->bsprite.setTexture(texture);
		this->bsprite.setTextureRect(areatexture);
		this->barea=area;
		this->activated=false;
		this->bname=name;
	};

	Button ()
	{
	}

	Button (sf::Texture& texture, sf::IntRect areatexture, sf::IntRect area, std::string name, int wheremove)
	{
		move=wheremove;
		bsprite.setTexture(texture);
		bsprite.setTextureRect(areatexture);
		barea=area;
		activated=false;
		bname=name;
	};
};

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

//Polimorfizm i dziedziczenie
class GameState
{
public :
    virtual int Run (sf::RenderWindow &window) = 0;
};

//State_Menu - nie używa resourcemanager, przechowuje dane potrzebne do wyświetlenia menu głównego
class State_Menu : public GameState
{
private:
    bool playing;

public:

    virtual int Run(sf::RenderWindow &window)
		{    
			sf::Event Event;
			bool Running = true;
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
        //When getting at alpha_max, we stop modifying the sprite
   

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
	}
};

//State_Extra - używa resourcemanager, przechowuje dane potrzebne do wyświetlenia menu extras
class State_Extra: public GameState
{
private:
    bool playing;

public:
	
    virtual int Run(sf::RenderWindow &window)
		{    
			sf::Event Event;
			bool Running = true;
			sf::Music bgmusic;
			sf::Text text;
			sf::Event event;
			int i;

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
							return (ExtrasMenu.MenuButtons[i].move);
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
    }
	

    //Never reaching this point normally, but just in case, exit the application
    return (-1);
	}
};

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


