#ifndef PHYSICS_ENTITY_HPP
#define PHYSICS_ENTITY_HPP

#include <SFML/System.hpp>	
#include <Game/Game.hpp>

#include <cstdio>

class Entity {
public:
	// Enum
	enum EntityType {
		ENTITY,
		SHAPE_ENTITY,
		PHYSICS_ENTITY,
		UI_ENTITY,
		JOINT_ENTITY,
		DISTANCE_JOINT_ENTITY,
		MOTOR_JOINT_ENTITY,
		WELD_JOINT_ENTITY
	};

	// Constructors
	Entity(Game* _game);
	virtual ~Entity();

	// Draw / Update
	virtual void Update(float _deltatime);
	virtual void FixedUpdate();
	virtual void Draw(float _deltatime);

	// Get / Set
	const sf::Vector2f& GetPosition();
	const sf::Vector2f& GetCenter();
	const sf::Vector2f& GetScale();
	float GetRotation();
	EntityType GetType();

	unsigned int GetID();
	void SetID(unsigned int _id);

	virtual void SetPosition(const sf::Vector2f& _pos);
	virtual void SetCenter(const sf::Vector2f& _center);
	virtual void SetScale(const sf::Vector2f& _scale);
	virtual void SetRotation(float _rot);

	void SetAlive(bool _v);
	bool GetAlive();

	// Serialize / Deserialize
	virtual void Serialize(FILE* _file);
	virtual void Deserialize(FILE* _file);

protected:
	Game* game;

	// Position / Scale / Rotation
	sf::Vector2f position;
	sf::Vector2f center;
	sf::Vector2f scale;
	float rotation;

	// The entity type.
	EntityType type;
	unsigned int id;
	bool alive;
};

#endif