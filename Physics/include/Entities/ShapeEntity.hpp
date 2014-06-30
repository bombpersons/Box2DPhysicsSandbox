#ifndef PHYSICS_SHAPEENTITY_HPP
#define PHYSICS_SHAPEENTITY_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <Entities/Entity.hpp>
#include <Game/Game.hpp>

class ShapeEntity : public Entity {
public:
	// Constructor
	ShapeEntity(Game* _game);
	~ShapeEntity();

	// Draw
	virtual void Draw(float _deltatime);

	// Set outline.
	void SetOutlineColor(const sf::Color& _color);

	// Set color.
	void SetFillColor(const sf::Color& _color);

	// Set oultline width
	void SetOutlineWidth(float _width);

	// Set vertices
	virtual void SetVertices(sf::Vector2f* _vertices, int _count);
	
	// Set as a circle
	virtual void SetCircle(float _radius);
	bool GetIsCircle();
	float GetRadius();

	// Set as a rectangle
	virtual void SetRectangle(sf::Vector2f _size);

protected:
	// Delete the shape.
	void DeleteShape();

	// Values
	sf::Color fillcolor;
	sf::Color outlinecolor;
	float outlinewidth;

	// The actual shape.
	sf::Shape* shape;

	// static texture
	static sf::Texture texture;
};

#endif