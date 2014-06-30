#ifndef PHYSICS_RESTITUTIONTOOL_HPP
#define PHYSICS_RESTITUTIONTOOL_HPP

#include <Tools/Tool.hpp>

class RestitutionTool : public Tool {
public:
	RestitutionTool(Game* _game);
	~RestitutionTool();

	// OnPress
	virtual void OnPress(Entity* _entity, sf::Vector2f _pos, sf::Mouse::Button);

	// Update
	virtual void Update(float _deltatime);

private:
	// The restitution value to set
	float restitution;
};

#endif