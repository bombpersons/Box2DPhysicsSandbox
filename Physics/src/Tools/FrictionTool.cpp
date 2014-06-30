#include <Tools/FrictionTool.hpp>
#include <Entities/PhysicsEntity.hpp>
#include <Entities/UIEntity.hpp>

FrictionTool::FrictionTool(Game* _game) : Tool(_game) {
}

FrictionTool::~FrictionTool() {
}

void FrictionTool::OnPress(Entity* _entity, sf::Vector2f _pos, sf::Mouse::Button _button) {
	if (_button == sf::Mouse::Button::Left) {
		// Check if the entity is a physics entity.
		PhysicsEntity* entity = dynamic_cast<PhysicsEntity*>(_entity);
		if (entity != NULL) {
			// Set the friction on the entity
			entity->SetFriction(friction);
		}
	}
}

void FrictionTool::Update(float _deltatime) {
	// Get the values from the properties window.
	Gwen::Controls::GroupBox* box = game->GetUI()->GetPropertiesWindow()->GetPanel(11);
	
	// Get the friction
	friction = atof(box->FindChildByName("FrictionBox", true)->GetValue().c_str());
}