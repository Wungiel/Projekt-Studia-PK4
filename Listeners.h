#pragma once
#include  <iostream>

//Klasa abstrakcyjna Listener, do przyszłej obsługi obserwatorów. Będzie: 
//move, do zmiany stanu gamestate - wymaga tylko numeru stanu, do którego przechodzimy
//change, do zmiany gamemode (by np. po kliknięciu na pomieszczenie pokazywały się jego własności) - potrzebujemy numeru trybu
//event, do włączania eventów 
//calculate, do zmiany stanów liczbowych - potrzebujemy gamestate w którym obecnie operujemy, zmiany wartości oraz określenia, jaką wartość zmieniamy

class Button;

class Listeners
{
public:
	virtual int Activated(Button &observed) = 0;
};

class MoveListeners : public Listeners
{
public:
	virtual int Activated(Button &observed);

};

class ChangeListeners : public Listeners
{
public:
	virtual int Activated(Button &observed);
};

class EventListeners : public Listeners
{
public:
	virtual int Activated(Button &observed);
};

class CalculateListeners : public Listeners
{
public:
	virtual int Activated(Button &observed);
};


