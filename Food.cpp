#include "stdafx.h"
#include "Food.h"



Food::Food(sf::Vector2f pos)
{
	_circle.setPosition(pos);
	_circle.setFillColor(sf::Color::White);
	_circle.setRadius(FoodSize/2.f);
}


Food::~Food()
{
}

sf::Vector2f Food::getPosition() const
{
	return _circle.getPosition();
}

void Food::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(this->_circle, states);
}

