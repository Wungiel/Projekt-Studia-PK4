#include "Button.h"

void Button::Load (sf::Texture& texture, sf::IntRect areatexture, sf::IntRect area, std::string name, int wheremove)
	{
		this->move=wheremove;
		this->bsprite.setTexture(texture);
		this->bsprite.setTextureRect(areatexture);
		this->barea=area;
		this->activated=false;
		this->bname=name;
	};

void Button::AddObservator (Listeners * Observator)
{
	this->observators.push_back(Observator);
};

void Button::CallObservators(void)
{
	for (int i=0; i < this->observators.size(); ++i)
	{
		this->observators[i]->Activated(*this);
	}
};

Button::Button (void)
	{
	}

Button::Button (sf::Texture& texture, sf::IntRect areatexture, sf::IntRect area, std::string name, int wheremove)
	{
		move=wheremove;
		bsprite.setTexture(texture);
		bsprite.setTextureRect(areatexture);
		barea=area;
		activated=false;
		bname=name;
	};

