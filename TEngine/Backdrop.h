#pragma once
#include <SFML/Graphics.hpp>

class Backdrop
{
private:


public:
	sf::Texture back;
	sf::Sprite backS;

	std::string pathToTexture;

	void render(sf::RenderWindow &w);


	Backdrop(std::string path2file, float);
	~Backdrop();
};

