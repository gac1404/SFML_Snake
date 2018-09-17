#pragma once
#include <SFML/Graphics.hpp>
#include <SFML\Window.hpp>

#define FoodSize 20.f

class Food: public sf::Drawable
{
private:

	sf::CircleShape _circle;

public:
	Food(sf::Vector2f pos = sf::Vector2f(0 , 0));
	~Food();

	sf::Vector2f getPosition() const;


	// Inherited via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;


};

