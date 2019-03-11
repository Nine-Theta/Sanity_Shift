#include "CameraRayComp.h"
#include "GameObject.h"
#include "Game.h"
#include "AbstractCollider.h"
namespace sge {

	CameraRayComp::CameraRayComp()
	{
	}


	CameraRayComp::~CameraRayComp()
	{
	}

	void sge::CameraRayComp::Start()
	{
		lua = p_gameObj->GetComponent<LuaComponent>();
	}

	void sge::CameraRayComp::OnDestroy()
	{
	}

	void sge::CameraRayComp::Update()
	{
	}

	void sge::CameraRayComp::FixedUpdate()
	{
		RaycastHit hit = Physics::Raycast(p_gameObj->GetCombinedPosition() + p_gameObj->forward() * 0.5f, p_gameObj->forward(), 5);
		//std::cout << "Raycast hit a collider: " << (hit.hit ? hit.collider->GetParent()->GetName() : "No") << std::endl;
		if (!hit.hit) return;
		if (lua != NULL)
			lua->CallFunctionWithGameObject("raycastresult",hit.collider->GetParent());
		LuaComponent* other = hit.collider->GetParent()->GetComponent<LuaComponent>();
		if (other != NULL) {
			other->CallFunctionWithGameObject("onraycasthit", p_gameObj);
			//lua->CallFunctionWithGameObject("raycastresult", hit.collider->GetParent());
		}
	}

	void sge::CameraRayComp::OnRender()
	{
	}

	void sge::CameraRayComp::OnCollision(Collider * other)
	{
	}

	void sge::CameraRayComp::OnTrigger(Collider * other)
	{
	}
}