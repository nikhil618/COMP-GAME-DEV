#pragma once

#include "Entity.h"
#include "EntityManager.h"
#include <iostream>
#include <SFML/Graphics.hpp>


struct PlayerConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V; float S; };
struct EnemyConfig { int SR, CR, OR, OG, OB, OT, VMIN, VMAX, L, SI; float SMIN, SMAX; };
struct BulletConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V, L; float S; };

class Game
{
	sf::RenderWindow m_window;
	EntityManager m_entities;
	sf::Font m_font;
	sf::Text m_text;
	PlayerConfig m_playerConfig;
	EnemyConfig m_enemyConfig;
	BulletConfig m_bulletConfig;
	int m_score = 0;
	int m_currentFrame = 0;
	int m_lastEnemySpawnTime = 0;
	bool m_paused = false;
	bool m_running = true;

	std::shared_ptr<Entity> m_player;

	
	void init(const std::string& config);
	void setPaused(bool paused);

	void sMovement();						// System: Enemy position / movement
	void sUserInput();						// System: User input
	void sLifeSpan();						// System: Lifespan
	void sRender();							// System: Render / Drawing
	void sEnemySpawner();					// System: Spawns enemies
	void sCollission();						// System: Collissions
	

	void spawnPlayer();
	void spawnEnemy();
	void spawnSmallEnemies(std::shared_ptr<Entity> entity);
	void spawnBullet(std::shared_ptr<Entity> entity, const Vec2 & mousePos);
	void spawnSpecialWeapon(std::shared_ptr<Entity> entity);

public:
	Game(const std::string& config);

	void run();

};