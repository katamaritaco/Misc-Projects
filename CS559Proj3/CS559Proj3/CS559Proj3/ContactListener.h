#pragma once
#include "PhysicsInclude.h"

//A Box2D component that lets us define what occurs on contact between two objects in the world.

class ContactListener : public b2ContactListener
{
public:
	ContactListener(void);

	~ContactListener(void);

	void BeginContact(b2Contact* contact);

	void EndContact(b2Contact* contact);

	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold); 

	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
};

