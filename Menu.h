#pragma once
#include<SFML/Graphics.hpp>
#define MAX_NUM_OF_ITTEMS 2
class Menu
{
public:
	Menu(float width, float height);

	~Menu();

	void draw(sf::RenderWindow& window);
	void Moveup();
	void Movedown();


private:
	int selectedItemindex;
	sf::Font font;
	sf::Text menu[MAX_NUM_OF_ITTEMS];
};