#ifndef PHYSICS_UIENTITY_HPP
#define PHYSICS_UIENTITY_HPP

#include <Entities/Entity.hpp>
#include <Gwen/Gwen.h>
#include <Controls/ToolsWindow.hpp>
#include <Controls/PropertiesWindow.hpp>
#include <Controls/MenuBar.hpp>

class UIEntity : public Entity {
public:
	// Constructor
	UIEntity(Game* _game);
	~UIEntity();

	// Get the windows
	ToolsWindow* GetToolsWindow();
	PropertiesWindow* GetPropertiesWindow();

	// Update
	virtual void Update(float _deltatime);

private:
	ToolsWindow* tools;
	PropertiesWindow* properties;
	MenuBar* menubar;
};

#endif