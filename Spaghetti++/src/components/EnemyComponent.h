#pragma once
#include "ObjectBehaviour.h"
#include "Collider.h"
#include "GameObject.h"
namespace sge {
	class EnemyComponent :
		public ObjectBehaviour
	{
	public:
		EnemyComponent();
		~EnemyComponent();

		// Geerbt über ObjectBehaviour
		virtual void Start() override;
		virtual void OnDestroy() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void OnRender() override;
		virtual void OnCollision(Collider * other) override;
		virtual void OnTrigger(Collider * other) override;
	private:
		bool wave = false;
	};

}