#ifndef PHYSICS_MOTORJOINT_HPP
#define PHYSICS_MOTORJOINT_HPP

#include <Entities/Joints/JointEntity.hpp>

class MotorJointEntity : public JointEntity {
public:
	MotorJointEntity(Game* _game);
	~MotorJointEntity();

	// Set the max torque
	void SetMaxTorque(float _torque);
	void SetMotorSpeed(float _speed);
	void SetUserControlled(bool _v);
	void SetAxis(sf::Vector2f _axis);
	void SetDamping(float _damping);
	void SetFrequency(float _frequency);

	// Create the joint.
	virtual void CreateJoint();

	// Draw it.
	virtual void Draw(float _deltatime);
	virtual void Update(float _deltatime);

	// Serialize / Deserialize
	virtual void Serialize(FILE* _file);
	virtual void Deserialize(FILE* _file);

private:
	float motorspeed;
	float motortorque;
	bool usercontrolled;
	sf::Vector2f axis;
	float damping;
	float frequency;
};

#endif