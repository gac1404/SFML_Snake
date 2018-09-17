#include "stdafx.h"
#include "Node.h"
#include <iostream>

Node::Node(sf::Vector2f pos)
{
	_rectangle.setSize(sf::Vector2f(NodeSize , NodeSize));
	_rectangle.setFillColor(sf::Color::Red);
	_rectangle.setPosition(pos);
	_rectangle.setOutlineThickness(OutlineSize);
	_rectangle.setOutlineColor(sf::Color::Black);
}

Node::Node(float x, float y)
{
	_rectangle.setSize(sf::Vector2f(NodeSize, NodeSize));
	_rectangle.setFillColor(sf::Color::Red);
	_rectangle.setPosition(sf::Vector2f(x , y));
	_rectangle.setOutlineThickness(OutlineSize);
	_rectangle.setOutlineColor(sf::Color::Black);
}


Node::~Node()
{
}

void Node::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(this->_rectangle, states);
}

void Node::setPossition(sf::Vector2f vec)
{
	_rectangle.setPosition(vec);
}

sf::Vector2f Node::getPosition() const
{
	return _rectangle.getPosition();
}

void Node::move()
{
	switch (_direction)
	{
	case Direction::Right:
		_rectangle.move(NodeSize , 0);
		break;
	case Direction::Left:
		_rectangle.move(-NodeSize, 0);
		break;
	case Direction::Up:
		_rectangle.move(0 , -NodeSize);
		break;
	case Direction::Down:
		_rectangle.move(0 , NodeSize);
		break;
	default:
		break;
	}
}

bool Node::setDirection(Direction direction)
{
	if ((direction == Direction::Down || direction == Direction::Up) &&
		(_direction == Direction::Down || _direction == Direction::Up))
	{
		return false;
	}

	if ((direction == Direction::Left || direction == Direction::Right) &&
		(_direction == Direction::Left || _direction == Direction::Right))
	{
		return false;
	}

	_direction = direction;
	return true;
}

Direction Node::getDirection() const
{
	//std::cout << "_direction: " << static_cast<int>(_direction) << std::endl;
	return _direction;
}

