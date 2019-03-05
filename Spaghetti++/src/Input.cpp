#include "Input.h"
#include "Game.h"
#include "SFML/Graphics/Transformable.hpp"
#include <iostream>
#include "components/LuaComponent.h"
#include "SFML/Window/Mouse.hpp"

namespace sge {

	std::string Input::keyNames[] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S",
		"T", "U", "V", "W", "X","Y", "Z", "Num0", "Num1", "Num2", "Num3", "Num4", "Num5","Num6", "Num7", "Num8", "Num9", "Escape",
		"LeftControl", "LeftShift", "LeftAlt", "LeftSystem", "RightControl", "RightShift", "RightAlt", "RightSystem", "Menu",
		"LeftBracket", "RightBracket", "Semicolon", "Comma", "Period", "Quote", "Slash", "Backslash", "Tilde", "Equal", "Hyphen",
		"Space", "Enter", "Backspace", "Tab", "PageUp", "PageDown", "End", "Home", "Insert", "Delete", "Add", "Subtract", "Multiply",
		"Divide", "Left", "Right", "Up", "Down", "Numpad0", "Numpad1", "Numpad2", "Numpad3", "Numpad4", "Numpad5", "Numpad6", "Numpad7",
		"Numpad8", "Numpad9", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12", "F13", "F14", "F15", "Pause", "Any" };
	
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

	bool Input::lockMousePos = true;

	Input::Input()
	{			
	}

	std::string Input::GetKeyName(char key)
	{
		return Input::keyNames[key];
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
		for (char i = 0; i < sf::Keyboard::KeyCount; i++)
		{
			if (keysPressed[i]) return true;
		}
		return false;
	}

	bool Input::GetAnyKeyDown()
	{
		for (char i = 0; i < sf::Keyboard::KeyCount; i++)
		{
			if (keysDown[i]) return true;
		}
		return false;
	}

	bool Input::GetAnyKeyUp()
	{
		for (char i = 0; i < sf::Keyboard::KeyCount; i++)
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

	glm::ivec2 Input::GetMouseScreenPosition()
	{
		return mousePos;
	}

	glm::ivec2 Input::GetMouseRelativePosition()
	{
		sf::Vector2i pos = sf::Vector2i(mousePos.x, mousePos.y) - sge::Game::GetInstance().getPosition();
		return glm::ivec2(pos.x, pos.y);
	}

	bool Input::MouseMoved()
	{
		return(MouseDelta().x != 0 || MouseDelta().y != 0);
	}

	void Input::setMouseLock(bool active)
	{
		std::cout << "called: " << active << std::endl;
		Input::lockMousePos = active;
		Game::GetInstance().setMouseCursorVisible(!active);
	}
	
	void Input::toggleMouseLock()
	{
		Input::lockMousePos = !lockMousePos;
		Game::GetInstance().setMouseCursorVisible(!lockMousePos);
	}

	void Input::OnUpdate()
	{
		lastMousePos = mousePos;
		/*
		if (sf::Mouse::getPosition().x <= 0)
		{
			sf::Mouse::setPosition(sf::Vector2i(1918, sf::Mouse::getPosition().y));
			lastMousePos.x = 1918;
		}
		if (sf::Mouse::getPosition().x >= 1919)
		{
			sf::Mouse::setPosition(sf::Vector2i(1, sf::Mouse::getPosition().y));
			lastMousePos.x = 1;
		}

		if (sf::Mouse::getPosition().y <= 0)
		{
			sf::Mouse::setPosition(sf::Vector2i(sf::Mouse::getPosition().x, 1078));
			lastMousePos.y = 1078;
		}
		if (sf::Mouse::getPosition().y >= 1079)
		{
			sf::Mouse::setPosition(sf::Vector2i(sf::Mouse::getPosition().x, 1));
			lastMousePos.y = 1;
		}
		*/
		mousePos = glm::ivec2(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
		if (lockMousePos)
		{
			sf::Vector2i pos = sge::Game::GetInstance().getPosition();
			sf::Vector2u size = sge::Game::GetInstance().getSize();
			int x = size.x*0.5 - 1 + pos.x;
			int y = size.y*0.5 - 1 + pos.y;
			sf::Mouse::setPosition(sf::Vector2i(x, y));
			lastMousePos = glm::ivec2(x, y);
		}
	}

	void Input::OnFixedUpdate()
	{	
		bool anyPressed = false;
		bool anyDown = false;
		bool anyUp = false;

		for (char i = 0; i < sf::Keyboard::KeyCount; i++)
		{
			if (keysDown[i]) keysDown[i] = false;
			if (keysUp[i]) keysUp[i] = false;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(i)))
			{
				if (!keysPressed[i]) {
					keysDown[i] = true;
					anyDown = true;
				}
				keysPressed[i] = true;
				anyPressed = true;
			}
			else if (keysPressed[i])
			{
				keysPressed[i] = false;
				keysUp[i] = true;
				anyUp = true;
			}
		}

		keysPressed[101] = anyPressed;
		keysDown[101] = anyDown;
		keysUp[101] = anyUp;

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