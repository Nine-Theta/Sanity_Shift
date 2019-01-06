#pragma once
//#include "GameObject.h"
#include "Time.h"
//#include "Game.h"
#include <vector>
namespace sge {
	class GameObject;
	class Collider;
	class ObjectBehaviour
	{
	protected:
		GameObject* p_gameObj = NULL;
		static inline float randf() //Quick way of making a random float between 0 and 1 available to all components
		{
			return (float)rand() / (float)RAND_MAX;
		}
	public:
		ObjectBehaviour();
		~ObjectBehaviour();
		void SetParent(GameObject* p_parent);
		GameObject* GetParent();
		virtual void Start() = 0;
		virtual void OnDestroy() = 0;
		virtual void Update() = 0;
		virtual void FixedUpdate() = 0;
		virtual void OnRender() = 0;
		virtual void OnCollision(Collider* other) = 0;
		virtual void OnTrigger(Collider* other) = 0;
	};

}