#include "Script.h"

void Script::HandleEvent(Event* e) {

	CollisionEnterEvent* collisionEnterE = dynamic_cast<CollisionEnterEvent*>(e);
	if (collisionEnterE) {
		OnCollisionEnter(collisionEnterE);
		return;
	}

	CollisionExitEvent* collisionExitE = dynamic_cast<CollisionExitEvent*>(e);
	if (collisionExitE) {
		OnCollisionExit(collisionExitE);
		return;
	}

	CollisionEvent* collisionE = dynamic_cast<CollisionEvent*>(e);
	if (collisionE) {
		OnCollision(collisionE);
		return;
	}

}