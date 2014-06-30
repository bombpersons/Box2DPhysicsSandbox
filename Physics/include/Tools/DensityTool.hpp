#ifndef PHYSICS_DENSITYTOOL_HPP
#define PHYSICS_DENSITYTOOL_HPP

#include <Tools/Tool.hpp>

class DensityTool : public Tool {
public:
	DensityTool(Game* _game);
	~DensityTool();

	// OnPress
	virtual void OnPress(Entity* _entity, sf::Vector2f _pos, sf::Mouse::Button);

	// Update
	virtual void Update(float _deltatime);

private:
	float density;
};

#endif