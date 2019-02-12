#include "RectangleComponent.h"
#include <iostream>
#include "Game.h"

namespace sge {

	RectangleComponent::RectangleComponent(float width, float height) {
		rect = sf::RectangleShape(sf::Vector2f(width, height));
		rect.setOrigin(width * 0.5f, height * 0.5f);
	}

	RectangleComponent::RectangleComponent() : RectangleComponent(100,100)
	{
	}


	RectangleComponent::~RectangleComponent()
	{
	}

	void RectangleComponent::Start()
	{
	}

	void RectangleComponent::OnDestroy()
	{
	}

	void RectangleComponent::Update()
	{
	}

	void RectangleComponent::FixedUpdate()
	{
	}


	void RectangleComponent::OnRender()
	{
		sf::RenderStates state = sf::RenderStates::Default;
//		state.transform = p_gameObj->GetCombinedTransform(); //TODO: Port to GLM
		sge::Game::GetInstance().draw(rect, state);
	}

	void RectangleComponent::OnCollision(Collider* other)
	{
	}

	void RectangleComponent::OnTrigger(Collider * other)
	{
	}

}