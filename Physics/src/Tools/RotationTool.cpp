#include <Tools/RotationTool.hpp>
#include <Game/Game.hpp>
#include <Entities/Entity.hpp>
#include <Entities/PhysicsEntity.hpp>

#include <iostream>

RotationTool::RotationTool(Game* _game) : Tool(_game) {
	drag = NULL;
}

RotationTool::~RotationTool() {

}

void RotationTool::OnPress(Entity* _entity, sf::Vector2f _pos, sf::Mouse::Button _button)
{
	// Detect the first press.
	if (_button == sf::Mouse::Button::Left) {
		if (_entity != NULL) {
			// Set this entity to be the thing we are dragging.
			drag = _entity;

			// Get the offset from the center of this entity
			offset = _entity->GetPosition() - _pos;

			// Get the original rotation
			rotation = _entity->GetRotation();
		}
	}
}

void RotationTool::OnRelease(Entity* _entity, sf::Vector2f _pos, sf::Mouse::Button _button)
{
	if (_button == sf::Mouse::Button::Left) {
		// Stop dragging it.
		drag = NULL;
		offset = sf::Vector2f(0, 0);
	}
}

void RotationTool::OnDrag(sf::Vector2f _delta, sf::Mouse::Button _button) {
	if (_button == sf::Mouse::Button::Left) {
		if (drag != NULL) {
			rotation += _delta.x;
		}
	}
}

void RotationTool::Update(float _deltatime) {
	if (drag != NULL) {
		// Get the position of the cursor in world space.
		sf::Vector2f pos = game->GetTarget()->mapPixelToCoords(sf::Mouse::getPosition(*(game->GetTarget())), game->GetTarget()->getView());
		pos += offset;
		drag->SetRotation(rotation);

		// If this is a physics object try to keep it still.
		PhysicsEntity* entity = dynamic_cast<PhysicsEntity*>(drag);
		if (entity != NULL) {
			entity->SetAngularVelocity(0);
			entity->Sleep(false);
			std::cout << entity->GetRotation() << std::endl;
		}
	}
}