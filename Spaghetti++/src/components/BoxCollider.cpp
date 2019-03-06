#include "components/CircleCollider.h"
#include "vec2.hpp"
#include "BoxCollider.h"

namespace sge {
	BoxCollider::BoxCollider() : AbstractCollider(1)
	{
	}
	BoxCollider::BoxCollider(vec3 size, float pMass) : AbstractCollider(pMass), dimensions(size)
	{
	}
	BoxCollider::~BoxCollider()
	{
	}
	void BoxCollider::Start()
	{
		btCollisionShape* shape = new btBoxShape(btVector3(1, 1, 1));
		btTransform transform = Physics::glmToBullet(p_gameObj->GetCombinedTransform());
		shape->setMargin(0.01);
		btVector3 inertia(0, 0, 0);
		if (mass > 0.f)
			shape->calculateLocalInertia(mass, inertia);

		btDefaultMotionState* motionState = new btDefaultMotionState(transform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, shape, inertia);
		rbody = new btRigidBody(rbInfo);
		rbody->setRestitution(.9f);
		rbody->setDamping(0.1f, 0.2);
		rbody->setUserPointer(this);
		id = Physics::AddBody(rbody);
		delete motionState;

		SetTrigger(trigger);
	}
	void BoxCollider::OnDestroy()
	{
	}
	void BoxCollider::Update()
	{
	}
	void BoxCollider::OnRender()
	{
	}
	void BoxCollider::OnCollision(Collider * other)
	{
	}
	void BoxCollider::OnTrigger(Collider * other)
	{
	}
}