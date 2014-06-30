#include <Tools/DensityTool.hpp>
#include <Entities/PhysicsEntity.hpp>
#include <Entities/UIEntity.hpp>

DensityTool::DensityTool(Game* _game) : Tool(_game) {
}

DensityTool::~DensityTool() {
}

void DensityTool::OnPress(Entity* _entity, sf::Vector2f _pos, sf::Mouse::Button _button) {
	if (_button == sf::Mouse::Button::Left) {
		// Check if the entity is a physics entity.
		PhysicsEntity* entity = dynamic_cast<PhysicsEntity*>(_entity);
		if (entity != NULL) {
			// Set the restitution on the entity
			entity->SetDensity(density);
		}
	}
}

void DensityTool::Update(float _deltatime) {
	// Get the values from the properties window.
	Gwen::Controls::GroupBox* box = game->GetUI()->GetPropertiesWindow()->GetPanel(13);
	
	// Get the friction
	density = atof(box->FindChildByName("DensityBox", true)->GetValue().c_str());
}