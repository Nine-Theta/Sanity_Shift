#pragma once
#include "ObjectBehaviour.h"
#include "Rigidbody2D.h"

namespace sge {
	class PlayerControls : public ObjectBehaviour
	{
	public:
		PlayerControls();
		~PlayerControls();

		// Geerbt über ObjectBehaviour
		virtual void Start() override;
		virtual void OnDestroy() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void OnRender() override;
		virtual void OnCollision(Collider* other) override;
		virtual void OnTrigger(Collider * other) override;
	private:
		Rigidbody2D* _rbody;


		// Geerbt über ObjectBehaviour

		// Geerbt über ObjectBehaviour
	};
}