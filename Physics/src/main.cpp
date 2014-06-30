#include <SFML/Graphics.hpp>
#include <cmath>

#include <Gwen/Renderers/SFML2.h>
#include <Gwen/Input/SFML.h>

#include <Gwen/Skins/Simple.h>
#include <Gwen/Skins/TexturedBase.h>
#include <Gwen/UnitTest/UnitTest.h>

#include <Game/PhysicsGame.hpp>

int main(int _argc, char** _argv) {
	PhysicsGame game(800, 600, "The Game");
	game.Run();

	return 0;
}