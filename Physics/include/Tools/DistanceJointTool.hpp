#ifndef PHYSICS_DISTANCEJOINTTOOL_HPP
#define PHYSICS_DISTANCEJOINTTOOL_HPP

#include <Tools/Tool.hpp>
#include <Entities/Joints/DistanceJointEntity.hpp>

class DistanceJointTool : public Tool {
public:
	DistanceJointTool(Game* _game);
	~DistanceJointTool();

	// OnPress
	virtual void OnPress(Entity* _entity, sf::Vector2f _pos, sf::Mouse::Button _button);

	// Update
	virtual void Update(float _deltatime);

private:
	PhysicsEntity* entities[2];
	sf::Vector2f pos[2];
	int clickcount;
	float damping, frequency;
};

#endif