#ifndef PHYSICS_SELECTTOOL_HPP
#define PHYSICS_SELECTTOOL_HPP

#include <Tools/Tool.hpp>

class SelectTool : public Tool {
public:
	SelectTool(Game* _game);
	virtual ~SelectTool();

	// Detect the object to select
	virtual void OnPress(Entity* _entity, sf::Vector2f _pos, sf::Mouse::Button _button);
	virtual void OnRelease(Entity* _entity, sf::Vector2f _pos, sf::Mouse::Button _button);

private:

};

#endif