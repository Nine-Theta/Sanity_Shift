#include "LuaComponent.h"
#include <string>
#include "GameObject.h"
#include "SpriteComponent.h"
#include "CameraComponent.h"
#include "CircleCollider.h"
#include "TextComponent.h"
#include "PlayerControls.h"
#include "SoundManager.h"
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
		_state.PushLightUserData(NULL, "sge.gameObject");
		_state.SetGlobal("nullobject");
		_state.RegisterLib(timeLib, "time");
		_state.RegisterLib(gameObjectLib, "gameObject");
		_state.RegisterLib(audioLib, "audio");
		_state.PushMetaLib("sge.keys", keysMetaLib);
		registerKeys();
		_state.CallFunction("start");
//		std::cout << _state.CallFunction("returnTest", 3)[1] << std::endl;
		
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
		LuaComponent* comp = _components[state];
		GameObject* obj = comp->GetState()->GetObjectFromStack<GameObject>("sge.gameObject");
		GameObject* parent = comp->GetState()->GetObjectFromStack<GameObject>("sge.gameObject");
		obj->SetParent(parent);
		return 0;
	}

	int LuaComponent::addComponent(lua_State * state)
	{
		LuaComponent* comp = _components[state];
		GameObject* obj = comp->GetState()->GetObjectFromStack<GameObject>("sge.gameObject");
		std::vector<std::string> args = comp->GetState()->GetArgsFromStack();
		std::string comps = args[args.size() - 1];
		//std::cout << "Attempting to add a component of type " << comps << std::endl;

		switch (hash(comps)) 
		{
			case hash("camera"): obj->AddComponent(new CameraComponent()); break;
			case hash("sprite"): obj->AddComponent(new SpriteComponent(args[0])); break;
			case hash("text"): {TextComponent* txt = new TextComponent();
				txt->SetSize(50);
				txt->SetText(args[0]);
				obj->AddComponent(txt);
				break;
			}
			case hash("collider"): obj->AddComponent(new CircleCollider(std::stoi(args[0]))); break;
			case hash("trigger"): obj->AddComponent(new CircleCollider(std::stoi(args[0]),true)); break;
			case hash("controls"): obj->AddComponent(new PlayerControls()); break;
			case hash("lua"): obj->AddComponent(new LuaComponent(args[0])); break;
			default: std::cout << "Component did not exist" << std::endl;
		}
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
		{"sendMessage", sendMessage},
		{"setText", setText},
		{NULL, NULL} // - signals the end of the registry
	};

	const struct luaL_Reg LuaComponent::timeLib[] = {
		{"seconds", getTime},
		{"deltaTime", deltaTime},
		{"fixedDelta", fixedDelta},
		{NULL, NULL} // - signals the end of the registry
	};

	const struct luaL_Reg LuaComponent::audioLib[] = {
		{"buffer", bufferAudio},
		{"play", playAudio},
		{"stream", streamAudio},
		{"stop", stopStream},
		{NULL, NULL} // - signals the end of the registry
	};

	const struct luaL_Reg LuaComponent::gameObjectLib[] = {
		{"new", newObject},
		{"find", findObject},
		{"deleteAll", deleteAll},
		{NULL, NULL} // - signals the end of the registry
	};

	const struct luaL_Reg LuaComponent::keysMetaLib[] = {
		{"pressed", isKeyDown},
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
		lua_State* state = _state.GetState();
		lua_getglobal(state, "oncollision");
		_state.PushLightUserData(other->GetParent());
		lua_pcall(state, 1, 1, 0);
	}
	void LuaComponent::OnTrigger(Collider * other)
	{
		lua_State* state = _state.GetState();
		lua_getglobal(state, "oncollision");
		_state.PushLightUserData(other->GetParent());
		lua_pcall(state, 1, 1, 0);
		//_state.CallFunction("oncollision");
	}
	LuaState * LuaComponent::GetState()
	{
		return &_state;
	}
	int LuaComponent::removeComponent(lua_State * state)
	{
		return 0;
	}
	int LuaComponent::bufferAudio(lua_State * state)
	{
		LuaComponent* comp = _components[state];
		std::string file = comp->GetState()->GetArgsFromStack()[0];
		SoundManager::BufferSound(file);
		return 0;
	}
	int LuaComponent::playAudio(lua_State * state)
	{
		LuaComponent* comp = _components[state];
		std::string file = comp->GetState()->GetArgsFromStack()[0];
		SoundManager::PlaySound(file);
		return 0;
	}
	int LuaComponent::streamAudio(lua_State * state)
	{
		LuaComponent* comp = _components[state];
		std::string file = comp->GetState()->GetArgsFromStack()[0];
		SoundManager::PlayBGM(file);
		return 0;
	}
	int LuaComponent::stopStream(lua_State * state)
	{
		LuaComponent* comp = _components[state];
		//std::string file = comp->GetState()->GetArgsFromStack()[0];
		SoundManager::StopBGM();
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
	int LuaComponent::sendMessage(lua_State * state)
	{
		LuaComponent* comp = _components[state];
		GameObject* obj = comp->GetState()->GetObjectFromStack<GameObject>("sge.gameObject");
		std::string message = comp->GetState()->GetArgsFromStack()[0];
		LuaComponent* receiver = (LuaComponent*)obj->GetComponent(typeid(LuaComponent));
		if (receiver != NULL) {
			lua_getglobal(receiver->_state.GetState(), "onmessage");
			lua_pushstring(receiver->_state.GetState(), message.c_str());
			lua_pcall(receiver->_state.GetState(), 1, 1, 0);
		}
		return 0;
	}
	int LuaComponent::setName(lua_State * state)
	{
		LuaComponent* comp = _components[state];
		GameObject* obj = comp->GetState()->GetObjectFromStack<GameObject>("sge.gameObject");
		std::string name = comp->GetState()->GetArgsFromStack()[0];
		obj->SetName(name);
		return 0;
	}
	int LuaComponent::setText(lua_State * state)
	{
		LuaComponent* comp = _components[state];
		GameObject* obj = comp->GetState()->GetObjectFromStack<GameObject>("sge.gameObject");
		std::string text = comp->GetState()->GetArgsFromStack()[0];
		TextComponent* textComp = (TextComponent*)obj->GetComponent(typeid(TextComponent));
		if (textComp == NULL) {
			textComp = new TextComponent();
			obj->AddComponent(textComp);
		}
		textComp->SetText(text);
		return 0;
	}
	int LuaComponent::getPos(lua_State * state)
	{
		LuaComponent* comp = _components[state];
		LuaState* ls = comp->GetState();
		GameObject* obj = comp->GetState()->GetObjectFromStack<GameObject>("sge.gameObject");
		glm::vec2 vec = obj->getPosition();
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
		obj->setPosition(glm::vec2((float)vals[1], (float)vals[0]));
		return 0;
	}
	int LuaComponent::getWorldPos(lua_State * state)
	{
		LuaComponent* comp = _components[state];
		GameObject* obj = comp->GetState()->GetObjectFromStack<GameObject>("sge.gameObject");
		LuaState* ls = comp->GetState();
		glm::vec2 vec = obj->GetCombinedPosition();
		lua_pushnumber(state, vec.x);
		lua_pushnumber(state, vec.y);
		return 2;
	}
	int LuaComponent::getTime(lua_State * state)
	{
		lua_pushnumber(state, TimeH::TimeRunning());
		return 1;
	}
	int LuaComponent::deltaTime(lua_State * state)
	{
		lua_pushnumber(state, TimeH::DeltaTime());
		return 1;
	}
	int LuaComponent::fixedDelta(lua_State * state)
	{
		lua_pushnumber(state, TimeH::FixedDelta());
		return 1;
	}
	int LuaComponent::newObject(lua_State * state)
	{
		GameObject* obj = new GameObject();
		obj->SetName("NewObject");
		//ObjectBehaviour* rcomp = new SpriteComponent("gecko.png");
		//obj->AddComponent(rcomp);
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
	int LuaComponent::deleteAll(lua_State * state)
	{
		LuaComponent* comp = _components[state];
//		std::string name = comp->GetState()->GetArgsFromStack()[0];
		std::cout << "Attempting to delete all game objects" << std::endl;
		//GameObject* obj = GameObject::Find(name);
		//std::cout << "Found game object: " << obj << std::endl;
		LuaState* ls = comp->GetState();
		//ls->PushLightUserData(obj, "sge.gameObject");
		GameObject::DestroyAll();
		return 0;
	}

	int LuaComponent::isKeyDown(lua_State * state)
	{
		LuaComponent* comp = _components[state];
		sf::Keyboard::Key key = static_cast<sf::Keyboard::Key>((int)comp->GetState()->GetNumbersFromStack()[0]);
		lua_pushboolean(state, sf::Keyboard::isKeyPressed(key));
		return 1;
	}

	void LuaComponent::registerKeys()
	{
		_state.OpenTable("keys");
		_state.PushToTable("up", sf::Keyboard::Up);
		_state.PushToTable("down", sf::Keyboard::Down);
		_state.PushToTable("left", sf::Keyboard::Left);
		_state.PushToTable("right", sf::Keyboard::Right);
		_state.PushToTable("space", sf::Keyboard::Space);
		_state.SaveTable("keys","sge.keys");
	}
}