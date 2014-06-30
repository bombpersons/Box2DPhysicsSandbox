#ifndef PHYSICS_PROPERTIESWINDOW_HPP
#define PHYSICS_PROPERTIESWINDOW_HPP

#include <Gwen/Gwen.h>
#include <Gwen/Controls/WindowControl.h>

#include <Game/Game.hpp>

class PropertiesWindow : public Gwen::Controls::WindowControl {
public:
	PropertiesWindow(Gwen::Controls::Base* _parent, Game* _game);
	~PropertiesWindow();

	// Called by the game when the tool changes.
	void OnToolChange(int _id);

	// Create the panels
	void CreatePanels();

	// Get a panel
	Gwen::Controls::GroupBox* GetPanel(int _index);
private:
	// The game.
	Game* game;

	// Different panels for different tools.
	Gwen::Controls::GroupBox* panels[20];
};

#endif