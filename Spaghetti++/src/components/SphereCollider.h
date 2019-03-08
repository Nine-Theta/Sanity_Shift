#pragma once
#include "Collider.h"
#include "AbstractCollider.h"
#include <iostream>
#include <math.h>
#include "GameObject.h"
#include "bullet/btBulletDynamicsCommon.h"
#include "core/Physics.h"
namespace sge {
	class SphereCollider : public AbstractCollider//all it does is keep track and control bullet colliders
	{
	public:
		SphereCollider(float radius, float pMass = 0);
		~SphereCollider();

		// Geerbt über Collider
	private:
		SphereCollider();
		float radius;


		// Geerbt über ObjectBehaviour
		virtual void Start() override;

		virtual void OnDestroy() override;

		virtual void Update() override;

		virtual void OnCollision(Collider * other) override;

		virtual void OnTrigger(Collider * other) override;

		// Geerbt über Collider
	};
}
