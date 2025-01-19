#include <iostream>
#include <fstream>
#include "Game.h"

Game::Game(const std::string& config)
{
	init(config);
}

void Game::init(const std::string & path)
{
	m_window.create(sf::VideoMode(1280, 720), "Assignment 2");
	m_window.setFramerateLimit(60);

	spawnPlayer();
}

void Game::run()
{
	while (m_running)
	{
		m_entities.update();

		if (!m_paused)
		{
			sEnemySpawner();
			sMovement();
			sCollission();
			sUserInput();
		}
		
		sRender();

		m_currentFrame++;
	}
}

void Game::setPaused(bool val)
{
	m_paused = val;
}

void Game::sMovement()
{
}

void Game::sUserInput()
{
	// TODO: handle user input here
	// note that you should only be setting the player's input component variables here
	// you should not implement the player's movement logic here
	// the movement system will read the variables you set in this function

	sf::Event event;
	while (m_window.pollEvent(event))
	{
		// this event triggers when the window is closed
		if (event.type == sf::Event::Closed)
		{
			m_running = false;
		}

		// this event is triggered when a key is pressed
		if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{

			case sf::Keyboard::W :
				std::cout << "W Key Pressed\n";
				// TODO: set player's input component "up" to true
				break;
			default: break;
			}
		}
		
		// this event is triggered when a key is released
		if (event.type == sf::Event::KeyReleased)
		{
			switch (event.key.code)
			{

			case sf::Keyboard::W:
				std::cout << "W Key Released\n";
				// TODO: set player's input component "up" to true
				break;
			default: break;
			}
		}

		if (event.type == sf::Event::MouseButtonPressed)
		{

			if (event.mouseButton.button == sf::Mouse::Left)
			{
				std::cout << "Left Mouse Button Clicked at (" << event.mouseButton.x << "," << event.mouseButton.y << ")\n";
				// call spawnBullet here
			}

			if (event.mouseButton.button == sf::Mouse::Right)
			{
				std::cout << "Right Mouse Button Clicked at (" << event.mouseButton.x << "," << event.mouseButton.y << ")\n";
				// call special power here
			}
		}
	}
}


void Game::sLifeSpan()
{
}

void Game::sRender()
{
	m_window.clear();

	m_player->cShape->circle.setPosition(m_player->cTransform->position.x, m_player->cTransform->position.y);

	m_player->cTransform->angle += 1.f;
	m_player->cShape->circle.setRotation(m_player->cTransform->angle);

	m_window.draw(m_player->cShape->circle);
	m_window.display();
}

void Game::sEnemySpawner()
{
	spawnEnemy();
}

void Game::sCollission()
{

}

void Game::spawnPlayer()
{
	auto entity = m_entities.addEntity("player");

	entity->cTransform = std::make_shared<CTransform>(Vec2(200.f, 200.f), Vec2(1.f, 1.f), 0.f);

	entity->cShape = std::make_shared<CShape>(32.f, 8, sf::Color(10, 10, 10), sf::Color(255, 0, 0), 4.f);

	entity->cInput = std::make_shared<CInput>();

	m_player = entity;
}
void Game::spawnEnemy()
{
	// auto entity = m_entities.addEntity("enemy");
	m_lastEnemySpawnTime = m_currentFrame;
}

void Game::spawnSmallEnemies(std::shared_ptr<Entity> entity)
{
}

void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2& mousePos)
{
}

void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity)
{
}
