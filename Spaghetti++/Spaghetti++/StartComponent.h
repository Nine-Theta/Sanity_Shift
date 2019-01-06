#pragma once
#include "ObjectBehaviour.h"
#include "Game.h"
namespace sge {
	class StartComponent : public ObjectBehaviour
	{
	public:
		StartComponent();
		~StartComponent();

		// Geerbt über ObjectBehaviour
		virtual void Start() override;
		virtual void OnDestroy() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void OnRender() override;
		virtual void OnCollision(Collider * other) override;
		virtual void OnTrigger(Collider * other) override;
	private:
		void launch();
		bool triggered = false;
	};
}

