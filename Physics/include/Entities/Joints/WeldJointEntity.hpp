#ifndef PHYSICS_WELDJOINTENTITY_HPP
#define PHYSICS_WELDJOINTENTITY_HPP

#include <Entities/Joints/JointEntity.hpp>

class WeldJointEntity : public JointEntity {
public:
	WeldJointEntity(Game* _game);
	virtual ~WeldJointEntity();

	// Create the joint.
	virtual void CreateJoint();

	// Draw the joint
	virtual void Draw(float _deltatime);

	// Serialize / Deserialize
	virtual void Serialize(FILE* _file);
	virtual void Deserialize(FILE* _file);

private:
};


#endif