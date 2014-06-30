#include <Game/OnDestroyListener.hpp>
#include <Game/Game.hpp>
#include <Entities/Entity.hpp>
#include <Entities/Joints/JointEntity.hpp>

OnDestroyListener::OnDestroyListener() {
}
OnDestroyListener::~OnDestroyListener() {
}

// Overrides
void OnDestroyListener::SayGoodbye(b2Joint* _joint) {
	// Check if this has any user data.
	if (_joint->GetUserData() != NULL) {
		((Entity*)_joint->GetUserData())->SetAlive(false);
		((JointEntity*)_joint->GetUserData())->JointDestroyed();
	}
}
void OnDestroyListener::SayGoodbye(b2Fixture* _fixture) {
	// Check if this has any user data.
	if (_fixture->GetUserData() != NULL)
		((Entity*)_fixture->GetUserData())->SetAlive(false);
}