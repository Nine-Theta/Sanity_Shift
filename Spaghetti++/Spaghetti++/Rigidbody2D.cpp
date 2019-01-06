#include "Rigidbody2D.h"
#include "Time.h"
#include "vec2.hpp"
#include <iostream>

namespace sge {

	Rigidbody2D::Rigidbody2D()
	{
	
	}


	Rigidbody2D::~Rigidbody2D()
	{
	}
	void Rigidbody2D::Start()
	{
	}
	void Rigidbody2D::OnDestroy()
	{
	}
	void Rigidbody2D::Update()
	{
	}
	void Rigidbody2D::FixedUpdate()
	{
		sf::Vector2f dir = normalized(velocity);
		velocity -= dir * drag;
		if (dot(velocity, dir) < 0)
			velocity = sf::Vector2f(0, 0);
		if (rotVel < 0) {
			rotVel += rotDrag;
			if (rotVel > 0)
				rotVel = 0;
		}
		else if (rotVel > 0) {
			rotVel -= rotDrag;
			if (rotVel < 0)
				rotVel = 0;
		}
		p_gameObj->setPosition(p_gameObj->getPosition() + velocity * Time::FixedDelta());
		p_gameObj->rotate(rotVel);
	}
	void Rigidbody2D::OnRender()
	{
	}
	void Rigidbody2D::SetVelocity(float x, float y)
	{
		velocity = sf::Vector2f(x, y);
	}
	void Rigidbody2D::AddVelocity(float x, float y)
	{
		velocity += sf::Vector2f(x, y);
	}
	void Rigidbody2D::AddVelocity(sf::Vector2f vel)
	{
		velocity += vel;
	}
	void Rigidbody2D::AddAngularVelocity(float vel)
	{
		rotVel += vel;
	}
	void Rigidbody2D::SetAngularVelocity(float vel)
	{
		rotVel = vel;
	}
	void Rigidbody2D::SetDrag(float drag)
	{
		this->drag = drag;
	}
	sf::Vector2f Rigidbody2D::GetVelocity()
	{
		return velocity;
	}
	void Rigidbody2D::OnTrigger(Collider * other)
	{
	}
	void Rigidbody2D::OnCollision(Collider* other)
	{
	}
}