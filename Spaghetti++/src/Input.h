#pragma once
//#include "SFML/Graphics/Transformable.hpp"
#include <vector>
#include "components/ObjectBehaviour.h"
#include "components/Collider.h"
namespace sge {
	
	class Input
	{
	private:
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
		static bool GetMouseButton(int button = 0);
		static bool GetMouseButtonDown(int button = 0);
		static bool GetMouseButtonUp(int button =0);
		static glm::ivec2 GetMousePosition();
		static glm::ivec2 MouseDelta();

		static void OnUpdate();
		static void OnFixedUpdate();
	};
}

