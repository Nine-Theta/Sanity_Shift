#pragma once
#include "ObjectBehaviour.h"
#include "SFML/Graphics.hpp"
#include "GameObject.h"
namespace sge {
	class Rigidbody2D : public ObjectBehaviour //Basic 2d rigidbody with linear drag, unlike commonly used rigidbodies
	{
	public:
		Rigidbody2D();
		~Rigidbody2D();

		// Geerbt über ObjectBehaviour
		virtual void Start() override;
		virtual void OnDestroy() override;
		void Update();
		void FixedUpdate();
		virtual void OnRender() override;

		void SetVelocity(float, float);
		void AddVelocity(float x, float y);
		void AddVelocity(glm::vec2 vel);
		void AddAngularVelocity(float vel);
		void SetAngularVelocity(float vel);
		void SetDrag(float drag);
		virtual void OnCollision(Collider* other) override;
		glm::vec2 GetVelocity();
		virtual void OnTrigger(Collider * other) override;
	private:
		glm::vec2 velocity = glm::vec2(0,0);
		float drag = 3;
		float rotVel = 0;
		float rotDrag = 0.01f;


		// Geerbt über ObjectBehaviour

		// Geerbt über ObjectBehaviour
	};

}
