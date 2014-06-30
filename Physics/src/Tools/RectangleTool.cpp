#include <Tools/RectangleTool.hpp>
#include <Entities/Entity.hpp>
#include <Game/Game.hpp>

#include <Entities/PhysicsEntity.hpp>
#include <Entities/UIEntity.hpp>

RectangleTool::RectangleTool(Game* _game) : Tool(_game) {
	width = 0.1f;
	height = 0.1f;
}

RectangleTool::~RectangleTool() {
}

void RectangleTool::OnPress(Entity* _entity, sf::Vector2f _pos, sf::Mouse::Button _button) {
}

void RectangleTool::OnRelease(Entity* _entity, sf::Vector2f _pos, sf::Mouse::Button _button) {
	if (_button == sf::Mouse::Button::Left) {
		// Create an entity here.
		PhysicsEntity* entity = new PhysicsEntity(game);
		entity->SetRectangle(sf::Vector2f(width/2.0f, height/2.0f));
		entity->SetPosition(_pos);

		game->GetEntityList()->Add(entity);
	}
}

void RectangleTool::Update(float _deltatime) {
	// Get the values from the properties window.
	Gwen::Controls::GroupBox* box = game->GetUI()->GetPropertiesWindow()->GetPanel(1);
	
	// Get the width and height
	width = atof(box->FindChildByName("WidthBox", true)->GetValue().c_str());
	if (width == 0.0f)
		width = 0.1f;
	height = atof(box->FindChildByName("HeightBox", true)->GetValue().c_str());
	if (height == 0.0f)
		height = 0.1f;
}