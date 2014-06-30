#include <Entities/ShapeEntity.hpp>

sf::Texture ShapeEntity::texture;

ShapeEntity::ShapeEntity(Game* _game) : Entity(_game) {
	// Set defaults
	shape = 0;

	SetFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
	SetOutlineColor(sf::Color::White);
	SetOutlineWidth(0.01f);

	type = SHAPE_ENTITY;

	// Load the image for the texture
	if (texture.getSize().x == 0)
		texture.loadFromFile("data/images/05.png");
}

ShapeEntity::~ShapeEntity() {
	DeleteShape();
}

// Draw
void ShapeEntity::Draw(float _deltatime) {
	if (shape != NULL) {
		// Set the shapes position and scale
		shape->setTexture(&texture);
		shape->setPosition(GetPosition());
		shape->setRotation(GetRotation());
		shape->setScale(GetScale());
		shape->setOrigin(GetCenter());

		game->GetTarget()->draw(*shape);
	}
}

// Set outline.
void ShapeEntity::SetOutlineColor(const sf::Color& _color) {
	outlinecolor = _color;
	if (shape != NULL)
		shape->setOutlineColor(_color);
}

// Set color.
void ShapeEntity::SetFillColor(const sf::Color& _color) {
	fillcolor = _color;
	if (shape != NULL)
		shape->setFillColor(_color);
}

// Set oultline width
void ShapeEntity::SetOutlineWidth(float _width) {
	outlinewidth = _width;
	if (shape != NULL)
		shape->setOutlineThickness(_width);
}

// Set vertices
void ShapeEntity::SetVertices(sf::Vector2f* _vertices, int _count) {
	// Clear the existing shape if it exists.
	DeleteShape();

	// Create a convex shape with those vertices.
	shape = new sf::ConvexShape(_count);
	sf::ConvexShape* convexShape = (sf::ConvexShape*)shape;
	
	// Loop through all the points and set them.
	for (int i = 0; i < _count; ++i) {
		convexShape->setPoint(i, _vertices[i]);
	}

	// Set the colors and outlines
	SetOutlineColor(outlinecolor);
	SetFillColor(fillcolor);
	SetOutlineWidth(outlinewidth);
}
	
// Set as a circle
void ShapeEntity::SetCircle(float _radius) {
	// Delete the shape if it exists.
	DeleteShape();

	// Create a circle shape.
	sf::CircleShape* circle = new sf::CircleShape(_radius);
	shape = circle;

	// Set the center
	SetCenter(sf::Vector2f(_radius, _radius));

	// Set the colors and outlines
	SetOutlineColor(outlinecolor);
	SetFillColor(fillcolor);
	SetOutlineWidth(outlinewidth);
}
bool ShapeEntity::GetIsCircle() {
	return (dynamic_cast<sf::CircleShape*>(shape) != NULL);
}
float ShapeEntity::GetRadius() {
	sf::CircleShape* shape = dynamic_cast<sf::CircleShape*>(this->shape);
	if (shape != NULL)
		return shape->getRadius();
	return 0.0f;
}

// Set as a rectangle
void ShapeEntity::SetRectangle(sf::Vector2f _size) {
	// Delete the shape if it already exists
	DeleteShape();

	// Create the rectangle
	sf::RectangleShape* rect = new sf::RectangleShape(_size);
	shape = rect;

	// Set the center 
	SetCenter(sf::Vector2f(_size.x / 2, _size.y / 2));

	// Set the colors and outlines
	SetOutlineColor(outlinecolor);
	SetFillColor(fillcolor);
	SetOutlineWidth(outlinewidth);
}

void ShapeEntity::DeleteShape() {
	// Delete the shape if it exists.
	if (shape != NULL)
		delete shape;
}