#include <Entities/Joints/DistanceJointEntity.hpp>
const float PI = 3.14159265358979f;

DistanceJointEntity::DistanceJointEntity(Game* _game) : JointEntity(_game) {
	type = DISTANCE_JOINT_ENTITY;
}

DistanceJointEntity::~DistanceJointEntity() {
}

void DistanceJointEntity::SetDamping(float _damping) {
	damping = _damping;
}
void DistanceJointEntity::SetFrequency(float _frequency) {
	frequency = _frequency;
}

void DistanceJointEntity::CreateJoint() {
	// Create the joint definition
	b2DistanceJointDef jointdef;
	jointdef.Initialize(bodyA->GetBody(), bodyB->GetBody(), b2Vec2(anchorA.x, anchorA.y), b2Vec2(anchorB.x, anchorB.y));

	// Calculate the length
	sf::Vector2f diff = anchorA - anchorB;
	float length = sqrt(diff.x*diff.x+diff.y*diff.y);
	jointdef.length = length;

	// Set so we don't collide with each other.
	jointdef.collideConnected = false;

	// Set damping and frequency
	jointdef.dampingRatio = damping;
	jointdef.frequencyHz = frequency;

	// Set the user data.
	jointdef.userData = this;

	// Create the joint.
	joint = game->GetWorld()->CreateJoint(&jointdef);
}

void DistanceJointEntity::Draw(float _deltatime) {
	// Draw two circles at the anchor points. 
	sf::CircleShape shape(10.0f / game->GetCamera().GetZoom());
	shape.setFillColor(sf::Color::Red);
	shape.setOutlineColor(sf::Color::White);
	shape.setOutlineThickness(1.0f / game->GetCamera().GetZoom());
	shape.setOrigin(shape.getRadius(), shape.getRadius());

	// Get local anchor points
	b2Vec2 localAnchorA = ((b2DistanceJoint*)joint)->GetLocalAnchorA();
	b2Vec2 localAnchorB = ((b2DistanceJoint*)joint)->GetLocalAnchorB();

	// Rotate these points by the rotation of the body.
	float angleA = 0;//((2*PI) / 360.0f) * ((PhysicsEntity*)joint->GetBodyA()->GetUserData())->GetSmoothedRotation();
	float angleB = 0;//((2*PI) / 360.0f) * ((PhysicsEntity*)joint->GetBodyB()->GetUserData())->GetSmoothedRotation();
	sf::Vector2f rotatedAnchorA(localAnchorA.x * cosf(angleA) - localAnchorA.y * sinf(angleA),
								localAnchorA.y * cosf(angleA) - localAnchorA.x * sinf(angleA));
	sf::Vector2f rotatedAnchorB(localAnchorB.x * cosf(angleB) - localAnchorB.y * sinf(angleB),
								localAnchorB.y * cosf(angleB) - localAnchorB.x * sinf(angleB));

	sf::Vector2f smoothAnchorA = ((PhysicsEntity*)joint->GetBodyA()->GetUserData())->GetSmoothedPosition() + rotatedAnchorA;
	sf::Vector2f smoothAnchorB = ((PhysicsEntity*)joint->GetBodyB()->GetUserData())->GetSmoothedPosition() + rotatedAnchorB;

	// Draw it
	shape.setPosition(smoothAnchorA.x, smoothAnchorA.y);
	game->GetTarget()->draw(shape);
	shape.setPosition(smoothAnchorB.x, smoothAnchorB.y);
	game->GetTarget()->draw(shape);

	// Draw a line between them.
	sf::VertexArray array(sf::PrimitiveType::Lines, 2);
	array[0] = sf::Vertex(smoothAnchorA, sf::Color::Red);
	array[1] = sf::Vertex(smoothAnchorB, sf::Color::Red);
	game->GetTarget()->draw(array);
}

void DistanceJointEntity::Serialize(FILE* _file) {
	JointEntity::Serialize(_file);

	// Write properties
	b2Vec2 anchorA = joint->GetAnchorA();
	b2Vec2 anchorB = joint->GetAnchorB();
	sf::Vector2f bodyA = ((Entity*)(joint->GetBodyA()->GetUserData()))->GetPosition();
	sf::Vector2f bodyB = ((Entity*)(joint->GetBodyB()->GetUserData()))->GetPosition();
	fwrite(&anchorA, sizeof(anchorA), 1, _file);
	fwrite(&anchorB, sizeof(anchorB), 1, _file);
	fwrite(&bodyA, sizeof(bodyA), 1, _file);
	fwrite(&bodyB, sizeof(bodyB), 1, _file);

	// Damping and freqency
	fwrite(&damping, sizeof(damping), 1, _file);
	fwrite(&frequency, sizeof(frequency), 1, _file);
}

void DistanceJointEntity::Deserialize(FILE* _file) {
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

	// Damping and frequency
	fread(&damping, sizeof(damping), 1, _file);
	fread(&frequency, sizeof(frequency), 1, _file);

	// Create the joint
	CreateJoint();
}