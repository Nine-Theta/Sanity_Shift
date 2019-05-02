#include "MeshComponent.h"
#include "core/AssetLoader.h"
#include "Game.h"
#include <assert.h>
#include "LightComponent.hpp"
#include "MannequinTriggerComp.h"
#include "materials/SpecularMaterial.hpp"
#include "AbstractCollider.h"

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

	bool MannequinTriggerComp::roomCheck()
	{
		vec3 pos = p_gameObj->GetCombinedPosition();
		vec3 dir = _player->GetCombinedPosition() - pos;
		float len = length(dir);
		RaycastHit hit = Physics::Raycast(p_gameObj->GetCombinedPosition() + vec3(0, 1, 0), normalize(dir), len);
		if (!hit.hit || length(hit.point - _player->GetCombinedPosition()) < 1.5f)
			return true;
		return false;
	}

	void sge::MannequinTriggerComp::Start()
	{
		_material = new SpecularMaterial("Mannequin/Diffuse.dds", "Mannequin/Specular.dds", "Mannequin/Normal.dds");
		_comp = new MeshComponent("Mannequin/Mannequin_" + std::to_string(1) + ".obj", _material);
		p_gameObj->AddComponent(_comp);
		mannequins = 11;
		_mesh.resize(mannequins);
		for (int i = 1; i <= mannequins; i++) {
			_mesh[i - 1] = AssetLoader::GetMesh("Mannequin/Mannequin_" + std::to_string(i) + ".obj"); //Mesh::load("Mannequin/Mannequin_" + std::to_string(i) + ".obj");
		}
		_player = CameraComponent::GetMain()->GetParent();
		_col = p_gameObj->GetComponent<AbstractCollider>();
		startPos = p_gameObj->GetCombinedPosition();
	}

	void sge::MannequinTriggerComp::OnDestroy()
	{
	}

	void sge::MannequinTriggerComp::Update()
	{//TODO: Add dot product light stuff
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

		//	p_gameObj->LookAt(p_gameObj->GetCombinedPosition() + vec3(dir.x,dir.y,-dir.z),vec3(0,1,0));
		if (_move) {
			bool inRoom = roomCheck();
			vec3 dir = inRoom ? _player->GetCombinedPosition() - p_gameObj->GetCombinedPosition() : (startPos - p_gameObj->GetCombinedPosition());
			vec3 lookDir = (_player->GetCombinedPosition() - p_gameObj->GetCombinedPosition());
			float dist = length(dir);
			if (!inRoom && !_spawnChanged) {
				_spawnChanged = true;
				float newR = 0.75f + 0.25f * randf();
				vec3 dist = (p_gameObj->GetCombinedPosition() - startPos) * newR;
				startPos += dist;
			}
			if (dist > 1) {
				float dist = length(dir);
				dir = normalize(vec3(dir.x, 0, dir.z));
				lookDir = normalize(vec3(lookDir.x, 0, lookDir.z));
				//p_gameObj->SetWorldPosition(p_gameObj->GetCombinedPosition() + dir * .8f * TimeH::FixedDelta());
				_col->GetRigidbody()->setLinearVelocity(Physics::glmToBullet(dir * 1.8f + (dir * clamp(inRoom ? dist * 0.5f : 8 - dist * 0.2f,0.f,5.f))));
				float facing = orientedAngle(vec2(0, -1), vec2(lookDir.x, -lookDir.z));
				btTransform t = _col->GetRigidbody()->getWorldTransform();
				t.setRotation(btQuaternion(facing, 0, 0));
				_col->GetRigidbody()->setWorldTransform(t);
			}
		}
		else {
			_col->GetRigidbody()->setLinearVelocity(btVector3(0, 0, 0));
		}

		if (intensity <= 0.f || dot(_player->GetCombinedPosition() - p_gameObj->GetCombinedPosition(), _player->forward()) > 0.1f || (3.f > length(_player->GetCombinedPosition() - p_gameObj->GetCombinedPosition()) && _move && intensity < 0.7f)) {
			_timer -= TimeH::DeltaTime();
			if (_timer > 0) return;
			if (_toChange) {
				swapModel(); 
				_spawnChanged = false;
			}
			_move = true;
			_toChange = false;
		}
		else {
			_toChange = true;
			_move = false;
			_timer = randf() * 0.15f + 0.15f;
		}
	}


	void sge::MannequinTriggerComp::FixedUpdate()
	{
		
	}

	void sge::MannequinTriggerComp::OnRender()
	{

	}

	void MannequinTriggerComp::OnCollision(Collider* other)
	{
	}

	void MannequinTriggerComp::OnTrigger(Collider * other)
	{
	}
}