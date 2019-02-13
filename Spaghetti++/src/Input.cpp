#include "Input.h"
#include "Game.h"
#include "SFML/Graphics/Transformable.hpp"
#include <iostream>
#include "components/LuaComponent.h"
#include "SFML/Window/Mouse.hpp"

namespace sge {

	bool Input::keysPressed[];
	bool Input::keysDown[];
	bool Input::keysUp[];

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

	bool Input::GetKey(char key)
	{
		return keysPressed[key];
	}

	bool Input::GetKeyDown(char key)
	{
		return keysDown[key];
	}

	bool Input::GetKeyUp(char key)
	{
		return keysUp[key];
	}

	bool Input::GetAnyKey()
	{
		for (char i = 0; i < 100; i++)
		{
			if (keysPressed[i]) return true;
		}
		return false;
	}

	bool Input::GetAnyKeyDown()
	{
		for (char i = 0; i < 100; i++)
		{
			if (keysDown[i]) return true;
		}
		return false;
	}

	bool Input::GetAnyKeyUp()
	{
		for (char i = 0; i < 100; i++)
		{
			if (keysUp[i]) return true;
		}
		return false;
	}

	bool Input::GetMouseButton(char button)
	{
		if (button == 0)
			return mousePressedLeft;
		else
			return mousePressedRight;
	}

	bool Input::GetMouseButtonDown(char button)
	{
		if (button == 0)
			return mouseDownLeft;
		else
			return mouseDownRight;
	}

	bool Input::GetMouseButtonUp(char button)
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
		for (char i = 0; i < 100; i++)
		{
			if (keysDown[i]) keysDown[i] = false;
			if (keysUp[i]) keysUp[i] = false;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(i)))
			{
				if (!keysPressed[i]) keysDown[i] = true;
				keysPressed[i] = true;
			}
			else if (keysPressed[i])
			{
				keysPressed[i] = false;
				keysUp[i] = true;
			}
		}

		if (mouseUpLeft) mouseUpLeft = false;
		if (mouseUpRight) mouseUpRight = false;
		if (mouseDownRight) mouseDownRight = false;
		if (mouseDownLeft) mouseDownLeft = false;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{			
			if(!mousePressedLeft) mouseDownLeft = true;
			mousePressedLeft = true;
		}
		else if (mousePressedLeft)
		{
			mousePressedLeft = false;
			mouseUpLeft = true;
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			if (!mousePressedRight) mouseDownRight = true;
			mousePressedRight = true;
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