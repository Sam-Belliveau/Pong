#include "Bot.h"

Bot::Bot(int width, int height, sf::Color color)
{
	this->height = (float)height;
	this->width = (float)width;

	this->paddleHeight = (float)(height >> BIT_SHIFT_PADDLE_HEIGHT);
	this->paddleWidth = (float)(width >> BIT_SHIFT_PADDLE_WIDTH);
	this->speed = (float)(width >> BIT_SHIFT_SPEED);

	this->vel = 0;

	this->pos.x = (float)(width >> 1);
	this->pos.y = (float)(height >> BIT_SHIFT_HEIGHT);

	this->paddle[0].color = color;
	this->paddle[1].color = color;
	this->paddle[2].color = color;
	this->paddle[3].color = color;
}

void Bot::update(float x, float bVel, float& BOT_ANGLE_MOD, float& MAX_ANGLE, float& HIT_ANGLE_MOD)
{
	/* Updating Position */
	pos.x += vel;
	vel *= FRICTION;

	if (abs(vel) < MIN_SPEED)
	{
		vel = 0.f;
	}

	/* AI Setting */
	if (x + bVel + (height / powf(2, BIT_SHIFT_BALL_SIZE)) > pos.x + (paddleWidth / (((FRICTION - 1) / (MAX_ANGLE * BOT_ANGLE_MOD)) + 1)) + vel)
	{
		moveRight();
	} 
	if (x + bVel - (height / powf(2, BIT_SHIFT_BALL_SIZE)) < pos.x - (paddleWidth / (((FRICTION - 1) / (MAX_ANGLE * BOT_ANGLE_MOD)) + 1)) + vel)
	{
		moveLeft();
	}

	/* Bounces Off Walls */
	if (pos.x - paddleWidth < 0)
	{
		pos.x = paddleWidth;
		vel = 0 - vel / 2.f;
	}
	else if (pos.x + paddleWidth > width)
	{
		pos.x = width - paddleWidth;
		vel = 0 - vel / 2.f;
	}

	/* Draw Paddle */
	paddle[0].position = sf::Vector2f(pos.x - paddleWidth, pos.y - paddleHeight);
	paddle[1].position = sf::Vector2f(pos.x + paddleWidth, pos.y - paddleHeight);
	paddle[2].position = sf::Vector2f(pos.x - paddleWidth, pos.y + paddleHeight);
	paddle[3].position = sf::Vector2f(pos.x + paddleWidth, pos.y + paddleHeight);
}

void Bot::moveRight()
{
	vel += speed;
}

void Bot::moveLeft()
{
	vel -= speed;
}
void Bot::moveCenter()
{
	vel = ((width / 2) - pos.x) / BIT_SHIFT_SPEED;
}
