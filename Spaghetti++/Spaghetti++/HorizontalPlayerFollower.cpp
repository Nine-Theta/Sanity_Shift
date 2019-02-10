#include "HorizontalPlayerFollower.h"
#include <iostream>

namespace sge {

	HorizontalPlayerFollower::HorizontalPlayerFollower()
	{
	}


	HorizontalPlayerFollower::~HorizontalPlayerFollower()
	{
	}
	void HorizontalPlayerFollower::Start()
	{
		player = GameObject::Find("Player");
		offset = p_gameObj->GetCombinedPosition() - player->GetCombinedPosition();
	}
	void HorizontalPlayerFollower::OnDestroy()
	{
	}
	void HorizontalPlayerFollower::Update()
	{
	}
	void HorizontalPlayerFollower::FixedUpdate()
	{
		if (player == NULL) return;
		p_gameObj->setPosition(glm::vec2(p_gameObj->getPosition().x + offset.x,p_gameObj->getPosition().y));
	}
	void HorizontalPlayerFollower::OnRender()
	{
	}
	void HorizontalPlayerFollower::OnCollision(Collider* other)
	{
		std::cout << "Player collided with bounds" << std::endl;
	}
	void HorizontalPlayerFollower::OnTrigger(Collider * other)
	{
	}
}
