#ifndef PHYSICS_REMOVETOOL_HPP
#define PHYSICS_REMOVETOOL_HPP

#include <Tools/Tool.hpp>

class RemoveTool : public Tool {
public:
	RemoveTool(Game* _game);
	~RemoveTool();

	// Detect the object to select
	virtual void OnPress(Entity* _entity, sf::Vector2f _pos, sf::Mouse::Button _button);
	virtual void OnRelease(Entity* _entity, sf::Vector2f _pos, sf::Mouse::Button _button);

private:

};

#endif