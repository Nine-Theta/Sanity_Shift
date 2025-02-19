#pragma once
//#include "GameObject.h"
#include "TimeH.h"
//#include "Game.h"
#include <vector>
#include "glm/glm.hpp"
#include "glm/geometric.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/common.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "glm/gtx/vector_angle.hpp"
#include "core/AssetLoader.h"
#include "core/Physics.h"

namespace sge {
	class GameObject;
	class Collider;

	using namespace glm;
	class ObjectBehaviour
	{
	protected:
		GameObject* p_gameObj = NULL;
		bool enabled = true;
		static inline float randf() //Quick way of making a random float between 0 and 1 available to all components
		{
			return (float)rand() / (float)RAND_MAX;
		}
	public:
		ObjectBehaviour();
		virtual ~ObjectBehaviour();
		void SetParent(GameObject* p_parent);
		GameObject* GetParent();
		virtual void SetEnabled(bool pEnabled);
		bool IsEnabled();
		virtual void Start() = 0;
		virtual void OnDestroy() = 0;
		virtual void Update() = 0;
		virtual void FixedUpdate() = 0;
		virtual void OnRender() = 0;
		virtual void OnCollisionStay(const Collision &col);
		virtual void OnCollisionEnter(const Collision &col);
		virtual void OnCollisionExit(const Collision &col);

		virtual void OnTriggerStay(const Collision &col);
		virtual void OnTriggerEnter(const Collision &col);
		virtual void OnTriggerExit(const Collision &col);
		virtual void OnTrigger(Collider* other);
		virtual void OnCollision(Collider* other);
	};

}