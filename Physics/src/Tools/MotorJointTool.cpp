#include <Tools/MotorJointTool.hpp>

#include <Entities/UIEntity.hpp>

MotorJointTool::MotorJointTool(Game* _game) : Tool(_game) {
	clickcount = 0;
	speed = 0;
	torque = 0;
}

MotorJointTool::~MotorJointTool() {
}

// Unequip
void MotorJointTool::Unequipped() {
	// Wipe the previous stuff
	clickcount = 0;
	entities[0] = 0;
	entities[1] = 0;
}

// Button pressed
void MotorJointTool::OnPress(Entity* _entity, sf::Vector2f _pos, sf::Mouse::Button _button) {
	// If it's the left mouse button
	if (_button == sf::Mouse::Button::Left) {
		// Ignore if we didn't click on an entity.
		PhysicsEntity* entity = dynamic_cast<PhysicsEntity*>(_entity);
		if (entity != NULL) {
			entities[clickcount] = entity;
			pos[clickcount] = _pos;
			clickcount++;

			// If the clickcount is more than 2, then start drawing a line for the axis definition.
			if (clickcount >= 2) {
				axispos[0] = _pos;
			}
		}
	}
}

void MotorJointTool::OnRelease(Entity* _entity, sf::Vector2f _pos, sf::Mouse::Button _button) {
	if (_button == sf::Mouse::Button::Left) {
			// If the clickcount is 2 or more, then put down a weld joint and reset.
			if (clickcount >= 2 ) {
				// Get the difference in position for the axis
				axis = axispos[0] - _pos;

				// Make sure both entities are different
				if (entities[0] != entities[1]) {
					// Make a weld joint.
					MotorJointEntity* weld = new MotorJointEntity(game);
					weld->SetBodyA(entities[1]);
					weld->SetBodyB(entities[0]);
					weld->SetAnchorA(pos[0]);
					weld->SetAnchorB(pos[1]);
					weld->SetMaxTorque(torque);
					weld->SetMotorSpeed(speed);
					weld->SetUserControlled(usercontrolled);
					weld->SetDamping(damping);
					weld->SetFrequency(frequency);
					weld->SetAxis(axis);

					// Create the joint.
					weld->CreateJoint();
					game->GetEntityList()->Add(weld);
				}

				// Reset.
				clickcount = 0;
			}
	}
}

void MotorJointTool::Update(float _deltatime) {
	// Get the values from the properties window.
	Gwen::Controls::GroupBox* box = game->GetUI()->GetPropertiesWindow()->GetPanel(7);
	
	// Get the width and height
	speed = atof(box->FindChildByName("MotorSpeedBox", true)->GetValue().c_str());
	torque = atof(box->FindChildByName("MotorTorqueBox", true)->GetValue().c_str());
	usercontrolled = ((Gwen::Controls::CheckBoxWithLabel*)box->FindChildByName("MotorUserControlledCheckBox", true))->Checkbox()->IsChecked();
	damping = atof(box->FindChildByName("MotorDampingBox", true)->GetValue().c_str());
	frequency = atof(box->FindChildByName("MotorFrequencyBox", true)->GetValue().c_str());
}

void MotorJointTool::Draw(float _deltatime) {
	// Draw the line for the axis
	if (clickcount >= 2) {
		sf::VertexArray array(sf::PrimitiveType::Lines, 2);
		array[0] = sf::Vertex(axispos[0], sf::Color::White);
		array[1] = sf::Vertex(game->GetTarget()->mapPixelToCoords(sf::Mouse::getPosition(*game->GetTarget())), sf::Color::White);
		game->GetTarget()->draw(array);
	}
}