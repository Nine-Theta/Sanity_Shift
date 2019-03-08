#include "GameObject.h"
#include "Game.h"
#include "SFML/Graphics/Transformable.hpp"
#include <iostream>
#include "components/LuaComponent.h"

namespace sge {
	GameObject::GameObject(GameObject* parent)
	{
		_p_parent = parent;
		if (_p_parent != NULL) {
			//std::cout << "Initialised an object with a parent" << std::endl;
			_combinedTransform = _p_parent->GetCombinedTransform();
			_p_parent->AddChild(this);
		}
		else {
			//std::cout << "Initialised an object without a parent" << std::endl;
			_combinedTransform = glm::mat4();
			//Game::GetInstance().AddToRoot(this);
		}
		Game::GetInstance().RegisterGameObject(this);
	}

	GameObject::GameObject() : GameObject(nullptr)
	{
	}

	GameObject::~GameObject()
	{
	}

	GameObject* GameObject::Create()
	{
		return Create(NULL);
	}

	GameObject* GameObject::Create(GameObject * p_parent)
	{
		GameObject* newObject = new GameObject(p_parent);
		return newObject;
	}

	GameObject * GameObject::Find(std::string name)
	{
		return Game::GetInstance().FindGameObject(name);
	}

	void GameObject::DestroyAll()
	{
		return Game::GetInstance().DestroyAllObjects();
	}

	void GameObject::SetParent(GameObject * p_parent)
	{
		FlagMoved();
		if (p_parent == this) return;
		if (_p_parent == NULL && p_parent != NULL) {
			Game::GetInstance().RemoveFromRoot(this);
		}
		else if (_p_parent != NULL && p_parent == NULL) {
			Game::GetInstance().AddToRoot(this);
		}
		else if (_p_parent != NULL && p_parent != _p_parent) {
			_p_parent->RemoveChild(this);
		}
		if (_p_parent != p_parent) {
			_p_parent = p_parent;
			if(_p_parent != NULL)
			_p_parent->AddChild(this);
		}
	}

	void GameObject::SetName(std::string newName)
	{
		_name = newName;
	}

	std::string GameObject::GetName()
	{
		return _name;
	}

	glm::vec3 GameObject::GetCombinedPosition()
	{
		return _combinedTransform[3];// * glm::vec4(0,0,0,0);
	}

	vec3 GameObject::GetPosition()
	{
		return _transform[3];
	}

	Rigidbody2D * GameObject::GetRigidbody()
	{
		return rigidbody;
	}

	void GameObject::SetWorldPosition(glm::vec3 pos)
	{
		FlagMoved();
		if (GetParent() != NULL) {
			glm::mat4 inverse = glm::inverse(GetParent()->GetCombinedTransform());
			_transform[3] = inverse * glm::vec4(pos, 1);
		}
		else
			_transform[3] = vec4(pos, 1);
	}

	void GameObject::SetPosition(glm::vec3 pos)
	{
		FlagMoved();
		_transform[3] = vec4(pos, 1);
	}

	void GameObject::SetWorldTransform(mat4 transform)
	{
		FlagMoved();
		if (_p_parent != NULL) {
			_combinedTransform = transform;
			_transform = inverse(_p_parent->_combinedTransform) * transform;
			//std::cout << "Updating transform of a child in world space not yet supported!" << std::endl;
		}
		else {
			_transform = transform;
		}
	}

	void GameObject::Rotate(glm::vec3 axis, float angle)
	{
		FlagMoved();
		_transform = glm::rotate(_transform, radians(angle), axis);
	}

	void GameObject::SetWorldRotation(glm::vec3 axis, float angle)
	{
		FlagMoved();
		vec4 pos = _combinedTransform[3];
		_combinedTransform = glm::rotate(mat4(), radians(angle), axis);
		_combinedTransform[3] = pos;
		if (GetParent() != NULL)
			_transform = inverse(GetParent()->GetCombinedTransform()) * _combinedTransform;
		else
			_transform = _combinedTransform;
	}

	void GameObject::SetRotation(glm::vec3 axis, float angle)
	{
		FlagMoved();
		vec4 pos = _transform[3];
		_transform = glm::rotate(mat4(), radians(angle), axis);
		_transform[3] = pos;
	}

	void GameObject::SetRotation(quat rotation)
	{
		FlagMoved();
		vec4 pos = _transform[3];
		_transform = glm::toMat4(rotation);
		_transform[3] = pos;
	}

	void GameObject::LookAt(vec3 target, vec3 pUp)
	{
		vec3 forward = normalize(target - GetCombinedPosition());
		vec3 left = cross(pUp, forward);
		vec3 up = cross(left, forward);
		mat4 newMat = lookAt(GetCombinedPosition(), target, pUp);
		newMat[3] = _combinedTransform[3];
		_combinedTransform = newMat;
		if (GetParent() != NULL)
			_transform = inverse(GetParent()->GetCombinedTransform()) * _combinedTransform;
		else
			_transform = _combinedTransform;
	}

	bool GameObject::HasMoved()
	{
		return moved;
	}

	void GameObject::setPosition(float x, float y)
	{
	}

	void GameObject::setPosition(glm::vec2)
	{
	}

	void GameObject::setRotation(float rot)
	{
	}

	glm::vec2 GameObject::getPosition()
	{
		return _transform[3];
	}

	void GameObject::SetActive(bool pEnabled)
	{
		if (enabled == pEnabled) return;
		enabled = pEnabled;
		for (ObjectBehaviour* comp : _components) {
			comp->SetEnabled(enabled);
		}
		//TODO: Implement parent override
	}

	bool GameObject::IsActive()
	{
		return enabled;
	}

	vec3 GameObject::forward()
	{
		return _combinedTransform[2];
	}
	vec3 GameObject::right()
	{
		return -_combinedTransform[0];
	}
	vec3 GameObject::up()
	{
		return _combinedTransform[1];
	}

	void GameObject::rotate(float rot)
	{
	}

	void GameObject::setScale(float x, float y, float z)
	{
	}

	float GameObject::getRotation()
	{
		return 0.0f;
	}

	/*void GameObject::operator delete(void * p)
	{
		std::cout << "Destroying a game object..." << std::endl;
		GameObject* obj = (GameObject*)p;
		return;
		if (obj->GetObjectState() < GOState::DESTROYED) {
			std::cout << "Marked game object for deletion, will destroy after frame: " << obj->GetName() << " - " <<  obj << std::endl;
			Game::GetInstance().RemoveGameObject(obj);
			obj->SetObjectState(GOState::DESTROYED);
		}
		else if (obj->GetObjectState() == GOState::DELETED) {
			std::cout << "Deleted a game object from memory " << std::endl;
			//free(p);
		}
		else {
			std::cout << "Tried to delete an object that is already marked for deletion, but not ready to be deleted yet!" << std::endl;
		}
	}*/

	void GameObject::OnUpdate()
	{
		if (_state > GOState::ACTIVE)
			return;
		UpdateTransform();
		for (std::vector<ObjectBehaviour*>::iterator itr = _components.begin(), end = _components.end(); itr != end; itr++) {
			(*itr)->Update();
		}
		for (std::vector<GameObject*>::iterator itr = _children.begin(), end = _children.end(); itr != end; itr++) {
			(*itr)->OnUpdate();
		}
	}
	void GameObject::OnFixedUpdate(){
		if (_state > GOState::ACTIVE)
			return;
		UpdateTransform();
		if (rigidbody != NULL) {
			rigidbody->FixedUpdate();
			//std::cout << _collider->GetParent() << " - Updated collider with that parent!" << std::endl;
		}

			if (_collider != NULL && !isstatic) //make colliders also check for collision even without rigidbody now. Slower, but lua. Thanks lua
				_collider->CollideWithAll();
		/*for (unsigned int i = 0; i < _components.size(); i++) {
			_components[i]->FixedUpdate();
		}*/
		for (ObjectBehaviour* component : _components) {
			if(component != NULL)
				component->FixedUpdate();
			//std::cout << component->GetParent() << " - Updated component with that parent!" << std::endl;
		}

		for (GameObject* obj : _children) {
			if (obj != NULL)
				obj->OnFixedUpdate();
			//std::cout << component->GetParent() << " - Updated component with that parent!" << std::endl;
		}
		/*for (std::vector<ObjectBehaviour*>::iterator itr = _components.begin(), end = _components.end(); itr != end; itr++) {
			(*itr)->FixedUpdate();
		}
		for (std::vector<GameObject*>::iterator itr = _children.begin(), end = _children.end(); itr != end; itr++) {
			(*itr)->OnFixedUpdate();
		}*/
	}

	void GameObject::OnRender()
	{
		if (_state > GOState::ACTIVE)
			return;
		UpdateTransform(true);
		for (ObjectBehaviour* comp : _components) {
			if(comp->IsEnabled())
				comp->OnRender();
			//std::cout << "Rendering children: " << _children.size() << std::endl;
		}
		for (GameObject* obj : _children) {
			if(obj->IsActive())
				obj->OnRender();
		}
		//std::cout << "Rendered components: " << _components.size() << std::endl;
	}

	void GameObject::OnCollisionStay(const Collision &col)
	{
		for (ObjectBehaviour* component : _components) {
			component->OnCollisionStay(col);
		}
	}

	void GameObject::OnCollisionEnter(const Collision & col)
	{
		for (ObjectBehaviour* component : _components) {
			component->OnCollisionEnter(col);
		}
	}

	void GameObject::OnCollisionExit(const Collision & col)
	{
		for (ObjectBehaviour* component : _components) {
			component->OnCollisionExit(col);
		}
	}

	void GameObject::OnTriggerStay(const Collision &col)
	{
		for (ObjectBehaviour* component : _components) {
			component->OnTriggerStay(col);
		}
	}

	void GameObject::OnTriggerEnter(const Collision & col)
	{
		for (ObjectBehaviour* component : _components) {
			component->OnTriggerEnter(col);
		}
	}

	void GameObject::OnTriggerExit(const Collision & col)
	{
		for (ObjectBehaviour* component : _components) {
			component->OnTriggerExit(col);
		}
	}

	void GameObject::OnCollision(Collider* other)
	{
		for (ObjectBehaviour* component : _components) {
		//	component->OnCollision(other);
		}
	}

	void GameObject::OnTrigger(Collider * other)
	{
		for (ObjectBehaviour* component : _components) {
			component->OnTrigger(other);
		}
	}


	ObjectBehaviour * GameObject::GetComponent(const type_info& type)
	{
		//std::cout << "Searching for component of type " << type.name() << std::endl;
		for (std::vector<ObjectBehaviour*>::iterator itr = _components.begin(), end = _components.end(); itr != end; itr++) {
			//std::cout << "Comparing to component type " << typeid(*(*itr)).name() << std::endl;
			if (typeid(*(*itr)) == type)
				return (*itr);
		}
		return nullptr;
	}


	/*template<class T>
	T * GameObject::GetComponent()
	{
		T* component = NULL;
		for (std::vector<ObjectBehaviour*>::iterator itr = _components.begin(), end = _components.end(); itr != end; itr++) {
			//std::cout << "Comparing to component type " << typeid(*(*itr)).name() << std::endl;
			component = (T)(*itr);
			if (component != NULL) return component;
		}
		return NULL;
	}*/

	std::vector<ObjectBehaviour*> GameObject::GetComponents()
	{
		return _components; 
	}

	void GameObject::AddComponent(ObjectBehaviour* p_component) {
		//Todo: Make operation fail if component of type already exists
		Collider* col = dynamic_cast<Collider*>(p_component);
		if (col != NULL) {
			if (_collider != NULL) {
				std::cout << "Attempted to add a collider to an object that already had one. Overriding and deleting the old one. Please do sanity checks!" << std::endl;
				delete _collider;
			}
			col->SetParent(this);
			_collider = col;
			//std::cout << "Added a collider to a gameobject" << std::endl;
			return;
		}
		Rigidbody2D* rbody = dynamic_cast<Rigidbody2D*>(p_component);
		if (rbody != NULL) {
			rigidbody = rbody;
			isstatic = false;
		}
		LuaComponent* lua = dynamic_cast<LuaComponent*>(p_component);
		if (lua != NULL) {
			isstatic = false;
		}
		p_component->SetParent(this);
		_components.push_back(p_component);
	}

	void GameObject::RemoveComponent(ObjectBehaviour * p_component, bool toDelete)
	{
		//TODO: Implement ability to remove a component from the game object, also considering specials like collider or rigidbody
		//_components.erase(p_component); 
	}

	void GameObject::Destroy(GameObject * p_object) //OVERRIDING DELETE BROKE EVERYTHING. Now this is how it's done until I figure that out
	{
		//std::cout << "Destroying a game object..." << std::endl;
		GameObject* obj = (GameObject*)p_object;
		if (obj->GetObjectState() < GOState::DESTROYED) {
			//std::cout << "Marked game object for deletion, will destroy after frame: " << obj->GetName() << " - " << obj << std::endl;
			Game::GetInstance().RemoveGameObject(obj);
			obj->SetObjectState(GOState::DESTROYED);
		}
		else if (obj->GetObjectState() == GOState::DELETED) {
			//std::cout << "Deleted a game object from memory: " << obj->GetName() << " - " << obj << std::endl;
			delete p_object;
		}
		else {
			std::cout << "Tried to delete an object that is already marked for deletion, but not ready to be deleted yet!" << std::endl;
		}
	}

	glm::mat4 GameObject::GetCombinedTransform() const
	{
		return _combinedTransform;//_combinedTransform;
	}
	sge::GOState GameObject::GetObjectState()
	{
		return _state;
	}
	GameObject * GameObject::GetParent()
	{
		return _p_parent;
	}
	std::vector<GameObject*> GameObject::GetChildren()
	{
		return _children;
	}
	Collider * GameObject::GetCollider()
	{
		return _collider;
	}
	void GameObject::SetObjectState(GOState state)
	{
		_state = state;
	}

	void GameObject::AddChild(GameObject * child)
	{
		_children.push_back(child);
	}

	void GameObject::RemoveChild(GameObject * child)
	{
		//_children.remove
		//TODO: make it possible to remove children
	}

	void GameObject::FlagMoved()
	{
		if (moved) return;
		moved = true;
		//std::cout << "An object was moved and will be recalculated: "<< GetName() << std::endl;
		for (GameObject* child : _children) {
			child->FlagMoved();
		}
	}

	void GameObject::UpdateTransform(bool flag)
	{
		if (!moved) return;
		if (_p_parent != NULL)
			_combinedTransform = _p_parent->GetCombinedTransform() * _transform;// .combine(getTransform());
		else
			_combinedTransform = _transform;//getTransform();
		if(flag)
			moved = false;
	}

	void GameObject::OnDestroy()
	{
		//std::cout << "Deleting a game object's components" << std::endl;
		for (std::vector<ObjectBehaviour*>::iterator itr = _components.begin(), end = _components.end(); itr != end; itr++) {
			ObjectBehaviour* obj = (*itr);
			obj->OnDestroy();
			//std::cout << "Deleting a component! " << std::endl;
			Game::GetInstance().RemoveFromNewComponents(obj);
			delete obj;
		}
		if (_collider != NULL)
		{
			_collider->OnDestroy();
			delete _collider;
			_collider = NULL;
		}
		_state = GOState::DELETED;
	}
	/*
	T * GameObject<T>::GetComponent()
	{
		return nullptr;
	}*/
}