#pragma once
#include "Collider.h"
#include "AbstractCollider.h"
#include <iostream>
#include <math.h>
#include "GameObject.h"
#include "bullet/btBulletDynamicsCommon.h"
#include "core/Physics.h"
namespace sge {
	class CapsuleCollider : public AbstractCollider//all it does is keep track and control bullet colliders
	{
	public:
		CapsuleCollider(float radius, float height, float pMass = 0);
		~CapsuleCollider();

		// Geerbt über Collider
	private:
		CapsuleCollider();
		float radius;
		float height;


		// Geerbt über ObjectBehaviour
		virtual void Start() override;

		virtual void OnDestroy() override;

		virtual void Update() override;

		virtual void OnCollision(Collider * other) override;
		virtual void OnCollisionStay(const Collision &col) override;

		virtual void OnTrigger(Collider * other) override;

		// Geerbt über Collider
	};
}
