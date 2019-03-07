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
		int mannequins;

		void swapModel();

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
