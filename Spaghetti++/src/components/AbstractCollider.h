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

		// Geerbt über Collider
	protected:
		AbstractCollider(float pMass = 0);
		AbstractCollider();
		int id;
		btRigidBody* rbody;
		float mass;


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
