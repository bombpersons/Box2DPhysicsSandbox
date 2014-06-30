#ifndef PHYSICS_ENTITYLIST_HPP
#define PHYSICS_ENTITYLIST_HPP

#include <vector>
#include <SFML/Graphics.hpp>

class Entity;

class EntityList {
public:
	// Constructors
	EntityList();
	~EntityList();

	// Add / Remove entities.
	void Add(Entity* _entity);
	void Remove(Entity* _entity);
	Entity* FindEntityAtPos(sf::Vector2f _pos);

	// Update / Draw the entities.
	void Update(float _deltatime);
	void FixedUpdate();
	void Draw(float _deltatime);
	std::vector<Entity*>* GetList();
	void RemoveDead();

	// Clear the list
	void Clear(Entity* _entity=NULL);

private:
	// A list of the entities.
	std::vector<Entity*> entities;
};

#endif