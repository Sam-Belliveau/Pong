#include "Player.h"
Player::Player(int width, int height, sf::Color color)
{
	this->height = (float)height;
	this->width = (float)width;

	this->paddleHeight = (float)(height >> BIT_SHIFT_PADDLE_HEIGHT);
	this->paddleWidth  = (float)(width >> BIT_SHIFT_PADDLE_WIDTH);
	this->speed = (float)(width >> BIT_SHIFT_SPEED);

	this->vel = 0;

	this->pos.x = (float)(width >> 1);
	this->pos.y = (float)(height - (height >> BIT_SHIFT_HEIGHT));

	this->paddle[0].color = color;
	this->paddle[1].color = color;
	this->paddle[2].color = color;
	this->paddle[3].color = color;
}

void Player::update()
{
	/* Moves Paddle */
	pos.x += vel;
	vel *= FRICTION;

	if (abs(vel) < MIN_SPEED)
	{
		vel = 0.f;
	}

	/* Wall Colision */
	if (pos.x - paddleWidth < 0)
	{
		pos.x = paddleWidth;
		vel = 0;
	} 
	else if (pos.x + paddleWidth > width)
	{
		pos.x = width - paddleWidth;
		vel = 0;
	}

	/* Draws Paddle */
	paddle[0].position = sf::Vector2f(pos.x - paddleWidth, pos.y - paddleHeight);
	paddle[1].position = sf::Vector2f(pos.x + paddleWidth, pos.y - paddleHeight);
	paddle[2].position = sf::Vector2f(pos.x - paddleWidth, pos.y + paddleHeight);
	paddle[3].position = sf::Vector2f(pos.x + paddleWidth, pos.y + paddleHeight);
}

void Player::moveRight()
{
	vel += speed;
}

void Player::moveLeft()
{
	vel -= speed;
}

void Player::moveCenter()
{
	vel = ((width / 2) - pos.x) / BIT_SHIFT_SPEED;
}
