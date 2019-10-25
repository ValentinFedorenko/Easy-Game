#pragma once
#include <SFML\Graphics.hpp>

sf::View view1; // камера 1
sf::View view2; // камера 2


sf::View kameraIgroka1(float x, float y)
{	
	view1.setCenter(x, y + 100);
	return view1;
}

sf::View kameraIgroka2(float x, float y)
{
	view2.setCenter(x, y + 100);
	return view2;
}

