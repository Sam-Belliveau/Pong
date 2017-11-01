#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"

class Bot
{
public:
	Bot(int width, int height, sf::Color color);

	sf::VertexArray paddle = sf::VertexArray(sf::TrianglesStrip, 4);
	sf::Vector2f pos;

	float vel;
	float speed;
	float paddleHeight;
	float paddleWidth;

	void update(float x, float bVel, float& BOT_ANGLE_MOD, float& MAX_ANGLE, float& HIT_ANGLE_MOD);
	void moveRight();
	void moveLeft();

	void moveCenter();

	float height;
	float width;
};
