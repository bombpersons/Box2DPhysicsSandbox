#ifndef PHYSICS_ROTATIONTOOL_HPP
#define PHYSICS_ROTATIONTOOL_HPP

#include <Tools/Tool.hpp>
#include <Box2D/Box2D.h>

class RotationTool : public Tool {
public:
	RotationTool(Game* _game);
	~RotationTool();

	virtual void OnPress(Entity* _entity, sf::Vector2f _pos, sf::Mouse::Button _button);
	virtual void OnRelease(Entity* _entity, sf::Vector2f _pos, sf::Mouse::Button _button);
	virtual void OnDrag(sf::Vector2f _delta, sf::Mouse::Button _button);

	virtual void Update(float _deltatime);

private:
	Entity* drag;
	sf::Vector2f offset;
	float rotation;
};

#endif