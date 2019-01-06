#include "CircleCollider.h"
#include "vec2.hpp"

namespace sge {

	CircleCollider::CircleCollider() : Collider()
	{
	}

	CircleCollider::CircleCollider(float radius) : CircleCollider()
	{
		SetRadius(radius);
	}


	CircleCollider::~CircleCollider()
	{
	}

	void CircleCollider::SetRadius(float radius)
	{
		this->radius = radius;
	}

	void sge::CircleCollider::Collide(Collider * p_col)
	{
		const type_info& type = typeid(*p_col);
		if (type == typeid(CircleCollider)) {
			CollideWithType((CircleCollider*)p_col);
		}
		else
			std::cout << "Collider doesn't know how to handle another collider type, no collision will be resolved!" << std::endl;
	}
	void CircleCollider::CollideWithType(CircleCollider* col)
	{
		//col->SetParent(GameObject::Find("Player"));
		if (p_gameObj == NULL || col->GetParent() == NULL) return;
		sf::Vector2f dist = p_gameObj->getPosition() - col->GetParent()->getPosition();
		//float distSq = magnitudeSq(dist);
		//float minDistSq = sqrtf(radius) + sqrtf(col->radius);
		float minDist = radius + col->radius;
		float distf = magnitude(dist);
		//std::cout << "Attempted to collide two circles at distance " << minDistSq << " and it's meant to be " << distSq << std::endl;
		if (distf < minDist) {
			if (isTrigger || col->isTrigger) {
				p_gameObj->OnTrigger(col);
				col->GetParent()->OnTrigger(this);
				return;
			}
			p_gameObj->OnCollision(col);
			col->GetParent()->OnCollision(this);
			float minDist = radius + col->radius;
			float diff = -(magnitude(sf::Vector2f(dist)) - minDist);
			sf::Vector2f colDir = normalized(dist);
			sf::Vector2f toMove = colDir * (diff + 1); //one pixel offset hack, shouldn't be used but faster than fixing collision
			p_gameObj->setPosition(p_gameObj->getPosition() + toMove);
			if (p_gameObj->GetRigidbody() != NULL) {
				Rigidbody2D* rbody = p_gameObj->GetRigidbody();
				sf::Vector2f vel = rbody->GetVelocity();
				float colVel = dot(vel, colDir);
				sf::Vector2f newColVel = colDir * colVel;
				rbody->AddVelocity(-newColVel - newColVel * bounciness);
			}
		}
	}
	void CircleCollider::OnCollision(Collider* other)
	{
	}
}