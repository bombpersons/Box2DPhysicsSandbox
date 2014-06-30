#include <Controls/MenuBar.hpp>

#include <Game/Game.hpp>
#include <Entities/PhysicsEntity.hpp>
#include <Entities/Joints/MotorJointEntity.hpp>
#include <Entities/Joints/DistanceJointEntity.hpp>
#include <Entities/Joints/WeldJointEntity.hpp>

#include <Gwen/Controls/Dialogs/FileOpen.h>

#include <Serialization/WorldSerializer.hpp>

MenuBar::MenuBar(Gwen::Controls::Base* _parent, Game* _game) : MenuStrip(_parent) {
	{
		Gwen::Controls::MenuItem* root = this->AddItem("File");
		root->GetMenu()->AddItem("New")->SetAction(this, &MenuBar::New);
		root->GetMenu()->AddItem("Save")->SetAction(this, &MenuBar::Save);
		root->GetMenu()->AddItem("Open")->SetAction(this, &MenuBar::Open);
	}
	{
		Gwen::Controls::MenuItem* root = this->AddItem("Scenes");
		root->GetMenu()->AddItem("Scene 1")->SetAction(this, &MenuBar::CreateScene1);
		root->GetMenu()->AddItem("Scene 2")->SetAction(this, &MenuBar::CreateScene2);
	}
	{
		Gwen::Controls::MenuItem* root = this->AddItem("Options");
		Gwen::Controls::MenuItem* smoothing = root->GetMenu()->AddItem("Physics Smoothing");
		smoothing->GetMenu()->AddItem("None")->SetAction(this, &MenuBar::SetSmoothingNone);
		smoothing->GetMenu()->AddItem("Extrapolate")->SetAction(this, &MenuBar::SetSmoothingExtrapolate);
		smoothing->GetMenu()->AddItem("Interpolate")->SetAction(this, &MenuBar::SetSmoothingInterpolate);
		
		Gwen::Controls::MenuItem* step = root->GetMenu()->AddItem("Time Step");
		step->GetMenu()->AddItem("5 fps")->SetAction(this, &MenuBar::SetTimeStep5);
		step->GetMenu()->AddItem("10 fps")->SetAction(this, &MenuBar::SetTimeStep10);
		step->GetMenu()->AddItem("30 fps")->SetAction(this, &MenuBar::SetTimeStep30);
		step->GetMenu()->AddItem("60 fps")->SetAction(this, &MenuBar::SetTimeStep60);

		Gwen::Controls::MenuItem* friction = root->GetMenu()->AddItem("Air Friction");
		friction->GetMenu()->AddItem("On")->SetAction(this, &MenuBar::TurnOnAirFriction);
		friction->GetMenu()->AddItem("Off")->SetAction(this, &MenuBar::TurnOffAirFriction);
	}

	// Set the game
	game = _game;
}

MenuBar::~MenuBar() {
}

void MenuBar::New() {
	game->ClearEntities((Entity*)game->GetUI());
	game->GetCamera().SetPosition(sf::Vector2f(0, 0));
}

void MenuBar::Save() {
	game->SetPhysicsActive(false);
	Gwen::Dialogs::FileSave(true, "Name", "Start Path", ".bin", this, &MenuBar::SaveFile);
}

void MenuBar::SaveFile(Gwen::Event::Info _info) {
	WorldSerializer::Serialize(game, _info.String.c_str());
	game->SetPhysicsActive(false);
}

void MenuBar::Open() {
	game->SetPhysicsActive(false);
	Gwen::Dialogs::FileOpen(true, "Name", "Start Path", ".bin", this, &MenuBar::OpenFile);
}

void MenuBar::OpenFile(Gwen::Event::Info _info) {
	WorldSerializer::Deserialize(game, _info.String.c_str());
	game->SetPhysicsActive(false);
	game->GetCamera().SetPosition(sf::Vector2f(0, 0));
}

void MenuBar::CreateScene1() {
	WorldSerializer::Deserialize(game, "data/levels/scene1.bin");
	game->SetPhysicsActive(false);
	game->GetCamera().SetPosition(sf::Vector2f(0, 0));
}

void MenuBar::CreateScene2() {
	WorldSerializer::Deserialize(game, "data/levels/scene2.bin");
	game->SetPhysicsActive(false);
	game->GetCamera().SetPosition(sf::Vector2f(0, 0));
}

void MenuBar::SetSmoothingNone() {
	game->SetSmoothing(Game::NONE);
}

void MenuBar::SetSmoothingExtrapolate() {
	game->SetSmoothing(Game::EXTRAPOLATION);
}

void MenuBar::SetSmoothingInterpolate() {
	game->SetSmoothing(Game::INTERPOLATION);
}

void MenuBar::SetTimeStep5() {
	game->SetPhysicsStepTime(5);
}
void MenuBar::SetTimeStep10() {
	game->SetPhysicsStepTime(10);
}
void MenuBar::SetTimeStep30() {
	game->SetPhysicsStepTime(30);
}
void MenuBar::SetTimeStep60() {
	game->SetPhysicsStepTime(60);
}

void MenuBar::TurnOnAirFriction() {
	game->SetAirFriction(true);
}
void MenuBar::TurnOffAirFriction() {
	game->SetAirFriction(false);
}