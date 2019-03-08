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
//		delete shape;
//		delete motionState;
		//std::cout << "ABSTRACT COLLIDER ON DESTROY GOT CALLED AND COLLIDER GOT DELETED!!!" << std::endl;
	}
	btRigidBody * AbstractCollider::GetRigidbody()
	{
		return rbody;
	}
	bool AbstractCollider::isTrigger()
	{
		if(rbody != NULL)
			return rbody->getCollisionFlags() & btCollisionObject::CF_NO_CONTACT_RESPONSE;
		return trigger;
	}
	void AbstractCollider::SetTrigger(bool ptrigger)
	{
		if(rbody != NULL)
			rbody->setCollisionFlags((rbody->getCollisionFlags() & ~btCollisionObject::CF_NO_CONTACT_RESPONSE) | (trigger ? btCollisionObject::CF_NO_CONTACT_RESPONSE : 0));
		trigger = ptrigger;
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

	void AbstractCollider::destroyCollider()
	{
		Physics::RemoveBody(rbody);
		delete rbody;
	}

	void AbstractCollider::OnDestroy()
	{
		destroyCollider();
	}
	void AbstractCollider::Update()
	{
	}
	void AbstractCollider::FixedUpdate()
	{

		if (mass == 0) {
			rbody->getMotionState()->setWorldTransform(Physics::glmToBullet(p_gameObj->GetCombinedTransform()));
			rbody->setWorldTransform(Physics::glmToBullet(p_gameObj->GetCombinedTransform()));
		}
		else {
			if (p_gameObj->HasMoved()) {
				rbody->getMotionState()->setWorldTransform(Physics::glmToBullet(p_gameObj->GetCombinedTransform()));
				rbody->setWorldTransform(Physics::glmToBullet(p_gameObj->GetCombinedTransform()));
			}
			else {
				btTransform trans = rbody->getWorldTransform();
				mat4 glTrans = Physics::bulletToGlm(trans);
				//glTrans[0] = trans.
				p_gameObj->SetWorldTransform(glTrans);
			}
		}
	}
	void AbstractCollider::OnRender()
	{
	}
	void AbstractCollider::OnCollision(Collider * other)
	{
	}
	void AbstractCollider::OnCollisionStay(const Collision & col)
	{
	}
	void AbstractCollider::OnTrigger(Collider * other)
	{
	}
}