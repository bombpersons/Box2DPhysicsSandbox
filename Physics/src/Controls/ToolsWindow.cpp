#include <Controls/ToolsWindow.hpp>
#include <Entities/PhysicsEntity.hpp>

ToolsWindow::ToolsWindow(Gwen::Controls::Base* _parent, Game* _game) : WindowControl(_parent) {
	// Set the game
	game = _game;
	
	// Null all the buttons
	memset(buttons, 0, sizeof(buttons));

	// Set defaults
	SetTitle("Tool Window");
	SetDeleteOnClose(false);
	SetClosable(false);
	SetSize(170, 300);
	
	// Margin for the buttons
	Gwen::Margin margin(4, 4, 4, 4);

	// Select tool
	buttons[0] = new Gwen::Controls::Button(this);
	buttons[0]->SetPadding(margin);
	buttons[0]->SetText(L"Select");
	buttons[0]->SetPos(0, 0);
	buttons[0]->onUp.Add(this, &ToolsWindow::SelectSelectTool);

	// Rectangle tool
	buttons[1] = new Gwen::Controls::Button(this);
	buttons[1]->SetPadding(margin);
	buttons[1]->SetText(L"Rectangle");
	buttons[1]->SetPos(0, 20);
	buttons[1]->onUp.Add(this, &ToolsWindow::SelectRectangleTool);

	// Circle tool
	buttons[2] = new Gwen::Controls::Button(this);
	buttons[2]->SetPadding(margin);
	buttons[2]->SetText(L"Circle");
	buttons[2]->SetPos(0, 40);
	buttons[2]->onUp.Add(this, &ToolsWindow::SelectCircleTool);

	// Polygon tool
	buttons[3] = new Gwen::Controls::Button(this);
	buttons[3]->SetPadding(margin);
	buttons[3]->SetText(L"Polygon");
	buttons[3]->SetPos(0, 60);
	buttons[3]->onUp.Add(this, &ToolsWindow::SelectPolygonTool);

	// Remove tool
	buttons[4] = new Gwen::Controls::Button(this);
	buttons[4]->SetPadding(margin);
	buttons[4]->SetText(L"Remove");
	buttons[4]->SetPos(0, 80);
	buttons[4]->onUp.Add(this, &ToolsWindow::SelectRemoveTool);

	// Move tool
	buttons[5] = new Gwen::Controls::Button(this);
	buttons[5]->SetPadding(margin);
	buttons[5]->SetText(L"Move");
	buttons[5]->SetPos(0, 100);
	buttons[5]->onUp.Add(this, &ToolsWindow::SelectMoveTool);

	// Weld tool
	buttons[6] = new Gwen::Controls::Button(this);
	buttons[6]->SetPadding(margin);
	buttons[6]->SetText(L"Weld");
	buttons[6]->SetPos(0, 120);
	buttons[6]->onUp.Add(this, &ToolsWindow::SelectWeldTool);

	// MotorJoint tool
	buttons[7] = new Gwen::Controls::Button(this);
	buttons[7]->SetPadding(margin);
	buttons[7]->SetText(L"Motor");
	buttons[7]->SetPos(0, 140);
	buttons[7]->onUp.Add(this, &ToolsWindow::SelectMotorJointTool);
	
	// Rotate tool
	buttons[8] = new Gwen::Controls::Button(this);
	buttons[8]->SetPadding(margin);
	buttons[8]->SetText(L"Rotate");
	buttons[8]->SetPos(0, 160);
	buttons[8]->onUp.Add(this, &ToolsWindow::SelectRotateTool);

	// Bodytype tool
	buttons[9] = new Gwen::Controls::Button(this);
	buttons[9]->SetPadding(margin);
	buttons[9]->SetText(L"Bodytype");
	buttons[9]->SetPos(0, 180);
	buttons[9]->onUp.Add(this, &ToolsWindow::SetBodyTypeTool);

	// Distance Joint tool
	buttons[10] = new Gwen::Controls::Button(this);
	buttons[10]->SetPadding(margin);
	buttons[10]->SetText(L"Distance Joint");
	buttons[10]->SetPos(0, 200);
	buttons[10]->onUp.Add(this, &ToolsWindow::SetDistanceJointTool);

	// Friction Joint tool
	buttons[11] = new Gwen::Controls::Button(this);
	buttons[11]->SetPadding(margin);
	buttons[11]->SetText(L"Friction");
	buttons[11]->SetPos(0, 220);
	buttons[11]->onUp.Add(this, &ToolsWindow::SetFrictionTool);

	// Restitution
	buttons[12] = new Gwen::Controls::Button(this);
	buttons[12]->SetPadding(margin);
	buttons[12]->SetText(L"Restitution");
	buttons[12]->SetPos(0, 240);
	buttons[12]->onUp.Add(this, &ToolsWindow::SetRestitutionTool);

	// Density
	buttons[13] = new Gwen::Controls::Button(this);
	buttons[13]->SetPadding(margin);
	buttons[13]->SetText(L"Density");
	buttons[13]->SetPos(0, 260);
	buttons[13]->onUp.Add(this, &ToolsWindow::SetDensityTool);
}

ToolsWindow::~ToolsWindow() {
	// Delete all the stuff
	for (int i = 0; i < sizeof(buttons) / sizeof(Gwen::Controls::Button*); ++i) {
		if (buttons[i] != NULL)
			delete buttons[i];
	}
}

void ToolsWindow::SelectSelectTool() {
	SetTool(0);
}
void ToolsWindow::SelectRectangleTool() {
	SetTool(1);
}
void ToolsWindow::SelectCircleTool() {
	SetTool(2);
}
void ToolsWindow::SelectPolygonTool() {
	SetTool(3);
}
void ToolsWindow::SelectRemoveTool() {
	SetTool(4);
}
void ToolsWindow::SelectMoveTool() {
	SetTool(5);
}
void ToolsWindow::SelectWeldTool() {
	SetTool(6);
}
void ToolsWindow::SelectMotorJointTool() {
	SetTool(7);
}
void ToolsWindow::SelectRotateTool() {
	SetTool(8);
}
void ToolsWindow::SetBodyTypeTool() {
	SetTool(9);
}
void ToolsWindow::SetDistanceJointTool() {
	SetTool(10);
}
void ToolsWindow::SetFrictionTool() {
	SetTool(11);
}
void ToolsWindow::SetRestitutionTool() {
	SetTool(12);
}
void ToolsWindow::SetDensityTool() {
	SetTool(13);
}

void ToolsWindow::SetTool(int _i) {
	for (int i = 0; i < sizeof(buttons) / sizeof(Gwen::Controls::Button*); ++i) {
		if (buttons[i] != NULL)
			buttons[i]->SetDisabled(false);
	}
	game->SetTool(_i);
	//buttons[_i]->SetDepressed(true);
	buttons[_i]->SetDisabled(true);
}