#pragma once
#include <SFML/Graphics.hpp>
//This one is purely meant to be inherited by other classes, so the main loop handles all
//Only implements "update()", "draw()"

class GameObject
{
public:
	void draw(sf::RenderWindow);
	void update();

	void getShape();  //REQUIREMENT if you want your object to render!

	GameObject();
	~GameObject();
};

