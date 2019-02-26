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

		btVector3 inertia(0, 0, 0);
		if (mass > 0.f)
			shape->calculateLocalInertia(mass, inertia);

		btDefaultMotionState* motionState = new btDefaultMotionState(transform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, shape, inertia);
		rbody = new btRigidBody(rbInfo);
		rbody->setRestitution(.3f);
		rbody->setDamping(0.79f, 10.96f);
		rbody->setRollingFriction(.96f);
		rbody->setFriction(.96f);
		id = Physics::AddBody(rbody);
	}
	void SphereCollider::OnDestroy()
	{
	}
	void SphereCollider::Update()
	{
	}
	void SphereCollider::OnRender()
	{
	}
	void SphereCollider::OnCollision(Collider * other)
	{
	}
	void SphereCollider::OnTrigger(Collider * other)
	{
	}
}