#pragma once
#include "SFML/Graphics.hpp"
class HealthBar
{
public:

	sf::RectangleShape fill;
	sf::RectangleShape body;


	float* health;
	void update();

	HealthBar(float &health);
	~HealthBar();
};

