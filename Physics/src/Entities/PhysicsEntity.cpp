#include <Entities/PhysicsEntity.hpp>
const float PI = 3.14159265358979f;

// Constructors
PhysicsEntity::PhysicsEntity(Game* _game) : ShapeEntity(_game) {
	// Set default values
	fixture = NULL;
	body = NULL;

	// Set friction and density
	SetFriction(0.3f);
	SetDensity(1.0f);
	SetRestitution(0.5f);
	SetBodyType(b2_dynamicBody);

	type = PHYSICS_ENTITY;

	prevPosition = sf::Vector2f(0, 0);
	prevRotation = 0;
}

PhysicsEntity::~PhysicsEntity() {
	// We need to destroy the box2d stuff here.
	if (body != NULL)
		game->GetWorld()->DestroyBody(body);
	body = NULL;
	fixture = NULL;
}

// Override the update function to update our position from the box2d body.
void PhysicsEntity::FixedUpdate() {
	// If there is no body, return
	if (body == NULL)
		return;

	// Get the box2d transform
	b2Transform transform = body->GetTransform();

	// Update the previous positions
	prevPosition = position;
	prevRotation = rotation;
		
	// The current position.
	position = sf::Vector2f(transform.p.x, transform.p.y);
	rotation = 360 * (transform.q.GetAngle() / (2*PI));

	// Apply air friction
	if (game->GetAirFriction() && GetBodyType() == b2_dynamicBody) {
		// http://en.wikipedia.org/wiki/Drag_equation
		float p, A, Cd, v;
		p = 1.0f; // The mass density of the fluid. In our case this is constant because it's all air.
		A = GetSurfaceArea(sf::Vector2f(body->GetLinearVelocity().x, body->GetLinearVelocity().y)); // This is the area that is moving forward. (we'll need to calculate this somehow)
		Cd = 1.05f; // This is the drag coefficient. (1.05 is the drag of a cube)
		v = body->GetLinearVelocity().Length();

		// Calculate the actual force.
		float dragforce = 0.5f * p * A * Cd * v;

		// Apply it in the correct direction
		b2Vec2 dir = body->GetLinearVelocity();
		dir.Normalize();
		dir = -dir;
		dir *= dragforce;

		// Apply the force
		body->ApplyForceToCenter(dir, true);
	}
}

// Draw in smoothed positions
void PhysicsEntity::Draw(float _deltatime) {
	sf::Vector2f oldposition = position;
	float oldrotation = rotation;

	// Set position and rotation
	position = GetSmoothedPosition();
	rotation = GetSmoothedRotation();

	// Draw
	ShapeEntity::Draw(_deltatime);

	// Put them back
	position = oldposition;
	rotation = oldrotation;
}

// Override the shape making functions so that we can create box2d bodies as well.
void PhysicsEntity::SetVertices(sf::Vector2f* _vertices, int _count) {
	ShapeEntity::SetVertices(_vertices, _count);

	// Create the body
	CreateBody();

	// Create the shape.
	b2PolygonShape shape;
	
	// Create a list of vertices.
	b2Vec2* verts = new b2Vec2[_count];
	for (int i = 0; i < _count; ++i) {
		verts[i].x = _vertices[i].x;
		verts[i].y = _vertices[i].y;
	}

	// Create the shape uses the vertices.
	shape.Set(verts, _count);

	// Create the fixture
	CreateFixture(&shape);
}
void PhysicsEntity::SetCircle(float _radius) {
	ShapeEntity::SetCircle(_radius);

	// Set up the box2d body.
	CreateBody();

	// Create the shape.
	b2CircleShape shape;
	shape.m_radius = _radius;

	// Create the fixture
	CreateFixture(&shape);
}
void PhysicsEntity::SetRectangle(sf::Vector2f _size) {
	// Create the points
	sf::Vector2f points[4];
	points[0].x = -_size.x / 2;
	points[0].y = -_size.y / 2;
	points[1].x = _size.x / 2;
	points[1].y = -_size.y / 2;
	points[2].x = _size.x / 2;
	points[2].y = _size.y / 2;
	points[3].x = -_size.x / 2;
	points[3].y = _size.y / 2;
	
	// Create the rectangle using the polygon set
	SetVertices(points, 4);
}

// Override sets for position, rotation and scale so that we can affect the physics body.
void PhysicsEntity::SetPosition(const sf::Vector2f& _pos) {
	ShapeEntity::SetPosition(_pos);

	// Set the bodies position to this.
	if (body != NULL)
		body->SetTransform(b2Vec2(_pos.x, _pos.y), rotation);
}
void PhysicsEntity::SetScale(const sf::Vector2f& _scale) {
	ShapeEntity::SetScale(_scale);

	// NEED TO DO SOMETHING FUNKY HERE
}
void PhysicsEntity::SetRotation(float _rot) {
	ShapeEntity::SetRotation(_rot);

	// Set the bodies position to this.
	if (body != NULL)
		body->SetTransform(b2Vec2(position.x, position.y), ((2*PI) / 360.0f) * _rot);
}

sf::Vector2f PhysicsEntity::GetSmoothedPosition() {
	// If the game is paused return the current position
	if (game->GetPhysiscActive() == false)
		return position;

	// Re-calculate the positions
	b2Vec2 spos;
	sf::Vector2f diff;
	switch (game->GetSmoothing()) {
	case Game::INTERPOLATION:
		diff = position - prevPosition;
		return prevPosition + (diff * game->GetPhysicsStepRatio());
		break;
	case Game::EXTRAPOLATION:
		spos = body->GetWorldCenter() + game->GetPhysicsStepRatio() * (1.0f / game->GetPhysicsStepTime()) * body->GetLinearVelocity();
		return sf::Vector2f(spos.x, spos.y);
		break;
	case Game::NONE:
	default:
		return position;
		break;
	}
}

float PhysicsEntity::GetSmoothedRotation() {
	// If the game is paused return the current position
	if (game->GetPhysiscActive() == false)
		return rotation;

	// Re-calculate the positions
	float rot;
	switch (game->GetSmoothing()) {
	case Game::INTERPOLATION:
		rot = rotation - prevRotation;
		return prevRotation + (rot * game->GetPhysicsStepRatio());
		break;
	case Game::EXTRAPOLATION:
		rot = body->GetAngle() + game->GetPhysicsStepRatio() * (1.0f / game->GetPhysicsStepTime()) * body->GetAngularVelocity();
		rot = 360 * (rot / (2*PI));
		return rot;
		break;
	case Game::NONE:
	default:
		return rotation;
		break;
	}
}

void PhysicsEntity::SetVelocity(sf::Vector2f _vel) {
	if (body != NULL)
		body->SetLinearVelocity(b2Vec2(_vel.x, _vel.y));
}

void PhysicsEntity::SetAngularVelocity(float _vel) {
	if (body != NULL)
		body->SetAngularVelocity(_vel);
}

void PhysicsEntity::Sleep(bool _v) {
	if (body != NULL)
		body->SetAwake(!_v);
}

// Set density
void PhysicsEntity::SetDensity(float _density) {
	density = _density;

	// Set the density on the fixture if we have one.
	if (fixture != NULL && body != NULL) {
		fixture->SetDensity(density);
		body->ResetMassData();
	}
}
float PhysicsEntity::GetDensity() {
	return density;
}

// Set friction
void PhysicsEntity::SetFriction(float _friction) {
	friction = _friction;

	// Set the friction on the fixture if we have one.
	if (fixture != NULL)
		fixture->SetFriction(friction);
}
float PhysicsEntity::GetFriction() {
	return friction;
}

	// Set restitution
	void SetRestitution(float _rest);
	float GetRestitution();
void PhysicsEntity::SetRestitution(float _rest) {
	restitution = _rest;

	// Set the restitution on the fixture if we have one.
	if (fixture != NULL)
		fixture->SetRestitution(restitution);
}
float PhysicsEntity::GetRestitution() {
	return restitution;
}

// Set the body type.
void PhysicsEntity::SetBodyType(b2BodyType _type) {
	// Set the bodytype.
	bodytype = _type;

	// Set it on the body if it exists.
	if (body != NULL)
		body->SetType(bodytype);
}
b2BodyType PhysicsEntity::GetBodyType() {
	return bodytype;
}

b2Body* PhysicsEntity::GetBody() {
	return body;
}

float PhysicsEntity::GetSurfaceArea(sf::Vector2f _axis) {
	// This could be a tricky one... 
  	if (GetIsCircle())
		return GetRadius() * 2;

	// Get the points
	int pointcount = ((b2PolygonShape*)fixture->GetShape())->GetVertexCount();

	// The angle to rotate by
	// Calculate the angle of the _axis
	float axisangle = atan2f(-_axis.y, _axis.x);
	float angle = body->GetAngle() + axisangle;

	// Rotate the points, such that they are axis aligned
	// Where the x axis is the viewing _axis
	b2Vec2* vertices = new b2Vec2[pointcount];
	for (int i = 0; i < pointcount; ++i) {
		b2Vec2 temp = ((b2PolygonShape*)fixture->GetShape())->GetVertex(i);

		// Rotate it.
		vertices[i].Set(temp.x * cosf(angle) - temp.y * sinf(angle),
						temp.y * cosf(angle) - temp.x * sinf(angle));
	}

	// Get the biggest and smallest points then get the range
	float smallest = 999999999999999999.0f;
	float biggest = -9999999999999999999.0f;
	for (int i = 0; i < pointcount; ++i) {
		if (vertices[i].y < smallest)
			smallest = vertices[i].y;
		if (vertices[i].y > biggest)
			biggest = vertices[i].y;
	}
	float range = biggest - smallest;

	return range;
}

void PhysicsEntity::CreateBody() {
	// Make sure there isn't a body already
	if (body != NULL)
		return;

	// Make a body definition.
	b2BodyDef bodydef;
	bodydef.type = bodytype;
	bodydef.position.Set(GetPosition().x, GetPosition().y);
	bodydef.userData = (void*)this;

	// Create the body.
	body = game->GetWorld()->CreateBody(&bodydef);
}

void PhysicsEntity::CreateFixture(b2Shape* _shape) {
	// If a fixture exists, destroy it
	if (fixture != NULL)
		if (body != NULL)
			body->DestroyFixture(fixture);

	// Create a fixture def
	b2FixtureDef fixturedef;
	fixturedef.shape = _shape;
	fixturedef.density = density;
	fixturedef.friction = friction;
	fixturedef.restitution = restitution;
	fixturedef.userData = (void*)this;

	// Create a new one.
	fixture = body->CreateFixture(&fixturedef);
}

void PhysicsEntity::Serialize(FILE* _file) {
	ShapeEntity::Serialize(_file);

	// Properties
	fwrite(&density, sizeof(density), 1, _file);
	fwrite(&friction, sizeof(friction), 1, _file);
	fwrite(&restitution, sizeof(restitution), 1, _file);
	fwrite(&bodytype, sizeof(bodytype), 1, _file);
	fwrite(&position, sizeof(position), 1, _file);
	fwrite(&rotation, sizeof(rotation), 1, _file);
	fwrite(&center, sizeof(center), 1, _file);

	// Velocity of the object
	b2Vec2 vel = body->GetLinearVelocity();
	float ang = body->GetAngularVelocity();
	fwrite(&vel, sizeof(vel), 1, _file);
	fwrite(&ang, sizeof(ang), 1, _file);

	// Write the vertices
	// Figure out if this is a circle or not.
	bool isCircle = GetIsCircle();

	// Write whether or not it will be circle data or polygon data
	fwrite(&isCircle, sizeof(isCircle), 1, _file);

	// Write the data.
	if (isCircle) {
		// Write the radius
		float radius = GetRadius();
		fwrite(&radius, sizeof(radius), 1, _file);
	} else {
		// Write the number of points.
		int pointcount = shape->getPointCount();
		fwrite(&pointcount, sizeof(pointcount), 1, _file);

		// Write all the points
		for (int i = 0; i < pointcount; ++i) {
			sf::Vector2f point = shape->getPoint(i);
			fwrite(&point, sizeof(point), 1, _file);
		}
	}
}

void PhysicsEntity::Deserialize(FILE* _file) {
	// Read everything back in the right order.
	
	// Properties
	fread(&density, sizeof(density), 1, _file);
	fread(&friction, sizeof(friction), 1, _file);
	fread(&restitution, sizeof(restitution), 1, _file);
	fread(&bodytype, sizeof(bodytype), 1, _file);
	fread(&position, sizeof(position), 1, _file);
	float rot;
	fread(&rot, sizeof(rot), 1, _file);
	fread(&center, sizeof(center), 1, _file);

	// Velocity of the object
	b2Vec2 vel;
	float ang;
	fread(&vel, sizeof(vel), 1, _file);
	fread(&ang, sizeof(ang), 1, _file);

	// Read stuff depending on whether or not this is a circle
	bool isCircle;
	fread(&isCircle, sizeof(isCircle), 1, _file);
	
	if (isCircle) {
		// Read the radius
		float radius;
		fread(&radius, sizeof(radius), 1, _file);

		// Create the body
		SetCircle(radius);
	} else {
		// Read how many points there are.
		int pointcount;
		fread(&pointcount, sizeof(pointcount), 1, _file);

		// Create an array of points
		sf::Vector2f* points = new sf::Vector2f[pointcount];
		
		// Read all the points
		fread(points, sizeof(sf::Vector2f), pointcount, _file);

		// Create it
		SetVertices(points, pointcount);
		delete points;
	}

	// Set the velocity
	body->SetLinearVelocity(vel);
	body->SetAngularVelocity(ang);
	SetRotation(rot);
}
