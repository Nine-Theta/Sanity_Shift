#include "Game.h"
#include <iostream>
#include <list>
#include <assert.h>
#include "Time.h"
#include "SFML/Graphics.hpp"
#include "GameObject.h"
#include "ObjectBehaviour.h"
#include "CameraComponent.h"
#include "SpriteComponent.h"
#include "Rigidbody2D.h"
#include "PlayerControls.h"
#include "CircleCollider.h"
#include "TextComponent.h"
#include "StartComponent.h"
#include <assert.h>
#include "LuaState.h"
#include "CameraComponent.h"
#include "Settings.h"

namespace sge {
	sf::CircleShape shape(100.f);

	Game* Game::instance = NULL;
	Game::Game() : sf::RenderWindow(sf::VideoMode(sge::Settings::GetInt("width"), sge::Settings::GetInt("height")), sge::Settings::GetSetting("windowname"))
	{
		/*_allObjects = new std::list<sge::GameObject*>;
		_newComponents = new std::list<sge::ObjectBehaviour*>;
		_rootObjects = new std::list<sge::GameObject*>;
		_deletedObjects = new std::list<sge::GameObject*>;*/
	}


	Game::~Game()
	{
		/*delete _allObjects;
		delete _newComponents;
		delete _rootObjects;*/
	}

	void Game::updateLoop()
	{
		sge::Time::Update();
		initNewComponents();
		sf::Event event;
		while (pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				close();
			if (event.type == sf::Event::Resized) {
				//would be better to move this to the renderer
				//this version implements nonconstrained match viewport scaling
				std::cout << ("Video mode changed to " + std::to_string(event.size.width) + " - " + std::to_string(event.size.height)) << std::endl;
				//_world->getMainCamera()->setProjection(glm::perspective(glm::radians(60.0f), (float)event.size.width / (float)event.size.height, 0.1f, 1000.0f));	//fix projection
				//glViewport(0, 0, event.size.width, event.size.height);
				
			}
		}
		while (Time::DoFixedStep()) {
			//std::cout << Time::GetFramerate() << std::endl;
			doFixedUpdate();
		}
		doUpdate();
		clear(sf::Color(0x152215FF));
		doRender();
		destroyOldObjects();
		assert(_allObjects.size() >= _rootObjects.size());
		//draw(shape);
		display();
	}

	void Game::destroyOldObjects()
	{
		//std::cout << "Deleting all components of all destroyed objects..." << std::endl;
		for (std::list<GameObject*>::iterator itr = _deletedObjects.begin(), end = _deletedObjects.end(); itr != end; itr++) {
			GameObject* obj = (*itr);
			obj->OnDestroy();
			_allObjects.remove(obj);
			if (obj->GetParent() == NULL) {
				_rootObjects.remove(obj);
			}
			GameObject::Destroy( obj);
		}
		_deletedObjects.clear();
	}

	void Game::doUpdate()
	{
		for (std::list<GameObject*>::iterator itr = _rootObjects.begin(), end = _rootObjects.end(); itr != end; itr++) {
			(*itr)->OnUpdate();
		}
	}

	void Game::doFixedUpdate()
	{
		/*for (std::list<GameObject*>::iterator itr = _rootObjects.begin(), end = _rootObjects.end(); itr != end; itr++) {
			(*itr)->OnFixedUpdate();
			std::cout << "Updating an object" << std::endl;
		}*/
		for (GameObject* obj : _rootObjects)
		{
			obj->OnFixedUpdate();
			//std::cout << "Fixed updating an object" << std::endl;
		}
		//std::cout << "Updated objects: " << _rootObjects.size() << std::endl;
	}

	void Game::doRender()
	{
		std::list<CameraComponent*> cameras = CameraComponent::GetCameras();
		//std::cout << "Drawing cameras: " << cameras.size() << std::endl;
		for (std::list<CameraComponent*>::iterator citr = cameras.begin(), cend = cameras.end(); citr != cend; citr++) {
			(*citr)->UpdateCamera();
			for (std::list<GameObject*>::iterator itr = _rootObjects.begin(), end = _rootObjects.end(); itr != end; itr++) {
				if((*itr)->GetObjectState() <= GOState::ACTIVE)
					(*itr)->OnRender();
			}
		}
	}

	void Game::initNewComponents()
	{
		for (GameObject* newObj : _newObjects) {
			if (newObj->GetParent() == NULL) {
				AddToRoot(newObj);
			}
			_allObjects.push_back(newObj);
		}
		_newObjects.clear();
		for (ObjectBehaviour* comp : _newComponents) {
			if(comp != NULL)
				comp->Start();
		}
		_newComponents.clear();
	}

	void Game::Run()
	{
		if (running) return;
		running = true;
		GameObject* obj = new GameObject();
		CameraComponent* ccam = new CameraComponent();
		obj->AddComponent(ccam);
		obj->SetName("Camera");
		TextComponent::LoadFont("font.ttf");
		GameObject* rect = new GameObject();
		rect->AddComponent(new StartComponent());
		rect->SetName("StartS");
		//LuaState state("test.lua");
		//std::cout << state.GetNumber("width");
		//std::cout << typeid(typeid(5)).name() << std::endl;
		while (running && isOpen()) {
			updateLoop();
		}
	}

	void Game::RegisterGameObject(sge::GameObject* p_object) {
		if (p_object->GetObjectState() != GOState::PRE_INIT || p_object == NULL) {
			std::cout << "Tried to register an already active or invalid object. Don't do that!";
			return;
		}
		_newObjects.push_back(p_object);
	}

	void Game::RemoveGameObject(sge::GameObject * p_object)
	{
		if (p_object->GetObjectState() < sge::GOState::DESTROYED) {
			/*_allObjects.remove(p_object);
			if (p_object->GetParent() == NULL) {
				_rootObjects.remove(p_object);
			}*/
			_deletedObjects.push_back(p_object);
		}
		//p_object->SetObjectState(GOState::DESTROYED);
	}

	void Game::RegisterNewComponent(sge::ObjectBehaviour* p_comp) {
		_newComponents.push_back(p_comp);
	}

	void Game::AddToRoot(GameObject * p_object)
	{
		_rootObjects.push_back(p_object);
		//std::cout << "Added an object to root updating: " << p_object << std::endl;
	}

	GameObject* Game::FindGameObject(std::string name) {
		for (GameObject* obj : _allObjects) {
			if (obj->GetName() == name)
				return obj;
		}
		return NULL;
	}

	size_t Game::GetObjectCount()
	{
		return _allObjects.size();
	}

	void Game::RemoveFromRoot(GameObject * p_object)
	{
		/*int offset;
		for (std::list<GameObject*>::iterator itr = _rootObjects.begin(), end = _rootObjects.end(); itr != end; itr++) {
			if ((*itr) == p_object) {
				offset = (*itr) - (*_rootObjects.begin());
			}
		}*/
		_rootObjects.remove(p_object);
	}

	void Game::RemoveFromNewComponents(ObjectBehaviour * p_comp)
	{
		bool contains = false;
		for (ObjectBehaviour* component : _newComponents) {
			if (component == p_comp) {
				contains = true;
				break;
			}
		}
		if(contains)
			_newComponents.remove(p_comp);
	}

	void Game::DestroyAllObjects()
	{
		for (GameObject* obj : _allObjects) {
			GameObject::Destroy(obj);
		}
	}

	sge::Game& Game::GetInstance()
	{
		if (instance == NULL)
			instance = new Game();
		return *instance;
	}
}
