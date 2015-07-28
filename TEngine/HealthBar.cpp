#include "HealthBar.h"


HealthBar::HealthBar(float &health)
{
	fill = sf::RectangleShape();
	fill.setSize(sf::Vector2f(250.f, 15.f));
	fill.setFillColor(sf::Color::Red);

	body = sf::RectangleShape();
	body.setSize(sf::Vector2f(250.f, 15.f));
	body.setFillColor(sf::Color(120, 120, 120, 255));

	this->health = &health;
}

void HealthBar::update()
{
	fill.setSize(sf::Vector2f(*health * 2.5f, 15.f));
}

HealthBar::~HealthBar()
{
}
