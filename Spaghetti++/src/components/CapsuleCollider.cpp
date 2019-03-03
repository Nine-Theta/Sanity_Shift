#include "components/CircleCollider.h"
#include "vec2.hpp"
#include "CapsuleCollider.h"


namespace sge {
	CapsuleCollider::CapsuleCollider() : AbstractCollider(1)
	{
	}
	CapsuleCollider::CapsuleCollider(float pRadius, float pHeight, float pMass) : AbstractCollider(pMass), radius(pRadius), height(pHeight)
	{
	}
	CapsuleCollider::~CapsuleCollider()
	{
	}
	void CapsuleCollider::Start()
	{
		btCollisionShape* shape = new btCapsuleShape(radius,height);
		btTransform transform = Physics::glmToBullet(p_gameObj->GetCombinedTransform());
		shape->setMargin(0.01f);

		btVector3 inertia(0, 0, 0);
		if (mass > 0.f)
			shape->calculateLocalInertia(mass, inertia);

		btDefaultMotionState* motionState = new btDefaultMotionState(transform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, shape, inertia);
		rbody = new btRigidBody(rbInfo);
		rbody->setRestitution(.3f);
		rbody->setDamping(0.9745f, .66f);
		rbody->setRollingFriction(.96f);
		rbody->setFriction(.996f);
		rbody->setSpinningFriction(.9f);
		rbody->setActivationState(DISABLE_DEACTIVATION);
		btVector3 angularfactor(0, 1, 0);
		rbody->setAngularFactor(angularfactor);
		id = Physics::AddBody(rbody);
		rbody->setUserPointer(this);
		rbody->setCollisionFlags(rbody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

		//std::cout << gContactAddedCallback << " = Contact added callback" <<  std::endl;
		//delete shape;
	}
	void CapsuleCollider::OnDestroy()
	{
	}
	void CapsuleCollider::Update()
	{
	}
	void CapsuleCollider::OnRender()
	{
	}
	void CapsuleCollider::OnCollision(Collider * other)
	{
	}
	void CapsuleCollider::OnTrigger(Collider * other)
	{
	}
}