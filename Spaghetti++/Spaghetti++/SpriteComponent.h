#pragma once
#include "ObjectBehaviour.h"
#include "SFML/Graphics.hpp"
namespace sge {
	class SpriteComponent : public ObjectBehaviour
	{
	public:
		SpriteComponent(std::string filepath);
		~SpriteComponent();
	private:
		sf::Sprite _sprite;

		// Geerbt über ObjectBehaviour
		virtual void Start() override;
		virtual void OnDestroy() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void OnRender() override;

		// Geerbt über ObjectBehaviour
		virtual void OnCollision(Collider* other) override;

		// Geerbt über ObjectBehaviour
		virtual void OnTrigger(Collider * other) override;
	};
}
