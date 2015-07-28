//*************************************
//*		        TEngine               *
//*************************************
//  Usado para: [nombre del juego xD]
//  (C) TajamSoft (Tatjam & Tajampi)
//  Graficos Tajampi
//  Codigo Tatjam
//
// Gracias por participar en el stream!


#include <SFML/Graphics.hpp>
#include <iostream>

#include "Player.h"
#include "Backdrop.h"

#include "HealthBar.h"
#define SCALE 4

int windowW = 800;
int windowH = 450;


//States:
//
//0 = Menu
//1 = Game
//2 = GameSetupPlayer
//3 = GameSetupScenery

using namespace std;

int main()
{

	int state = 0;  //Menu

	cout << "Setting up SFML!" << endl;
    sf::RenderWindow window(sf::VideoMode(windowW, windowH), "Fighting Game", sf::Style::Close);
	sf::View view(sf::Rect<float>(0, 0, window.getSize().x, window.getSize().y));
	window.setView(view);

	

	cout << "Loading Menu backdrop" << endl;
	//Backdrops:
	sf::Texture menuBackTex = sf::Texture();
	if (!menuBackTex.loadFromFile("Resources/Backdrop/Island.png"))
	{
		cout << "Failed to load ISLAND menu background..." << endl;
	}
	else
	{
		cout << "Loaded!" << endl;
	}
	sf::Sprite menuBackSprite = sf::Sprite();
	menuBackSprite.setTexture(menuBackTex);
	menuBackSprite.setScale(2.f, 2.f);
	

	sf::Texture selectBackTex = sf::Texture();
	sf::Sprite selectBackSprite = sf::Sprite();
	selectBackSprite.setScale(2.f, 2.f);

	sf::Texture levelBackTex = sf::Texture();
	sf::Sprite levelBackSprite = sf::Sprite();
	//TEXTURES SHOULD NOT BE APPLIED:
	levelBackTex.loadFromFile("Resources/Backdrop/MountainRoad.png");
	levelBackSprite.setTexture(levelBackTex);
	levelBackSprite.setScale(2.f, 2.f);

	sf::Clock mouseClock = sf::Clock();

	window.setFramerateLimit(60);



	Player p = Player(SCALE, 400.f);
	Player p2 = Player(SCALE, 400.f);
	p.body.setPosition(25, 180);
	p2.body.setPosition(775, 180);
	p2.body.setScale(-p2.body.getScale().x, p2.body.getScale().y);

	bool loadPlayers = true;
	bool loadFrames = true;
	bool p2Selecting = false;

	int pID;
	int p2ID;

	HealthBar pBar = HealthBar(p.health);
	HealthBar p2Bar = HealthBar(p2.health);
	

	//Menu related:




	//Selected:
	//
	//0 = Play
	//1 = Options?
	//2 = Exit

	int selected = 0;  

	sf::Font font = sf::Font();
	
	font.loadFromFile("Resources/Font/8bitwonder.ttf");

	sf::Text playText = sf::Text();
	playText.setString("Play");
	playText.setFont(font);
	playText.setPosition(view.getSize().x / 2 - 40, view.getSize().y / 2 - 20);
	playText.setColor(sf::Color(255, 255, 255, 255));

	sf::Text exitText = sf::Text();
	exitText.setString("Exit");
	exitText.setFont(font);
	exitText.setPosition(view.getSize().x / 2 - 35, view.getSize().y / 2 + 60);
	exitText.setColor(sf::Color(255, 255, 255, 255));

	sf::Texture test = sf::Texture();
	test.loadFromFile("Resources/Player/Punch.png");
	

	sf::CircleShape selectTriangle = sf::CircleShape(18, 3);

	selectTriangle.setRotation(90.0f);
	
	sf::Time deltaTime;
	sf::Clock clock = sf::Clock();

	sf::Clock sinClock = sf::Clock();

	//Frames:
	sf::Texture presleyFrameTex;
	sf::Sprite presleyFrameSprite;

	sf::Texture gentlemanFrameTex;
	sf::Sprite gentlemanFrameSprite;

	bool isRunning = true;


	bool wasMousePressed = false;

    while (window.isOpen() && isRunning)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
			switch (event.type)
			{
				case(sf::Event::Closed):
					window.close();
			}
			
        }	

		deltaTime = clock.restart();
		sf::RectangleShape indicator = sf::RectangleShape();
		//Game:
		if (state == 1)
		{
			if (loadPlayers)
			{
	
				cout << "Setting up players!" << endl;
				p.setup(0);
				p2.setup(0);
				loadPlayers = false;
				p.playAnim(1);
				p2.playAnim(0);

				p2Bar.body.setPosition(800.f - 250.f, 0.0f);
				p2Bar.fill.setPosition(800.f - 250.f, 0.0f);
			}


			p.update(deltaTime.asSeconds());
			p2.update(deltaTime.asSeconds());

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && p.canMove)
			{
				p.body.move(-p.velocity * deltaTime.asSeconds(), 0);
				p.playAnim(1);
				
				/*if (p2.facing == 0)
				{
				p2.body.setScale(-p.body.getScale().x, p.body.getScale().y);
				p.facing = 1;
				}*/
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && p.canMove)
			{
				p.body.move(p.velocity * deltaTime.asSeconds(), 0);
				p.playAnim(1);
				
				/*if (p2.facing == 1)
				{
				p2.body.setScale(-p.body.getScale().x, p.body.getScale().y);
				p.facing = 0;
				}*/
			}
			else
			{
				p.playAnim(0);
			}


			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
			{
				p.punch(p2);
			}

			/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				p.body.move(0, -200 * deltaTime.asSeconds());
				p.body.setScale(p.body.getScale().x - 3.f * deltaTime.asSeconds(), p.body.getScale().x - 3.f * deltaTime.asSeconds());
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				p.body.move(0, 200 * deltaTime.asSeconds());
				p.body.setScale(p.body.getScale().x + 3.f * deltaTime.asSeconds(), p.body.getScale().x + 3.f * deltaTime.asSeconds());
			}*/

			//P2:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && p2.canMove)
			{
				p2.body.move(-p.velocity * deltaTime.asSeconds(), 0);
				p2.playAnim(1);
				/*if (p2.facing == 0)
				{
				p2.body.setScale(-p.body.getScale().x, p.body.getScale().y);
				p.facing = 1;
				}*/
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && p2.canMove)
			{
				p2.body.move(p.velocity * deltaTime.asSeconds(), 0);
				p2.playAnim(1);
				/*if (p2.facing == 1)
				{
				p2.body.setScale(-p.body.getScale().x, p.body.getScale().y);
				p.facing = 0;
				}*/
			}
			else
			{
				p2.playAnim(0);
			}

			//ATACK:

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
			{
				p2.punch(p);
			}


			/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				p2.body.move(0, -200 * deltaTime.asSeconds());
				p2.body.setScale(p2.body.getScale().x - 3.f * deltaTime.asSeconds(), p2.body.getScale().x - 3.f * deltaTime.asSeconds());
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				p2.body.move(0, 200 * deltaTime.asSeconds());
				p2.body.setScale(p2.body.getScale().x + 3.f * deltaTime.asSeconds(), p2.body.getScale().x + 3.f * deltaTime.asSeconds());
			}*/


			if (p2.body.getGlobalBounds().intersects(p.body.getGlobalBounds()))
			{
				/*p.speed = -200;
				p2.speed = 200;*/
				p.onCollision();
				p2.onCollision();
			}

			if (p.body.getPosition().x < 5)
			{
				p.body.setPosition(5, p.body.getPosition().y);
			}
			if (p2.body.getPosition().x > 790)
			{
				p2.body.setPosition(790, p2.body.getPosition().y);
			}
			window.clear();

			window.draw(levelBackSprite);

			

			if (p.body.getScale().x > p2.body.getScale().x)
			{
				p2.render(window);
				p.render(window);
			}
			else
			{
				p.render(window);
				p2.render(window);
			}

			pBar.update();
			window.draw(pBar.body);
			window.draw(pBar.fill);
			window.draw(p2Bar.body);
			window.draw(p2Bar.fill);

			window.display();
		}
		//Menu:
		else if (state == 0)
		{

			if (selected == 0)
			{
				selectTriangle.setPosition(playText.getPosition().x - 40, playText.getPosition().y + 3);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				{
					selected = 1;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					state = 2;
				}
				playText.setPosition(playText.getPosition().x, playText.getPosition().y + sin(-sinClock.getElapsedTime().asSeconds())/8);
				exitText.setPosition(view.getSize().x / 2 - 35, view.getSize().y / 2 + 60);
			}
			else if (selected == 1)
			{
				selectTriangle.setPosition(exitText.getPosition().x - 40, exitText.getPosition().y + 3);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				{
					selected = 0;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					isRunning = false;
				}
				exitText.setPosition(exitText.getPosition().x, exitText.getPosition().y + sin(-sinClock.getElapsedTime().asSeconds()) / 8);
				playText.setPosition(view.getSize().x / 2 - 40, view.getSize().y / 2 - 20);
			}

			window.clear();
			window.draw(menuBackSprite);
			window.draw(playText);
			window.draw(exitText);
			window.draw(selectTriangle);
			window.display();
		}
		//Player Select:
		else if (state == 2)
		{
			if (loadFrames)
			{

				cout << "Loading backdrop...";
				if (!selectBackTex.loadFromFile("Resources/Backdrop/SelectBack.png"))
				{
					cout << "Failed! " << endl;
				}
				else
				{
					cout << "Loaded!" << endl;
				}
				selectBackSprite.setTexture(selectBackTex);

				cout << "Loading frames..." << endl;

				cout << "Loading Presley's frame..";
				if (!presleyFrameTex.loadFromFile("Resources/Player/Frame.png"))
				{
					cout << "Failed to load texture " << endl;
				}
				else
				{
					cout << "Loaded!" << endl;
				}
				presleyFrameSprite.setTexture(presleyFrameTex);
				presleyFrameSprite.setScale(3.0f, 3.0f);
				presleyFrameSprite.setPosition(15.f, 15.f);
				loadFrames = false;
			}


			
			if (sf::Mouse::getPosition(window).x > presleyFrameSprite.getPosition().x - presleyFrameSprite.getOrigin().x &&
				sf::Mouse::getPosition(window).x < (presleyFrameSprite.getPosition().x +
				presleyFrameSprite.getGlobalBounds().width - presleyFrameSprite.getOrigin().x))
			{
				if (sf::Mouse::getPosition(window).y > presleyFrameSprite.getPosition().y - presleyFrameSprite.getOrigin().y &&
					sf::Mouse::getPosition(window).y < (presleyFrameSprite.getPosition().y - presleyFrameSprite.getOrigin().y +
					presleyFrameSprite.getGlobalBounds().height - presleyFrameSprite.getOrigin().y))
				{
					presleyFrameSprite.setScale(3.f + sin(sinClock.getElapsedTime().asSeconds()*10) / 10, 3.f + sin(sinClock.getElapsedTime().asSeconds()*10) / 10);
					if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
					{
						if (!wasMousePressed)
						{

							if (p2Selecting)
							{
								cout << "Player 2 selected. Starting game!" << endl;
								p2ID = 0;
								state = 1;
								p2Selecting = false;
							}
							else
							{
								cout << "Player 1 selected. Waiting for player 2!" << endl;
								pID = 0;
								p2Selecting = true;
							}
							if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
							{
								if (!wasMousePressed)
								{

									mouseClock.restart();
									wasMousePressed = true;
									cout << "Mouse wait..." << endl;
								}
							}

							
						}
					}
				}
			}
			else
			{
				presleyFrameSprite.setScale(3.f, 3.f);
			}

			window.clear();
			window.draw(selectBackSprite);
			window.draw(presleyFrameSprite);

			window.display();
		}

		if (wasMousePressed)
		{
			if (mouseClock.getElapsedTime().asMilliseconds() > 250)
			{
				cout << "Mouse restored!" << endl;
				wasMousePressed = false;
			}
		}
		//std::cout << deltaTime.asSeconds() << std::endl;
    }

    return 0;
}