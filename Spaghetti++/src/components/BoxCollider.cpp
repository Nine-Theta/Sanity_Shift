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
		btCollisionShape* shape = new btBoxShape(btVector3(dimensions.x * 0.5f, dimensions.y * 0.5f, dimensions.z * 0.5f));//new btBoxShape(btVector3(1.32f, 2.33f, 0.15f)); 
		btTransform transform = Physics::glmToBullet(p_gameObj->GetCombinedTransform());
		//shape->setMargin(0.01f);
		btVector3 inertia(0, 0, 0);
		if (mass > 0.f)
			shape->calculateLocalInertia(mass, inertia);

		btDefaultMotionState* motionState = new btDefaultMotionState(transform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, shape, inertia);
		rbody = new btRigidBody(rbInfo);
		rbody->setRestitution(.5f);
		rbody->setFriction(0.5f);
		rbody->setDamping(0.1f, 0.2);
		rbody->setUserPointer(this);
		id = Physics::AddBody(rbody);

		SetTrigger(trigger);
	}
	void BoxCollider::OnDestroy()
	{
		destroyCollider();
	}
	void BoxCollider::Update()
	{
	}
	void BoxCollider::OnCollision(Collider * other)
	{
	}
	void BoxCollider::OnTrigger(Collider * other)
	{
	}
}