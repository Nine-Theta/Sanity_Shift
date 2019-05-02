#pragma once
#include "ObjectBehaviour.h"
#include "Rigidbody2D.h"
namespace sge {
	class ControlComponent : public ObjectBehaviour
	{
	public:
		ControlComponent();
		~ControlComponent();

		// Geerbt über ObjectBehaviour
		virtual void Start() override;
		virtual void OnDestroy() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void OnRender() override;
		virtual void OnCollision(Collider* other) override;
		virtual void OnTrigger(Collider * other) override;
	private:
		Rigidbody2D* rbody;


		// Geerbt über ObjectBehaviour

		// Geerbt über ObjectBehaviour
	};
}