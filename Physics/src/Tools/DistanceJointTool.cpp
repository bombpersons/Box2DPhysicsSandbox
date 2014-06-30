#include <Tools/DistanceJointTool.hpp>
#include <Entities/UIEntity.hpp>

DistanceJointTool::DistanceJointTool(Game* _game) : Tool(_game) {
	clickcount = 0;
}

DistanceJointTool::~DistanceJointTool() {	
}

void DistanceJointTool::OnPress(Entity* _entity, sf::Vector2f _pos, sf::Mouse::Button _button) {
	if (_button == sf::Mouse::Button::Left) {
		// Check if the entity is a physics entity
		PhysicsEntity* entity = dynamic_cast<PhysicsEntity*>(_entity);
		if (entity != NULL) {
			entities[clickcount] = entity;
			pos[clickcount] = _pos;
			clickcount++;

			// If clickcount is more than 2 then we can make the joint
			if (clickcount >= 2) {

				// Create the entity
				DistanceJointEntity* joint = new DistanceJointEntity(game);
				joint->SetAnchorA(pos[0]);
				joint->SetAnchorB(pos[1]);
				joint->SetBodyA(entities[0]);
				joint->SetBodyB(entities[1]);
				joint->CreateJoint();

				// Add it
				game->GetEntityList()->Add(joint);

				// Reset.
				clickcount = 0;
			}
		}
	}
}

void DistanceJointTool::Update(float _deltatime) {
	// Get the values from the properties window.
	Gwen::Controls::GroupBox* box = game->GetUI()->GetPropertiesWindow()->GetPanel(7);
	
	// Get the damping and frequency
	damping = atof(box->FindChildByName("MotorDampingBox", true)->GetValue().c_str());
	frequency = atof(box->FindChildByName("MotorFrequencyBox", true)->GetValue().c_str());
}