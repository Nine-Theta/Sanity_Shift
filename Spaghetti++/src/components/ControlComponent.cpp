#include "components/ControlComponent.h"
#include <iostream>
#include "vec2.hpp"
#include "Time.h"

namespace sge {

	ControlComponent::ControlComponent()
	{
	}


	ControlComponent::~ControlComponent()
	{
	}
	void ControlComponent::Start()
	{
		rbody = (Rigidbody2D*)p_gameObj->GetComponent(typeid(Rigidbody2D));
	}
	void ControlComponent::OnDestroy()
	{
	}
	void ControlComponent::Update()
	{
	}
	void ControlComponent::FixedUpdate()
	{
		if (rbody == NULL) return;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			rbody->AddAngularVelocity(-3 * TimeH::FixedDelta());
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			rbody->AddAngularVelocity(3 * TimeH::FixedDelta());

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			vec2 toAdd = vec2(0, 300 * TimeH::FixedDelta());
			//toAdd = rotate(toAdd, p_gameObj->getRotation());
			if (length(rbody->GetVelocity()) < 250)
				rbody->AddVelocity(toAdd);
		}
	}
	void ControlComponent::OnRender()
	{
	}
	void ControlComponent::OnCollision(Collider* other)
	{
	}
	void ControlComponent::OnTrigger(Collider * other)
	{
	}
}