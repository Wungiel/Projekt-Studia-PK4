#include "Listeners.h"
#include "Button.h"

int MoveListeners::Activated(Button &observed)
{
	return observed.move;
};


int ChangeListeners::Activated(Button &observed)
{
	std::cout << "Aktywacja ChangeListenera" << std::endl;
	return observed.move;
};

int EventListeners::Activated(Button &observed)
{
	std::cout << "Aktywacja EventListenera" << std::endl;
	return observed.move;
};

int CalculateListeners::Activated(Button &observed)
{
	std::cout << "Aktywacja CalculateListenera" << std::endl;
	return observed.move;
};
