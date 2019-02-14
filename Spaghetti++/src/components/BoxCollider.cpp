#include "components/CircleCollider.h"
#include "vec2.hpp"
#include "BoxCollider.h"

namespace sge {
	BoxCollider::BoxCollider()
	{
	}
	BoxCollider::BoxCollider(vec3 size, float pMass) : dimensions(size), mass(pMass)
	{
	}
	BoxCollider::~BoxCollider()
	{
	}
	void BoxCollider::Start()
	{
		btCollisionShape* shape = new btBoxShape(btVector3(dimensions.x, dimensions.y, dimensions.z));
		btTransform transform = Physics::glmToBullet(p_gameObj->GetCombinedTransform());

		btVector3 inertia(0, 0, 0);
		if(mass > 0.f)
			shape->calculateLocalInertia(mass, inertia);

		btDefaultMotionState* motionState = new btDefaultMotionState(transform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, shape, inertia);
		rbody = new btRigidBody(rbInfo);
		rbody->setRestitution(.6f);
		id = Physics::AddBody(rbody);
	}
	void BoxCollider::OnDestroy()
	{
	}
	void BoxCollider::Update()
	{
	}
	void BoxCollider::FixedUpdate()
	{
		btTransform trans = rbody->getWorldTransform();
		mat4 glTrans = Physics::bulletToGlm(trans);
		//glTrans[0] = trans.
		p_gameObj->SetWorldTransform(glTrans);
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