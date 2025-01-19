#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Vec2.h"
#include "iostream"

int main()
{
	Game g("config.txt");
	g.run();
	
	return 0;
}



/*
	// Testing Vec2 class

	if (true)
	{
		Vec2 v1 = Vec2(10.1, 20.2);
		Vec2 v2 = Vec2(1.3, 1.3);

		Vec2 v3 = v1 + v2;
		v1 += v2;

		std::cout << "(" << v1.x << "," << v1.y << ") + (" << v2.x << "," << v2.y << ") = (" << v3.x << "," << v3.y << ")" << std::endl;
		std::cout << "(" << v1.x << "," << v1.y << ") += (" << v2.x << "," << v2.y << ") => v1 (" << v1.x << "," << v1.y << ")" << std::endl << std::endl;
	}

	if (true)
	{
		Vec2 v1 = Vec2(10.1, 20.2);
		Vec2 v2 = Vec2(1.3, 1.3);

		Vec2 v3 = v1 - v2;
		v1 -= v2;

		std::cout << "(" << v1.x << "," << v1.y << ") - (" << v2.x << "," << v2.y << ") = (" << v3.x << "," << v3.y << ")" << std::endl;
		std::cout << "(" << v1.x << "," << v1.y << ") -= (" << v2.x << "," << v2.y << ") => v1 (" << v1.x << "," << v1.y << ")" << std::endl << std::endl;
	}

	if (true)
	{
		Vec2 v1 = Vec2(10.1, 20.2);
		Vec2 v2 = Vec2(1.3, 1.3);

		Vec2 v3 = v1 * 2.f;
		std::cout << "(" << v1.x << "," << v1.y << ") * 2.f = v3 (" << v3.x << "," << v3.y << ")" << std::endl;
		v1 *= v2;
		std::cout << "(" << v1.x << "," << v1.y << ") *= (" << v2.x << "," << v2.y << ") => v1 (" << v1.x << "," << v1.y << ")" << std::endl << std::endl;
	}

	if (true)
	{
		Vec2 v1 = Vec2(10.1, 20.2);
		Vec2 v2 = Vec2(1.3, 1.3);

		Vec2 v3 = v1 / 2.f;
		v1 /= v2;

		std::cout << "(" << v1.x << "," << v1.y << ") / 2.f = v3 (" << v3.x << "," << v3.y << ")" << std::endl;
		std::cout << "(" << v1.x << "," << v1.y << ") /= (" << v2.x << "," << v2.y << ") => v1 (" << v1.x << "," << v1.y << ")" << std::endl << std::endl;
	}

	if (true)
	{
		Vec2 v1 = Vec2(10, 10);
		Vec2 v2 = Vec2(10.f, 10.f);

		std::cout << (v1 == v2) << std::endl;
	}


	if (true)
	{
		Vec2 v1 = Vec2(3, 0);
		Vec2 v2 = Vec2(3, 4);

		std::cout << v1.dist(v2);
	}*/