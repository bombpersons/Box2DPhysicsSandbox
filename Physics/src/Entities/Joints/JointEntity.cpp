#include <Entities/Joints/JointEntity.hpp>

JointEntity::JointEntity(Game* _game) : ShapeEntity(_game) {
	// Default values
	bodyA = NULL;
	bodyB = NULL;
	joint = NULL;
	anchorA.x = 0; anchorA.y = 0;
	anchorB.x = 0; anchorB.y = 0;

	type = JOINT_ENTITY;
}

JointEntity::~JointEntity() {
	if (joint != NULL) {
		if (joint->GetUserData() == this) {
			game->GetWorld()->DestroyJoint(joint);
		}
		joint = NULL;
	}
}

// Set variables
void JointEntity::SetBodyA(PhysicsEntity* _entity) {
	bodyA = _entity;
}
void JointEntity::SetBodyB(PhysicsEntity* _entity) {
	bodyB = _entity;
}

// Set anchors
void JointEntity::SetAnchorA(sf::Vector2f _pos) {
	anchorA = _pos;
}
void JointEntity::SetAnchorB(sf::Vector2f _pos) {
	anchorB = _pos;
}

// Create the joint
void JointEntity::CreateJoint() {
}

// Joint destroyed
void JointEntity::JointDestroyed() {
	joint = NULL;
}