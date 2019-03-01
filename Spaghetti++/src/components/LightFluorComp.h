#pragma once
#include "ObjectBehaviour.h"
#include "SFML/Graphics.hpp"
#include "core/Mesh.hpp"
#include "materials/AbstractMaterial.hpp"
namespace sge {
	class LightFlourComp : public ObjectBehaviour
	{
	public:
		LightFlourComp();
		~LightFlourComp();
	private:
		vec4 glow = vec4(0,0.4f,0.1f,1.0f);
		float chargePerSec = 0.25f;
		float dischargePerSec = 0.1f;

		// Geerbt über ObjectBehaviour
		virtual void Start() override;
		virtual void OnDestroy() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void OnRender() override;

		// Geerbt über ObjectBehaviour
		virtual void OnCollision(Collider* other) override;

		// Geerbt über ObjectBehaviour
		virtual void OnTrigger(Collider * other) override;
	};
}
