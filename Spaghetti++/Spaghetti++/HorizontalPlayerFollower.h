#pragma once
#include "ObjectBehaviour.h"
#include "GameObject.h"
namespace sge {
	class HorizontalPlayerFollower : public ObjectBehaviour
	{
	public:
		HorizontalPlayerFollower();
		~HorizontalPlayerFollower();

		// Geerbt �ber ObjectBehaviour
		virtual void Start() override;
		virtual void OnDestroy() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void OnRender() override;
		virtual void OnCollision(Collider* other) override;
		virtual void OnTrigger(Collider * other) override;
	private:
		GameObject* player = NULL;
		sf::Vector2f offset;


		// Geerbt �ber ObjectBehaviour

		// Geerbt �ber ObjectBehaviour
	};

}