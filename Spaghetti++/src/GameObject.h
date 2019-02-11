#pragma once
//#include "SFML/Graphics/Transformable.hpp"
#include <vector>
#include "components/ObjectBehaviour.h"
#include "components/Collider.h"
#include "components/Rigidbody2D.h"

#include "components/TextComponent.h"
namespace sge {
	enum GOState { PRE_INIT, ACTIVE, DESTROYED, DELETED };
	class Rigidbody2D;
	//template<class T>
	//template <class T>
	class GameObject// : public sf::Transformable
	{
	private:
		glm::mat4 _transform = glm::mat4();
		glm::mat4 _combinedTransform = glm::mat4();
		GameObject* _p_parent = NULL;
		sge::GOState _state = GOState::PRE_INIT;
		std::vector<ObjectBehaviour*> _components;
		std::vector<GameObject*> _children;
		std::string _name;
		sge::Collider* _collider = NULL;
		bool isstatic = true;
		Rigidbody2D* rigidbody = NULL;
		void SetObjectState(GOState state);
		void AddChild(GameObject* child);
		void RemoveChild(GameObject* child);

	public:
		GameObject();
		GameObject(GameObject* p_parent);
		~GameObject();
		glm::mat4 GetCombinedTransform() const;
		sge::GOState GetObjectState();
		GameObject* GetParent();
		Collider* GetCollider();
		void OnDestroy();
		static GameObject* Create();
		static void Destroy(GameObject* p_object);
		static void DestroyAll();
		static GameObject* Create(GameObject* p_parent);
		static GameObject* Find(std::string name);
		void SetParent(GameObject* p_parent);
		void SetName(std::string newName);
		std::string GetName();
		glm::vec3 GetCombinedPosition();
		Rigidbody2D* GetRigidbody();
		void SetWorldPosition(glm::vec3 pos);
		//Dummies for old SFML-based functions:
		void setPosition(float x, float y);
		void setPosition(glm::vec2);
		void setRotation(float rot);
		glm::vec2 getPosition();

		vec3 forward();
		void rotate(float rot);
		void setScale(float x, float y, float z = 1);
		float getRotation();
		//void operator delete(void * p);
		//template <class T>
		//T* GetComponent<T>();

		void OnUpdate();
		void OnFixedUpdate();
		void OnRender();
		void OnCollision(Collider* other);
		void OnTrigger(Collider* other);
		//template <typename T, typename = enable_if<is_base_of<ObjectBehaviour, T>::value>::type>
		ObjectBehaviour* GetComponent(const type_info& type); //Please use typeid of object type, not pointer type
		template<class T>
		T* GetComponent(); //Please use typeid of object type, not pointer type
		std::vector<ObjectBehaviour*> GetComponents();
		void AddComponent(ObjectBehaviour * p_component);
		void RemoveComponent(ObjectBehaviour* p_component, bool toDelete);
	};
	/*template<typename T>
	inline T * GameObject::GetComponent()
	{
		static_assert(std::is_base_of<sge::ObjectBehaviour, T>::value, "T must inherit from list");
		T* component = NULL;
		for (std::vector<ObjectBehaviour*>::iterator itr = _components.begin(), end = _components.end(); itr != end; itr++) {
			//std::cout << "Comparing to component type " << typeid(*(*itr)).name() << std::endl;
			component = (T)(*itr);
			if (component != NULL) return component;
		}
		return NULL;
	}*/
}

