#pragma once
#include "iostream"
#include "Vec2.h"
#include <SFML/Graphics.hpp>

class CTransform
{
public:
	Vec2 position = { 0.f, 0.f };
	Vec2 velocity = { 0.f, 0.f };
	float angle = 0.f;

	CTransform(const Vec2& p, const Vec2& v, float a)
		: position(p), velocity(v), angle(a)
	{
	}

};


class CShape
{
public:
	sf::CircleShape circle;

	CShape(float radius, int points, const sf::Color& fill, const sf::Color& outline, float thickness)
		: circle(radius, points)
	{
		circle.setFillColor(fill);
		circle.setOutlineColor(outline);
		circle.setOutlineThickness(thickness);
		circle.setOrigin(radius, radius);
	}
};

class CCollission
{
public:
	float radius = 0;
	CCollission(float radi)
		: radius(radi)
	{
	}
};

class CScore
{
public:
	int score = 0;
	CScore(int s)
		: score(s)
	{
	}
};

class CLifeSpan
{
public:
	int remaining = 0;
	int total = 0;

	CLifeSpan(int t)
		: remaining(total), total(t)
	{
	}
};

class CInput
{
public:
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;

	CInput() {}
};














