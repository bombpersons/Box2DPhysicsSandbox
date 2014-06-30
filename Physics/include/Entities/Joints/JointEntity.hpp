#ifndef PHYSICS_JOINTENTITY_HPP
#define PHYSICS_JOINTENTITY_HPP

#include <Entities/ShapeEntity.hpp>
#include <Entities/PhysicsEntity.hpp>
#include <Box2D/Box2D.h>

class JointEntity : public ShapeEntity {
public:
	JointEntity(Game* _game);
	virtual ~JointEntity();

	// Set variables
	virtual void SetBodyA(PhysicsEntity* _entity);
	virtual void SetBodyB(PhysicsEntity* _entity);

	// Set the anchor points.
	void SetAnchorA(sf::Vector2f _pos);
	void SetAnchorB(sf::Vector2f _pos);

	// Create the joint.
	virtual void CreateJoint();
	virtual void JointDestroyed();

protected:
	// The joint.
	b2Joint* joint;

	// The bodies that are connected.
	PhysicsEntity *bodyA, *bodyB;

	// The anchor points
	sf::Vector2f anchorA, anchorB;
};

#endif