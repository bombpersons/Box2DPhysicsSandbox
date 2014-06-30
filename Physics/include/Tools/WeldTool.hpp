#ifndef PHYSICS_WELDTOOL_HPP
#define PHYSICS_WELDTOOL_HPP

#include <Tools/Tool.hpp>
#include <Entities/Joints/WeldJointEntity.hpp>

class WeldTool : public Tool {
public:
	WeldTool(Game* _game);
	~WeldTool();

	// When the tool is equipped.
	virtual void Unequipped();

	// When a button is pressed
	virtual void OnPress(Entity* _entity, sf::Vector2f _pos, sf::Mouse::Button _button);

private:
	PhysicsEntity* entities[2];
	sf::Vector2f pos[2];
	int clickcount;
};

#endif