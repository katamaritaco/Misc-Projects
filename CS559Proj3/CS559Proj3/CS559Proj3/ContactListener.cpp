#include "ContactListener.h"
#include "glutInclude.h"
#include "PhysicsInclude.h"


ContactListener::ContactListener(void)
{
}


ContactListener::~ContactListener(void)
{
}

void ContactListener::BeginContact(b2Contact* contact)
{
	//Update sphere if it's hitting another
	b2Fixture * fixtureA = contact->GetFixtureA();
	b2Fixture * fixtureB = contact->GetFixtureB();
	sphere_data * dataA = (sphere_data * )fixtureA->GetUserData();
	sphere_data * dataB = (sphere_data * )fixtureB->GetUserData();
	if ((dataA != NULL) && (dataB != NULL))
	{
		//Null implies we're hitting a wall,
		//so don't do updates
		if (!dataA->active && !dataA->isPlayer)
		{
			num_spheres--;
		}
		if (!dataB->active && !dataB->isPlayer)
		{
			num_spheres--;
		}
		dataA->active = true;
		dataB->active = true;
		dataA->time_left = max_time;
		dataB->time_left = max_time;
#ifdef _DEBUG
		printf("Collided!\n");
#endif
	}
}

void ContactListener::EndContact(b2Contact* contact)
{
}

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
}

void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
}