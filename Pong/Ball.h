#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Constants.h"
#include "Player.h"
#include "Bot.h"

class Ball
{
public:
	Ball(int width, int height, sf::Color color);
	void update(Player * player, Bot * bot, float& MAX_ANGLE, float& SPEED_JUMP, float& HIT_ANGLE_MOD);

	void playerWin();
	void botWin();
	void reset();

	unsigned int playerScore = 0, botScore = 0;

	float size = 10;
	float startSpeed;

	sf::Vector2f vel;
	sf::Vector2f pos;
	sf::VertexArray ball = sf::VertexArray(sf::TrianglesStrip, 4);

	float height;
	float width;
};