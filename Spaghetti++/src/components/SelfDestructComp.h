#pragma once
#include "ObjectBehaviour.h"
#include "Time.h"
#include <iostream>
namespace sge {
	class SelfDestructComp :
		public ObjectBehaviour
	{
	public:
		SelfDestructComp(float sdTime);
		~SelfDestructComp();

		// Geerbt über ObjectBehaviour
		virtual void Start() override;
		virtual void OnDestroy() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void OnRender() override;
		virtual void OnCollision(Collider * other) override;
		virtual void OnTrigger(Collider * other) override;
	private:
		float time;
	};

}