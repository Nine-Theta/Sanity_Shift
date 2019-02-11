#pragma once
#include "ObjectBehaviour.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include "vec2.hpp"
namespace sge {
	class ShootComponent : public ObjectBehaviour
	{
	public:
		ShootComponent();
		~ShootComponent();

		// Geerbt über ObjectBehaviour
		virtual void Start() override;
		virtual void OnDestroy() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void OnRender() override;
		virtual void OnCollision(Collider * other) override;
		virtual void OnTrigger(Collider * other) override;
	private:
		bool lastShot = true;
		void shoot();
	};

}