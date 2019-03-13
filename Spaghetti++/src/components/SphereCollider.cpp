#include "components/CircleCollider.h"
#include "vec2.hpp"
#include "SphereCollider.h"

namespace sge {
	SphereCollider::SphereCollider() : AbstractCollider(1)
	{
	}
	SphereCollider::SphereCollider(float pRadius, float pMass) : AbstractCollider(pMass), radius(pRadius)
	{
	}
	SphereCollider::~SphereCollider()
	{
	}
	void SphereCollider::Start()
	{
		btCollisionShape* shape = new btSphereShape(radius);
		btTransform transform = Physics::glmToBullet(p_gameObj->GetCombinedTransform());
		shape->setMargin(0.01f);

		btVector3 inertia(0, 0, 0);
		if (mass > 0.f)
			shape->calculateLocalInertia(mass, inertia);

		btDefaultMotionState* motionState = new btDefaultMotionState(transform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, shape, inertia);
		rbody = new btRigidBody(rbInfo);
		rbody->setRestitution(.5f);
		rbody->setFriction(0.5f);
		rbody->setDamping(0.3f, 0.2);
		rbody->setUserPointer(this);
		id = Physics::AddBody(rbody);

		SetTrigger(trigger);
	}
	void SphereCollider::OnDestroy()
	{
		destroyCollider();
	}
	void SphereCollider::Update()
	{
	}
	void SphereCollider::OnCollision(Collider * other)
	{
	}
	void SphereCollider::OnTrigger(Collider * other)
	{
	}
}