#ifndef PHYSICS_TOOLSWINDOW_HPP
#define PHYSICS_TOOLSWINDOW_HPP

#include <Gwen/Gwen.h>
#include <Gwen/Controls/WindowControl.h>

#include <Game/Game.hpp>

class ToolsWindow : public Gwen::Controls::WindowControl {
public:
	ToolsWindow(Gwen::Controls::Base* _parent, Game* _game);
	~ToolsWindow();

	// Select tool functions
	void SelectSelectTool();
	void SelectRectangleTool();
	void SelectCircleTool();
	void SelectPolygonTool();
	void SelectRemoveTool();
	void SelectMoveTool();
	void SelectWeldTool();
	void SelectMotorJointTool();
	void SelectRotateTool();
	void SetBodyTypeTool();
	void SetDistanceJointTool();
	void SetFrictionTool();
	void SetRestitutionTool();
	void SetDensityTool();

	// Set a tool
	void SetTool(int _i);

private:
	// The game
	Game *game;

	// Controls
	Gwen::Controls::Button* buttons[20];
};

#endif