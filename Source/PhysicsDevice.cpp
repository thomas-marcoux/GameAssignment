#include "PhysicsDevice.h"
#include "ContactListener.h"
#include "Object.h"
#include "Texture.h"

PhysicsDevice::PhysicsDevice(GAME_VEC const& gravity) :
	gravity(GV2PV(gravity))
{
}

PhysicsDevice::~PhysicsDevice()
{
}

bool PhysicsDevice::Initialize()
{
	world = std::make_unique<b2World>(gravity);
	if (!world)
		return false;
	ContactListener* cl = new ContactListener();
	world->SetContactListener(cl);
	return true; 
}

bool PhysicsDevice::Update(float dt)
{
	world->Step(dt, 8, 3);
	return true;
}

bool PhysicsDevice::CreateFixture(Object *object, GAME_OBJECTFACTORY_INITIALIZERS const& GOI)
{
	std::unique_ptr<b2BodyDef>	bd(std::make_unique<b2BodyDef>());
	bd->userData = object;
	switch (GOI.body_type)
	{
	case GAME_STATIC:
		bd->type = b2_staticBody; break;
	case GAME_KINEMATIC:
		bd->type = b2_kinematicBody; break;
	case GAME_DYNAMIC:
		bd->type = b2_dynamicBody; break;
	}
	bd->position.Set(RW2PW(GOI.pos.x), RW2PW(GOI.pos.y));
	bd->angle = TO_RADIAN(GOI.angle);
	if (object->getType() == LEEVER_TYPE || object->getType() == ARROW_TYPE)
		bd->fixedRotation = true;

	b2Body* body = world->CreateBody(bd.release());
	b2FixtureDef	shapefd;
	b2PolygonShape	pShape;
	b2CircleShape	cShape;

	body->SetAngularDamping(GOI.angularDamping);
	body->SetLinearDamping(GOI.linearDamping);
	switch (GOI.shape)
	{
	case GAME_RECTANGLE:
		pShape.SetAsBox(RW2PW(GOI.width), RW2PW(GOI.height)); 
		shapefd.shape = &pShape; break;
	case GAME_CIRCLE:
		cShape.m_radius = (RW2PW(GOI.width));
		shapefd.shape = &cShape; break;
	}
	shapefd.density = GOI.density;
	shapefd.friction = GOI.friction;
	shapefd.restitution = GOI.restitution;
	if (!GOI.collision) //Disable collision for the body
		shapefd.filter.maskBits = 0x0000;
	body->CreateFixture(&shapefd);
	object->setPhysics(this);
	return true;
}

bool PhysicsDevice::SetTransform(Object * object, GAME_VEC position, GAME_FLT angle)
{
	b2Body* body = FindBody(object);
	body->SetTransform(GV2PV(position), TO_RADIAN(angle));
	return true;
}

bool PhysicsDevice::SetLinearVelocity(Object * object, GAME_VEC linearVelociy)
{
	b2Body* body = FindBody(object);
	body->SetLinearVelocity(GV2PV(linearVelociy));
	return true;
}

bool PhysicsDevice::SetAngularVelocity(Object * object, GAME_FLT angularVelocity)
{
	b2Body* body = FindBody(object);
	body->SetAngularDamping(TO_RADIAN(angularVelocity));
	return true;
}

bool PhysicsDevice::SetTorque(Object * object, GAME_FLT torque)
{
	b2Body* body = FindBody(object);
	body->ApplyTorque(RW2PW(torque), true);
	return true;
}

bool PhysicsDevice::SetLinearImpulse(Object * object, GAME_VEC forceVec, GAME_VEC forceCenter)
{
	b2Body* body = FindBody(object);
	body->ApplyLinearImpulse(GV2PV(forceVec), body->GetWorldPoint(GV2PV(forceCenter)), true);
	return true;
}

bool PhysicsDevice::SetStatic(Object * object)
{
	b2Body* body = FindBody(object);
	body->SetType(b2_staticBody);
	return true;
}

bool PhysicsDevice::SetStopPhysics(Object * object)
{
	b2Body* body = FindBody(object);
	body->SetActive(false);
	return true;
}

bool PhysicsDevice::SetAngle(Object * object, GAME_FLT angle)
{
	b2Body* body = FindBody(object);
	body->SetTransform(body->GetPosition(), TO_RADIAN(angle));
	return true;
}

GAME_FLT PhysicsDevice::GetAngularVelocity(Object * object)
{
	b2Body* body = FindBody(object);
	return PW2RW(body->GetAngularVelocity());
}

GAME_VEC PhysicsDevice::GetPosition(Object * object)
{
	return AlignCenters(object);
}

GAME_FLT PhysicsDevice::GetAngle(Object * object)
{
	b2Body* body = FindBody(object);
	return TO_DEGREE(body->GetAngle());
}

GAME_VEC PhysicsDevice::GetVelocity(Object * object)
{
	b2Body* body = FindBody(object);
	return PV2GV(body->GetLinearVelocity());
}

GAME_VEC PhysicsDevice::GetLinearVelocity(Object * object)
{
	b2Body* body = FindBody(object);
	return PV2GV(body->GetLinearVelocity());
}

bool PhysicsDevice::createDistanceJoint(Object * object1, Object * object2, GAME_FLT maxDistance, GAME_VEC anchor1, GAME_VEC anchor2)
{
	b2DistanceJointDef jd;
	jd.bodyA = FindBody(object1);
	jd.bodyB = FindBody(object2);
	jd.collideConnected = false;
	jd.localAnchorA = GV2PV(anchor1);
	jd.localAnchorB = GV2PV(anchor2);
	jd.length = RW2PW(maxDistance);
	world->CreateJoint(&jd);
	return true;
}

bool PhysicsDevice::createDistanceJoint(Object * object1, Object * object2, GAME_FLT maxDistance)
{
	return createDistanceJoint(object1, object2, maxDistance, 
		PV2GV(FindBody(object1)->GetLocalCenter()), PV2GV(FindBody(object2)->GetLocalCenter()));
}

bool PhysicsDevice::createRopeJoint(Object * object1, Object * object2, GAME_FLT maxDistance, GAME_VEC anchor1, GAME_VEC anchor2, bool collide)
{
	b2RopeJointDef jd;
	jd.bodyA = FindBody(object1);
	jd.bodyB = FindBody(object2);
	jd.collideConnected = collide;
	jd.localAnchorA = GV2PV(anchor1);
	jd.localAnchorB = GV2PV(anchor2);
	jd.maxLength= RW2PW(maxDistance);
	world->CreateJoint(&jd);
	return true;
}

bool PhysicsDevice::createRopeJoint(Object * object1, Object * object2, GAME_FLT maxDistance, bool collide)
{
	return createRopeJoint(object1, object2, maxDistance,
		PV2GV(FindBody(object1)->GetLocalCenter()), PV2GV(FindBody(object2)->GetLocalCenter()), collide);
}

bool PhysicsDevice::createRevolvingJoint(Object * object1, Object * object2, bool collide, GAME_VEC anchor1, GAME_VEC anchor2,
	GAME_FLT referenceAngle, bool enableLimit, GAME_FLT lowerAngle, GAME_FLT upperAngle, bool enableMotor, GAME_FLT motorSpeed, GAME_FLT maxMotorTorque)
{
	b2RevoluteJointDef jd;
	jd.bodyA = FindBody(object1);
	jd.bodyB = FindBody(object2);
	jd.collideConnected = collide;
	jd.localAnchorA = GV2PV(anchor1);
	jd.localAnchorB = GV2PV(anchor2);
	jd.referenceAngle = TO_RADIAN(referenceAngle);
	jd.enableLimit = enableLimit;
	jd.lowerAngle = TO_RADIAN(lowerAngle);
	jd.upperAngle = TO_RADIAN(upperAngle);
	jd.enableMotor = enableMotor;
	jd.motorSpeed = TO_RADIAN(motorSpeed);
	jd.maxMotorTorque = TO_RADIAN(maxMotorTorque);
	world->CreateJoint(&jd);
	return true;
}

bool PhysicsDevice::createRevolvingJoint(Object * object1, Object * object2, GAME_VEC anchor1, GAME_VEC anchor2)
{
	return createRevolvingJoint(object1, object2, false, anchor1, anchor2, 0, false, 0, 0, true, 20.0f, 100.0f);
}

bool PhysicsDevice::createRevolvingJoint(Object * object1, Object * object2)
{
	return createRevolvingJoint(object1, object2,
		PV2GV(FindBody(object1)->GetLocalCenter()), PV2GV(FindBody(object2)->GetLocalCenter()));
}

b2Body * PhysicsDevice::FindBody(Object* object)
{
	for (b2Body* body = world->GetBodyList(); body; body = body->GetNext())
	{
		if (body->GetUserData() == object)
			return body;
	}
	return nullptr;
}

b2Vec2 PhysicsDevice::GV2PV(GAME_VEC gv)
{
	return b2Vec2(RW2PW(gv.x), RW2PW(gv.y));
}

GAME_VEC PhysicsDevice::PV2GV(b2Vec2 pv)
{
	GAME_VEC gv;
	gv.x = PW2RW(pv.x);
	gv.y = PW2RW(pv.y);
	return gv;
}

GAME_VEC PhysicsDevice::AlignCenters(Object * object)
{
	b2Body* body = FindBody(object);
	b2Vec2 physPosition = body->GetPosition();
	GAME_VEC position;
	std::shared_ptr<Texture> texture = object->getTexture();
	
	position.x = PW2RW(physPosition.x) - (texture->getWidth() / 2);
	position.y = PW2RW(physPosition.y) - (texture->getHeight() / 2);
	return position;
}
