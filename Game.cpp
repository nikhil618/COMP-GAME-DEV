#include <iostream>
#include <fstream>
#include "Game.h"

Game::Game(const std::string& config)
{
	init(config);
}

void Game::init(const std::string& path)
{
	std::ifstream fin(path);
	std::string temp;
	while (fin >> temp)
	{
		if (temp == "Window")
		{
			fin >> m_windowConfig.WW >> m_windowConfig.WH >> m_windowConfig.FL >> m_windowConfig.FS;
		}
		if (temp == "Font")
		{
			fin >> m_fontConfig.FONT >> m_fontConfig.FS >> m_fontConfig.FR >> m_fontConfig.FG >> m_fontConfig.FB;
		}
		if (temp == "Player")
		{
			fin >> m_playerConfig.SR >> m_playerConfig.CR >> m_playerConfig.S >> m_playerConfig.FR >> m_playerConfig.FG >> m_playerConfig.FB >> m_playerConfig.OR >> m_playerConfig.OG >> m_playerConfig.OB >> m_playerConfig.OT >> m_playerConfig.V ;
		}
		if (temp == "Enemy")
		{
			fin >> m_enemyConfig.SR >> m_enemyConfig.CR >> m_enemyConfig.SMIN >> m_enemyConfig.SMAX >> m_enemyConfig.OR >> m_enemyConfig.OG >> m_enemyConfig.OB >> m_enemyConfig.OT >> m_enemyConfig.VMIN >> m_enemyConfig.VMAX >> m_enemyConfig.L >> m_enemyConfig.SI;
		}
		if (temp == "Bullet")
		{
			fin >> m_bulletConfig.SR >> m_bulletConfig.CR >> m_bulletConfig.S >> m_bulletConfig.FR >> m_bulletConfig.FG >> m_bulletConfig.FB >> m_bulletConfig.OR >> m_bulletConfig.OG >> m_bulletConfig.OB >> m_bulletConfig.OT >> m_bulletConfig.V >> m_bulletConfig.L;
		}
	}
	m_window.create(sf::VideoMode(m_windowConfig.WW, m_windowConfig.WH), "Assignment 2", m_windowConfig.FS ? sf::Style::Fullscreen : sf::Style::Default);
	m_window.setFramerateLimit(m_windowConfig.FL);

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
		}
		sUserInput();
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
	m_player->cTransform->velocity = { 0, 0 };

	if (m_player->cInput->up) {
		m_player->cTransform->velocity.y = -m_playerConfig.S;
	}

	if (m_player->cInput->down) {
		m_player->cTransform->velocity.y = m_playerConfig.S;
	}

	if (m_player->cInput->left) {
		m_player->cTransform->velocity.x = -m_playerConfig.S;
	}
	
	if (m_player->cInput->right) {
		m_player->cTransform->velocity.x = m_playerConfig.S;
	}

	m_player->cTransform->position.x += m_player->cTransform->velocity.x;
	m_player->cTransform->position.y += m_player->cTransform->velocity.y;
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
				case sf::Keyboard::W:
					if (!m_paused)
					{
						m_player->cInput->up = true;
					}
					break;
				case sf::Keyboard::A:
					if (!m_paused)
					{
						m_player->cInput->left = true;
					}
					break;
				case sf::Keyboard::S:
					if (!m_paused)
					{
						m_player->cInput->down = true;
					}
					break;
				case sf::Keyboard::D:
					if (!m_paused)
					{
						m_player->cInput->right = true;
					}
					break;
				case sf::Keyboard::P:
					m_paused = !m_paused;
				break;
				case sf::Keyboard::Escape:
					m_running = false;
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
					m_player->cInput->up = false;
					break;
				case sf::Keyboard::A:
					m_player->cInput->left = false;
					break;
				case sf::Keyboard::S:
					m_player->cInput->down = false;
					break;
				case sf::Keyboard::D:
					m_player->cInput->right = false;
				break;
				default: break;
			}
		}

		if (event.type == sf::Event::MouseButtonPressed)
		{

			if (event.mouseButton.button == sf::Mouse::Left)
			{
				// std::cout << "Left Mouse Button Clicked at (" << event.mouseButton.x << "," << event.mouseButton.y << ")\n";
				spawnBullet(m_player, Vec2(event.mouseButton.x, event.mouseButton.y));
				// call spawnBullet here
			}

			if (event.mouseButton.button == sf::Mouse::Right)
			{
				// std::cout << "Right Mouse Button Clicked at (" << event.mouseButton.x << "," << event.mouseButton.y << ")\n";
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

	for (auto& e : m_entities.getEntities())
	{
		e->cShape->circle.setPosition(e->cTransform->position.x, e->cTransform->position.y);

		e->cTransform->angle += 1.f;
		e->cShape->circle.setRotation(e->cTransform->angle);

		m_window.draw(e->cShape->circle);
	}
	m_window.display();
}

void Game::sEnemySpawner()
{
	if (m_currentFrame - m_lastEnemySpawnTime >= m_enemyConfig.SI || (m_lastEnemySpawnTime == 0 && m_currentFrame == 0))
	{
		spawnEnemy();
	}
}

void Game::sCollission()
{

}

void Game::spawnPlayer()
{
	auto entity = m_entities.addEntity("player");

	float mx = m_window.getSize().x / 2.f;
	float my = m_window.getSize().y / 2.f;

	entity->cTransform = std::make_shared<CTransform>(Vec2(mx, my), Vec2(m_playerConfig.S, m_playerConfig.S), 0.f);

	entity->cShape = std::make_shared<CShape>(m_playerConfig.SR, m_playerConfig.V, sf::Color(m_playerConfig.FR, m_playerConfig.FG, m_playerConfig.FB), sf::Color(m_playerConfig.OR, m_playerConfig.OG, m_playerConfig.OB), m_playerConfig.OT);

	entity->cInput = std::make_shared<CInput>();

	m_player = entity;
}

void Game::spawnEnemy()
{
	auto entity = m_entities.addEntity("enemy");
	// float ex = rand() % (m_window.getSize().x - 16) + 16;
	// float ey = rand() % (m_window.getSize().y - 16) + 16;
	float ex = m_enemyConfig.SR + rand() % (m_window.getSize().x - (2 * m_enemyConfig.SR) + 1);
	float ey = m_enemyConfig.SR + rand() % (m_window.getSize().y - (2 * m_enemyConfig.SR) + 1);
	float vertices = m_enemyConfig.VMIN + rand() % (m_enemyConfig.VMAX - m_enemyConfig.VMIN + 1);
	entity->cTransform = std::make_shared<CTransform>(Vec2(ex, ey), Vec2(0.f, 0.f), 0.f);

	entity->cShape = std::make_shared<CShape>(m_enemyConfig.SR, vertices, sf::Color(m_enemyConfig.OR, m_enemyConfig.OG, m_enemyConfig.OB), sf::Color(m_enemyConfig.OR, m_enemyConfig.OG, m_enemyConfig.OB), m_enemyConfig.OT);

	entity->cInput = std::make_shared<CInput>();

	m_lastEnemySpawnTime = m_currentFrame;
}

void Game::spawnSmallEnemies(std::shared_ptr<Entity> entity)
{
}

void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2& mousePos)
{
	auto bulletEntity = m_entities.addEntity("bullet");
	float bx = m_player->cTransform->position.x;
	float by = m_player->cTransform->position.y;

	bulletEntity->cTransform = std::make_shared<CTransform>(Vec2(bx, by), Vec2(0.f, 0.f), 0.f);

	bulletEntity->cShape = std::make_shared<CShape>(2.f, 100, sf::Color(255, 255, 255), sf::Color(0, 0, 255), 1.f);

	bulletEntity->cInput = std::make_shared<CInput>();

}

void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity)
{
}
