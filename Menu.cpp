#include "Menu.h"

using namespace sf;

Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("arial.ttf"))
	{
		//error
	}

	menu[0].setFont(font);
	menu[0].setFillColor(Color::Red);
	menu[0].setString("Play");
	menu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_NUM_OF_ITTEMS + 1) * 1));

	menu[2].setFont(font);
	menu[2].setFillColor(Color::White);
	menu[2].setString("Exit");
	menu[2].setPosition(sf::Vector2f(width / 2, height / (MAX_NUM_OF_ITTEMS + 1) * 3));
}

Menu::~Menu()
{

}

void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_NUM_OF_ITTEMS, i++;)
	{
		//window.draw(menu[i]);
	}
}