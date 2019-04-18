#pragma once
#include "ObjectBehaviour.h"
#include "SFML/Graphics.hpp"
#include "core/Mesh.hpp"
#include "materials/AbstractMaterial.hpp"
#include "materials/FluorescentMaterial.hpp"
namespace sge {
	class MannequinTriggerComp : public ObjectBehaviour
	{
	public:
		MannequinTriggerComp();
		~MannequinTriggerComp();
	private:
		std::vector<Mesh*> _mesh;
		AbstractMaterial* _material;
		MeshComponent* _comp;
		bool _toChange = false;
		bool _move = false;
		bool _spawnChanged = false;
		float _timer = 0;
		int mannequins;
		GameObject* _player;
		AbstractCollider* _col;
		vec3 startPos;

		void swapModel();
		bool roomCheck();

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
