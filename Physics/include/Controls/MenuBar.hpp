#ifndef PHYSICS_MENUBAR_HPP
#define PHYSICS_MENUBAR_HPP

#include <Gwen/Controls/Button.h>
#include <Gwen/Controls/MenuStrip.h>

class Game;

class MenuBar : public Gwen::Controls::MenuStrip { 
public:
	MenuBar(Gwen::Controls::Base* _parent, Game* _game);
	~MenuBar();

	// Save / Open
	void New();
	void Save();
	void SaveFile(Gwen::Event::Info _info);
	void Open();
	void OpenFile(Gwen::Event::Info _info);

	// Create scenes
	void CreateScene1();
	void CreateScene2();

	// Set smoothing modes
	void SetSmoothingNone();
	void SetSmoothingExtrapolate();
	void SetSmoothingInterpolate();

	// Set time step
	void SetTimeStep5();
	void SetTimeStep10();
	void SetTimeStep30();
	void SetTimeStep60();

	// Turn on / off the air friction
	void TurnOnAirFriction();
	void TurnOffAirFriction();

private:
	Game* game;
};

#endif