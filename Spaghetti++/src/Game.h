#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

#include "GL/glew.h"
#include "glm/glm.hpp"
#include "SFML/Graphics.hpp"
#include <list>
#include "Input.h"
namespace sge {
	using namespace glm;
	class Game : public sf::Window
	{
	private:
		Game();
		~Game();
		void updateLoop();
		void destroyOldObjects();

		void doUpdate();
		void doFixedUpdate();
		void doRender();
		void initNewComponents();

		void _printVersionInfo();
		void _initializeGlew();
		void _initializeOGL();

		static Game *instance;
		bool running = false;
		bool destructionPhase = false;
		std::list<sge::GameObject*> _allObjects;
		std::list<sge::ObjectBehaviour*> _newComponents;

		std::list<sge::GameObject*> _rootObjects;
		std::list<sge::GameObject*> _newObjects;
		std::list<sge::GameObject*> _deletedObjects;
	public:
		void Run();
		void RegisterGameObject(sge::GameObject * p_object);
		void RemoveGameObject(sge::GameObject* p_object);
		void AddToRoot(GameObject* p_object);
		void RegisterNewComponent(ObjectBehaviour* p_object);
		void RemoveFromRoot(GameObject* p_object);
		void RemoveFromNewComponents(ObjectBehaviour* p_comp);
		void DestroyAllObjects();
		void CloseGame();
		bool IsDestroying();
		GameObject* FindGameObject(std::string name);
		size_t GetObjectCount();
		static sge::Game& GetInstance();
	};
}
