#include "LuaComponent.h"
#include <string>
#include "GameObject.h"
#include "SpriteComponent.h"
namespace sge {

	std::map <lua_State*, LuaComponent*> LuaComponent::_components;
	LuaComponent::LuaComponent(std::string file) : _state("components/" + file)
	{
		_components[_state.GetState()] = this;
		lua_State* st = _state.GetState();

	}

	LuaComponent::~LuaComponent()
	{
		_components.erase(_state.GetState());
	}
	void LuaComponent::Start()
	{
		_state.RegisterLib(gameObjectLib, "test");
		_state.PushMetaLib("sge.gameObject", gameObjectMetaLib);
		_state.PushLightUserData(GetParent(), "sge.gameObject");
		_state.SetGlobal("parent");
		_state.RegisterLib(timeLib, "time");
		_state.RegisterLib(gameObjectLib, "gameObject");
		_state.CallFunction("start");
		std::cout << _state.CallFunction("returnTest", 3)[1] << std::endl;
		
	}

	int LuaComponent::test(lua_State* state) {
		std::cout << "Test method got called from Lua" << std::endl;
		lua_pushinteger(state, 15);
		return 1;
	}

	int LuaComponent::getLParent(lua_State* state)
	{
		LuaComponent* comp = _components[state];
		LuaState* ls = comp->GetState();
		std::cout << "Parent should be: " << comp->GetParent() << std::endl;
		ls->PushLightUserData(comp->GetParent());
		return 1;
	}

	int LuaComponent::setParent(lua_State * state)
	{
		return 0;
	}

	int LuaComponent::addComponent(lua_State * state)
	{
		return 0;
	}

	const struct luaL_Reg LuaComponent::gameObjectMetaLib[] = {
		{"getParent", getLParent},
		{"addComponent", addComponent},
		{"removeComponent", removeComponent},
		{"delete", gDelete},
		{"getName", getName},
		{"setName", setName},
		{"getPos", getPos},
		{"getWorldPos", getWorldPos},
		{"setPos", setPos},
		{"setParent", setParent},
		{NULL, NULL} // - signals the end of the registry
	};

	const struct luaL_Reg LuaComponent::timeLib[] = {
		{"seconds", getTime},
		{"deltaTime", deltaTime},
		{"fixedDelta", fixedDelta},
		{NULL, NULL} // - signals the end of the registry
	};

	const struct luaL_Reg LuaComponent::gameObjectLib[] = {
		{"new", newObject},
		{"find", findObject},
		{NULL, NULL} // - signals the end of the registry
	};

	void LuaComponent::OnDestroy()
	{
		_state.CallFunction("ondestroy");
	}
	void LuaComponent::Update()
	{
		_state.CallFunction("update");
	}
	void LuaComponent::FixedUpdate()
	{
		_state.CallFunction("fixedupdate");
	}
	void LuaComponent::OnRender()
	{
		_state.CallFunction("onrender");
	}
	void LuaComponent::OnCollision(Collider * other)
	{
		_state.CallFunction("oncollision");
	}
	void LuaComponent::OnTrigger(Collider * other)
	{
		_state.CallFunction("oncollision");
	}
	LuaState * LuaComponent::GetState()
	{
		return &_state;
	}
	int LuaComponent::removeComponent(lua_State * state)
	{
		return 0;
	}
	int LuaComponent::gDelete(lua_State * state)
	{
		LuaComponent* comp = _components[state];
		GameObject* obj = comp->GetState()->GetObjectFromStack<GameObject>("sge.gameObject");
		GameObject::Destroy(obj);
		return 0;
	}
	int LuaComponent::getName(lua_State * state)
	{
		LuaComponent* comp = _components[state];
		GameObject* obj = comp->GetState()->GetObjectFromStack<GameObject>("sge.gameObject");
		lua_pushstring(state,obj->GetName().c_str());
		return 1;
	}
	int LuaComponent::setName(lua_State * state)
	{
		LuaComponent* comp = _components[state];
		GameObject* obj = comp->GetState()->GetObjectFromStack<GameObject>("sge.gameObject");
		std::string name = comp->GetState()->GetArgsFromStack()[0];
		obj->SetName(name);
		return 0;
	}
	int LuaComponent::getPos(lua_State * state)
	{
		LuaComponent* comp = _components[state];
		LuaState* ls = comp->GetState();
		GameObject* obj = comp->GetState()->GetObjectFromStack<GameObject>("sge.gameObject");
		sf::Vector2 vec = obj->getPosition();
		lua_pushnumber(state, vec.x);
		lua_pushnumber(state, vec.y);
		return 2;
	}
	int LuaComponent::setPos(lua_State * state)
	{
		LuaComponent* comp = _components[state];
		GameObject* obj = comp->GetState()->GetObjectFromStack<GameObject>("sge.gameObject");
		std::vector<double> vals = comp->GetState()->GetNumbersFromStack();
		//std::cout << "Test: " << vals.size() << std::endl;
		obj->setPosition(sf::Vector2f((float)vals[1], (float)vals[0]));
		return 0;
	}
	int LuaComponent::getWorldPos(lua_State * state)
	{
		LuaComponent* comp = _components[state];
		GameObject* obj = comp->GetState()->GetObjectFromStack<GameObject>("sge.gameObject");
		LuaState* ls = comp->GetState();
		sf::Vector2 vec = obj->GetCombinedPosition();
		lua_pushnumber(state, vec.x);
		lua_pushnumber(state, vec.y);
		return 2;
	}
	int LuaComponent::getTime(lua_State * state)
	{
		lua_pushnumber(state, Time::TimeRunning());
		return 1;
	}
	int LuaComponent::deltaTime(lua_State * state)
	{
		lua_pushnumber(state, Time::DeltaTime());
		return 1;
	}
	int LuaComponent::fixedDelta(lua_State * state)
	{
		lua_pushnumber(state, Time::FixedDelta());
		return 1;
	}
	int LuaComponent::newObject(lua_State * state)
	{
		GameObject* obj = new GameObject();
		obj->SetName("NewObject");
		ObjectBehaviour* rcomp = new SpriteComponent("gecko.png");
		obj->AddComponent(rcomp);
		LuaComponent* comp = _components[state];
		LuaState* ls = comp->GetState();
		ls->PushLightUserData(obj, "sge.gameObject");
		return 1;
	}
	int LuaComponent::findObject(lua_State * state)
	{
		LuaComponent* comp = _components[state];
		std::string name = comp->GetState()->GetArgsFromStack()[0];
		std::cout << "Attempting to find game object: " + name << std::endl;
		GameObject* obj = GameObject::Find(name);
		std::cout << "Found game object: " << obj << std::endl;
		LuaState* ls = comp->GetState();
		ls->PushLightUserData(obj, "sge.gameObject");
		return 1;
	}
}