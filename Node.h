#pragma once
#include <SFML/Graphics.hpp>
#include <SFML\Window.hpp>

#define NodeSize 20
#define OutlineSize -NodeSize/8.f

enum class Direction
{
	Right,
	Left,
	Up,
	Down,
};

class Node : public sf::Drawable
{
private:
	
	Direction _direction = Direction::Down;
	sf::RectangleShape _rectangle;
	

public:
	Node(sf::Vector2f pos = sf::Vector2f( 0.f , 0.f));
	Node(float x, float y);
	~Node();

	virtual void draw(sf::RenderTarget & target,sf::RenderStates states) const override;


	void setPossition(sf::Vector2f vec);
	sf::Vector2f getPosition() const;
	void move();
	bool setDirection(Direction direction);
	Direction getDirection() const;



};

