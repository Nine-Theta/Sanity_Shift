#pragma once
#include "Collider.h"
#include <iostream>
#include <math.h>
#include "GameObject.h"
#include "bullet/btBulletDynamicsCommon.h"
#include "core/Physics.h"
namespace sge {
	class BoxCollider : public ObjectBehaviour//all it does is keep track and control bullet colliders
	{
	public:
		BoxCollider(vec3 size, float pMass = 0);
		~BoxCollider();

		// Geerbt über Collider
	private:
		BoxCollider();
		int id;
		btRigidBody* rbody;
		vec3 dimensions;
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
