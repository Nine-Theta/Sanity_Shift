#pragma once
#include "Collider.h"
#include <iostream>
#include <math.h>
#include "GameObject.h"
#include "bullet/btBulletDynamicsCommon.h"
#include "core/Physics.h"
namespace sge {
	class AbstractCollider : public ObjectBehaviour//all it does is keep track and control bullet colliders
	{
	public:
		~AbstractCollider();

		btRigidBody* GetRigidbody();
		bool isTrigger();
		void SetTrigger(bool trigger);
		// Geerbt über Collider
	protected:
		AbstractCollider(float pMass = 0);
		AbstractCollider();
		void destroyCollider();
		int id;
		btRigidBody* rbody = NULL;
		float mass;

		bool trigger = false;

		btCollisionShape* shape;
		btTransform transform;
		btDefaultMotionState* motionState;

		// Geerbt über ObjectBehaviour
		virtual void Start() override;

		virtual void OnDestroy() override;

		virtual void Update() override;

		virtual void FixedUpdate() override;

		virtual void OnRender() override;

		virtual void OnCollision(Collider * other) override;
		virtual void OnCollisionStay(const Collision &col) override;

		virtual void OnTrigger(Collider * other) override;

		// Geerbt über Collider
	};
}
