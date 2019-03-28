#include "Game.h"
#include <iostream>
#include <list>
#include <assert.h>
#include "TimeH.h"
#include "GameObject.h"
#include "components/ObjectBehaviour.h"
#include "components/CameraComponent.h"
#include "components/SpriteComponent.h"
#include "components/Rigidbody2D.h"
#include "components/PlayerControls.h"
#include "components/CircleCollider.h"
#include "components/TextComponent.h"
#include "components/StartComponent.h"
#include "components/MeshComponent.h"
#include "components/BoxCollider.h"
#include "materials/WobbleMaterial.hpp"
#include "materials/SpecularMaterial.hpp"
#include "components/MeshCollider.h"
#include <assert.h>
#include "LuaState.h"
#include "components/CameraComponent.h"
#include "Settings.h"
#include "components/LuaComponent.h"
#include "components/LightComponent.hpp"

#include "core/Sound.hpp"

namespace sge {
	sf::CircleShape shape(100.f);

	Game* Game::instance = NULL;
	Game::Game() : sf::Window(sf::VideoMode(sge::Settings::GetInt("width"), sge::Settings::GetInt("height")), sge::Settings::GetSetting("windowname"), sf::Style::Default, sf::ContextSettings(24, 8, 3, 3, 3))
	{
		_initializeGlew();
		_printVersionInfo();
		_initializeOGL();
		Sound::InitHRTF();
		LightComponent::GenLightUBO();
		Physics::Init();
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
		sge::TimeH::Update();
		initNewComponents();
		sf::Event event;
		unsigned polys = AbstractMaterial::GetRenderedPolys();
		while (pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				close();
				return;
			}
			if (event.type == sf::Event::Resized) {
				std::cout << ("Video mode changed to " + std::to_string(event.size.width) + " - " + std::to_string(event.size.height)) << std::endl;
				CameraComponent::GetMain()->SetProjection(Settings::GetInt("fov"), (float)event.size.width / (float)event.size.height, 0.1f, 1000.0f);//glm::perspective(glm::radians(60.0f), (float)event.size.width / (float)event.size.height, 0.1f, 1000.0f));	//fix projection
				glViewport(0, 0, event.size.width, event.size.height);
			}
		}
		while (TimeH::DoFixedStep()) {
			//std::cout << TimeH::GetFramerate() << std::endl;
			doFixedUpdate();
			destroyOldObjects();
			setTitle(sge::Settings::GetSetting("windowname") + " FPS: " + std::to_string(TimeH::GetFramerateAvg()) + " Triangles: " + std::to_string(polys));
		}
		doUpdate();
		//clear(sf::Color(0x152215FF));
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
		if (Game::hasFocus()) Input::OnUpdate();
		for (std::list<GameObject*>::iterator itr = _rootObjects.begin(), end = _rootObjects.end(); itr != end; itr++) {
			(*itr)->OnUpdate();
		}
	}

	void Game::doFixedUpdate()
	{
		if (Game::hasFocus())Input::OnFixedUpdate();
		/*for (std::list<GameObject*>::iterator itr = _rootObjects.begin(), end = _rootObjects.end(); itr != end; itr++) {
			(*itr)->OnFixedUpdate();
			std::cout << "Updating an object" << std::endl;
		}*/
		Physics::Update(TimeH::FixedDelta());
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
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		LightComponent::UpdateLights();
		//std::cout << "Drawing cameras: " << cameras.size() << std::endl;
		for (std::list<CameraComponent*>::iterator citr = cameras.begin(), cend = cameras.end(); citr != cend; citr++) {
			(*citr)->UpdateCamera();
			(*citr)->OnRender();
			//std::cout << "Rendering camera on frame: " << TimeH::GetFrame() << std::endl;
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
			newObj->UpdateTransform();
			_allObjects.push_back(newObj);
		}
		_newObjects.clear();
		for (ObjectBehaviour* comp : _newComponents) {
			if (comp != NULL) {
				comp->GetParent()->UpdateTransform();
				comp->Start();
			}
		}
		_newComponents.clear();
	}
	
	void Game::Run()
	{
		if (running) return;
		running = true;
		GameObject* obj = new GameObject();
		obj->AddComponent(new LuaComponent("../startscene.lua"));
		//obj->AddComponent(new BoxCollider(vec3(1, 1, 1), 0));
		updateLoop();
		LuaComponent* lua = (LuaComponent*)obj->GetComponent(typeid(LuaComponent));
		//std::cout << "Found test component: " << obj->GetComponent<BoxCollider>() << std::endl;
		lua->GetState()->CallFunction("init");
		GameObject::Destroy(obj);
		TextComponent::LoadFont("font.ttf");
		//Sound* snd = new Sound("LaserBlaster.wav");
		/*GameObject* room = new GameObject();
		room->AddComponent(new MeshComponent("CollisionBox.obj",new SpecularMaterial("rustypaint.png","rustypaint_s.png")));
		room->AddComponent(new MeshCollider("CollisionBox.obj",0.f));
		room->SetWorldPosition(vec3(1,1,-4));
		updateLoop();
		//GameObject* cam = GameObject::Find("Camera");
		GameObject* light = GameObject::Find("FlashLight");
		light->AddComponent(new MeshComponent("flashlight_test.obj", new SpecularMaterial("white.png", "rustypaint_s.png")));
		//light->SetParent(cam);
		//room->AddComponent(new MeshComponent("monkeyhead.obj",new WobbleMaterial("rustypaint.png")));

		//PhysicsTest
		
		GameObject* floor = new GameObject();
		floor->SetWorldPosition(vec3(0, -4.12f, 0));
		floor->SetRotation(vec3(0, 0, 1), 20);*/
		//floor->AddComponent(new BoxCollider(vec3(20, 1, 20), 0));
		//room->AddComponent(new LightComponent(sf::Color::White, 10.f, 0.11f));
		/*CameraComponent* ccam = new CameraComponent();
		obj->AddComponent(ccam);
		obj->SetName("Camera");
		GameObject* rect = new GameObject();
		rect->AddComponent(new StartComponent());
		rect->SetName("StartS");
		//LuaComponent* luac = new LuaComponent("testcomponent.lua");
		//obj->AddComponent(luac);*/
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
		//std::cout << "Finding: " << name << std::endl;
		for (GameObject* obj : _allObjects) {
			//std::cout << "Comparing to: " << obj->GetName() << std::endl;
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
	
	void Game::CloseGame() {
		instance->DestroyAllObjects();
		running = false;
	}

	void Game::DestroyAllObjects()
	{
		for (GameObject* obj : _allObjects) {
			GameObject::Destroy(obj);
		}
	}

	void Game::_printVersionInfo() {
		std::cout << "Context info:" << std::endl;
		std::cout << "----------------------------------" << std::endl;
		//print some debug stats for whoever cares
		const GLubyte *vendor = glGetString(GL_VENDOR);
		const GLubyte *renderer = glGetString(GL_RENDERER);
		const GLubyte *version = glGetString(GL_VERSION);
		const GLubyte *glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
		//nice consistency here in the way OpenGl retrieves values
		GLint major, minor;
		glGetIntegerv(GL_MAJOR_VERSION, &major);
		glGetIntegerv(GL_MINOR_VERSION, &minor);

		printf("GL Vendor : %s\n", vendor);
		printf("GL Renderer : %s\n", renderer);
		printf("GL Version (string) : %s\n", version);
		printf("GL Version (integer) : %d.%d\n", major, minor);
		printf("GLSL Version : %s\n", glslVersion);

		std::cout << "----------------------------------" << std::endl << std::endl;
	}

	void Game::_initializeGlew() {
		std::cout << "Initializing GLEW..." << std::endl;
		//initialize the opengl extension wrangler
		GLint glewStatus = glewInit();
		std::cout << "Initialized GLEW, status (1 == OK, 0 == FAILED):" << (glewStatus == GLEW_OK) << std::endl << std::endl;
	}

	void Game::_initializeOGL() {
		//make sure we test the depthbuffer
		glEnable(GL_DEPTH_TEST);
		glFrontFace(GL_CCW);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glDepthMask(GL_TRUE);
		glDepthFunc(GL_LESS);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glClearColor(0.02f, 0.02f, 0.04f, 1.0f);
	}

	sge::Game& Game::GetInstance()
	{
		if (instance == NULL)
			instance = new Game();
		return *instance;
	}
}
