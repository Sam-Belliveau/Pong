#include "SFML/Graphics.hpp"
#include <iostream>
#include "Bot.h"
#include "Ball.h"
#include "Player.h"

const int width		= 1280;
const int height	= 720;
const int lineHeight= 5;

const sf::Color front(224, 224, 224);
const sf::Color  line(128, 128, 128);
const sf::Color  text(196, 196, 196);
const sf::Color  back(32, 32, 32);

float MAX_ANGLE = 1.f;
float SPEED_JUMP = (1.f + (1.f / 28.f));
float BOT_ANGLE_MOD = (31.f / 32.f);
float HIT_ANGLE_MOD = 6.f;

const std::string modes[6] = { "1 - Super Easy", "2 - Easy", "3 - Normal", "4 - Hard", "5 - Brutal", "6 - Imposible" };
const float maxAngleSet[6] = { 0.5f, 1.f, 1.5f, 2.f, 2.5f, 3.f };
const float speedJumpSet[6] = { (1.f + (1.f / 64.f)), (1.f + (1.f / 32.f)), (1.f + (1.f / 28.f)), (1.f + (1.f / 24.f)), (1.f + (1.f / 20.f)), (1.f + (1.f / 16.f)) };
const float botAngleMod[6] = { (7.f / 8.f), (15.f / 16.f), (31.f / 32.f), 1, 1 + (1.f / 64.f), 1 + (1.f / 24.f) };
const float hitAngleMod[6] = { 8, 8, 6, 6, 4, 4 };


int main()
{
	printf("Controls:\n");
	printf("	Move	- Arrow Keys\n");
	printf("	Pause	- Esc.\n");
	printf("	Reset	- Space\n");
	printf("\n");
	printf("Game Modes (Numbers To Select):\n");
	printf("	1. Super Easy\n");
	printf("	2. Easy\n");
	printf("	3. Normal\n");
	printf("	4. Hard\n");
	printf("	5. Brutal\n");
	printf("	6. Imposible\n");
	printf("\nFor The Hackers Out There\n");
	printf("Here Are The Memory Adresses:\n");


	sf::ContextSettings settings;
	settings.antialiasingLevel = 0;

	sf::RenderWindow window(sf::VideoMode(width, height), "Pong", sf::Style::Default, settings);

	sf::VertexArray center = sf::VertexArray(sf::TrianglesStrip, 4);
	center[0].color = line;
	center[1].color = line;
	center[2].color = line;
	center[3].color = line;
	
	center[0].position = sf::Vector2f(0,		(height >> 1) - lineHeight);
	center[1].position = sf::Vector2f(0,		(height >> 1) + lineHeight);
	center[2].position = sf::Vector2f(width,	(height >> 1) - lineHeight);
	center[3].position = sf::Vector2f(width,	(height >> 1) + lineHeight);

	window.setFramerateLimit(60);

	Player player(width, height, front);

	Bot bot(width, height, front);

	Ball ball(width, height, front);

	sf::Font font;

	if (!font.loadFromFile("Consolas.ttf"))
	{
	}

	sf::Text botScore, playerScore, pause, reset, mode;
	
	pause.setFont(font);
	pause.setColor(front);
	pause.setCharacterSize(height >> 3);
	pause.setPosition(sf::Vector2f((width >> 1) - ((height >> 3)*(5.f / 3.f)), (height >> 1) - (height >> 2)));
	reset.setStyle(sf::Text::Bold);
	pause.setString("PAUSED");

	reset.setFont(font);
	reset.setColor(front);
	reset.setCharacterSize(height >> 3);
	reset.setPosition(sf::Vector2f((width >> 1) - ((height >> 3)*(5.f / 3.f)), (height >> 1) - (height >> 2)));
	reset.setStyle(sf::Text::Bold);
	reset.setString("RESET!");

	mode.setFont(font);
	mode.setColor(front);
	mode.setCharacterSize(height >> 3);
	mode.setPosition(sf::Vector2f((width >> 3), (height >> 1) - (height >> 2)));
	mode.setStyle(sf::Text::Bold);
	mode.setString("ERROR!");

	playerScore.setFont(font);
	playerScore.setColor(text);
	playerScore.setCharacterSize(height >> 3);
	playerScore.setPosition(sf::Vector2f(0, (height >> 1) + (lineHeight << 1)));

	botScore.setFont(font);
	botScore.setColor(text);
	botScore.setCharacterSize(height >> 3);
	botScore.setPosition(sf::Vector2f(0, (height >> 1) - ((lineHeight << 1) + (height >> 3) + (height >> 4))));

	printf("	----=YOUR VARIABLES=----\n");
	printf("	Your Score (UNSIGNED INT):\n		%p\n\n", (void *)&ball.playerScore);
	printf("	Your Speed (FLOAT):\n		%p\n\n", (void *)&player.vel);
	printf("	Your Position X (FLOAT):\n		%p\n\n", (void *)&player.pos.x);
	printf("	Your Position Y (FLOAT):\n		%p\n\n", (void *)&player.pos.y);
	printf("	Your Width (FLOAT):\n		%p\n\n", (void *)&player.paddleWidth);
	printf("	Your Height (FLOAT):\n		%p\n\n\n", (void *)&player.paddleHeight);

	printf("	----=BOT VARIABLES=----\n");
	printf("	Bot's Score(UNSIGNED INT):\n		%p\n\n", (void *)&ball.botScore);
	printf("	Bot's Speed (FLOAT):\n		%p\n\n", (void *)&bot.vel);
	printf("	Bot's Position X (FLOAT):\n		%p\n\n", (void *)&bot.pos.x);
	printf("	Bot's Position Y (FLOAT):\n		%p\n\n", (void *)&bot.pos.y);
	printf("	Bot's Width (FLOAT):\n		%p\n\n", (void *)&bot.paddleWidth);
	printf("	Bot's Height (FLOAT):\n		%p\n\n\n", (void *)&bot.paddleHeight);

	printf("	----=BALL VARIABLES=----\n");
	printf("	Ball's Position X (FLOAT):\n		%p\n\n", (void *)&ball.pos.x);
	printf("	Ball's Position Y (FLOAT):\n		%p\n\n", (void *)&ball.pos.y);
	printf("	Ball's Velocity X (FLOAT):\n		%p\n\n", (void *)&ball.vel.x);
	printf("	Ball's Velocity Y (FLOAT):\n		%p\n\n", (void *)&ball.vel.y);
	printf("	Ball's Size (FLOAT):\n	%p", (void *)&ball.size);

	while (window.isOpen())
	{
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				return 0;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			player.moveLeft();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			player.moveRight();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.draw(pause);
			window.display();
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {}

			while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				sf::Event evnt;
				while (window.pollEvent(evnt))
				{
					switch (evnt.type)
					{
					case sf::Event::Closed:
						window.close();
						return 0;
					}
				}
			}

			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			window.draw(reset);
			window.display();
			ball.reset();
			player.pos.x = width >> 1;
			bot.pos.x = width >> 1;
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				sf::Event evnt;
				while (window.pollEvent(evnt))
				{
					switch (evnt.type)
					{
					case sf::Event::Closed:
						window.close();
						return 0;
					}
				}
			}
			sf::sleep(sf::seconds(1));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			mode.setString(modes[0]);
			MAX_ANGLE = maxAngleSet[0];
			SPEED_JUMP = speedJumpSet[0];
			BOT_ANGLE_MOD = botAngleMod[0];
			HIT_ANGLE_MOD = hitAngleMod[0];
			window.draw(mode);
			window.display();

			ball.reset();
			player.pos.x = width >> 1;
			bot.pos.x = width >> 1;

			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
			{
				sf::Event evnt;
				while (window.pollEvent(evnt))
				{
					switch (evnt.type)
					{
					case sf::Event::Closed:
						window.close();
						return 0;
					}
				}
			}
			window.setFramerateLimit(60);
			sf::sleep(sf::seconds(1));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			mode.setString(modes[1]);
			MAX_ANGLE = maxAngleSet[1];
			SPEED_JUMP = speedJumpSet[1];
			BOT_ANGLE_MOD = botAngleMod[1];
			HIT_ANGLE_MOD = hitAngleMod[1];
			window.draw(mode);
			window.display();

			ball.reset();
			player.pos.x = width >> 1;
			bot.pos.x = width >> 1;

			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
			{
				sf::Event evnt;
				while (window.pollEvent(evnt))
				{
					switch (evnt.type)
					{
					case sf::Event::Closed:
						window.close();
						return 0;
					}
				}
			}
			window.setFramerateLimit(60);
			sf::sleep(sf::seconds(1));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		{
			mode.setString(modes[2]);
			MAX_ANGLE = maxAngleSet[2];
			SPEED_JUMP = speedJumpSet[2];
			BOT_ANGLE_MOD = botAngleMod[2];
			HIT_ANGLE_MOD = hitAngleMod[2];
			window.draw(mode);
			window.display();

			ball.reset();
			player.pos.x = width >> 1;
			bot.pos.x = width >> 1;

			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
			{
				sf::Event evnt;
				while (window.pollEvent(evnt))
				{
					switch (evnt.type)
					{
					case sf::Event::Closed:
						window.close();
						return 0;
					}
				}
			}
			window.setFramerateLimit(60);
			sf::sleep(sf::seconds(1));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
		{
			mode.setString(modes[3]);
			MAX_ANGLE = maxAngleSet[3];
			SPEED_JUMP = speedJumpSet[3];
			BOT_ANGLE_MOD = botAngleMod[3];
			HIT_ANGLE_MOD = hitAngleMod[3];
			window.draw(mode);
			window.display();

			ball.reset();
			player.pos.x = width >> 1;
			bot.pos.x = width >> 1;

			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
			{
				sf::Event evnt;
				while (window.pollEvent(evnt))
				{
					switch (evnt.type)
					{
					case sf::Event::Closed:
						window.close();
						return 0;
					}
				}
			}
			window.setFramerateLimit(60);
			sf::sleep(sf::seconds(1));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
		{
			mode.setString(modes[4]);
			MAX_ANGLE = maxAngleSet[4];
			SPEED_JUMP = speedJumpSet[4];
			BOT_ANGLE_MOD = botAngleMod[4];
			HIT_ANGLE_MOD = hitAngleMod[4];
			window.draw(mode);
			window.display();

			ball.reset();
			player.pos.x = width >> 1;
			bot.pos.x = width >> 1;

			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
			{
				sf::Event evnt;
				while (window.pollEvent(evnt))
				{
					switch (evnt.type)
					{
					case sf::Event::Closed:
						window.close();
						return 0;
					}
				}
			}
			window.setFramerateLimit(60);
			sf::sleep(sf::seconds(1));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
		{
			mode.setString(modes[5]);
			MAX_ANGLE = maxAngleSet[5];
			SPEED_JUMP = speedJumpSet[5];
			BOT_ANGLE_MOD = botAngleMod[5];
			HIT_ANGLE_MOD = hitAngleMod[5];
			window.draw(mode);
			window.display();

			ball.reset();
			player.pos.x = width >> 1;
			bot.pos.x = width >> 1;

			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
			{
				sf::Event evnt;
				while (window.pollEvent(evnt))
				{
					switch (evnt.type)
					{
					case sf::Event::Closed:
						window.close();
						return 0;
					}
				}
			}
			window.setFramerateLimit(60);
			sf::sleep(sf::seconds(1));
		}

		window.clear(back);

		/* UPDATING */
		player.update(); 
		bot.update(ball.pos.x, ball.vel.x, BOT_ANGLE_MOD, MAX_ANGLE, HIT_ANGLE_MOD);
		ball.update(&player, &bot, MAX_ANGLE, SPEED_JUMP, HIT_ANGLE_MOD);

		botScore.setString(" " + std::to_string(ball.botScore));
		playerScore.setString(" " + std::to_string(ball.playerScore));

		/* DRAWING */
		window.draw(center);
		window.draw(playerScore);
		window.draw(botScore);

		window.draw(ball.ball);
		window.draw(bot.paddle);
		window.draw(player.paddle);

		window.display();
	}
}