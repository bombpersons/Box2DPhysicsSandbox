#ifndef PHYSICS_POLYGONTOOL_HPP
#define PHYSICS_POLYGONTOOL_HPP

#include <Tools/Tool.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class PolygonTool : public Tool {
public:
	PolygonTool(Game* _game);
	~PolygonTool();

	// Detect the object to select
	virtual void OnPress(Entity* _entity, sf::Vector2f _pos, sf::Mouse::Button _button);
	virtual void OnRelease(Entity* _entity, sf::Vector2f _pos, sf::Mouse::Button _button);

	// Equip
	virtual void Equipped();

	// Draw
	virtual void Draw(float _deltatime);

	// Check if the shape is convex
	bool IsConvex();

	// Check for a line intersecting any of the lines on the shape.
	int IntersectingOnShape(sf::Vector2f _linea, sf::Vector2f _lineb);

	// Check if a line is intersecting an other
	bool AreLinesIntersecting(sf::Vector2f _line1a, sf::Vector2f _line1b, sf::Vector2f _line2a, sf::Vector2f _line2b, sf::Vector2f* _out);
	
	// Cross product
	float Cross(sf::Vector2f _one, sf::Vector2f _two);

private:
	// The preview shape.
	sf::ConvexShape preview;

	// The current list of vertices.
	std::vector<sf::Vector2f> vertices;
};

#endif