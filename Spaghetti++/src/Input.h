#pragma once
//#include "SFML/Graphics/Transformable.hpp"
#include <vector>
#include "components/ObjectBehaviour.h"
#include "components/Collider.h"
namespace sge {
	
	class Input
	{
	private:
		static bool keysPressed [100];
		static bool keysDown [100];
		static bool keysUp [100];

		static bool mouseDownLeft;
		static bool mouseDownRight;
		static bool mousePressedLeft;
		static bool mousePressedRight;
		static bool mouseUpLeft;
		static bool mouseUpRight;
		static glm::ivec2 mousePos;
		static glm::ivec2 lastMousePos;

	public:
		Input();
		~Input();
		static bool GetKey(char key);
		static bool GetKeyDown(char key);
		static bool GetKeyUp(char key);

		static bool GetAnyKey();
		static bool GetAnyKeyDown();
		static bool GetAnyKeyUp();

		static bool GetMouseButton(char button = 0);
		static bool GetMouseButtonDown(char button = 0);
		static bool GetMouseButtonUp(char button = 0);
		static glm::ivec2 GetMousePosition();
		static glm::ivec2 MouseDelta();

		static void OnUpdate();
		static void OnFixedUpdate();
	};
}

