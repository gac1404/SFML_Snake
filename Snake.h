#pragma once
#include <SFML/Graphics.hpp>
#include <SFML\Window.hpp>
#include <vector>
#include "Node.h"

class Snake : public sf::Drawable
{
private:
	std::vector<Node> _nodeVec;
	Direction _direction = Direction::Right;

public:
	Snake();
	~Snake();

	void addNode();
	void setDirection(Direction direction);
	void move();
	sf::Vector2f getHeadPossition() const;
	Direction getHeadDirection() const;
	const std::vector<Node>& getNodeVec() const;

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
};

