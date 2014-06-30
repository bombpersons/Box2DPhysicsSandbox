#include <Tools/CircleTool.hpp>

#include <Entities/PhysicsEntity.hpp>
#include <Entities/UIEntity.hpp>
#include <cstdlib>

CircleTool::CircleTool(Game* _game) : Tool(_game) {
	radius = 1.0f;
}

CircleTool::~CircleTool() {
}

void CircleTool::OnPress(Entity* _entity, sf::Vector2f _pos, sf::Mouse::Button _button) {
}

void CircleTool::OnRelease(Entity* _entity, sf::Vector2f _pos, sf::Mouse::Button _button) {
	if (_button == sf::Mouse::Button::Left) {
		// Create an entity here.
		PhysicsEntity* entity = new PhysicsEntity(game);
		entity->SetCircle(radius);
		entity->SetPosition(_pos);

		game->GetEntityList()->Add(entity);
	}
}

void CircleTool::Update(float _timedelta) {
	// Get the values from the properties window.
	Gwen::Controls::GroupBox* box = game->GetUI()->GetPropertiesWindow()->GetPanel(2);
	
	// Get the radius
	radius = atof(box->FindChildByName("RadiusBox", true)->GetValue().c_str());
	if (radius == 0.0f)
		radius = 0.1f;
}