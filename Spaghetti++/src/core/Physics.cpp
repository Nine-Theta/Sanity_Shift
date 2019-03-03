//#include "core/AssetLoader.h"
#include <iostream>
//#include <map>
//#include "SFML/Audio.hpp"
#include "components/AbstractCollider.h"
#include "Physics.h"
#include "GameObject.h"
//extern ContactDestroyedCallback gContactDestroyedCallback;// = ::gContactDestroyedCallback;// = Physics::customContactDestroyedCallback;
	//extern ContactAddedCallback gContactAddedCallback = ::gContactAddedCallback;// = Physics::customContactDestroyedCallback;
	//extern int wololo = 45;
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
		//gContactAddedCallback = customContactAddedCallback;
//		customContactDestroyedCallback(NULL); 
		//gContactDestroyedCallback = Physics::customContactDestroyedCallback;
		//gContactAddedCallback = Physics::customContactAddedCallback;
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
		int cols = 0;
		int contacts = world->getDispatcher()->getNumManifolds();
		float pulse = 0;
		for (int i = 0; i < contacts; i++) {
			btPersistentManifold* contactManifold = world->getDispatcher()->getManifoldByIndexInternal(i);
			const btCollisionObject* obA = contactManifold->getBody0();
			const btCollisionObject* obB = contactManifold->getBody1();

			int numContacts = contactManifold->getNumContacts();

			if (numContacts > 0) {
				Collision col;
				col.collider = (AbstractCollider*)obB->getUserPointer();
				col.otherCollider = (AbstractCollider*)obA->getUserPointer();
				col.contactPoints = numContacts;

				col.otherCollider->GetParent()->OnCollisionStay(col);

				Collision col2;
				col2.collider = (AbstractCollider*)obA->getUserPointer();
				col2.otherCollider = (AbstractCollider*)obB->getUserPointer();
				col2.contactPoints = numContacts;

				col2.otherCollider->GetParent()->OnCollisionStay(col2);
			}
			/*for (int j = 0; j < numContacts; j++)
			{
				btManifoldPoint& pt = contactManifold->getContactPoint(j);
				pulse += pt.getAppliedImpulse();
				if (pt.getDistance() < 0.f)
				{
				}
				cols++;
			}*/
		}
	}

	//extern bool customContactDestroyedCallback(void* userData) {
	//	//AbstractCollider* col = (AbstractCollider*)userData;
	//	//if(col != NULL)
	//	//std::cout << "custom destroyed callback! " << col->GetParent()->GetName() << std::endl;
	//	std::cout << "custom destroyed callback! " << std::endl;
	//	return false;
	//}

	extern bool customContactAddedCallback(btManifoldPoint &cp, const btCollisionObjectWrapper *colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper *colObj1Wrap, int partId1, int index1) {
		std::cout << "custom added callback!" << std::endl;
		return false;
	}

}