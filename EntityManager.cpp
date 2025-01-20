#include "EntityManager.h"

EntityManager::EntityManager()
{
}

void EntityManager::update()
{
		// TODO: add entities from m_entitiesToAdd the the proper location(s)
		//  - add them to the vector of all entities
		//	- add them to the vector inside the map, with the tag as a key

	for (auto& e : m_entitiesToAdd)
	{
		m_entities.push_back(e);
	}

	m_entitiesToAdd.clear();

	// remove dead entities from the vector of all entities
	removeDeadEntities(m_entities);

	// remove dead entities from each vector in the entity map
	// C++17 way of iterating through [key, value] pairs in a map
	for (auto& [tag, entityVector] : m_entityMap)
	{
		removeDeadEntities(entityVector);
	}
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag)
{
	const auto entity = std::shared_ptr<Entity>(new Entity(m_totalEntities++, tag));
	
	m_entitiesToAdd.push_back(entity);

	return entity;
}

const EntityVector& EntityManager::getEntities()
{
	return m_entities;
}

const EntityVector& EntityManager::getEntities(std::string &tag)
{
	// TODO: This is incorrect, return the correct vector from the map
	return m_entityMap[tag];
}

void EntityManager::removeDeadEntities(EntityVector& vector)
{
}


