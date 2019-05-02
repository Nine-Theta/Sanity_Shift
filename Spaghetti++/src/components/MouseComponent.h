#pragma once
#include "ObjectBehaviour.h"
#include <list>
#include "SFML/Graphics.hpp"
namespace sge {
	class MouseComponent : public ObjectBehaviour
	{
	private:
		bool leftPressed = false;
		bool rightPressed = false;

	public:
		void OnDestroy();
		void OnRender();
		void Start();
		bool GetButtonDown(int button);
		bool GetButtonUp(int button);
		MouseComponent();
		~MouseComponent();

		// Geerbt über ObjectBehaviour
		void Update();
		void FixedUpdate();

		// Geerbt über ObjectBehaviour
		virtual void OnCollision(Collider* other) override;

		// Geerbt über ObjectBehaviour
		virtual void OnTrigger(Collider * other) override;
	};
}
