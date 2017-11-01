#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"

class Player
{
public:
	Player(int width, int height, sf::Color color);

	sf::VertexArray paddle = sf::VertexArray(sf::TrianglesStrip, 4);
	sf::Vector2f pos;

	float vel;
	float speed;
	float paddleHeight;
	float paddleWidth;

	void update();
	void moveRight();
	void moveLeft();
	void moveCenter();

	float height;
	float width;
};
