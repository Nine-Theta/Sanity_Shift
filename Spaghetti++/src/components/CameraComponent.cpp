#include "components/CameraComponent.h"
#include "GameObject.h"
#include <list>
#include <iostream>
#include "Game.h"
#include "Settings.h"
#include "CameraComponent.h"

namespace sge {
	std::list<CameraComponent*> CameraComponent::cameras = std::list<CameraComponent*>();
	CameraComponent* CameraComponent::main = NULL;

	void CameraComponent::OnDestroy()
	{
		CameraComponent::cameras.remove(this);
		if (CameraComponent::main == this)
			CameraComponent::main = NULL;
	}
	void CameraComponent::OnRender()
	{
		p_gameObj->UpdateTransform();
		viewM = glm::rotate(mat4(), radians(180.f), vec3(0, 1, 0)) * inverse(p_gameObj->GetCombinedTransform());
	}
	void CameraComponent::Start()
	{
		CameraComponent::cameras.push_back(this);
		//std::cout << "Spawned camera on object: " << p_gameObj->GetName() << std::endl;
	}
	void CameraComponent::UpdateCamera()
	{
		view.setSize(sf::Vector2f(width, height));
		//view.setCenter(sf::Vector2f(width * 0.5, height * 0.5));
		view.zoom(scale);
		//view.setCenter(p_gameObj->GetCombinedPosition()); //TODO: Port to GLM
		view.setRotation(p_gameObj->getRotation());
//		Game::GetInstance().setView(view);		//Port to GLM too
	}
	void CameraComponent::SetProjection(float fov, float aspect, float near, float far)
	{
		projectionM = perspective(radians(fov), aspect, near, far);
	}
	void CameraComponent::SetProjection(float width, float height, float far)
	{
		projectionM = glm::ortho(0.f, width, 0.f, height, -1.f, far);
	}
	mat4 CameraComponent::GetView()
	{
		return viewM;
	}
	mat4 CameraComponent::GetProjection()
	{
		return projectionM;
	}
	CameraComponent::CameraComponent()
	{
		width = sge::Settings::GetInt("width");
		height = sge::Settings::GetInt("height");
		if (main == NULL) {
			main = this;
			this->SetProjection(Settings::GetInt("fov"), width / height, 0.1f, 1000.0f);
		}
	}


	CameraComponent::~CameraComponent()
	{
	}

	std::list<CameraComponent*> CameraComponent::GetCameras()
	{
		return CameraComponent::cameras;
	}

	CameraComponent * CameraComponent::GetMain()
	{
		return main;
	}

	void CameraComponent::Update()
	{
	}

	void CameraComponent::FixedUpdate()
	{
	}

	void CameraComponent::OnCollision(Collider* other)
	{
	}

	void CameraComponent::OnTrigger(Collider * other)
	{
	}

}