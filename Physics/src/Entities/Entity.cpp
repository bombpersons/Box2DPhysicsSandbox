#include <Entities/Entity.hpp>
#include <Entities/EntityIDGenerator.hpp>

Entity::Entity(Game* _game) {
	// Set defaults for variables
	position = sf::Vector2f(0, 0);
	center = sf::Vector2f(0, 0);
	scale = sf::Vector2f(1, 1);
	rotation = 0;

	// Set the parent game
	game = _game;

	type = ENTITY;
	id = 0;
	alive = true;
}

Entity::~Entity() {
}

// Update
void Entity::Update(float _deltatime) {
}
void Entity::FixedUpdate() {
}

// Draw
void Entity::Draw(float _deltatime) {
}

// Get / Set
const sf::Vector2f& Entity::GetPosition() {
	return position;
}
const sf::Vector2f& Entity::GetCenter() {
	return center;
}
const sf::Vector2f& Entity::GetScale() {
	return scale;
}
float Entity::GetRotation() {
	return rotation;
}
Entity::EntityType Entity::GetType() {
	return type;
}

unsigned int Entity::GetID() {
	return id;
}
void Entity::SetID(unsigned int _id) {
	id = _id;
}

void Entity::SetPosition(const sf::Vector2f& _pos) {
	position = _pos;
}
void Entity::SetCenter(const sf::Vector2f& _center) {
	center = _center;
}
void Entity::SetScale(const sf::Vector2f& _scale) {
	scale = _scale;
}
void Entity::SetRotation(float _rot) {
	rotation = _rot;
}

void Entity::SetAlive(bool _v) {
	alive = _v;
}
bool Entity::GetAlive() {
	return alive;
}

// Serialize / Deserialize
void Entity::Serialize(FILE* _file) {
	// Write the type of this entity
	fwrite(&type, sizeof(type), 1, _file);
}
void Entity::Deserialize(FILE* _file) {
}