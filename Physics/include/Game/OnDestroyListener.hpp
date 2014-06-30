#ifndef PHYSICS_ONDESTROYLISTENER_HPP
#define PHYSICS_ONDESTROYLISTENER_HPP

#include <Box2D/Box2D.h>
#include <vector>

class Game;
class Entity;

class OnDestroyListener : public b2DestructionListener {
public:
	OnDestroyListener();
	~OnDestroyListener();

	// Overrides
	virtual void SayGoodbye(b2Joint* _joint);
	virtual void SayGoodbye(b2Fixture* _fixture);

	// Destroy the entities
	void DestroyEntities(Game* _game);
	void Clear();

private:
	std::vector<Entity*> todestroy;
};

#endif