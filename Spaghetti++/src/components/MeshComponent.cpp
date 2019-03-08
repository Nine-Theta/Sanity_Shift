#include "MeshComponent.h"
#include "core/AssetLoader.h"
#include "Game.h"
#include <assert.h>


extern int wololo;
namespace sge {
	Mesh * MeshComponent::GetMesh()
	{
		return _mesh;
	}
	MeshComponent::MeshComponent(std::string path, AbstractMaterial* material)
	{
		//Mesh* mesh = AssetLoader::GetMesh(path);
		//if(mesh == NULL)
			//_mesh = AssetLoader::GetMesh("ERROR.obj");
		_mesh = AssetLoader::GetMesh(path);//Mesh::load(Settings::GetSetting("meshDir") + path);
		//std::cout << _mesh << std::endl;
		assert(_mesh != NULL);
		_material = material;
		//_mesh.setOrigin(_mesh.getTexture()->getSize().x * 0.5f, _mesh.getTexture()->getSize().y * 0.5f);
		//_sprite.setOrigin(0.5f, 0.5f);
	}


	MeshComponent::~MeshComponent()
	{
		//std::cout << "DELETED A MESH RENDERER!!" << std::endl;
	}

	void MeshComponent::SetMesh(Mesh * newMesh)
	{
		_mesh = newMesh;
	}

	AbstractMaterial * MeshComponent::GetMaterial()
	{
		return _material;
	}

	void sge::MeshComponent::Start()
	{
	}

	void sge::MeshComponent::OnDestroy()
	{
	}

	void sge::MeshComponent::Update()
	{
	}

	void sge::MeshComponent::FixedUpdate()
	{
	}

	void sge::MeshComponent::OnRender()
	{
		//sf::RenderStates state = sf::RenderStates::Default;
//		state.transform = p_gameObj->GetCombinedTransform();
		//sge::Game::GetInstance().draw(_mesh, state); //not setting transform. TODO: port to use GLM and GLSL instead of SFML
		_material->render(this, CameraComponent::GetMain());

	}

	void MeshComponent::OnCollision(Collider* other)
	{
	}

	void MeshComponent::OnTrigger(Collider * other)
	{
	}

}