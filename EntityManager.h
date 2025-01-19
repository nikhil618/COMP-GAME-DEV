#pragma once

#include  "Entity.h"
#include <vector>
#include <map>

typedef std::vector<std::shared_ptr<Entity>> EntityVector;
typedef std::map<std::string, EntityVector> EntityMap;

class EntityManager
{
	EntityVector m_entities;
	EntityVector m_entitiesToAdd;
	EntityMap m_entityMap;
	size_t m_totalEntities = 0;

	void removeDeadEntities(EntityVector& vector);

public:
	EntityManager();
	
	void update();

	std::shared_ptr<Entity> addEntity(const std::string& tag);

	const EntityVector& getEntities();

	const EntityVector& getEntities(std::string& tag);
	
};
