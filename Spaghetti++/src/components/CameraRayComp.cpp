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
		hitPos = GameObject::Find("FlashlightTarget");
	}

	void sge::CameraRayComp::OnDestroy()
	{
	}

	void sge::CameraRayComp::Update()
	{
	}

	void sge::CameraRayComp::FixedUpdate()
	{
		RaycastHit hit = Physics::Raycast(p_gameObj->GetCombinedPosition() + p_gameObj->forward() * 0.7f, p_gameObj->forward(), 5);
		//std::cout << "Raycast hit a collider: " << (hit.hit ? hit.collider->GetParent()->GetParent()->GetName() : "No") << std::endl;
		if (hitPos != NULL) {
			float camDistance;
			if (hit.hit)
				camDistance = dot(hit.point - p_gameObj->GetCombinedPosition(), p_gameObj->forward());
			else
				camDistance = 6.f;
			focusDistance -= (focusDistance - camDistance) * 0.1f;
			hitPos->SetWorldPosition(p_gameObj->GetCombinedPosition() + p_gameObj->forward() * focusDistance);
		}
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