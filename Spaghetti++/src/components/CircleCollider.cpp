#include "components/CircleCollider.h"
#include "vec2.hpp"

namespace sge {

	CircleCollider::CircleCollider() : Collider()
	{
	}

	CircleCollider::CircleCollider(float radius, bool trigger) : CircleCollider() 
	{
		SetRadius(radius);
		isTrigger = trigger;
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
		glm::vec3 dist = p_gameObj->GetCombinedPosition() - col->GetParent()->GetCombinedPosition();
		//float distSq = magnitudeSq(dist);
		//float minDistSq = sqrtf(radius) + sqrtf(col->radius);
		float minDist = radius + col->radius;
		float distf = glm::length(dist);
		//std::cout << "Attempted to collide two circles at distance " << minDist << " and it's meant to be " << distf << std::endl;
		if (distf < minDist) {
			if (isTrigger || col->isTrigger) {
				p_gameObj->OnTrigger(col);
				col->GetParent()->OnTrigger(this);
				return;
			}
			p_gameObj->OnCollision(col);
			col->GetParent()->OnCollision(this);
			float minDist = radius + col->radius;
			float diff = -(glm::length(dist) - minDist);
			glm::vec3 colDir = glm::normalize(dist);
			glm::vec3 toMove = colDir * (diff + 1); //one pixel offset hack, shouldn't be used but faster than fixing collision
			p_gameObj->SetWorldPosition(p_gameObj->GetCombinedPosition() + toMove);
			if (p_gameObj->GetRigidbody() != NULL) {
				Rigidbody2D* rbody = p_gameObj->GetRigidbody();
				vec2 vel = rbody->GetVelocity();
				float colVel = glm::dot(vel, vec2(colDir));
				vec2 newColVel = colDir * colVel;
				rbody->AddVelocity(-newColVel - newColVel * bounciness);
			}
		}
	}
	void CircleCollider::OnCollision(Collider* other)
	{
	}
}