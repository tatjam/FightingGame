#include "Player.h"
#include <string>
#include <vector>
#include <iostream>
#include "SFML/Graphics.hpp"


void Player::render(sf::RenderWindow &win)
{
	win.draw(body);
}

void Player::setup(int pId)
{
	animClock = sf::Clock();
	for (int i = 0; i < 10; i++)
	{
		sf::Texture texture;
		std::string toLoad = "";

		if (i == 0)
			toLoad = "Resources/Player/Idle0.png";
		if (i == 1)
			toLoad = "Resources/Player/Idle1.png";
		if (i == 2)
			toLoad = "Resources/Player/Idle2.png";
		if (i == 3)
			toLoad = "Resources/Player/Punch.png";
		if (i == 4)
			toLoad = "Resources/Player/Punch1.png";
		if (i == 5)
			toLoad = "Resources/Player/Run0.png";
		if (i == 6)
			toLoad = "Resources/Player/Run1.png";
		if (i == 7)
			toLoad = "Resources/Player/Run2.png";
		if (i == 8)
			toLoad = "Resources/Player/Duck0.png";
		if (i == 9)
			toLoad = "Resources/Player/Duck1.png";
		if (i == 10)
			toLoad = "Resources/Player/Duck2.png";


		std::cout << "Loading " << toLoad << "...";
		if (!texture.loadFromFile(toLoad))
		{
			std::cout << "Could not load texture from file!" << std::endl;
		}
		else
		{
			std::cout << "Loaded!" << std::endl;
			this->textures[i] = texture;
		}

	}

	body.setTexture(textures[0]);
}

void Player::onCollision()
{
	canMove = false;
	justCollided = true;
	collClock.restart();
}

Player::Player(float scale, float speed)
{
	collClock = sf::Clock();

	this->velocity = speed;

	/*
	sf::Texture texture;
	if (!texture.loadFromFile("Resources/Player/Idle0.png"))
	{
		std::cout << "Could not load texture from file!" << std::endl;
	}
	else
	{
		//std::cout << "Loaded!" << std::endl;
		this->textures[0] = texture; 
	}
	sf::Sprite body;
	body.setTexture(textures[0]);
	*/

	
	sf::Sprite body;
	this->body = body;
	this->body.setScale(sf::Vector2f(scale, scale));
}


void Player::update(float deltaTime)
{
	updateAnim();
	

	if (abs(speed * deltaTime) < 1.0f)
	{
		canMove = true;
	}

	if (!(speed <= 0.2f) || !(speed >= 0.2f))
	{

		if (speed > 0)
		{

			if (speed - (10000.f * deltaTime) < 0)
			{
				speed = 0;
			}
			else
			{
				speed -= 10000.f * deltaTime;
			}
		}
		else
		{
			if (speed + (10000.f * deltaTime) > 0)
			{
				speed = 0;
			}
			else
			{
				speed += 10000.f * deltaTime;
			}
		}

		std::cout << speed << std::endl;
		body.move(speed * deltaTime, 0.0f);
	}
	else
	{
		speed = 0;
		canMove = true;
	}

}

void Player::playAnim(int id)
{
	if (playingAnim != id)
	{
		playingAnim = id;
		animFrame = 0;
		animClock.restart();
	}
}

void Player::punch(Player &p2)
{
	if (punchAvailable)
	{
		canMove = false;
		playingAnim = 0;
		doAnim = false;
		doingPunch = true;
		animClock.restart();
		if (activeHand == false)
		{
			body.setTexture(textures[3], true);
			activeHand = true;
		}
		else
		{
			body.setTexture(textures[4], true);
			activeHand = false;
		}

		//Actual damage:

		//If we are player 2:
		if (body.getScale().x < 0)
		{
			if (p2.body.getGlobalBounds().contains(sf::Vector2f(body.getPosition().x - 10, body.getPosition().y)));
			{
				p2.health -= 1.0f;
				p2.speed = -20.f;
			}
		}
		else
		{
			if (p2.body.getGlobalBounds().contains(sf::Vector2f(body.getPosition().x + 10, body.getPosition().y)));
			{
				p2.health -= 1.0f;
				p2.speed = 20.f;
			}
		}

		punchAvailable = false;
	}
	
}

void Player::updateAnim()
{
	if (doAnim)
	{

		if (playingAnim == 0 && animClock.getElapsedTime().asMilliseconds() > 500.f)
		{

			if (animFrame == 0)
			{
				body.setTexture(textures[0], true);
				animFrame = 1;
				animClock.restart();
				return;
			}
			if (animFrame == 1)
			{
				body.setTexture(textures[1], true);
				animFrame = 2;
				animClock.restart();
				return;
			}
			if (animFrame == 2)
			{
				if ((rand() % 100) < 50)
					body.setTexture(textures[0], true);
				else
					body.setTexture(textures[2], true);
				animFrame = 0;
				animClock.restart();
				return;
			}




		}
		if (playingAnim == 1 && animClock.getElapsedTime().asMilliseconds() > 200.f)
		{
			if (animFrame == 0)
			{
				body.setTexture(textures[5], true);
				animFrame = 1;
				animClock.restart();
				return;
			}
			if (animFrame == 1)
			{
				body.setTexture(textures[6], true);
				animFrame = 2;
				animClock.restart();
				return;
			}
			if (animFrame == 2)
			{
				body.setTexture(textures[5], true);
				animFrame = 3;
				animClock.restart();
				return;
			}
			if (animFrame == 3)
			{
				body.setTexture(textures[7], true);
				animFrame = 0;
				animClock.restart();
				return;
			}



		}
	}

	if (doingPunch && animClock.getElapsedTime().asMilliseconds() > 400)
	{
		doingPunch = false;
		punchAvailable = true;
		//animClock.restart();
		canMove = true;
		doAnim = true;
	}
	if (doingPunch)
	{
		canMove = false;
	}
}

Player::~Player()
{
}
