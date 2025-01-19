#pragma once

#include <iostream>
#include <memory>
#include "Components.h"

class Entity
{
	friend class EntityManager;

	bool m_active = true;
	size_t m_id = 0;
	std::string m_tag = "Default";

	// Constructor Destructor
	// IMP:- Constructor is defined as private so no other class other than the friend EntityManager class can instantiate it
	Entity(const size_t& id, const std::string& tag)
		: m_id(id), m_tag(tag)
	{
	}

public:

	// Component pointers
	std::shared_ptr<CTransform> cTransform;
	std::shared_ptr<CShape> cShape;
	std::shared_ptr<CCollission> cCollission;
	std::shared_ptr<CScore> cScore;
	std::shared_ptr<CLifeSpan> cLifeSpan;
	std::shared_ptr<CInput> cInput;


	// Private member access functions
	bool isActive() const;
	const std::string & tag() const;
	const size_t id() const;
	void destroy();
};