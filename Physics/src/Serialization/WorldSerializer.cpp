#include <Serialization/WorldSerializer.hpp>
#include <Entities/Entity.hpp>
#include <Entities/PhysicsEntity.hpp>
#include <Entities/Joints/DistanceJointEntity.hpp>
#include <Entities/Joints/WeldJointEntity.hpp>
#include <Entities/Joints/MotorJointEntity.hpp>
#include <Entities/UIEntity.hpp>
#include <Entities/EntityList.hpp>

bool WorldSerializer::Serialize(Game* _game, const char* _filename) {
	// Open the file
	FILE* file = fopen(_filename, "wb");
	if (file != NULL) {
		// Loop every entity and serialize 
		std::vector<Entity*>* entities = _game->GetEntityList()->GetList();

		// Put the physics bodies and joints into seperate lists so we can save them in order.
		std::vector<Entity*> bodies;
		std::vector<Entity*> joints;
		for (int i = 0; i < entities->size(); ++i) {
			if (dynamic_cast<PhysicsEntity*>((*entities)[i]) != NULL)
				bodies.push_back((*entities)[i]);
			else if (dynamic_cast<JointEntity*>((*entities)[i]) != NULL)
				joints.push_back((*entities)[i]);
		}

		// Serialize the bodies
		for (int i = 0; i < bodies.size(); ++i) {
			bodies[i]->Serialize(file);
		}
		for (int i = 0; i < joints.size(); ++i) {
			joints[i]->Serialize(file);
		}
	}
	fclose(file);
	
	return true;
}

bool WorldSerializer::Deserialize(Game* _game, const char* _filename) {
	// Clear the world
	_game->ClearEntities((Entity*)_game->GetUI());

	// Open the file
	FILE* file = fopen(_filename, "rb");
	if (file != NULL) {
		while (!feof(file)) {
			// Read the type information
			Entity::EntityType type;
			size_t read = fread(&type, sizeof(type), 1, file);
			if (read == 0)
				break;

			// The entity to create.
			Entity* entity;
			entity = NULL;

			// Create the entity.
			switch(type) {
			case Entity::PHYSICS_ENTITY:
				entity = new PhysicsEntity(_game);
				break;
			case Entity::WELD_JOINT_ENTITY:
				entity = new WeldJointEntity(_game);
				break;
			case Entity::DISTANCE_JOINT_ENTITY:
				entity = new DistanceJointEntity(_game);
				break;
			case Entity::MOTOR_JOINT_ENTITY:
				entity = new MotorJointEntity(_game);
				break;
			default:
				break;
			}

			// Deserialize and add to the list
			if (entity != NULL) {
				entity->Deserialize(file);
				_game->GetEntityList()->Add(entity);
			}
		}
	}
	fclose(file);

	return true;
}