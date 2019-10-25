#include <SFML/Graphics.hpp>
#include "map.h"
#include "view.h"
#include <vector>
#include <list>

using namespace sf;

class Player
{
public:
	String path;
	float x, y, one, two, left, right, dx, dy, speed = 0;
	int dir = 0; //Направление игрока
	Image image;
	Texture texture;
	Sprite sprite;

	Player(String File, int X, int Y, float One, float Two, float Left, float Right)
	{
		one = One, two = Two, left = Left, right = Right;
		path = File;
		image.loadFromFile(path);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X, y = Y;
		sprite.setTextureRect(IntRect(one, two, left, right));
	}

	void update(float time)
	{
		switch (dir)
		{
		case 0: dx = speed; dy = 0; break;
		case 1: dx = -speed; dy = 0; break;
		case 2: dx = 0; dy = speed; break;
		case 3: dx = 0; dy = -speed; break;
		}
		x += dx * time;
		y += dy * time;

		speed = 0;
		sprite.setPosition(x, y);
	}

	float getPlayersX() { return x; };
	float getPlayersY() { return y; };

	
};




// MAIN !  !  !  !  !  !
int main()
{
	//"ЭКРАН
	sf::RenderWindow window(sf::VideoMode(1600, 1000), L"Привет");
	
	Player player1("D:/SFML/SFML/hero.jpg", 100, 100, 77, 893, 88, 120);//1 игрок
	Player player2("D:/SFML/SFML/hero.jpg", 1400, 800, 429, 198, 79, 128);//2 игрок

	view1.setViewport(sf::FloatRect(0, 0, 0.5, 1));

	view2.setViewport(sf::FloatRect(0.5, 0, 0.5, 1));



	Image mapImage;
	mapImage.loadFromFile("D:/SFML/SFML/pixel.png");

	Texture mapTexture;
	mapTexture.loadFromImage(mapImage);

	Sprite mapSprite;
	mapSprite.setTexture(mapTexture);


	//Создаем время
	Clock clock;

	//ОСНОВНОЙ ЦИКЛ
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 100;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//Передвижение первого игрока
		if (Keyboard::isKeyPressed(Keyboard::W)) {
			player1.dir = 3; player1.speed = 0.1;
			kameraIgroka1(player1.getPlayersX(), player1.getPlayersY());//1
		}
		if (Keyboard::isKeyPressed(Keyboard::S)) {
			player1.dir = 2; player1.speed = 0.1;
			kameraIgroka1(player1.getPlayersX(), player1.getPlayersY());//1
		}
		if (Keyboard::isKeyPressed(Keyboard::A)) {
			player1.dir = 1; player1.speed = 0.1;
			kameraIgroka1(player1.getPlayersX(), player1.getPlayersY());//1
		}
		if (Keyboard::isKeyPressed(Keyboard::D)) {
			player1.dir = 0; player1.speed = 0.1;
			kameraIgroka1(player1.getPlayersX(), player1.getPlayersY());//1
		}

		//Передвижение второго игрока
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			player2.dir = 3; player2.speed = 0.1;
			kameraIgroka2(player2.getPlayersX(), player2.getPlayersY());//2
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			player2.dir = 2; player2.speed = 0.1;
			kameraIgroka2(player2.getPlayersX(), player2.getPlayersY());//2
		}
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			player2.dir = 1; player2.speed = 0.1;
			kameraIgroka2(player2.getPlayersX(), player2.getPlayersY());//2
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			player2.dir = 0; player2.speed = 0.1;
			kameraIgroka2(player2.getPlayersX(), player2.getPlayersY());//2
		}




		player2.update(time);
		player1.update(time);


		////


		window.clear(Color(42, 50, 91));

		window.setView(view1); // 1 КАМЕРА(СЛЕВА)

		//РИСУЕМ КАРТУ
		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ')  mapSprite.setTextureRect(IntRect(0, 0, 50, 50)); 
				if (TileMap[i][j] == '0')  mapSprite.setTextureRect(IntRect(256, 384, 50, 50));



				mapSprite.setPosition(j * 40, i * 40);

				window.draw(mapSprite);
			}
		window.draw(player1.sprite);
		window.draw(player2.sprite);

		window.setView(view2); // 2 КАМЕРА(СПРАВА)

		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ')  mapSprite.setTextureRect(IntRect(0, 0, 50, 50)); 
				if (TileMap[i][j] == '0')  mapSprite.setTextureRect(IntRect(256, 384, 50, 50));



				mapSprite.setPosition(j * 40, i * 40);

				window.draw(mapSprite);
			}
		window.draw(player1.sprite);
		window.draw(player2.sprite);







		window.display();
	}

	return 0;
}