#ifndef PHYSICS_MOTORJOINTTOOL_HPP
#define PHYSICS_MOTORJOINTTOOL_HPP

#include <Tools/Tool.hpp>
#include <Entities/Joints/MotorJointEntity.hpp>

class MotorJointTool : public Tool {
public:
	MotorJointTool(Game* _game);
	~MotorJointTool();

	// When the tool is equipped.
	virtual void Unequipped();

	// When a button is pressed
	virtual void OnPress(Entity* _entity, sf::Vector2f _pos, sf::Mouse::Button _button);
	virtual void OnRelease(Entity* _entity, sf::Vector2f _pos, sf::Mouse::Button _button);

	// Update
	virtual void Update(float _deltatime);
	virtual void Draw(float _deltatime);

private:
	PhysicsEntity* entities[2];
	sf::Vector2f pos[2];
	int clickcount;
	sf::Vector2f axispos[2];

	// The torque and speed
	float speed, torque;
	bool usercontrolled;
	sf::Vector2f axis;
	float damping;
	float frequency;
};

#endif