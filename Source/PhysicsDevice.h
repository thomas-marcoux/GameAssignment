#ifndef PHYSICSDEVICE_H
#define PHYSICSDEVICE_H

#include "Box2D/Box2D.h"
#include "Definitions.h"
#include "Object.h"

class PhysicsDevice
{
public:
	PhysicsDevice();
	PhysicsDevice(GAME_VEC const&);
	~PhysicsDevice();
	bool Initialize();
	bool Update(float dt);
	bool CreateFixture(Object*, GAME_OBJECTFACTORY_INITIALIZERS const&);
	bool SetTransform(Object* object, GAME_VEC position, GAME_FLT angle);
	bool SetLinearVelocity(Object* object, GAME_VEC linearVelociy);
	bool SetAngularVelocity(Object* object, GAME_FLT angularVelocity);
	bool SetTorque(Object* object, GAME_FLT torque);
	bool SetLinearImpulse(Object* object, GAME_VEC forceVec, GAME_VEC forceCenter);
	bool SetStatic(Object* object);
	bool SetStopPhysics(Object* object);
	bool SetAngle(Object* object, GAME_FLT angle);
	GAME_FLT GetAngularVelocity(Object* object);
	GAME_VEC GetPosition(Object* object);
	GAME_FLT GetAngle(Object* object);
	GAME_VEC GetVelocity(Object* object);
	GAME_VEC GetLinearVelocity(Object* object);
	b2World* getWorld() { return world.get(); }
private:
	inline float PW2RW(GAME_FLT x) { return x * fPRV; }
	inline float RW2PW(GAME_FLT x) { return x / fPRV; }
	inline float RW2PW(GAME_INT x) { return (float)x / fPRV; }
	b2Body* FindBody(Object*);
	b2Vec2 GV2PV(GAME_VEC gv);
	GAME_VEC PV2GV(b2Vec2 pv);
	
private:
	std::unique_ptr<b2World>	world;
	const b2Vec2	gravity;
};

#endif // !PHYSICSDEVICE_H
