#include "ContactListener.h"
#include "Object.h"
#include "PhysicsDevice.h"

void ContactListener::PreSolve(b2Contact * contact, const b2Manifold * oldManifold)
{
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();
	Object* objectA = static_cast<Object*>(bodyA->GetUserData());
	Object* objectB = static_cast<Object*>(bodyB->GetUserData());

	objectA->pDevice->SetLinearVelocity(objectA, { -300, 0 });
}
