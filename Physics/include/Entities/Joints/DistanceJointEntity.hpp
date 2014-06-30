#ifndef PHYSICS_DISTANCEJOINTENTITY_HPP
#define PHYSICS_DISTACNEJOINTENTITY_HPP

#include <Entities/Joints/JointEntity.hpp>

class DistanceJointEntity : public JointEntity {
public:
	DistanceJointEntity(Game* _game);
	~DistanceJointEntity();

	// Set damping and frequency
	void SetDamping(float _damping);
	void SetFrequency(float _frequency);

	// Create the joint
	virtual void CreateJoint();
	
	// Draw the joint
	virtual void Draw(float _deltatime);

	// Serialize / Deserialize
	virtual void Serialize(FILE* _file);
	virtual void Deserialize(FILE* _file);

private:
	float damping, frequency;
};

#endif