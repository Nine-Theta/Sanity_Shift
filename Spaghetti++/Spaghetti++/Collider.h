#pragma once
#include "ObjectBehaviour.h"
#include <list>
namespace sge {
	class Collider : public ObjectBehaviour
	{
	public:
		Collider();
		~Collider();

		// Geerbt über ObjectBehaviour
		virtual void Start() override;
		virtual void OnDestroy() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void OnRender() override;
		void CollideWithAll();
		virtual void OnCollision(Collider* other) override;
		virtual void OnTrigger(Collider * other) override;
		void SetTrigger(bool trigger);
		bool IsTrigger();
	protected:
		static std::list<Collider*> _allColliders;
		float bounciness = 0.9f;
		bool isTrigger = false;
		virtual void Collide(Collider* p_col) = 0;


		// Geerbt über ObjectBehaviour

		// Geerbt über ObjectBehaviour
	};

}