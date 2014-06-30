#ifndef PHYSICS_BODYTYPETOOL_HPP
#define PHYSICS_BODYTYPETOOL_HPP

#include <Tools/Tool.hpp>
#include <Box2D/Box2D.h>

class BodyTypeTool : public Tool {
public:
	BodyTypeTool(Game* _game);
	~BodyTypeTool();

	// OnRelease
	virtual void OnRelease(Entity* _entity, sf::Vector2f _pos, sf::Mouse::Button _button);

	// Update
	virtual void Update(float _deltatime);

private:
	b2BodyType type;
};

#endif