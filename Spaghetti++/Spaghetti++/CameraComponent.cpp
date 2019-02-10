#include "CameraComponent.h"
#include "GameObject.h"
#include <list>
#include <iostream>
#include "Game.h"
#include "Settings.h"

namespace sge {
	std::list<CameraComponent*> CameraComponent::cameras = std::list<CameraComponent*>();

	void CameraComponent::OnDestroy()
	{
		CameraComponent::cameras.remove(this);
	}
	void CameraComponent::OnRender()
	{
	}
	void CameraComponent::Start()
	{
		CameraComponent::cameras.push_back(this);
	}
	void CameraComponent::UpdateCamera()
	{
		view.setSize(sf::Vector2f(width, height));
		//view.setCenter(sf::Vector2f(width * 0.5, height * 0.5));
		view.zoom(scale);
		//view.setCenter(p_gameObj->GetCombinedPosition()); //TODO: Port to GLM
		view.setRotation(p_gameObj->getRotation());
		Game::GetInstance().setView(view);
	}
	CameraComponent::CameraComponent()
	{
		width = sge::Settings::GetInt("width");
		height = sge::Settings::GetInt("height");
	}


	CameraComponent::~CameraComponent()
	{
		CameraComponent::cameras.remove(this);
	}

	std::list<CameraComponent*> CameraComponent::GetCameras()
	{
		return CameraComponent::cameras;
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