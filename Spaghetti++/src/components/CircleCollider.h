#pragma once
#include "Collider.h"
#include <iostream>
#include <math.h>
#include "GameObject.h"
namespace sge {
	class CircleCollider : public Collider
	{
	public:
		CircleCollider();
		CircleCollider(float radius, bool trigger = false);
		~CircleCollider();

		void SetRadius(float radius);
		// Geerbt über Collider
		virtual void Collide(Collider * p_col) override;
		virtual void OnCollision(Collider* other) override;
	private:
		void CollideWithType(CircleCollider* col);

		float radius = 0;

		// Geerbt über Collider
	};
}
