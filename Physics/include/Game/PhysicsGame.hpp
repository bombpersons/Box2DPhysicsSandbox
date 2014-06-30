#ifndef PHYSICS_PHYSICSGAME_HPP
#define PHYSICS_PHYSICSGAME_HPP

#include <Game/Game.hpp>

class PhysicsGame : public Game {
public:
	// Constructor
	PhysicsGame(int _width, int _height, char* _title);
	virtual ~PhysicsGame();

private:
};

#endif