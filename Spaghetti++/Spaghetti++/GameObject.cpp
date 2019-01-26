#include "GameObject.h"
#include "Game.h"
#include "SFML/Graphics/Transformable.hpp"
#include <iostream>
#include "LuaComponent.h"

namespace sge {
	GameObject::GameObject(GameObject* parent) : Transformable()
	{
		_p_parent = parent;
		if (_p_parent != NULL) {
			//std::cout << "Initialised an object with a parent" << std::endl;
			_combinedTransform = _p_parent->GetCombinedTransform();
			_p_parent->AddChild(this);
		}
		else {
			//std::cout << "Initialised an object without a parent" << std::endl;
			_combinedTransform = sf::Transform::Identity;
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

	void GameObject::SetParent(GameObject * p_parent)
	{
		if (_p_parent == NULL && p_parent != NULL) {
			Game::GetInstance().RemoveFromRoot(this);
		}
		_p_parent = p_parent;
	}

	void GameObject::SetName(std::string newName)
	{
		_name = newName;
	}

	std::string GameObject::GetName()
	{
		return _name;
	}

	sf::Vector2f GameObject::GetCombinedPosition()
	{
		return _combinedTransform.transformPoint(sf::Vector2f(0,0));
	}

	Rigidbody2D * GameObject::GetRigidbody()
	{
		return rigidbody;
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
		if (_p_parent != NULL)
			_combinedTransform = _p_parent->GetCombinedTransform().combine(getTransform());
		else
			_combinedTransform = getTransform();
		for (std::vector<ObjectBehaviour*>::iterator itr = _components.begin(), end = _components.end(); itr != end; itr++) {
			//(*itr)->Update();
		}
		for (std::vector<GameObject*>::iterator itr = _children.begin(), end = _children.end(); itr != end; itr++) {
			(*itr)->OnUpdate();
		}
	}
	void GameObject::OnFixedUpdate(){
		if (_state > GOState::ACTIVE)
			return;
		if (_p_parent != NULL) {
			_combinedTransform = _p_parent->GetCombinedTransform().combine(getTransform());
			//std::cout << "Object that is a child has a transform of position: " << _combinedTransform.transformPoint(sf::Vector2f(0, 0)).y << std::endl;
		}
		else
			_combinedTransform = getTransform();
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
		/*for (std::vector<ObjectBehaviour*>::iterator itr = _components.begin(), end = _components.end(); itr != end; itr++) {
			(*itr)->FixedUpdate();
		}
		for (std::vector<GameObject*>::iterator itr = _children.begin(), end = _children.end(); itr != end; itr++) {
			(*itr)->OnFixedUpdate();
		}*/
	}

	void GameObject::OnRender()
	{
		for (std::vector<ObjectBehaviour*>::iterator itr = _components.begin(), end = _components.end(); itr != end; itr++) {
			(*itr)->OnRender();
		}
		//std::cout << "Rendered components: " << _components.size() << std::endl;
		for (std::vector<GameObject*>::iterator itr = _children.begin(), end = _children.end(); itr != end; itr++) {
			(*itr)->OnRender();
			//std::cout << "Rendering children: " << _children.size() << std::endl;
		}
	}

	void GameObject::OnCollision(Collider* other)
	{
		for (ObjectBehaviour* component : _components) {
			component->OnCollision(other);
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

	sf::Transform GameObject::GetCombinedTransform()
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

	void GameObject::OnDestroy()
	{
		//std::cout << "Deleting a game object's components" << std::endl;
		for (std::vector<ObjectBehaviour*>::iterator itr = _components.begin(), end = _components.end(); itr != end; itr++) {
			ObjectBehaviour* obj = (*itr);
			obj->OnDestroy();
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