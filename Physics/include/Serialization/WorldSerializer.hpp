#ifndef PHYSICS_WORLDSERIALIZER_HPP
#define PHYSICS_WORLDSERIALIZER_HPP

#include <Game/Game.hpp>

class WorldSerializer {
public:
	static bool Serialize(Game* _game, const char* _filename);
	static bool Deserialize(Game* _game, const char* _filename);

private:

};

#endif