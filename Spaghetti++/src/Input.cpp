#include "Input.h"
#include "Game.h"
#include "SFML/Graphics/Transformable.hpp"
#include <iostream>
#include "components/LuaComponent.h"
#include "SFML/Window/Mouse.hpp"

namespace sge {

	bool Input::mouseDownLeft;
	bool Input::mouseDownRight;
	bool Input::mousePressedLeft;
	bool Input::mousePressedRight;
	bool Input::mouseUpLeft;
	bool Input::mouseUpRight;
	glm::ivec2 Input::mousePos;
	glm::ivec2 Input::lastMousePos;

	Input::Input()
	{	
	}

	bool Input::GetMouseButton(int button)
	{
		if (button == 0)
			return mousePressedLeft;
		else
			return mousePressedRight;
	}

	bool Input::GetMouseButtonDown(int button)
	{
		if (button == 0)
			return mouseDownLeft;
		else
			return mouseDownRight;
	}

	bool Input::GetMouseButtonUp(int button)
	{
		if (button == 0)
			return mouseUpLeft;
		else
			return mouseUpRight;
	}

	glm::ivec2 Input::MouseDelta()
	{
		return mousePos - lastMousePos;
	}

	glm::ivec2 Input::GetMousePosition()
	{
		return mousePos;
	}

	void Input::OnUpdate()
	{
		lastMousePos = mousePos;
		mousePos = glm::ivec2(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
	}

	void Input::OnFixedUpdate()
	{
		
		if (mouseUpLeft) mouseUpLeft = false;
		if (mouseUpRight) mouseUpRight = false;
		if (mouseDownLeft) mouseDownLeft = false;
		if (mouseDownRight) mouseDownRight = false;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			mousePressedLeft = true;
			mouseDownLeft = true;
		}
		else if (mousePressedLeft)
		{
			mousePressedLeft = false;
			mouseUpLeft = true;
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			mousePressedRight = true;
			mouseDownRight = true;
		}
		else if (mousePressedRight)
		{
			mousePressedRight = false;
			mouseUpRight = true;
		}
	}

	Input::~Input()
	{
	}
}