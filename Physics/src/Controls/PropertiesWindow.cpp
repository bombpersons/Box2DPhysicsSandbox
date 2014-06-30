#include <Controls/PropertiesWindow.hpp>

PropertiesWindow::PropertiesWindow(Gwen::Controls::Base* _parent, Game* _game) : WindowControl(_parent) {
	// Set the game
	game = _game;

	// Set defaults
	SetTitle("Properties");
	SetDeleteOnClose(false);
	SetClosable(false);
	SetSize(200, 400);
	SetPos(1000, 0);
	// NULL all panels
	memset(panels, 0, sizeof(panels));

	// Create the panels
	CreatePanels();
}

PropertiesWindow::~PropertiesWindow() {
}

void PropertiesWindow::OnToolChange(int _id) {
	// Hide all the panels
	for (int i = 0; i < sizeof(panels) / sizeof(Gwen::Controls::GroupBox*); ++i) {
		if (panels[i] != NULL) {
			panels[i]->SetHidden(true);
			if (_id == i)
				panels[i]->SetHidden(false);
		}
	}
}

void PropertiesWindow::CreatePanels() {
	// The select tool panel
	panels[0] = new Gwen::Controls::GroupBox(this, "Select Tool");
	panels[0]->Dock(Gwen::Pos::Fill);
	Gwen::Controls::Label* text = new Gwen::Controls::Label(panels[0]);
	text->SetText(L"Select Tool Panel");

	// The rectangle tool panel
	panels[1] = new Gwen::Controls::GroupBox(this, "Rectangle Tool");
	panels[1]->Dock(Gwen::Pos::Fill);
	Gwen::Controls::Label* rectWidthText = new Gwen::Controls::Label(panels[1], "WidthLabel");
	rectWidthText->SetText("Width: ");
	rectWidthText->SetPos(10, 10);
	Gwen::Controls::Label* rectHeightText = new Gwen::Controls::Label(panels[1], "HeightLabel");
	rectHeightText->SetText("Height: ");
	rectHeightText->SetPos(10, 50);
	Gwen::Controls::TextBox* rectWidthBox = new Gwen::Controls::TextBox(panels[1], "WidthBox");
	rectWidthBox->SetPos(50, 10);
	rectWidthBox->SetText("2");
	rectWidthBox->SetSize(50, 20);
	Gwen::Controls::TextBox* rectHeightBox = new Gwen::Controls::TextBox(panels[1], "HeightBox");
	rectHeightBox->SetPos(50, 50);
	rectHeightBox->SetText("2");
	rectHeightBox->SetSize(50, 20);

	// The circle tool panel
	panels[2] = new Gwen::Controls::GroupBox(this, "Circle Tool");
	panels[2]->Dock(Gwen::Pos::Fill);
	Gwen::Controls::Label* circleRadiusText = new Gwen::Controls::Label(panels[2], "RadiusLabel");
	circleRadiusText->SetText("Radius: ");
	circleRadiusText->SetPos(10, 10);
	Gwen::Controls::TextBox* circleRadiusBox = new Gwen::Controls::TextBox(panels[2], "RadiusBox");
	circleRadiusBox->SetText("0.5");
	circleRadiusBox->SetPos(50, 10);
	circleRadiusBox->SetSize(50, 20);

	// Motor tool panel
	panels[7] = new Gwen::Controls::GroupBox(this, "Motor Tool");
	panels[7]->Dock(Gwen::Pos::Fill);
	Gwen::Controls::Label* motorSpeedText = new Gwen::Controls::Label(panels[7], "MotorSpeedLabel");
	motorSpeedText->SetText("Speed: ");
	motorSpeedText->SetPos(10, 10);
	Gwen::Controls::TextBox* motorSpeedBox = new Gwen::Controls::TextBox(panels[7], "MotorSpeedBox");
	motorSpeedBox->SetText("20");
	motorSpeedBox->SetPos(50, 10);
	motorSpeedBox->SetSize(50, 20);
	Gwen::Controls::Label* motorTorqueText = new Gwen::Controls::Label(panels[7], "MotorTorqueLabel");
	motorTorqueText->SetText("Torque: ");
	motorTorqueText->SetPos(10, 50);
	Gwen::Controls::TextBox* motorTorqueBox = new Gwen::Controls::TextBox(panels[7], "MotorTorqueBox");
	motorTorqueBox->SetText("10");
	motorTorqueBox->SetPos(50, 50);
	motorTorqueBox->SetSize(50, 20);
	Gwen::Controls::CheckBoxWithLabel* userControlled = new Gwen::Controls::CheckBoxWithLabel(panels[7], "MotorUserControlledCheckBox");
	userControlled->Label()->SetText("User Controlled (Arrow Keys)");
	userControlled->Checkbox()->SetChecked(true);
	userControlled->SetPos(10, 90);
	userControlled->SetSize(200, 20);
	Gwen::Controls::Label* motorDampingLabel = new Gwen::Controls::Label(panels[7], "MotorDampingLabel");
	motorDampingLabel->SetText("Damping: ");
	motorDampingLabel->SetPos(10, 130);
	Gwen::Controls::TextBox* motorDampingBox = new Gwen::Controls::TextBox(panels[7], "MotorDampingBox");
	motorDampingBox->SetText("0.7");
	motorDampingBox->SetPos(80, 130);
	motorDampingBox->SetSize(50, 20);
	Gwen::Controls::Label* motorFrequencyLabel = new Gwen::Controls::Label(panels[7], "MotorFrequencyLabel");
	motorFrequencyLabel->SetText("Frequency: ");
	motorFrequencyLabel->SetPos(10, 170);
	Gwen::Controls::TextBox* motorFrequencyBox = new Gwen::Controls::TextBox(panels[7], "MotorFrequencyBox");
	motorFrequencyBox->SetText("2.0");
	motorFrequencyBox->SetPos(80, 170);
	motorFrequencyBox->SetSize(50, 20);

	// Bodytype tool
	panels[9] = new Gwen::Controls::GroupBox(this, "Body Type Tool");
	panels[9]->Dock(Gwen::Pos::Fill);
	Gwen::Controls::ComboBox* combobox = new Gwen::Controls::ComboBox(panels[9], "ComboBox");
	combobox->SetPos(10, 10);
	combobox->AddItem(L"Dynamic", "Dynamic");
	combobox->AddItem(L"Static", "Static");
	combobox->AddItem(L"Kinematic", "Kinematic");

	// Distance Joint tool
	panels[10] = new Gwen::Controls::GroupBox(this, "Distance Joint Tool");
	panels[10]->Dock(Gwen::Pos::Fill);
	Gwen::Controls::Label* distanceDampingLabel = new Gwen::Controls::Label(panels[10], "DampingLabel");
	distanceDampingLabel->SetPos(10, 10);
	distanceDampingLabel->SetText("Damping: ");
	Gwen::Controls::TextBox* distanceDampingBox = new Gwen::Controls::TextBox(panels[10], "DampingBox");
	distanceDampingBox->SetPos(80, 10);
	distanceDampingBox->SetSize(50, 20);
	distanceDampingBox->SetText("0.7");
	Gwen::Controls::Label* distanceFrequencyLabel = new Gwen::Controls::Label(panels[10], "FrequencyLabel");
	distanceFrequencyLabel->SetPos(10, 50);
	distanceFrequencyLabel->SetText("Frequency: ");
	Gwen::Controls::TextBox* distanceFrequencyBox = new Gwen::Controls::TextBox(panels[10], "FrequencyBox");
	distanceFrequencyBox->SetPos(80, 50);
	distanceFrequencyBox->SetSize(50, 20);
	distanceFrequencyBox->SetText("2.0");

	// Friction Tool
	panels[11] = new Gwen::Controls::GroupBox(this, "Friction Tool");
	panels[11]->Dock(Gwen::Pos::Fill);
	Gwen::Controls::Label* frictionLabel = new Gwen::Controls::Label(panels[11], "FrictionLabel");
	frictionLabel->SetPos(10, 10);
	frictionLabel->SetText("Friction");
	Gwen::Controls::TextBox* frictionBox = new Gwen::Controls::TextBox(panels[11], "FrictionBox");
	frictionBox->SetPos(50, 10);
	frictionBox->SetSize(50, 20);
	frictionBox->SetText("0.5");

	// Restitution Tool
	panels[12] = new Gwen::Controls::GroupBox(this, "Restitution Tool");
	panels[12]->Dock(Gwen::Pos::Fill);
	Gwen::Controls::Label* restitutionLabel = new Gwen::Controls::Label(panels[12], "RestitutionLabel");
	restitutionLabel->SetPos(10, 10);
	restitutionLabel->SetText("Restitution");
	Gwen::Controls::TextBox* restitutionBox = new Gwen::Controls::TextBox(panels[12], "RestitutionBox");
	restitutionBox->SetPos(50, 10);
	restitutionBox->SetSize(50, 20);
	restitutionBox->SetText("0.5");

	// Density Tool
	panels[13] = new Gwen::Controls::GroupBox(this, "Density Tool");
	panels[13]->Dock(Gwen::Pos::Fill);
	Gwen::Controls::Label* densityLabel = new Gwen::Controls::Label(panels[13], "DensityLabel");
	densityLabel->SetPos(10, 10);
	densityLabel->SetText("Density");
	Gwen::Controls::TextBox* densityBox = new Gwen::Controls::TextBox(panels[13], "DensityBox");
	densityBox->SetPos(50, 10);
	densityBox->SetSize(50, 20);
	densityBox->SetText("1.0");
}

Gwen::Controls::GroupBox* PropertiesWindow::GetPanel(int _index) {
	return panels[_index];
}