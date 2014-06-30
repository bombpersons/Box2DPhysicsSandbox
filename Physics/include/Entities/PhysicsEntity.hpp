#ifndef PHYSICS_PHYSICSENTITY_HPP
#define PHYSICS_PHYSICSENTITY_HPP

#include <Box2D/Box2D.h>

#include <Entities/ShapeEntity.hpp>

class PhysicsEntity : public ShapeEntity {
public:
	// Constructors
	PhysicsEntity(Game* _game);
	virtual ~PhysicsEntity();

	// Override the update function to update our position from the box2d body.
	virtual void FixedUpdate();
	virtual void Draw(float _deltatime);

	// Override the shape making functions so that we can create box2d bodies as well.
	virtual void SetVertices(sf::Vector2f* _vertices, int _count);
	virtual void SetCircle(float _radius);
	virtual void SetRectangle(sf::Vector2f _size);
	
	// Override sets for position, rotation and scale so that we can affect the physics body.
	virtual void SetPosition(const sf::Vector2f& _pos);
	virtual void SetScale(const sf::Vector2f& _scale);
	virtual void SetRotation(float _rot);

	sf::Vector2f GetSmoothedPosition();
	float GetSmoothedRotation();

	void SetVelocity(sf::Vector2f _vel);
	void SetAngularVelocity(float _vel);

	void Sleep(bool _v);

	// Set density
	void SetDensity(float _density);
	float GetDensity();
	// Set friction
	void SetFriction(float _friction);
	float GetFriction();
	// Set restitution
	void SetRestitution(float _rest);
	float GetRestitution();

	// Set the body type.
	void SetBodyType(b2BodyType _type);
	b2BodyType GetBodyType();

	// Get the body
	b2Body* GetBody();

	// Get Surface Area
	float GetSurfaceArea(sf::Vector2f _axis);

	// Serialize + Deserialize
	virtual void Serialize(FILE* _file);
	virtual void Deserialize(FILE* _file);

protected:
	void CreateBody();
	void CreateFixture(b2Shape* _shape);

private:
	// Keep track of the box2d body.
	b2Body* body;
	b2Fixture* fixture;

	// The previous's step's position and rotation
	sf::Vector2f prevPosition;
	float prevRotation;

	// Properties of the body.
	float density;
	float friction;
	float restitution;
	b2BodyType bodytype;
};

#endif