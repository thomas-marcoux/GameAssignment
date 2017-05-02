#include "ContactListener.h"
#include "Object.h"
#include "PhysicsDevice.h"
#include "SlideBehaviorComponent.h"

void ContactListener::PreSolve(b2Contact * contact, const b2Manifold * oldManifold)
{
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();
	Object* objectA = static_cast<Object*>(bodyA->GetUserData());
	Object* objectB = static_cast<Object*>(bodyB->GetUserData());
	OBJECT_TYPE	typeA = objectA->getType();
	OBJECT_TYPE	typeB = objectB->getType();

	//If the blast collides with an enemy type, kill it
	if (((typeB == OCTOROK_TYPE || typeB == LEEVER_TYPE || typeB == DESTRUCTIBLE_TYPE) && typeA == BLAST_TYPE)
		|| (typeB == BLAST_TYPE && (typeA == OCTOROK_TYPE || typeA == LEEVER_TYPE || typeA == DESTRUCTIBLE_TYPE)))
	{
		objectB->kill();
		objectA->kill();
	}
	//If an arrow collides with a static object, kill the arrow
	if ((typeA == ROCK_TYPE && typeB == ARROW_TYPE)
		|| (typeB == ROCK_TYPE && typeA == ARROW_TYPE))
	{
		if (typeA == ARROW_TYPE)
			objectA->kill();
		else
			objectB->kill();
	}
	//Stop the blast if it runs into a static object
	if ((typeA == ROCK_TYPE && typeB == BLAST_TYPE)
		|| (typeB == ROCK_TYPE && typeA == BLAST_TYPE))
	{
		if (typeA == BLAST_TYPE)
			objectA->kill();
		else
			objectB->kill();
	}
	//Turn leever around if they run into each other
	if (typeA == LEEVER_TYPE || typeB == LEEVER_TYPE)
	{
		SlideBehaviorComponent*	leever;
		if (typeA == LEEVER_TYPE)
		{
			leever = objectA->GetComponent<SlideBehaviorComponent>();
			if (leever)
				leever->turn();
		}
		else
		{
			leever = objectA->GetComponent<SlideBehaviorComponent>();
			if (leever)
				leever->turn();
		}
	}
}
