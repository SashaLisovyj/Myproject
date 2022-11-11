#include <iostream> //підклюяаємо бібліотеку вводу/виводу
#include <SFML/Graphics.hpp> //підклюяаємо бібліотеку SFML для роботи з графікою
#include <ctime> //підклюяаємо бібліотеку для генератора випадкових чисел

using namespace sf; //використовуємо простір імен sf
using namespace std; //використовуємо простір імен std

int main()
{
	RenderWindow window(VideoMode(800, 400), "Sea Battle Game"); //ствоюємо вікно з заголовком і розміром 800x600 пікселів

	//Menu menu(window.getSize().x, window.getSize().y);

	int tile_width = 32; //зміна, що відповідає за розмір однієї плитки
	int Logic_map[12][12]; //зміна, що відповідає за розмір логічного ігрового поля
	int View_map[12][12]; //зміна, що відповідає за розмір графічного ігрового поля

	bool isMove = false; //зміна, що відповідає за рух спрайтів
	float dx = 0, dy = 0; //зміні, що відповідає за визначення координат спрайтів

	Texture texturemap, textureships, texture_sub, texture_dest, texture_cruiser, texture_betteship; //створюємо текстури

	//завантажуємо png файл у текстуру
	texturemap.loadFromFile("game_tiles.png");
	texture_betteship.loadFromFile("battleship(128).png");
	texture_cruiser.loadFromFile("cruiser(96).png");
	texture_dest.loadFromFile("destroyer(64).png");
	texture_sub.loadFromFile("submarine(32).png");


	Sprite spritemap, sprite_sub, sprite_dest, sprite_cruiser, sprite_betteship; //створюємо спрайти

	//встановлюємо у спрайт текстури
	spritemap.setTexture(texturemap);
	sprite_betteship.setTexture(texture_betteship);
	sprite_cruiser.setTexture(texture_cruiser);
	sprite_dest.setTexture(texture_dest);
	sprite_sub.setTexture(texture_sub);

	//задаємо початкові позиції для спрайтів
	spritemap.setPosition(300, 300);
	sprite_betteship.setPosition(0, 0);
	sprite_cruiser.setPosition(150, 0);
	sprite_dest.setPosition(250, 0);
	sprite_sub.setPosition(350, 0);

	srand(time(NULL)); //функція для генерації випадкових чисел

	//створюємо ігрове поле розміром 10x10
	for (int i = 1; i <= 10; i++)
		for (int j = 1; j <= 10; j++)
		{
			View_map[i][j] = 0;//встановлюємо спрайт з індексом 0
			if (rand() % 5 == 0)Logic_map[i][j] = 3;//встановлюємо спрайт ворожого корабля якщо випадкове число дорівнює нулю
			else Logic_map[i][j] = 1;//якщо випадкове число не нуль то спрайт з індексом 1
		}

	while (window.isOpen()) //основний цикл, виконується до того як вікно не закриють
	{
		Vector2i pos = Mouse::getPosition(window); //отримуєм координати з мишки коли вона на вікні
		int x = pos.x / tile_width; // ділимо отриману координату x на розмір плитки
		int y = pos.y / tile_width; //ділимо отриману координату y на розмір плитки

		Event event; //створюємо об'єкт класу event 
		while (window.pollEvent(event))  //створюємо цикл щоб використовувати події
		{
			if (event.type == Event::Closed) // якщо натискаємо на кнопку закрити, то вікно закриється
				window.close();
				
			if (Keyboard::isKeyPressed(Keyboard::Escape)) // якщо натискаємо на клавішу Escape, то вікно закриється
				window.close();

			if (event.type == Event::MouseButtonPressed) // перевіряємо чи натискаємо ми на мишку
			{
				if (event.key.code == Mouse::Left) //якщо натискаємо на ліву кнопку то міняємо спрайт з індексом 0 на 1
				{
					View_map[x][y] = Logic_map[x][y];
					if (Logic_map[x][y] == 3)View_map[x][y] = 4; //  якщо на логічному полі є спрайт з індексом 3 то на графічному полі встановлюємо спрайт знищеного корабля

					if (sprite_betteship.getGlobalBounds().contains(pos.x, pos.y)) //отримуємо координати xy з сторін спрайту
					{
						//зміна руху получає значення 1 і зміні dx dy отримують місце розташування спрайту по xy
						isMove = true;
						dx = pos.x - sprite_betteship.getPosition().x;
						dy = pos.y - sprite_betteship.getPosition().y;
					}
				}
			}
			if (event.type == Event::MouseButtonReleased) // якщо ліву кнопку мишки не натискаємо то перестаємо рухати спрайт
			{
				if (event.key.code == Mouse::Left)
				{
					isMove = false;
				}
			}
		}
			if (isMove)//якщо isMove має значення 1 то мишкою встановлюємо нову позицію страйта 
			{
			sprite_betteship.setPosition(pos.x - dx, pos.y - dy);
			}

		window.clear(Color::White);//встановлюємо білий задній фон
		//menu.draw(window);
		for (int i = 1; i <= 10; i++)
			for (int j = 1; j <= 10; j++)
			{
				//View_map[i][j] = Logic_map[i][j];
				spritemap.setTextureRect(IntRect(View_map[i][j] * tile_width, 0, tile_width, tile_width)); //встановлюємо плитку потрібного нам індексу розміром 32x32
				spritemap.setPosition(i * tile_width, j * tile_width); //встановлюємо потрібну нам позицію 
				window.draw(spritemap);//виводимо на екран ігрову карту
			}	
		//виводимо на еран спрайти кораблів
		window.draw(sprite_betteship);
		window.draw(sprite_cruiser);
		window.draw(sprite_dest);
		window.draw(sprite_sub);

		//відображає на екрані вінрендерене вікно
		window.display();
	}

	return 0;
