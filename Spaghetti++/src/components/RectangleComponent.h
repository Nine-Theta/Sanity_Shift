#pragma once
#include "ObjectBehaviour.h"
#include "SFML/Graphics.hpp"
namespace sge {
	class RectangleComponent : public ObjectBehaviour
	{
	public:
		RectangleComponent();
		RectangleComponent(float, float);
		~RectangleComponent();

		// Geerbt über ObjectBehaviour
		virtual void Start() override;
		virtual void OnDestroy() override;
		void Update();
		void FixedUpdate();
		virtual void OnRender() override;
		virtual void OnCollision(Collider* other) override;
		virtual void OnTrigger(Collider * other) override;
	private:
		sf::RectangleShape rect;


		// Geerbt über ObjectBehaviour

		// Geerbt über ObjectBehaviour
	};

}