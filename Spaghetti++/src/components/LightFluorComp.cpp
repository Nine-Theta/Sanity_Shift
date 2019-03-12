#include "MeshComponent.h"
#include "core/AssetLoader.h"
#include "Game.h"
#include <assert.h>
#include "LightComponent.hpp"
#include "LightFluorComp.h"

namespace sge {
	LightFluorComp::LightFluorComp()
	{

	}

	LightFluorComp::~LightFluorComp()
	{
	}

	void sge::LightFluorComp::Start()
	{
		material = (FluorescentMaterial*)p_gameObj->GetComponent<MeshComponent>()->GetMaterial();
	}

	void sge::LightFluorComp::OnDestroy()
	{
	}

	void sge::LightFluorComp::Update()
	{
	}


	void sge::LightFluorComp::FixedUpdate()
	{
		
	}

	void sge::LightFluorComp::OnRender()
	{
		//TODO: Add dot product light stuff
		GLLight* lights = LightComponent::GetLights();
		float intensity = 0;
		vec3 pos = p_gameObj->GetCombinedPosition();
		int lightCount = LightComponent::GetLightCount();
		for (int i = 0; i < lightCount; i++) {
			GLLight light = lights[i];
			if (light.minRad < 0) continue;
			vec3 lpos = vec3(light.pos.x, light.pos.y, light.pos.z);
			vec3 dir = normalize(pos - lpos);
			float angleFalloff = clamp(dot(dir, vec3(light.dir.x, light.dir.y, light.dir.z)), 0.f, 1.f);
			float falloff = smoothstep(min(light.minRad, light.maxRad), max(light.minRad, light.maxRad), angleFalloff);
			float dist = distance(lpos, pos);
			float distFalloff = clamp(1.0 - dist * dist / (light.color.w*light.color.w), 0.0, 1.0);
			distFalloff *= distFalloff;

			intensity += clamp(falloff * falloff, 0.f, 1.f) * distFalloff;
		}
		float extraCharge = clamp(((intensity * chargePerSec)), 0.f, 1.f);
		//std::cout << "Charge amount from " << lightCount << " lamps: " << extraCharge << std::endl;
		glow = vec4(vec3(glow), clamp(glow.w += (extraCharge - dischargePerSec) * TimeH::DeltaTime(), 0.f, 2.f));
		material->setGlowCol(glow);
	}

	void LightFluorComp::OnCollision(Collider* other)
	{
	}

	void LightFluorComp::OnTrigger(Collider * other)
	{
	}
}