#pragma once
#include "Collider.h"
#include <iostream>
#include <math.h>
#include "GameObject.h"
#include "bullet/btBulletDynamicsCommon.h"
#include "core/Physics.h"
namespace sge {
	class MeshCollider : public ObjectBehaviour//all it does is keep track and control bullet colliders
	{
	public:
		MeshCollider(std::string mesh, float pMass = 0);
		MeshCollider(float pMass = 0);
		~MeshCollider();

		// Geerbt über Collider
	private:
		int id;
		btRigidBody* rbody;
		Mesh* cmesh;
		float mass;

		//Collider related
		btTriangleIndexVertexArray* meshArray;
		btCollisionShape* shape;
		btTransform transform;
		btDefaultMotionState* motionState;

		void makeCollider();
		void destroyCollider();

		btTriangleIndexVertexArray* meshToBT(Mesh* mesh);
		btTriangleMesh* meshToBTSlow(Mesh* mesh);
		// Geerbt über ObjectBehaviour
		virtual void Start() override;

		virtual void OnDestroy() override;

		virtual void Update() override;

		virtual void FixedUpdate() override;

		virtual void OnRender() override;

		virtual void OnCollision(Collider * other) override;

		virtual void OnTrigger(Collider * other) override;

		// Geerbt über Collider
	};
}
