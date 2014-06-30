#ifndef PHYSICS_FRICTIONTOOL_HPP
#define PHYSICS_FIRCTIONTOOL_HPP

#include <Tools/Tool.hpp>

class FrictionTool : public Tool {
public:
	FrictionTool(Game* _game);
	~FrictionTool();

	// OnPress
	virtual void OnPress(Entity* _entity, sf::Vector2f _pos, sf::Mouse::Button);

	// Update
	virtual void Update(float _deltatime);

private:
	// The friction value to set
	float friction;
};

#endif