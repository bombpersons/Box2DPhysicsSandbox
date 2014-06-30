#ifndef PHYSICS_RECTANGLETOOL_HPP
#define PHYSICS_RECTANGLETOOL_HPP

#include <Tools/Tool.hpp>

class RectangleTool : public Tool {
public:
	RectangleTool(Game* _game);
	virtual ~RectangleTool();

	// Called when the tool is used.
	virtual void OnPress(Entity* _entity, sf::Vector2f _pos, sf::Mouse::Button _button);
	virtual void OnRelease(Entity* _entity, sf::Vector2f _pos, sf::Mouse::Button _button);

	// Update
	virtual void Update(float _deltatime);

private:
	float width, height;
};

#endif