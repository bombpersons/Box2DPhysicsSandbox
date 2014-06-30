#ifndef PHYSICS_ENTITYIDGENERATOR_HPP
#define PHYSICS_ENTITYIDGENERATOR_HPP

#include <cstdlib>

class EntityIDGenerator {
public:
	~EntityIDGenerator();

	static void Init() {
		srand(time(NULL));
	}

	static unsigned int GenerateID() {
		return rand();
	}

private:
	EntityIDGenerator() {}
};

#endif