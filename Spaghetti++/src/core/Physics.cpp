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


	std::unordered_map<ColliderPair, int, collider_hash> Physics::_collisionPairs;
	std::unordered_map<AbstractCollider*, int> Physics::_colliders;

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
		if (world == NULL) return 0;
		AbstractCollider* col = (AbstractCollider*)body->getUserPointer();
		if (_colliders.find(col) != _colliders.end()) {
			std::cout << "Added a collider that is already known!" << std::endl;
			return 0;
		}
		world->addRigidBody(body);
		_colliders[col] = 1;
		return world->getNumCollisionObjects() - 1;
	}
	void Physics::RemoveBody(btRigidBody * body)
	{
		if (world == NULL) return;
		AbstractCollider* col = (AbstractCollider*)body->getUserPointer();
		if (_colliders.find(col) == _colliders.end()) return;
		_colliders.erase(col);
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

				ColliderPair pair;
				pair.colA = col.otherCollider;
				pair.colB = col.collider;
				pair.trigger = pair.colA->isTrigger() || pair.colB->isTrigger();

				col.trigger = pair.trigger;
				col.contactPoints = numContacts;
				if (col.otherCollider->GetParent() != NULL) {
					if (pair.trigger)
						col.otherCollider->GetParent()->OnTriggerStay(col);
					else
						col.otherCollider->GetParent()->OnCollisionStay(col);
				}

				Collision col2;
				col2.collider = (AbstractCollider*)obA->getUserPointer();
				col2.otherCollider = (AbstractCollider*)obB->getUserPointer();
				col2.contactPoints = numContacts;

				col2.trigger = pair.trigger;
				if (col2.otherCollider->GetParent() != NULL) {
					if(pair.trigger)
						col2.otherCollider->GetParent()->OnTriggerStay(col2);
					else
						col2.otherCollider->GetParent()->OnCollisionStay(col2);
				}



				_collisionPairs[pair] = _collisionPairs[pair] == NULL ? -TimeH::GetFixedFrame() : TimeH::GetFixedFrame();
			}
			/*for (int j = 0; j < numContacts; j++)
			{
				btManifoldPoint& pt = contactManifold->getContactPoint(j);
			}*/
		}
		updateCollisions();
	}

	RaycastHit Physics::Raycast(vec3 start, vec3 dir, float length)
	{
		btVector3 startBt = btVector3(start.x, start.y, start.z);
		vec3 end = start + (length > 0 ? dir * length : dir * FLT_MAX);
		btVector3 endBt = btVector3(end.x, end.y, end.z);
		btCollisionWorld::ClosestRayResultCallback RayCallback(startBt, endBt);
		world->rayTest(startBt, endBt, RayCallback);
		
		RaycastHit hit;
		hit.hit = RayCallback.hasHit();
		hit.collider = NULL;
		if (hit.hit) {
			btVector3 v3 = RayCallback.m_hitPointWorld;
			hit.point = glm::vec3((float)v3.x(), (float)v3.y(), (float)v3.z());
			v3 = RayCallback.m_hitNormalWorld;
			hit.normal = glm::vec3((float)v3.x(), (float)v3.y(), (float)v3.z());
			hit.collider = (AbstractCollider*)RayCallback.m_collisionObject->getUserPointer();
		}
		return hit;
	}

	void Physics::updateCollisions()
	{
		//std::cout << "Checking collisions: " << _collisionPairs.size() << " - " << std::endl;
		std::vector<ColliderPair> oldCols;
		for (auto i = _collisionPairs.begin(); i != _collisionPairs.end(); i++) {
			//std::cout << i->first << " : " << i->second << '\n';
			AbstractCollider* colA = i->first.colA;
			AbstractCollider* colB = i->first.colB;

			int step = i->second;

			if (_colliders.find(colA) == _colliders.end() || _colliders.find(colB) == _colliders.end()) {
				oldCols.push_back(i->first);
				std::cout << "Found an old collision of colliders that do not exist any longer! Deleting.." << std::endl;
				break;
			}

			//std::cout << "Checking collisions on frame: " << TimeH::GetFixedFrame() << " - " << step << std::endl;
			if (step < 0) {
				Collision col;
				col.collider = colB;
				col.otherCollider = colA;

				if ((col.collider != NULL && col.otherCollider != NULL)) {
					bool trigger = i->first.trigger;
					if (col.otherCollider->GetParent() != NULL && col.collider->GetParent() != NULL) {
						if (trigger)
							col.otherCollider->GetParent()->OnTriggerEnter(col);
						else
							col.otherCollider->GetParent()->OnCollisionEnter(col);

						Collision col2;
						col2.collider = colA;
						col2.otherCollider = colB;

						if (trigger)
							col2.otherCollider->GetParent()->OnTriggerEnter(col2);
						else
							col2.otherCollider->GetParent()->OnCollisionEnter(col2);
					}
				}
			}
			if (abs(step) != TimeH::GetFixedFrame()) {
				Collision col;
				col.collider = colB;
				col.otherCollider = colA;
				
				if ((col.collider != NULL && col.otherCollider != NULL)) {
					bool trigger = i->first.trigger;
					if (col.otherCollider->GetParent() != NULL && col.collider->GetParent() != NULL) {
						if (trigger)
							col.otherCollider->GetParent()->OnTriggerExit(col);
						else
							col.otherCollider->GetParent()->OnCollisionExit(col);

						Collision col2;
						col2.collider = colA;
						col2.otherCollider = colB;

						if (trigger)
							col2.otherCollider->GetParent()->OnTriggerExit(col2);
						else
							col2.otherCollider->GetParent()->OnCollisionExit(col2);
					}
				}
				oldCols.push_back(i->first);
			}
		}
		for (ColliderPair pair : oldCols) {
			_collisionPairs.erase(pair);
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