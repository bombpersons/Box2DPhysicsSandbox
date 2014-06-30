#include <Tools/BodyTypeTool.hpp>
#include <Entities/UIEntity.hpp>
#include <Entities/PhysicsEntity.hpp>

BodyTypeTool::BodyTypeTool(Game* _game) : Tool(_game) {

}

BodyTypeTool::~BodyTypeTool() {
}

void BodyTypeTool::OnRelease(Entity* _entity, sf::Vector2f _pos, sf::Mouse::Button _button) {
	if (_button == sf::Mouse::Button::Left) {
		if (_entity != NULL) {
			PhysicsEntity* entity = dynamic_cast<PhysicsEntity*>(_entity);
			if (entity != NULL) {
				entity->SetBodyType(type);
			}
		}
	}
}

void BodyTypeTool::Update(float _deltatime) {
	// Get the values from the properties window.
	Gwen::Controls::GroupBox* box = game->GetUI()->GetPropertiesWindow()->GetPanel(9);
	
	// Get the width and height
	Gwen::TextObject text = box->FindChildByName("ComboBox", true)->GetValue();
	if (text == "Dynamic")
		type = b2_dynamicBody;
	if (text == "Static")
		type = b2_staticBody;
	if (text == "Kinematic")
		type = b2_kinematicBody;
}