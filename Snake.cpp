#include "stdafx.h"
#include "Snake.h"

#include <iostream>


Snake::Snake()
{
	_nodeVec.push_back(Node(sf::Vector2f(400 , 500)));
}

Snake::~Snake()
{
}

void Snake::addNode()
{
	switch ((_nodeVec.end() - 1)->getDirection())
	{
	case Direction::Right:
		_nodeVec.push_back(Node(_nodeVec.back().getPosition().x - NodeSize, _nodeVec.back().getPosition().y));
		break;
	case Direction::Left:
		_nodeVec.push_back(Node(_nodeVec.back().getPosition().x + NodeSize, _nodeVec.back().getPosition().y));
		break;
	case Direction::Down:
		_nodeVec.push_back(Node(_nodeVec.back().getPosition().x, _nodeVec.back().getPosition().y - NodeSize));
		break;
	case Direction::Up:
		_nodeVec.push_back(Node(_nodeVec.back().getPosition().x, _nodeVec.back().getPosition().y + NodeSize));
		break;
	default:
		break;
	}

	((_nodeVec.end() - 1)->setDirection((_nodeVec.end() - 2)->getDirection()));
	
}

void Snake::setDirection(Direction direction)
{
	_direction = direction;
	_nodeVec.front().setDirection(direction);
}

void Snake::move()
{
	for (auto it = _nodeVec.rbegin(); it != _nodeVec.rend() - 1; it++)
	{
		it->setDirection((it + 1)->getDirection());
		it->setPossition((it + 1)->getPosition());
	}
	//tutaj skonczylem, dodac obsluge pierwszego elementu

	_nodeVec.front().move();
}

sf::Vector2f Snake::getHeadPossition() const
{
	return _nodeVec.front().getPosition();
}

Direction Snake::getHeadDirection() const
{
	return _nodeVec.front().getDirection();
}

const std::vector<Node>& Snake::getNodeVec() const
{
	return _nodeVec;
}

void Snake::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (const auto &node : _nodeVec)
	{
		node.draw(target , states);
	}
}

