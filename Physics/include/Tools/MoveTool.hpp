#ifndef PHYSICS_MOVETOOL_HPP
#define PHYSICS_MOVETOOL_HPP

#include <Tools/Tool.hpp>
#include <Box2D/Box2D.h>

class MoveTool : public Tool {
public:
	MoveTool(Game* _game);
	~MoveTool();

	virtual void OnPress(Entity* _entity, sf::Vector2f _pos, sf::Mouse::Button _button);
	virtual void OnRelease(Entity* _entity, sf::Vector2f _pos, sf::Mouse::Button _button);

	virtual void Update(float _deltatime);

private:
	Entity* drag;
	sf::Vector2f offset;
	float rotation;
};

#endif