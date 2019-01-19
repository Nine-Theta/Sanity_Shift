#pragma once
#include "ObjectBehaviour.h"
#include "LuaState.h"

namespace sge {
	class LuaComponent :
		public ObjectBehaviour
	{
	public:
		LuaComponent(std::string file);
		~LuaComponent();

		// Geerbt über ObjectBehaviour
		virtual void Start() override;
		virtual void OnDestroy() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void OnRender() override;
		virtual void OnCollision(Collider * other) override;
		virtual void OnTrigger(Collider * other) override;
	protected:
		LuaState _state;
	};
}