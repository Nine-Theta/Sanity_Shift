#pragma once
#include "ObjectBehaviour.h"
#include "TextComponent.h"

#include "GameObject.h"
namespace sge {
	class DebugComponent :
		public ObjectBehaviour
	{
	public:
		DebugComponent();
		~DebugComponent();

		// Geerbt über ObjectBehaviour
		virtual void Start() override;
		virtual void OnDestroy() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void OnRender() override;
		virtual void OnCollision(Collider * other) override;
		virtual void OnTrigger(Collider * other) override;
	private:
		TextComponent* txt;
	};
}

