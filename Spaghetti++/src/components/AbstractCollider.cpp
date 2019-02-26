#include "components/CircleCollider.h"
#include "vec2.hpp"
#include "AbstractCollider.h"

namespace sge {
	AbstractCollider::AbstractCollider()
	{
	}
	AbstractCollider::AbstractCollider(float pMass) : mass(pMass)
	{
	}
	AbstractCollider::~AbstractCollider()
	{
	}
	btRigidBody * AbstractCollider::GetRigidbody()
	{
		return rbody;
	}
	void AbstractCollider::Start()
	{
		btCollisionShape* shape = new btBoxShape(btVector3(1, 1, 1));
		btTransform transform = Physics::glmToBullet(p_gameObj->GetCombinedTransform());

		btVector3 inertia(0, 0, 0);
		if(mass > 0.f)
			shape->calculateLocalInertia(mass, inertia);

		btDefaultMotionState* motionState = new btDefaultMotionState(transform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, shape, inertia);
		rbody = new btRigidBody(rbInfo);
		rbody->setRestitution(.9f);
		rbody->setDamping(0.8f, 0.3f);
		id = Physics::AddBody(rbody);
	}
	void AbstractCollider::OnDestroy()
	{
	}
	void AbstractCollider::Update()
	{
	}
	void AbstractCollider::FixedUpdate()
	{
		btTransform trans = rbody->getWorldTransform();
		mat4 glTrans = Physics::bulletToGlm(trans);
		//glTrans[0] = trans.
		p_gameObj->SetWorldTransform(glTrans);
	}
	void AbstractCollider::OnRender()
	{
	}
	void AbstractCollider::OnCollision(Collider * other)
	{
	}
	void AbstractCollider::OnTrigger(Collider * other)
	{
	}
}