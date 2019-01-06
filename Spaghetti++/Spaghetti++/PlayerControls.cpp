#include "PlayerControls.h"
#include "Time.h"

namespace sge {

	PlayerControls::PlayerControls()
	{
	}


	PlayerControls::~PlayerControls()
	{
	}

	void sge::PlayerControls::Start()
	{
		_rbody = (Rigidbody2D*)(p_gameObj->GetComponent(typeid(Rigidbody2D)));
		GameObject* startS = GameObject::Find("StartS");
		if (startS != NULL)
			GameObject::Destroy( startS);
	}

	void sge::PlayerControls::OnDestroy()
	{
	}

	void sge::PlayerControls::Update()
	{
	}

	void sge::PlayerControls::FixedUpdate()
	{
		if (_rbody == NULL) return;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			_rbody->AddVelocity(0, -1600 * Time::FixedDelta());// AddAngularVelocity(-3 * Time::FixedDelta());
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			_rbody->AddVelocity(0, 1600 * Time::FixedDelta());
		p_gameObj->setRotation(_rbody->GetVelocity().y * 0.03f);
	}

	void sge::PlayerControls::OnRender()
	{
	}

	void PlayerControls::OnCollision(Collider* other)
	{
	}

	void PlayerControls::OnTrigger(Collider * other)
	{
	}

}