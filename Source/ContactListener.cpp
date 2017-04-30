#include "ContactListener.h"
#include "Object.h"
#include "PhysicsDevice.h"

void ContactListener::PreSolve(b2Contact * contact, const b2Manifold * oldManifold)
{
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();
	Object* objectA = static_cast<Object*>(bodyA->GetUserData());
	Object* objectB = static_cast<Object*>(bodyB->GetUserData());
	OBJECT_TYPE	typeA = objectA->getType();
	OBJECT_TYPE	typeB = objectB->getType();

	//If an arrow collides with an enemy type, kill it
	if (((typeB == OCTOROK_TYPE || typeB == LEEVER_TYPE) && typeA == ARROW_TYPE)
		|| (typeB == ARROW_TYPE && (typeA == OCTOROK_TYPE || typeA == LEEVER_TYPE)))
	{
		if (typeA == ARROW_TYPE)
			objectB->kill();
		else
			objectA->kill();
	}
	//If an arrow collides with a rock, kill the arrow
	if ((typeA == ROCK_TYPE && typeB == ARROW_TYPE)
		|| (typeB == ROCK_TYPE && typeA == ARROW_TYPE))
	{
		if (typeA == ARROW_TYPE)
			objectA->kill();
		else
			objectB->kill();
	}
}
