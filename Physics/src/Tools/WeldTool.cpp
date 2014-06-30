#include <Tools/WeldTool.hpp>

WeldTool::WeldTool(Game* _game) : Tool(_game) {
	clickcount = 0;
}

WeldTool::~WeldTool() {
}

// Unequip
void WeldTool::Unequipped() {
	// Wipe the previous stuff
	clickcount = 0;
	entities[0] = 0;
	entities[1] = 0;
}

// Button pressed
void WeldTool::OnPress(Entity* _entity, sf::Vector2f _pos, sf::Mouse::Button _button) {
	// If it's the left mouse button
	if (_button == sf::Mouse::Button::Left) {
		// Ignore if we didn't click on an entity.
		PhysicsEntity* entity = dynamic_cast<PhysicsEntity*>(_entity);
		if (entity != NULL) {
			entities[clickcount] = entity;
			pos[clickcount] = _pos;
			clickcount++;

			// If the clickcount is 2 or more, then put down a weld joint and reset.
			if (clickcount >= 2 ) {
				// Make sure both entities are different
				if (entities[0] != entities[1]) {
					// Make a weld joint.
					WeldJointEntity* weld = new WeldJointEntity(game);
					weld->SetBodyA(entities[0]);
					weld->SetBodyB(entities[1]);
					weld->SetAnchorA(pos[0]);
					weld->SetAnchorB(pos[1]);

					// Create the joint.
					weld->CreateJoint();
					game->GetEntityList()->Add(weld);
				}

				// Reset.
				clickcount = 0;
			}
		}
	}
}