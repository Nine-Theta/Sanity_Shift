#pragma once
//#include "SFML/Graphics/Transformable.hpp"
#include <vector>
#include "components/ObjectBehaviour.h"
#include "components/Collider.h"
namespace sge {
	
	class Input
	{
	private:
		static std::string keyNames[102];

		static bool keysPressed [102];
		static bool keysDown [102];
		static bool keysUp [102];

		static bool mouseDownLeft;
		static bool mouseDownRight;
		static bool mousePressedLeft;
		static bool mousePressedRight;
		static bool mouseUpLeft;
		static bool mouseUpRight;
		static glm::ivec2 mousePos;
		static glm::ivec2 lastMousePos;

		static bool lockMousePos;

	public:
		Input();
		~Input();
		static std::string GetKeyName(char key);

		static bool GetKey(char key);
		static bool GetKeyDown(char key);
		static bool GetKeyUp(char key);

		static bool GetAnyKey();
		static bool GetAnyKeyDown();
		static bool GetAnyKeyUp();

		static bool GetMouseButton(char button = 0);
		static bool GetMouseButtonDown(char button = 0);
		static bool GetMouseButtonUp(char button = 0);
		static glm::ivec2 GetMouseScreenPosition();
		static glm::ivec2 GetMouseRelativePosition();
		static glm::ivec2 MouseDelta();
		static bool MouseMoved();

		static void setMouseLock(bool active);
		static void toggleMouseLock();

		static void OnUpdate();
		static void OnFixedUpdate();
	};
}

