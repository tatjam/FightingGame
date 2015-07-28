#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Player
{
	
public:
	float health = 100.f;
	float damage;
	float abDamage;

	bool canMove = true;

	bool doAnim = true;

	bool punchAvailable = true;

	bool doingPunch = false;

	bool justCollided = false;

	//True = Left
	//False = Right
	bool activeHand = false;

	sf::Clock animClock;
	sf::Clock collClock;

	float speed = 0;

	float velocity = 200.f;
	int facing = 0;   //0 = Right, 1 = Left
	sf::Texture textures[11];
	sf::Sprite body;

	void render(sf::RenderWindow &win);
	void setup(int pId);
	void update(float deltaTime);

	void onCollision();
	
	int playingAnim = 0;

	int animFrame = 0;


	//Anim ids:
	//
	//0 = Idle
	//1 = Run
	//2 = Jump

	
	void playAnim(int id);

	//Has to be run every frame
	void updateAnim();

	void punch(Player &p2);

	void duck();

	void kick();

	Player(float, float);
	~Player();
};

