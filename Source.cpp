#include <iostream>
#include <SFML/Graphics.hpp>
#include <ctime>
#include <time.h>
#include <cstdlib>

using namespace sf;
using namespace std;

int main()
{
	RenderWindow window(VideoMode(800, 400), "Sea Battle Game");

	//Menu menu(window.getSize().x, window.getSize().y);

	int tile_width = 32;
	int Logic_map[12][12];
	int View_map[12][12];

	bool isMove = false;
	float dx = 0, dy = 0;

	Texture texturemap, textureships, texture_sub, texture_dest, texture_cruiser, texture_betteship;

	texturemap.loadFromFile("game_tiles.png");
	texture_betteship.loadFromFile("battleship(128).png");
	texture_cruiser.loadFromFile("cruiser(96).png");
	texture_dest.loadFromFile("destroyer(64).png");
	texture_sub.loadFromFile("submarine(32).png");


	Sprite spritemap, sprite_sub, sprite_dest, sprite_cruiser, sprite_betteship;

	spritemap.setTexture(texturemap);
	sprite_betteship.setTexture(texture_betteship);
	sprite_cruiser.setTexture(texture_cruiser);
	sprite_dest.setTexture(texture_dest);
	sprite_sub.setTexture(texture_sub);

	spritemap.setPosition(300, 300);
	sprite_betteship.setPosition(0, 0);
	sprite_cruiser.setPosition(150, 0);
	sprite_dest.setPosition(250, 0);
	sprite_sub.setPosition(350, 0);

	srand(time(NULL));

	for (int i = 1; i <= 10; i++)
		for (int j = 1; j <= 10; j++)
		{
			View_map[i][j] = 0;
			if (rand() % 5 == 0)Logic_map[i][j] = 3;
			else Logic_map[i][j] = 1;
		}
/*
	for (int i = 1; i <= 10; i++)
	{
		for (int j = 1; j <= 10; j++)
		{
			int count = 0;
			if (Logic_map[i][j] == 4) continue;
			if (Logic_map[i+1][j] == 4) count++;
			if (Logic_map[i][j+1] == 4) count++;
			if (Logic_map[i-1][j] == 4) count++;
			if (Logic_map[i][j-1] == 4) count++;
			if (Logic_map[i+1][j+1] == 4) count++;
			if (Logic_map[i-1][j-1] == 4) count++;
			if (Logic_map[i-1][j+1] == 4) count++;
			if (Logic_map[i+1][j-1] == 4) count++;
			Logic_map[i][j] = count;
		}
	}
*/
	while (window.isOpen())
	{
		Vector2i pos = Mouse::getPosition(window);
		int x = pos.x / tile_width;
		int y = pos.y / tile_width;

		Event event;
		while (window.pollEvent(event)) 
		{
			if (event.type == Event::Closed)
				window.close();
				
			if (Keyboard::isKeyPressed(Keyboard::Escape))
				window.close();

			if (event.type == Event::MouseButtonPressed)
			{
				if (event.key.code == Mouse::Left)
				{
					View_map[x][y] = Logic_map[x][y];

					if (sprite_betteship.getGlobalBounds().contains(pos.x, pos.y))
					{
						isMove = true;
						dx = pos.x - sprite_betteship.getPosition().x;
						dy = pos.y - sprite_betteship.getPosition().y;
					}
				}
				else if (event.key.code == Mouse::Right)
				{
					Logic_map[x][y] = 2;
				}
			}
			if (event.type == Event::MouseButtonReleased)
			{
				if (event.key.code == Mouse::Left)
				{
					isMove = false;
				}
			}
		}
			if (isMove)
			{
			sprite_betteship.setPosition(pos.x - dx, pos.y - dy);
			}

		window.clear(Color::White);
		//menu.draw(window);
		for (int i = 1; i <= 10; i++)
			for (int j = 1; j <= 10; j++)
			{
				//View_map[i][j] = Logic_map[i][j];
				spritemap.setTextureRect(IntRect(View_map[i][j] * tile_width, 0, tile_width, tile_width));
				spritemap.setPosition(i * tile_width, j * tile_width);
				window.draw(spritemap);
			}	

		window.draw(sprite_betteship);
		window.draw(sprite_cruiser);
		window.draw(sprite_dest);
		window.draw(sprite_sub);

		window.display();
	}

	return 0;
}