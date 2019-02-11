#include "ObjectBehaviour.h"
#include "GameObject.h"
#include <iostream>
#include "Game.h"
#include <assert.h>

namespace sge {
	ObjectBehaviour::ObjectBehaviour()
	{
		Game::GetInstance().RegisterNewComponent(this);
	}


	ObjectBehaviour::~ObjectBehaviour()
	{
		Game::GetInstance().RemoveFromNewComponents(this);
	}

	void ObjectBehaviour::SetParent(GameObject * p_parent)
	{
		std::vector<ObjectBehaviour*> components = p_parent->GetComponents();
		//std::cout << p_parent->GetCollider() <<std::endl << this << std::endl << "<Check if the collider is this" << std::endl;
		if (p_gameObj == p_parent || std::find(components.begin(), components.end(), this) != components.end() || this == p_parent->GetCollider()) {
			std::cout << "Component already part of this parent" << std::endl;
		}
		else {
			assert(p_parent != NULL);
			if (p_gameObj != NULL)
				p_gameObj->RemoveComponent(this, false);
			p_gameObj = p_parent;
			assert(p_gameObj != NULL);
		}
	}

	GameObject * ObjectBehaviour::GetParent()
	{
		return p_gameObj;
	}

	void ObjectBehaviour::OnDestroy()
	{
	}

	void ObjectBehaviour::Update()
	{
	}

	void ObjectBehaviour::FixedUpdate()
	{
	}

}