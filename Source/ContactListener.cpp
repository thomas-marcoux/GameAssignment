#include "ContactListener.h"
#include "Object.h"
#include "PhysicsDevice.h"

void ContactListener::PreSolve(b2Contact * contact, const b2Manifold * oldManifold)
{
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();
	Object* objectA = static_cast<Object*>(bodyA->GetUserData());
	Object* objectB = static_cast<Object*>(bodyB->GetUserData());

	if (((objectB->getType() == OCTOROK_TYPE || objectB->getType() == LEEVER_TYPE) && objectA->getType() == ARROW_TYPE)
		|| (objectB->getType() == ARROW_TYPE && (objectA->getType() == OCTOROK_TYPE || objectA->getType() == LEEVER_TYPE)))
	{
		if (objectA->getType() == ARROW_TYPE)
			objectB->kill();
		else
			objectA->kill();
	}
}
