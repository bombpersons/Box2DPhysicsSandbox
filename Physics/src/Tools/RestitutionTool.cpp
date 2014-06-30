#include <Tools/RestitutionTool.hpp>
#include <Entities/PhysicsEntity.hpp>
#include <Entities/UIEntity.hpp>

RestitutionTool::RestitutionTool(Game* _game) : Tool(_game) {
}

RestitutionTool::~RestitutionTool() {
}

void RestitutionTool::OnPress(Entity* _entity, sf::Vector2f _pos, sf::Mouse::Button _button) {
	if (_button == sf::Mouse::Button::Left) {
		// Check if the entity is a physics entity.
		PhysicsEntity* entity = dynamic_cast<PhysicsEntity*>(_entity);
		if (entity != NULL) {
			// Set the restitution on the entity
			entity->SetRestitution(restitution);
		}
	}
}

void RestitutionTool::Update(float _deltatime) {
	// Get the values from the properties window.
	Gwen::Controls::GroupBox* box = game->GetUI()->GetPropertiesWindow()->GetPanel(12);
	
	// Get the friction
	restitution = atof(box->FindChildByName("RestitutionBox", true)->GetValue().c_str());
}