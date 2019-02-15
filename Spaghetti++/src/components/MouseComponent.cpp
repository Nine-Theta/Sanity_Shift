#include "components/MouseComponent.h"
#include "GameObject.h"
#include <list>
#include <iostream>
#include "Game.h"
#include "Settings.h"
#include "MouseComponent.h"
#include "SFML/Window/Mouse.hpp"

namespace sge {	

	void MouseComponent::OnDestroy()
	{		
	}
	
	void MouseComponent::Start()
	{
	}

	MouseComponent::MouseComponent()
	{		
	}
	
	MouseComponent::~MouseComponent()
	{
	}

	bool MouseComponent::GetButtonDown(int button = 0)
	{
		switch (button)
		{
		case 0:
			return sf::Mouse::isButtonPressed(sf::Mouse::Left);
		case 1:
			return sf::Mouse::isButtonPressed(sf::Mouse::Right);
		case 2:
			return sf::Mouse::isButtonPressed(sf::Mouse::Middle);
		default:
			return false;
		}
	}
	
	void MouseComponent::Update()
	{
	}

	void MouseComponent::FixedUpdate()
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{

		}
	}

	void MouseComponent::OnCollision(Collider* other)
	{
	}

	void MouseComponent::OnTrigger(Collider * other)
	{
	}

	void MouseComponent::OnRender()
	{
	}

}