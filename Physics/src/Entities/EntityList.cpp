#include <Entities/EntityList.hpp>
#include <Entities/Entity.hpp>
#include <Entities/Joints/JointEntity.hpp>
#include <Entities/PhysicsEntity.hpp>

// Constructors
EntityList::EntityList() {
}

EntityList::~EntityList() {
	Clear();
}

// Add / Remove entities.
void EntityList::Add(Entity* _entity) {
	entities.push_back(_entity);
}
void EntityList::Remove(Entity* _entity) {
	for (int i = 0; i < entities.size(); ++i) {
		if (entities[i] == _entity) {
			_entity->SetAlive(false);
			return;
		}
	}
}
Entity* EntityList::FindEntityAtPos(sf::Vector2f _pos) {
	for (std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it) {
		if ((*it)->GetPosition().x == _pos.x && (*it)->GetPosition().y == _pos.y)
			return (*it);
	}
	return NULL;
}

// Update / Draw the entities.
void EntityList::Update(float _deltatime) {
	// Loop through all the entities and update them.
	for (std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it) {
		(*it)->Update(_deltatime);
	}
}
void EntityList::FixedUpdate() {
	for (std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it) {
		(*it)->FixedUpdate();
	}
}
void EntityList::Draw(float _deltatime) {
	// Loop through all the entities and update them.
	for (std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it) {
		(*it)->Draw(_deltatime);
	}
}
std::vector<Entity*>* EntityList::GetList() {
	return &entities;
}

void EntityList::RemoveDead() {
	std::vector<Entity*> bodies;
	std::vector<Entity*> joints;

	for (std::vector<Entity*>::iterator it = entities.begin(); it != entities.end();) {
		if (!(*it)->GetAlive()) {
			if (dynamic_cast<PhysicsEntity*>(*it) != NULL)
				bodies.push_back(*it);
			else if (dynamic_cast<JointEntity*>(*it) != NULL)
				joints.push_back(*it);
			else
				delete (*it);

			it = entities.erase(it);
		} else {
			it++;
		}
	}
	
	for (int i = 0; i < joints.size(); ++i) {
		delete joints[i];
	}
	for (int i = 0; i < bodies.size(); ++i) {
		delete bodies[i];
	}
}

// Clear the list
void EntityList::Clear(Entity* _entity) {
	// Put the physics bodies and joints into seperate lists so we can delete them in order.
	std::vector<Entity*> bodies;
	std::vector<Entity*> joints;
	for (int i = 0; i < entities.size(); ++i) {
		if (dynamic_cast<PhysicsEntity*>((entities)[i]) != NULL)
			bodies.push_back((entities)[i]);
		else if (dynamic_cast<JointEntity*>((entities)[i]) != NULL)
			joints.push_back((entities)[i]);
	}

	// Delete joints first.
	for (int i = 0; i < joints.size(); ++i) {
		joints[i]->SetAlive(false);
	}
	RemoveDead();

	for (int i = 0; i < bodies.size(); ++i) {
		bodies[i]->SetAlive(false);
	}
	RemoveDead();

	// Delete everything else
	for (int i = 0; i < entities.size(); ++i) {
		if (_entity != entities[i])
			entities[i]->SetAlive(false);
	}
	RemoveDead();
}