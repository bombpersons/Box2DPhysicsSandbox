#include <Entities/Joints/MotorJointEntity.hpp>
#include <cmath>
const float PI = 3.14159265358979f;

MotorJointEntity::MotorJointEntity(Game* _game) : JointEntity(_game) {
	motorspeed = 0;
	motortorque = 0;
	damping = 1;
	axis = sf::Vector2f(0, 0);

	type = MOTOR_JOINT_ENTITY;
}

MotorJointEntity::~MotorJointEntity() {
}

void MotorJointEntity::SetMaxTorque(float _torque) {
	motortorque = _torque;
}
void MotorJointEntity::SetMotorSpeed(float _speed) {
	motorspeed = _speed;
}
void MotorJointEntity::SetUserControlled(bool _v) {
	usercontrolled = _v;
}
void MotorJointEntity::SetAxis(sf::Vector2f _axis) {
	axis = _axis;

	// Normalize it.
 	float length = sqrt(axis.x*axis.x + axis.y*axis.y);
	axis.x /= length;
	axis.y /= length;
}
void MotorJointEntity::SetDamping(float _damping) {
	damping = _damping;
}
void MotorJointEntity::SetFrequency(float _frequency) {
	frequency = _frequency;
}

void MotorJointEntity::CreateJoint() {
	// Move bodyA to the second anchor point.
	bodyB->SetPosition(anchorB);

	// Make the joint
	b2WheelJointDef jointdef;
	jointdef.Initialize(bodyA->GetBody(), bodyB->GetBody(), bodyB->GetBody()->GetWorldCenter(), b2Vec2(axis.x, axis.y));
	jointdef.collideConnected = false;
	jointdef.userData = this;

	// Torque and speed
	jointdef.motorSpeed = motorspeed;
	jointdef.maxMotorTorque = motortorque;
	jointdef.enableMotor = true;
	
	// Axis and dampening (for suspension)
	jointdef.localAxisA = b2Vec2(axis.x, axis.y);
	jointdef.dampingRatio = damping;
	jointdef.frequencyHz = frequency;

	// Create the joint
	joint = game->GetWorld()->CreateJoint(&jointdef);
}

void MotorJointEntity::Draw(float _deltatime) {
	// Create a circle and draw it in place of the anchor points.
	sf::CircleShape shape(10.0f / game->GetCamera().GetZoom());
	shape.setFillColor(sf::Color::Yellow);
	shape.setOutlineColor(sf::Color::White);
	shape.setOutlineThickness(1.0f / game->GetCamera().GetZoom());
	shape.setOrigin(shape.getRadius(), shape.getRadius());

	b2Vec2 localAnchorB = ((b2WheelJoint*)joint)->GetLocalAnchorB();
	sf::Vector2f localAnchorBsf(localAnchorB.x, localAnchorB.y);
	sf::Vector2f smoothAnchorB = ((PhysicsEntity*)joint->GetBodyB()->GetUserData())->GetSmoothedPosition() - localAnchorBsf;
	shape.setPosition(smoothAnchorB);
	
	// Draw it.
	game->GetTarget()->draw(shape);

	// The axis
	// Get the smoothed angle
	float angle = ((2*PI) / 360.0f) * bodyA->GetSmoothedRotation();

	// Calculate the rotation
	b2Vec2 localaxis = ((b2WheelJoint*)joint)->GetLocalAxisA();
	sf::Vector2f worldaxis(localaxis.x * cosf(angle) - localaxis.y * sinf(angle),
						   localaxis.y * cosf(angle) - localaxis.x * sinf(angle));
	sf::VertexArray array(sf::PrimitiveType::Lines, 2);
	array[0] = sf::Vertex(shape.getPosition(), sf::Color::Yellow);
	array[1] = sf::Vertex(shape.getPosition() + worldaxis, sf::Color::Yellow);
	game->GetTarget()->draw(array);
}

void MotorJointEntity::Update(float _deltatime) {
	if (joint == NULL)
		return;

	if (usercontrolled) {
		float speed = 0.0f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) speed -= motorspeed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) speed += motorspeed;
		((b2WheelJoint*)joint)->SetMotorSpeed(speed);
	}
}

void MotorJointEntity::Serialize(FILE* _file) {
	JointEntity::Serialize(_file);

	// axis
	b2Vec2 localaxis = ((b2WheelJoint*)joint)->GetLocalAxisA();
	sf::Vector2f worldaxis(localaxis.x * cosf(this->bodyA->GetBody()->GetAngle()) - localaxis.y * sinf(this->bodyA->GetBody()->GetAngle()),
						   localaxis.y * cosf(this->bodyA->GetBody()->GetAngle()) - localaxis.x * sinf(this->bodyA->GetBody()->GetAngle()));
	b2Vec2 worldaxisb(worldaxis.x, worldaxis.y);
	worldaxisb.Normalize();

	// Write properties
	b2Vec2 anchorA = joint->GetAnchorA() - (((b2WheelJoint*)joint)->GetJointTranslation() * worldaxisb);
	b2Vec2 anchorB = joint->GetAnchorB() - (((b2WheelJoint*)joint)->GetJointTranslation() * worldaxisb);
	sf::Vector2f bodyA = ((Entity*)(joint->GetBodyA()->GetUserData()))->GetPosition();
	sf::Vector2f bodyB = ((Entity*)(joint->GetBodyB()->GetUserData()))->GetPosition();
	fwrite(&anchorA, sizeof(anchorA), 1, _file);
	fwrite(&anchorB, sizeof(anchorB), 1, _file);
	fwrite(&bodyA, sizeof(bodyA), 1, _file);
	fwrite(&bodyB, sizeof(bodyB), 1, _file);

	// Other properties
	fwrite(&motorspeed, sizeof(motorspeed), 1, _file);
	fwrite(&motortorque, sizeof(motortorque), 1, _file);
	fwrite(&usercontrolled, sizeof(usercontrolled), 1, _file);
	fwrite(&worldaxis, sizeof(worldaxis), 1, _file);
	fwrite(&damping, sizeof(damping), 1, _file);
	fwrite(&frequency, sizeof(frequency), 1, _file);
}

void MotorJointEntity::Deserialize(FILE* _file) {
	// Read properties
	b2Vec2 anchorA, anchorB;
	sf::Vector2f bodyA, bodyB;
	fread(&anchorA, sizeof(anchorA), 1, _file);
	fread(&anchorB, sizeof(anchorB), 1, _file);
	fread(&bodyA, sizeof(bodyA), 1, _file);
	fread(&bodyB, sizeof(bodyB), 1, _file);

	// Resolve the bodies
	Entity* bA = game->GetEntityList()->FindEntityAtPos(bodyA);
	Entity* bB = game->GetEntityList()->FindEntityAtPos(bodyB);
	SetBodyA((PhysicsEntity*)bA);
	SetBodyB((PhysicsEntity*)bB);

	// Set anchors
	SetAnchorA(sf::Vector2f(anchorA.x, anchorA.y));
	SetAnchorB(sf::Vector2f(anchorB.x, anchorB.y));

	// Other properties
	fread(&motorspeed, sizeof(motorspeed), 1, _file);
	fread(&motortorque, sizeof(motortorque), 1, _file);
	fread(&usercontrolled, sizeof(usercontrolled), 1, _file);

	// axis
	sf::Vector2f worldaxis;
	fread(&worldaxis, sizeof(worldaxis), 1, _file);
	SetAxis(worldaxis);

	// other stuff.
	fread(&damping, sizeof(damping), 1, _file);
	fread(&frequency, sizeof(frequency), 1, _file);

	// Create the joint
	CreateJoint();
}