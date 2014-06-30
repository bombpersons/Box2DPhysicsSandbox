#include <Entities/UIEntity.hpp>

UIEntity::UIEntity(Game* _game) : Entity(_game) {
	// Add UI elements here.
	tools = new ToolsWindow(game->GetCanvas(), _game);
	properties = new PropertiesWindow(game->GetCanvas(), _game);
	menubar = new MenuBar(game->GetCanvas(), _game);

	type = UI_ENTITY;
}

UIEntity::~UIEntity(){ 
	if (tools != NULL)
		delete tools;
	if (properties != NULL)
		delete properties;
}

ToolsWindow* UIEntity::GetToolsWindow() {
	return tools;
}
PropertiesWindow* UIEntity::GetPropertiesWindow() {
	return properties;
}

void UIEntity::Update(float _deltatime) {
	properties->OnToolChange(game->GetCurrentTool());
}