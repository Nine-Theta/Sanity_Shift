#pragma once
#include "ObjectBehaviour.h"
#include "LuaComponent.h"

#include "GameObject.h"
namespace sge {
	class CameraRayComp :
		public ObjectBehaviour
	{
	public:
		CameraRayComp();
		~CameraRayComp();

		// Geerbt über ObjectBehaviour
		virtual void Start() override;
		virtual void OnDestroy() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void OnRender() override;
		virtual void OnCollision(Collider * other) override;
		virtual void OnTrigger(Collider * other) override;
	private:
		LuaComponent* lua;
		GameObject* hitPos;
		float focusDistance = 5.f;

	};
}

