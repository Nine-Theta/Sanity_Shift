#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

#include "GL/glew.h"
#include "SFML/Graphics.hpp"
#include <list>
namespace sge {
	class Game : public sf::RenderWindow
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

		static Game *instance;
		bool running = false;
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
		GameObject* FindGameObject(std::string name);
		size_t GetObjectCount();
		static sge::Game& GetInstance();
	};
}
