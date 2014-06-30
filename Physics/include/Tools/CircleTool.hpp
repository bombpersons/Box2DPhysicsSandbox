#ifndef PHYSICS_CIRCLETOOL_HPP
#define PHYSICS_CIRCLETOOL_HPP

#include <Tools/Tool.hpp>

class CircleTool : public Tool {
public:
	CircleTool(Game* _game);
	~CircleTool();

	// Detect the object to select
	virtual void OnPress(Entity* _entity, sf::Vector2f _pos, sf::Mouse::Button _button);
	virtual void OnRelease(Entity* _entity, sf::Vector2f _pos, sf::Mouse::Button _button);

	// Update
	virtual void Update(float _deltatime);

private:
	// Values
	float radius;
};

#endif