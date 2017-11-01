#include "Ball.h"

Ball::Ball(int width, int height, sf::Color color)
{
	this->height = (float)height;
	this->width = (float)width;

	this->startSpeed = (float)(height >> BIT_SHIFT_START_SPEED);

	this->size = (float)((width + height) >> BIT_SHIFT_BALL_SIZE);

	this->ball[0].color = color;
	this->ball[1].color = color;
	this->ball[2].color = color;
	this->ball[3].color = color;

	reset();
}

void Ball::update(Player * player, Bot * bot, float& MAX_ANGLE, float& SPEED_JUMP, float& HIT_ANGLE_MOD)
{
	/* Moves Ball */
	pos.x += vel.x;
	pos.y += vel.y;

	/* Bounces Off Walls */
	if (pos.x - size < 0)
	{
		pos.x = size;
		vel.x = 0.f - vel.x;
	} else if (pos.x + size > width)
	{
		pos.x = width - size;
		vel.x = 0.f - vel.x;
	}

	/* Resets When Hitting Top Or Bottom */
	if (pos.y - size < 0)
	{
		pos.y = (height / 2.f);
		pos.x = (width / 2.f);
		vel.y = -startSpeed;
		vel.x = 0;
		player->moveCenter();
		bot->moveCenter();
		playerWin();
	} else if (pos.y + size > height)
	{
		pos.y = (height / 2.f);
		pos.x = (width / 2.f);
		vel.y = startSpeed;
		vel.x = 0;
		player->moveCenter();
		bot->moveCenter();
		botWin();
	}

	if (vel.y > (player->paddleHeight + bot->paddleHeight))
	{
		vel.y = (player->paddleHeight + bot->paddleHeight);
	}

	if (pos.y + size > player->pos.y - player->paddleHeight &&
		pos.y - size < player->pos.y + player->paddleHeight) //Checks to see if it is on same y as player
	{
		if (pos.x - size < player->pos.x + player->paddleWidth &&
			pos.x + size > player->pos.x - player->paddleWidth) // if it is on same x as player
		{
			pos.y = player->pos.y - player->paddleHeight - size;
			vel.y = 0 - vel.y * SPEED_JUMP; // Makes Slightly Higher

			if (abs(player->vel / HIT_ANGLE_MOD) < MIN_STILL_MOD / HIT_ANGLE_MOD)
			{
				vel.x *= MIN_STILL_MOD;
			} else
			{
				vel.x = fmaxf(abs(vel.x), 1) * (player->vel / HIT_ANGLE_MOD);
			}
		}
	} 
	if (pos.y - size < bot->pos.y + bot->paddleHeight &&
		pos.y + size> bot->pos.y - player->paddleHeight) //Checks to see if it is on same y as bot
	{
		if (pos.x - size < bot->pos.x + bot->paddleWidth &&
			pos.x + size > bot->pos.x - bot->paddleWidth) // if it is on same x as bot
		{
			pos.y = bot->pos.y + size + bot->paddleHeight; // Resets y to remove 
			vel.y = 0 - vel.y * SPEED_JUMP; // Makes Slightly Higher
			
			if (abs(bot->vel / HIT_ANGLE_MOD) < MIN_STILL_MOD / HIT_ANGLE_MOD)
			{
				vel.x *= MIN_STILL_MOD;
			} else
			{
				vel.x = fmaxf(abs(vel.x), 1) * (bot->vel / HIT_ANGLE_MOD);
			}
		}
	}

	if (vel.x > abs(vel.y) * MAX_ANGLE)
	{
		vel.x = abs(vel.y) * MAX_ANGLE;
	} else if (vel.x < -abs(vel.y) * MAX_ANGLE)
	{
		vel.x = -abs(vel.y) * MAX_ANGLE;
	}

	/* Draw Ball */
	ball[0].position = sf::Vector2f(pos.x - size, pos.y - size);
	ball[1].position = sf::Vector2f(pos.x + size, pos.y - size);
	ball[2].position = sf::Vector2f(pos.x - size, pos.y + size);
	ball[3].position = sf::Vector2f(pos.x + size, pos.y + size);
}

void Ball::playerWin()
{
	playerScore++;
}

void Ball::botWin()
{
	botScore++;
}

void Ball::reset()
{
	playerScore = 0;
	botScore = 0;

	this->vel.x = 0;
	this->vel.y = startSpeed;

	this->pos.x = (width / 2);
	this->pos.y = (height / 2);
}
