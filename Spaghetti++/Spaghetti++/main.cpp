
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Settings.h"

#include <stdio.h>
#include <lua.hpp>

class TestObject {
public:
	int counter;
	int multiplier;
};

static int getTestObject(lua_State *lua) {
	TestObject* object = new TestObject();
	object->counter = 20;
	lua_pushlightuserdata(lua, object);
	return 1;
}

static int getCounter(lua_State *lua) {
	TestObject* object = static_cast<TestObject*>(lua_touserdata(lua, 1));
	lua_pushinteger(lua, object->counter);
	return 1;
}

static const struct luaL_Reg testObjectLib[] = {
	{"getCounter", getCounter},
	{"getTestObject", getTestObject},
	{NULL, NULL} // - signals the end of the registry
};

int main3(void) {
	lua_State *lua = luaL_newstate();
	luaL_openlibs(lua);
	luaL_newlib(lua, testObjectLib);
	lua_setglobal(lua, "testObject");
	luaL_loadfile(lua, "userdata.lua");
	lua_call(lua, 0, 0);

	return 0;
}

using namespace std;
int main(int argc, char * argv[])
{
	//sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	//shape.setFillColor(sf::Color::Green);
	ios_base::sync_with_stdio(false);
	sge::Settings::ReadSettings();
	sge::Game &game = sge::Game::GetInstance();
	game.Run();
	/*while (game.isOpen())
	{
		sf::Event event;
		while (game.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				game.close();
		}

		game.clear();
		game.draw(shape);
		game.display();
	}*/
	return 0;
}