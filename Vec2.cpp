#include "Vec2.h"
#include "iostream";

Vec2::Vec2()
{
}

Vec2::Vec2(float xin, float yin)
	: x(xin), y(yin)
{
}

bool Vec2::operator == (const Vec2& rhs) const
{
	return (x == rhs.x && y == rhs.y);
}

bool Vec2::operator != (const Vec2& rhs) const
{
	return (x != rhs.x || y != rhs.y);
}

Vec2 Vec2::operator + (const Vec2& rhs) const
{
	return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator - (const Vec2& rhs) const
{
	return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator * (const float value) const
{
	return Vec2(x * value, y * value);
}

Vec2 Vec2::operator / (const float value) const
{
	if (value != 0.f)
	{
		return Vec2(x / value, y / value);
	}
	else
	{
		std::cout << "Illegal division operator: Trying to divide by 0 (x,y) (" << x << "," << y << ")" << std::endl;
		return Vec2(x, y);
	}
	
}

void Vec2::operator += (const Vec2& rhs)
{
	x += rhs.x;
	y += rhs.y;
}

void Vec2::operator -= (const Vec2& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
}

void Vec2::operator *= (const Vec2& rhs)
{
	x *= rhs.x;
	y *= rhs.y;
}

void Vec2::operator /= (const Vec2& rhs)
{
	if (rhs.x != 0.f)
	{
		x /= rhs.x;
	}
	if (rhs.y != 0.f)
	{
		y /= rhs.y;
	}
}


/*
	Distance between two points (x1, y1) & (x2, y2) =  d=sqrt((x2 – x1)² + (y2 – y1)²)
*/
float Vec2::dist(const Vec2& rhs) const
{
	float xsq = (x - rhs.x) * (x - rhs.x);
	float ysq = (y - rhs.y) * (y - rhs.y);
	return sqrt(xsq + ysq);
}
