#include <Entities/Joints/WeldJointEntity.hpp>

WeldJointEntity::WeldJointEntity(Game* _game) : JointEntity(_game) {
	type = WELD_JOINT_ENTITY;
}

WeldJointEntity::~WeldJointEntity() {
}

void WeldJointEntity::CreateJoint() {
	// Create the joint definition
	b2WeldJointDef jointdef;
	jointdef.bodyA = bodyA->GetBody();
	jointdef.bodyB = bodyB->GetBody();

	// Don't collide these two bodies.
	jointdef.collideConnected = false;

	// Get the average location between the two bodies
	sf::Vector2f pos = bodyA->GetPosition() + bodyB->GetPosition();
	pos.x /= 2;
	pos.y /= 2;
	
	jointdef.Initialize(bodyA->GetBody(), bodyB->GetBody(), b2Vec2(pos.x, pos.y));

	// The reference angle.
	//jointdef.referenceAngle = bodyB->GetBody()->GetAngle() - bodyA->GetBody()->GetAngle();

	//jointdef.frequencyHz = 1.0f;
	//jointdef.dampingRatio = 0.5f;

	// Pointer to this entity
	jointdef.userData = this;

	// Create the joint
	joint = game->GetWorld()->CreateJoint(&jointdef);
}

// Draw
void WeldJointEntity::Draw(float _deltatime) {
	if (joint != NULL) {
		// Create a circle and draw it in place of the anchor points.
		sf::CircleShape shape(10.0f / game->GetCamera().GetZoom());
		shape.setFillColor(sf::Color::Green);
		shape.setOutlineColor(sf::Color::White);
		shape.setOutlineThickness(1.0f / game->GetCamera().GetZoom());
		shape.setOrigin(shape.getRadius(), shape.getRadius());

		// Draw the first one.
		shape.setPosition(bodyA->GetSmoothedPosition());
		game->GetTarget()->draw(shape);

		// Draw the second one.
		shape.setPosition(bodyB->GetSmoothedPosition());
		game->GetTarget()->draw(shape);

		// Draw a line between them
		sf::VertexArray array(sf::PrimitiveType::Lines, 2);
		array[0].position = bodyA->GetSmoothedPosition();
		array[0].color = sf::Color::Green;
		array[1].position = bodyB->GetSmoothedPosition();
		array[1].color = sf::Color::Green;
		game->GetTarget()->draw(array);
	}
}

void WeldJointEntity::Serialize(FILE* _file) {
	JointEntity::Serialize(_file);

	// Write properties of the joint.
	b2Vec2 anchorA = joint->GetAnchorA();
	b2Vec2 anchorB = joint->GetAnchorB();
	sf::Vector2f bodyA = ((Entity*)joint->GetBodyA()->GetUserData())->GetPosition();
	sf::Vector2f bodyB = ((Entity*)joint->GetBodyB()->GetUserData())->GetPosition();

	fwrite(&anchorA, sizeof(anchorA), 1, _file);
	fwrite(&anchorB, sizeof(anchorB), 1, _file);
	fwrite(&bodyA, sizeof(bodyA), 1, _file);
	fwrite(&bodyB, sizeof(bodyB), 1, _file);
}

void WeldJointEntity::Deserialize(FILE* _file) {
	// Read the properties and resolve the bodies
	b2Vec2 anchorA;
	b2Vec2 anchorB;
	sf::Vector2f bodyA;
	sf::Vector2f bodyB;

	fread(&anchorA, sizeof(anchorA), 1, _file);
	fread(&anchorB, sizeof(anchorB), 1, _file);
	fread(&bodyA, sizeof(bodyA), 1, _file);
	fread(&bodyB, sizeof(bodyB), 1, _file);

	// Resolve these and make the joint.
	Entity* bA = game->GetEntityList()->FindEntityAtPos(bodyA);
	Entity* bB = game->GetEntityList()->FindEntityAtPos(bodyB);
	SetBodyA((PhysicsEntity*)bA);
	SetBodyB((PhysicsEntity*)bB);
	CreateJoint();
}