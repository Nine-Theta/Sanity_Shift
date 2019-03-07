#include "MeshComponent.h"
#include "core/AssetLoader.h"
#include "Game.h"
#include <assert.h>
#include "LightComponent.hpp"
#include "MannequinTriggerComp.h"
#include "materials/SpecularMaterial.hpp"

namespace sge {
	MannequinTriggerComp::MannequinTriggerComp()
	{
	}

	MannequinTriggerComp::~MannequinTriggerComp()
	{
	}

	void MannequinTriggerComp::swapModel()
	{
		int selection = (int)(randf() * (mannequins - 1) + 0.5f);
		_comp->SetMesh(_mesh[selection]);
	}

	void sge::MannequinTriggerComp::Start()
	{
		_material = new SpecularMaterial("Mannequin/Diffuse.dds", "Mannequin/Specular.dds", "Mannequin/Normal.dds");
		_comp = new MeshComponent("Mannequin/Mannequin_" + std::to_string(1) + ".obj", _material);
		p_gameObj->AddComponent(_comp);
		mannequins = 7;
		_mesh.resize(mannequins);
		for (int i = 1; i <= mannequins; i++) {
			_mesh[i - 1] = AssetLoader::GetMesh("Mannequin/Mannequin_" + std::to_string(i) + ".obj"); //Mesh::load("Mannequin/Mannequin_" + std::to_string(i) + ".obj");
		}
	}

	void sge::MannequinTriggerComp::OnDestroy()
	{
	}

	void sge::MannequinTriggerComp::Update()
	{
	}


	void sge::MannequinTriggerComp::FixedUpdate()
	{
		
	}

	void sge::MannequinTriggerComp::OnRender()
	{
		//TODO: Add dot product light stuff
		GLLight* lights = LightComponent::GetLights();
		float intensity = 0;
		vec3 pos = p_gameObj->GetCombinedPosition();
		int lightCount = LightComponent::GetLightCount();
		for (int i = 0; i < lightCount; i++) {
			GLLight light = lights[i];
			vec3 lpos = vec3(light.pos.x, light.pos.y, light.pos.z);
			vec3 dir = normalize(pos - lpos);
			float angleFalloff = clamp(dot(dir, vec3(light.dir.x, light.dir.y, light.dir.z)), 0.f, 1.f);
			float falloff = smoothstep(min(light.minRad, light.maxRad), max(light.minRad, light.maxRad), angleFalloff);
			float dist = distance(lpos, pos);
			float distFalloff = clamp(1.0 - dist * dist / (light.color.w*light.color.w), 0.0, 1.0);
			distFalloff *= distFalloff;

			intensity += clamp(falloff * falloff, 0.f, 1.f) * distFalloff;
		}

		if (intensity > 0.01f) {
			if (_toChange)
				swapModel();

			_toChange = false;
		}
		else {
			_toChange = true;
		}

	}

	void MannequinTriggerComp::OnCollision(Collider* other)
	{
	}

	void MannequinTriggerComp::OnTrigger(Collider * other)
	{
	}
}