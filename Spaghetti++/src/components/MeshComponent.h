#pragma once
#include "ObjectBehaviour.h"
#include "SFML/Graphics.hpp"
#include "core/Mesh.hpp"
#include "materials/AbstractMaterial.hpp"
namespace sge {
	class MeshComponent : public ObjectBehaviour
	{
	public:
		Mesh* GetMesh();
		MeshComponent(std::string filepath, AbstractMaterial* material);
		~MeshComponent();
	private:
		Mesh* _mesh;

		// Geerbt �ber ObjectBehaviour
		virtual void Start() override;
		virtual void OnDestroy() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void OnRender() override;

		// Geerbt �ber ObjectBehaviour
		virtual void OnCollision(Collider* other) override;

		// Geerbt �ber ObjectBehaviour
		virtual void OnTrigger(Collider * other) override;
	};
}
