#include "core/AssetLoader.h"
#include <iostream>
#include <map>
#include "SFML/Audio.hpp"
#include "Physics.h"
namespace sge {
	btDefaultCollisionConfiguration* Physics::collisionConfig;
	btCollisionDispatcher* Physics::dispatcher;
	btBroadphaseInterface* Physics::overlappingPairCache;
	btSequentialImpulseConstraintSolver* Physics::solver;
	btDiscreteDynamicsWorld* Physics::world;

	Physics::Physics()
	{
	}


	Physics::~Physics()
	{
	}
	void Physics::Init()
	{
		collisionConfig = new btDefaultCollisionConfiguration();
		dispatcher = new btCollisionDispatcher(collisionConfig);
		overlappingPairCache = new btDbvtBroadphase();
		solver = new btSequentialImpulseConstraintSolver();
		world = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfig);
		world->setGravity(btVector3(0, -9.81f, 0));
	}
	int Physics::AddBody(btRigidBody * body)
	{
		world->addRigidBody(body);
		return world->getNumCollisionObjects() - 1;
	}
	void Physics::RemoveBody(btRigidBody * body)
	{
		world->removeRigidBody(body);
	}
	int Physics::AddCollision(btCollisionObject * obj)
	{
		world->addCollisionObject(obj);
		return world->getNumCollisionObjects() - 1;
	}
	btTransform Physics::GetTransform(int id)
	{
		return btTransform();//world->getCollisionObjectArray()[id];
	}
	void Physics::Update(float dt)
	{
		world->stepSimulation(dt, 10, TimeH::FixedDelta());
	}
}