#pragma once
#include <SFML/Graphics.hpp>
#include <SFML\Window.hpp>

class SingleObject : public sf::Drawable
{
private:

	sf::Vector2f _possition{ 0 , 0 };
	;
public:
	SingleObject();
	virtual ~SingleObject();
};

