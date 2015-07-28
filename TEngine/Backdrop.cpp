#include "Backdrop.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>


void Backdrop::render(sf::RenderWindow &win)
{
	std::cout << pathToTexture << std::endl;
	win.draw(backS);
}

Backdrop::Backdrop(std::string path2file, float scale)
{
	pathToTexture = path2file;
	std::cout << path2file << "..";
	sf::Texture texture;
	if (!texture.loadFromFile("Resources/Island.png"))
	{
		std::cout << "Could not load texture from file!" << std::endl;
	}
	else
	{
		std::cout << "Loaded!" << std::endl;
		this->back = texture;
	}
	sf::Sprite body;
	body.setTexture(this->back);
	this->backS = body;
	this->backS.setScale(sf::Vector2f(scale, scale));
	
}


Backdrop::~Backdrop()
{
}
