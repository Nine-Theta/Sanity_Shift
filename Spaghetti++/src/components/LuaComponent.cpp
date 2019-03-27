#include "LuaComponent.h"
#include <string>
#include "GameObject.h"
#include "SpriteComponent.h"
#include "CameraComponent.h"
#include "CircleCollider.h"
#include "TextComponent.h"
#include "PlayerControls.h"
#include "SoundManager.h"
#include "LightComponent.hpp"
#include "MeshComponent.h"
#include "BoxCollider.h"
#include "MeshCollider.h"
#include "materials/SpecularMaterial.hpp"
#include "materials/FluorescentMaterial.hpp"
#include "Input.h"
#include "game.h"

#include "SoundComponent.h"
#include "SphereCollider.h"
#include "CapsuleCollider.h"
#include "LightFluorComp.h"
#include "CameraRayComp.h"
#include "MannequinTriggerComp.h"
namespace sge {

	std::map <lua_State*, LuaComponent*> LuaComponent::_components;
	LuaComponent::LuaComponent(std::string file) : _state("components/" + file)
	{
		_components[_state.GetState()] = this;
		lua_State* st = _state.GetState();
		distTarget = GetParent();
		//std::cout << "Registered a lua component: " << st << std::endl;
	}

	LuaComponent::~LuaComponent()
	{
		_components.erase(_state.GetState());
		//std::cout << "Deleted a lua component" << std::endl;
	}
	void LuaComponent::Start()
	{
		_state.RegisterLib(gameObjectLib, "test");
		_state.PushMetaLib("sge.gameObject", gameObjectMetaLib);
		_state.PushLightUserData(GetParent(), "sge.gameObject");
		_state.SetGlobal("parent");
		_state.PushLightUserData((GameObject*)NULL, "sge.gameObject");
		_state.SetGlobal("nullobject");
		_state.RegisterLib(timeLib, "time");
		_state.RegisterLib(gameObjectLib, "gameObject");
		_state.RegisterLib(audioLib, "audio");
		_state.PushMetaLib("sge.keys", keysMetaLib);
		registerKeys();
		_state.RegisterLib(mouseLib, "mouse");
		_state.RegisterLib(utilityLib, "util");
		_state.CallFunction("start");

		distTarget = CameraComponent::GetMain() != NULL ? CameraComponent::GetMain()->GetParent() : NULL;
		if (distTarget == NULL)
			distTarget = GetParent();
		
	}

	int LuaComponent::test(lua_State* state) {
		std::cout << "Test method got called from Lua" << std::endl;
		lua_pushinteger(state, 15);
		return 1;
	}

	int LuaComponent::getLParent(lua_State* state)
	{
		LuaComponent* comp = _components[state];
		//std::cout << state << std::endl;
		//std::cout << comp << std::endl;
		LuaState* ls = comp->GetState();
		GameObject* obj = comp->GetState()->GetObjectFromStack<GameObject>("sge.gameObject");
		std::cout << "Parent should be: " << obj->GetParent()->GetName() << std::endl;
		ls->PushLightUserData(obj->GetParent(),"sge.gameObject");
		return 1;
	}

	int LuaComponent::setParent(lua_State * state)
	{
		LuaComponent* comp = _components[state];
		GameObject* obj = comp->GetState()->GetObjectFromStack<GameObject>("sge.gameObject");
		GameObject* parent = comp->GetState()->GetObjectFromStackTop<GameObject>("sge.gameObject");
		obj->SetParent(parent);
		//comp->GetState()->PushLightUserData(parent, "sge.gameObject");
		//comp->GetState()->SetGlobal("parent");
		return 0;
	}

	int LuaComponent::setActive(lua_State * state)
	{
		LuaComponent* comp = _components[state];
		GameObject* obj = comp->GetState()->GetObjectFromStack<GameObject>("sge.gameObject");
		obj->SetActive(comp->GetState()->GetBoolsFromStack()[0]);
		return 0;
	}

	int LuaComponent::setTrigger(lua_State * state)
	{
		LuaComponent* comp = _components[state];
		GameObject* obj = comp->GetState()->GetObjectFromStack<GameObject>("sge.gameObject");
		AbstractCollider* col = obj->GetComponent<AbstractCollider>();
		if(col != NULL)
			col->SetTrigger(comp->GetState()->GetBoolsFromStack()[0]);
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
			//case hash("collider"): obj->AddComponent(new CircleCollider(std::stof(args[0]))); break;
			//case hash("trigger"): obj->AddComponent(new CircleCollider(std::stof(args[0]),true)); break;
			case hash("controls"): obj->AddComponent(new PlayerControls()); break;
			case hash("glowcontroller"): obj->AddComponent(new LightFluorComp()); break;
			case hash("lua"): obj->AddComponent(new LuaComponent(args[0])); break;
			case hash("raycast"): obj->AddComponent(new CameraRayComp()); break;
			case hash("mannequin"): obj->AddComponent(new MannequinTriggerComp()); break;
			case hash("mesh"): { 
				if(args.size() == 5)
					obj->AddComponent(new MeshComponent(args[3], new SpecularMaterial(args[2], args[1], args[0]))); 
				else {
					if(args[4] == "specular")
						obj->AddComponent(new MeshComponent(args[3], new SpecularMaterial(args[2], args[1], args[0])));
					else if(args[4] == "glow")
						obj->AddComponent(new MeshComponent(args[3], new FluorescentMaterial(args[2], args[1], args[0])));
				}
				break;
			}
			case hash("light"): { LightComponent* comp = new LightComponent(sf::Color(100, 100, 120), std::stof(args[0]));
				comp->SetSpotlightAngle(180, 180);
				comp->SetAmbient(0.00f);
				obj->AddComponent(comp); break;
			}
			case hash("spotlight"): { LightComponent* comp = new LightComponent(sf::Color(180, 180, 140), std::stof(args[0]));
				comp->SetSpotlightAngle(10, 28);
				comp->SetAmbient(0.000f);
				obj->AddComponent(comp); break;
			}
			case hash("pointlight"): { LightComponent* comp = new LightComponent(sf::Color(80,80, 50), std::stof(args[0]));
				comp->SetSpotlightAngle(180, 180);
				comp->SetAmbient(0.00f);
				obj->AddComponent(comp); break;
			}
			case hash("boxcollider"): { 
				vec3 dimensions = vec3(std::stof(args[3]), std::stof(args[2]), std::stof(args[1]));
				std::cout << "Parsed collider and should be: " << args[1] << " and is: " << dimensions.z << std::endl;
				BoxCollider* comp = new BoxCollider(dimensions, std::stof(args[0]));
				obj->AddComponent(comp); break;
			}
			case hash("spherecollider"): { SphereCollider* comp = new SphereCollider(std::stof(args[1]), std::stof(args[0]));
				obj->AddComponent(comp); break;
			}
			case hash("capsulecollider"): { CapsuleCollider* comp = new CapsuleCollider(std::stof(args[2]), std::stof(args[1]), std::stof(args[0]));
				obj->AddComponent(comp); break;
			}
			case hash("meshcollider"): { MeshCollider* comp = new MeshCollider(args[0]);
				obj->AddComponent(comp); break;
			}
			case hash("sound"): { SoundComponent* comp = new SoundComponent(args[0]);
				obj->AddComponent(comp); break;
			}
			default: std::cout << "Component did not exist" << std::endl;
		}
		return 0;
	}

	const struct luaL_Reg LuaComponent::gameObjectMetaLib[] = {
		{"getParent", getLParent},
		{"getChildren", getChildren},
		{"addComponent", addComponent},
		{"removeComponent", removeComponent},
		{"delete", gDelete},
		{"getName", getName},
		{"setName", setName},
		{"getPos", getPos},
		{"getWorldPos", getWorldPos},
		{"setPos", setPos},
		{"setWorldPos", setWorldPos},
		{"rotate", rotate},
		{"setRotation", setRotation},
		{"setWorldRotation", setWorldRotation},
		{"setRotationQ", setRotationQ},
		{"forward", forward},
		{"right", right},
		{"up", up},
		{"setParent", setParent},
		{"setActive", setActive},
		{"setTrigger", setTrigger},
		{"sendMessage", sendMessage},
		{"callFunction", callFunction},
		{"setText", setText},
		{"setFluorReaction", setFluorReaction},
		{"playSound", playSound},
		{"setSound", setSound},
		{"stopSound", stopSound},
		{"addForce", addForce},
		{"setDistanceLimit", setDistanceLimit},
		{NULL, NULL} // - signals the end of the registry
	};

	const struct luaL_Reg LuaComponent::timeLib[] = {
		{"seconds", getTime},
		{"deltaTime", deltaTime},
		{"fixedDelta", fixedDelta},
		{"settimescale", setTimeScale },
		{"gettimescale", getTimeScale },
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
		{"pressed", isKeyPressed},
		{"down", isKeyDown},
		{"up", isKeyUp},
		{"anyPressed", isAnyKeyPressed},
		{"anyDown", isAnyKeyDown},
		{"anyUp", isAnyKeyUp},
		{NULL, NULL} // - signals the end of the registry
	};

	const struct luaL_Reg LuaComponent::mouseLib[] = 
	{
		{"buttonPressed", isButtonPressed },
		{"buttonDown", isButtonDown },
		{"buttonUp", isButtonUp },
		{"position", getMousePos },
		{"relativePosition", getMouseRelativePos },
		{"delta", getMouseDelta },
		{"moved", didMouseMove },
		{"setLock", setMouseLock },
		{"toggleLock", toggleMouseLock },
		{NULL, NULL} // - signals the end of the registry
	};

	const struct luaL_Reg LuaComponent::utilityLib[] =
	{
		{"raycast", raycast},
		{"exitGame", exitGame},
		{NULL, NULL} // - signals the end of the registry
	};

	void LuaComponent::OnDestroy()
	{
		_state.CallFunction("ondestroy");
	}
	void LuaComponent::Update()
	{
		if (GetParent() == NULL || distTarget == NULL) return;
		//if (glm::distance2(distTarget->GetCombinedPosition(), GetParent()->GetCombinedPosition()) > distLimitSq) {
			//std::cout << "A lua comp was not updated because the dist limit was reached: " << GetParent()->GetName() << std::endl;
		//	return;
		//}
		_state.CallFunction("update");
	}
	void LuaComponent::FixedUpdate()
	{
		if (GetParent() == NULL || distTarget == NULL) return;
		if (glm::distance2(distTarget->GetCombinedPosition(), GetParent()->GetCombinedPosition()) > distLimitSq) return;
		//LuaComponent* comp = _components[_state.GetState()];
		//if (comp == NULL) std::cout << "UPDATING A BROKEN LUA COMPONENT" << std::endl;
		_state.CallFunction("fixedupdate");
	}
	void LuaComponent::OnRender()
	{
		if (GetParent() == NULL || distTarget == NULL) return;
		if (glm::distance2(distTarget->GetCombinedPosition(), GetParent()->GetCombinedPosition()) > distLimitSq) return;
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
	void LuaComponent::OnCollisionEnter(const Collision & col)
	{
		lua_State* state = _state.GetState();
		lua_getglobal(state, "oncollisionenter");
		_state.PushLightUserData(col.collider->GetParent());
		lua_pcall(state, 1, 1, 0);
	}
	void LuaComponent::OnCollisionStay(const Collision & col)
	{
		lua_State* state = _state.GetState();
		lua_getglobal(state, "oncollisionstay");
		_state.PushLightUserData(col.collider->GetParent());
		lua_pcall(state, 1, 1, 0);
	}
	void LuaComponent::OnCollisionExit(const Collision & col)
	{
		lua_State* state = _state.GetState();
		lua_getglobal(state, "oncollisionexit");
		_state.PushLightUserData(col.collider->GetParent());
		lua_pcall(state, 1, 1, 0);
	}
	void LuaComponent::OnTriggerEnter(const Collision & col)
	{
		lua_State* state = _state.GetState();
		lua_getglobal(state, "ontriggerenter");
		_state.PushLightUserData(col.collider->GetParent());
		lua_pcall(state, 1, 1, 0);
	}
	void LuaComponent::OnTriggerStay(const Collision & col)
	{
		lua_State* state = _state.GetState();
		lua_getglobal(state, "ontriggerstay");
		_state.PushLightUserData(col.collider->GetParent());
		lua_pcall(state, 1, 1, 0);
	}
	void LuaComponent::OnTriggerExit(const Collision & col)
	{
		lua_State* state = _state.GetState();
		lua_getglobal(state, "ontriggerexit");
		_state.PushLightUserData(col.collider->GetParent());
		lua_pcall(state, 1, 1, 0);
	}
	void LuaComponent::CallFunction(std::string function)
	{
		lua_State* state = _state.GetState();
		lua_getglobal(state, function.c_str());
		//_state.PushLightUserData(other->GetParent());
		lua_pcall(state, 0, 0, 0);
		/*if (status) {
			std::cout << "Lua error: " << std::to_string(status) << "\n" << lua_tostring(state, -1) << "\n" << "Stack: " << lua_gettop(state) << std::endl;
		}*/
	}
	void LuaComponent::CallFunctionWithGameObject(std::string function, GameObject * object)
	{
		lua_State* state = _state.GetState();
		lua_getglobal(state, function.c_str());
		_state.PushLightUserData(object);
		int status = lua_pcall(state, 1, 0, 0);
		if (false && status) {
			std::cout << "Lua error: " << std::to_string(status) << "\n" << lua_tostring(state, -1) << "\n" << "Stack: " << lua_gettop(state) << std::endl;
			lua_pop(state, -1);
			//std::cout << lua_tostring(state, -1) << std::endl;
		}
	}
	LuaState * LuaComponent::GetState()
	{
		return &_state;
	}
	int LuaComponent::removeComponent(lua_State * state)
	{
		LuaComponent* comp = _components[state];
		GameObject* obj = comp->GetState()->GetObjectFromStack<GameObject>("sge.gameObject");
		std::vector<std::string> args = comp->GetState()->GetArgsFromStack();
		std::string comps = args[args.size() - 1];
		//std::cout << "Attempting to add a component of type " << comps << std::endl;

		switch (hash(comps))
		{
		case hash("camera"): obj->RemoveComponent(obj->GetComponent<CameraComponent>()); break;
		case hash("sprite"): obj->RemoveComponent(obj->GetComponent<SpriteComponent>()); break;
		case hash("text"): obj->RemoveComponent(obj->GetComponent<TextComponent>()); break;
						   //case hash("collider"): obj->AddComponent(new CircleCollider(std::stof(args[0]))); break;
						   //case hash("trigger"): obj->AddComponent(new CircleCollider(std::stof(args[0]),true)); break;
		case hash("controls"): obj->RemoveComponent(obj->GetComponent<PlayerControls>()); break;
		case hash("glowcontroller"): obj->RemoveComponent(obj->GetComponent<LightFluorComp>()); break;
		case hash("lua"): obj->RemoveComponent(obj->GetComponent<LuaComponent>()); break;
		case hash("raycast"): obj->RemoveComponent(obj->GetComponent<CameraRayComp>()); break;
		case hash("mannequin"): obj->RemoveComponent(obj->GetComponent<MannequinTriggerComp>()); break;
		case hash("mesh"): obj->RemoveComponent(obj->GetComponent<MeshComponent>()); break;
		case hash("light"): obj->RemoveComponent(obj->GetComponent<LightComponent>()); break;
		case hash("spotlight"): obj->RemoveComponent(obj->GetComponent<LightComponent>()); break;
		case hash("pointlight"): obj->RemoveComponent(obj->GetComponent<LightComponent>()); break;
		case hash("boxcollider"): obj->RemoveComponent(obj->GetComponent<BoxCollider>()); break;
		case hash("spherecollider"): obj->RemoveComponent(obj->GetComponent<SphereCollider>()); break;
		case hash("capsulecollider"): obj->RemoveComponent(obj->GetComponent<CapsuleCollider>()); break;
		case hash("meshcollider"): obj->RemoveComponent(obj->GetComponent<MeshCollider>()); break;
		case hash("sound"): obj->RemoveComponent(obj->GetComponent<SoundComponent>()); break;
		default: std::cout << "Component did not exist" << std::endl;
		}
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
	int LuaComponent::callFunction(lua_State * state)
	{
		LuaComponent* comp = _components[state];
		GameObject* obj = comp->GetState()->GetObjectFromStack<GameObject>("sge.gameObject");
		std::string message = comp->GetState()->GetArgsFromStack()[0];
		LuaComponent* receiver = (LuaComponent*)obj->GetComponent(typeid(LuaComponent));
		if (receiver != NULL) {
			lua_getglobal(receiver->_state.GetState(), message.c_str());
			receiver->GetState()->PushLightUserData(obj->GetParent());
			lua_pcall(receiver->_state.GetState(), 1, 1, 0);
		}
		return 0;
	}
	int LuaComponent::setName(lua_State * state)
	{
		LuaComponent* comp = _components[state];
		//std::cout << "Stack size before obj: " << comp->GetState()->GetStackSize();
		GameObject* obj = comp->GetState()->GetObjectFromStack<GameObject>("sge.gameObject");
		//std::cout << "Stack size after obj: " << comp->GetState()->GetStackSize();
		std::vector<std::string> args = comp->GetState()->GetArgsFromStack();
		//std::cout << "Stack size after obj: " << comp->GetState()->GetStackSize();
		std::string name = args[0];
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
	int LuaComponent::setFluorReaction(lua_State * state)
	{
		LuaComponent* comp = _components[state];
		GameObject* obj = comp->GetState()->GetObjectFromStack<GameObject>("sge.gameObject");
		int n = comp->GetState()->GetNumbersFromStack()[0];
		MeshComponent* mesh = obj->GetComponent<MeshComponent>();
		if (mesh == NULL) return 0;
		FluorescentMaterial* material = (FluorescentMaterial*)mesh->GetMaterial();
		if(material != NULL)
			material->setReactionMult(n);
		return 0;
	}

	int LuaComponent::getPos(lua_State * state)
	{
		LuaComponent* comp = _components[state];
		LuaState* ls = comp->GetState();
		GameObject* obj = comp->GetState()->GetObjectFromStack<GameObject>("sge.gameObject");
		glm::vec3 vec = obj->GetPosition();
		lua_pushnumber(state, vec.x);
		lua_pushnumber(state, vec.y);
		lua_pushnumber(state, vec.z);
		return 3;
	}
	int LuaComponent::forward(lua_State * state)
	{
		LuaComponent* comp = _components[state];
		LuaState* ls = comp->GetState();
		GameObject* obj = comp->GetState()->GetObjectFromStack<GameObject>("sge.gameObject");
		glm::vec3 vec = obj->forward();
		lua_pushnumber(state, vec.x);
		lua_pushnumber(state, vec.y);
		lua_pushnumber(state, vec.z);
		return 3;
	}
	int LuaComponent::right(lua_State * state)
	{
		LuaComponent* comp = _components[state];
		LuaState* ls = comp->GetState();
		GameObject* obj = comp->GetState()->GetObjectFromStack<GameObject>("sge.gameObject");
		glm::vec3 vec = obj->right();
		lua_pushnumber(state, vec.x);
		lua_pushnumber(state, vec.y);
		lua_pushnumber(state, vec.z);
		return 3;
	}
	int LuaComponent::up(lua_State * state)
	{
		LuaComponent* comp = _components[state];
		LuaState* ls = comp->GetState();
		GameObject* obj = comp->GetState()->GetObjectFromStack<GameObject>("sge.gameObject");
		glm::vec3 vec = obj->up();
		lua_pushnumber(state, vec.x);
		lua_pushnumber(state, vec.y);
		lua_pushnumber(state, vec.z);
		return 3;
	}
	int LuaComponent::setPos(lua_State * state)
	{
		LuaComponent* comp = _components[state];
		GameObject* obj = comp->GetState()->GetObjectFromStack<GameObject>("sge.gameObject");
		std::vector<double> vals = comp->GetState()->GetNumbersFromStack();
		//std::cout << "Test: " << vals.size() << std::endl;
		obj->SetPosition(glm::vec3((float)vals[2],(float)vals[1], (float)vals[0]));
		return 0;
	}
	int LuaComponent::addForce(lua_State * state)
	{
		LuaComponent* comp = _components[state];
		GameObject* obj = comp->GetState()->GetObjectFromStack<GameObject>("sge.gameObject");
		std::vector<double> vals = comp->GetState()->GetNumbersFromStack();
		AbstractCollider* col = obj->GetComponent<AbstractCollider>();
		if (col != NULL)
			col->GetRigidbody()->applyCentralForce(btVector3((float)vals[2], (float)vals[1], (float)vals[0]));
		return 0;
	}
	int LuaComponent::playSound(lua_State * state)
	{
		LuaComponent* comp = _components[state];
		GameObject* obj = comp->GetState()->GetObjectFromStack<GameObject>("sge.gameObject");
		std::vector<double> vals = comp->GetState()->GetNumbersFromStack();
		SoundComponent* col = obj->GetComponent<SoundComponent>();
		if (col != NULL) {
			col->Play();
		}
		else {
			std::cout << "ATTEMPTED TO PLAY A SOUND THAT DOES NOT EXIST " << std::endl;
		}
		return 0;
	}
	int LuaComponent::setSound(lua_State * state)
	{
		LuaComponent* comp = _components[state];
		GameObject* obj = comp->GetState()->GetObjectFromStack<GameObject>("sge.gameObject");
		std::vector<std::string> vals = comp->GetState()->GetArgsFromStack();
		SoundComponent* col = obj->GetComponent<SoundComponent>();
		if (col != NULL) {
			col->SetSound(vals[0]);
		}
		else {
			col = new SoundComponent(vals[0]);
			obj->AddComponent(col);
		}
		return 0;
	}
	int LuaComponent::stopSound(lua_State * state)
	{
		LuaComponent* comp = _components[state];
		GameObject* obj = comp->GetState()->GetObjectFromStack<GameObject>("sge.gameObject");
		std::vector<double> vals = comp->GetState()->GetNumbersFromStack();
		SoundComponent* col = obj->GetComponent<SoundComponent>();
		if (col != NULL) {
			if (vals.size() > 0)
				col->Stop((float)vals[0]);
			else
				col->Stop();
		}
		else {
			std::cout << "ATTEMPTED TO STOP A SOUND THAT DOES NOT EXIST " << std::endl;
		}
		return 0;
	}
	int LuaComponent::setWorldPos(lua_State * state)
	{
		LuaComponent* comp = _components[state];
		GameObject* obj = comp->GetState()->GetObjectFromStack<GameObject>("sge.gameObject");
		std::vector<double> vals = comp->GetState()->GetNumbersFromStack();
		//std::cout << "Test: " << vals.size() << std::endl;
		obj->SetWorldPosition(glm::vec3((float)vals[2], (float)vals[1], (float)vals[0]));
		return 0;
	}
	int LuaComponent::setDistanceLimit(lua_State * state)
	{
		LuaComponent* comp = _components[state];
		GameObject* obj = comp->GetState()->GetObjectFromStack<GameObject>("sge.gameObject");
		std::vector<double> vals = comp->GetState()->GetNumbersFromStack();
		//std::cout << "Test: " << vals.size() << std::endl;
		comp->distLimitSq = pow((float)vals[0], 2);
		return 0;
	}
	int LuaComponent::rotate(lua_State * state)
	{
		LuaComponent* comp = _components[state];
		GameObject* obj = comp->GetState()->GetObjectFromStack<GameObject>("sge.gameObject");
		std::vector<double> vals = comp->GetState()->GetNumbersFromStack();
		//std::cout << "Test: " << vals.size() << std::endl;
		obj->Rotate(glm::vec3((float)vals[3], (float)vals[2], (float)vals[1]), (float)vals[0]);
		//obj->Rotate(glm::vec3(0, 1, 0), 20);
		return 0;
	}
	int LuaComponent::setWorldRotation(lua_State * state)
	{
		LuaComponent* comp = _components[state];
		GameObject* obj = comp->GetState()->GetObjectFromStack<GameObject>("sge.gameObject");
		std::vector<double> vals = comp->GetState()->GetNumbersFromStack();
		//std::cout << "Test: " << vals.size() << std::endl;
		obj->SetWorldRotation(glm::vec3((float)vals[3], (float)vals[2], (float)vals[1]), (float)vals[0]);
		//obj->SetRotation(glm::vec3(1, 0, 0), -40);
		//obj->Rotate(glm::vec3(0, 1, 0), 20);
		return 0;
	}
	int LuaComponent::setRotation(lua_State * state)
	{
		LuaComponent* comp = _components[state];
		GameObject* obj = comp->GetState()->GetObjectFromStack<GameObject>("sge.gameObject");
		std::vector<double> vals = comp->GetState()->GetNumbersFromStack();
		//std::cout << "Test: " << vals.size() << std::endl;
		obj->SetRotation(glm::vec3((float)vals[3], (float)vals[2], (float)vals[1]), (float)vals[0]);
		//obj->SetRotation(glm::vec3(1, 0, 0), -40);
		//obj->Rotate(glm::vec3(0, 1, 0), 20);
		return 0;
	}
	int LuaComponent::setRotationQ(lua_State * state)
	{
		LuaComponent* comp = _components[state];
		GameObject* obj = comp->GetState()->GetObjectFromStack<GameObject>("sge.gameObject");
		std::vector<double> vals = comp->GetState()->GetNumbersFromStack();
		//std::cout << "Test: " << vals.size() << std::endl;
		obj->SetRotation(quat((float)vals[3], (float)vals[2], (float)vals[1], (float)vals[0]));
		//obj->SetRotation(glm::vec3(1, 0, 0), -40);
		//obj->Rotate(glm::vec3(0, 1, 0), 20);
		return 0;
	}
	int LuaComponent::getWorldPos(lua_State * state)
	{
		LuaComponent* comp = _components[state];
		LuaState* ls = comp->GetState();
		GameObject* obj = comp->GetState()->GetObjectFromStack<GameObject>("sge.gameObject");
		glm::vec3 vec = obj->GetCombinedPosition();
		lua_pushnumber(state, vec.x);
		lua_pushnumber(state, vec.y);
		lua_pushnumber(state, vec.z);
		return 3;
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

	int LuaComponent::setTimeScale(lua_State* state) {
		LuaComponent* comp = _components[state];
		TimeH::SetTimeScale(comp->GetState()->GetNumbersFromStack()[0]);
		return 0;
	}

	int LuaComponent::getTimeScale(lua_State* state)
	{
		lua_pushnumber(state, TimeH::GetTimeScale());
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

	int LuaComponent::getChildren(lua_State* state) {
		LuaComponent* comp = _components[state];
		LuaState* ls = comp->GetState();
		//std::cout << comp << std::endl;
		GameObject* obj = ls->GetObjectFromStack<GameObject>("sge.gameObject");
		std::vector<GameObject*> children = obj->GetChildren();
		int childrenC = children.size();
		lua_newtable(state);
		for (int i = 0; i < childrenC; i++) {
			//comp->GetState()->PushToTable(std::to_string(i), children[i]);
			//lua_pushlightuserdata(state, children[i]);
			comp->GetState()->PushLightUserData(children[i], "sge.gameObject");
			lua_rawseti(state, -2, i);
		}
		return 1;
	}

#pragma region Mouse/Keyboard Input

	int LuaComponent::isKeyPressed(lua_State * state)
	{
		LuaComponent* comp = _components[state];
		lua_pushboolean(state, Input::GetKey(comp->GetState()->GetNumbersFromStack()[0]));
		return 1;
	}

	int LuaComponent::isKeyDown(lua_State * state)
	{
		LuaComponent* comp = _components[state];
		lua_pushboolean(state, Input::GetKeyDown(comp->GetState()->GetNumbersFromStack()[0]));
		return 1;
	}

	int LuaComponent::isKeyUp(lua_State * state)
	{
		LuaComponent* comp = _components[state];
		lua_pushboolean(state, Input::GetKeyUp(comp->GetState()->GetNumbersFromStack()[0]));
		return 1;
	}

	int LuaComponent::isAnyKeyPressed(lua_State * state)
	{
		lua_pushboolean(state, Input::GetAnyKey());
		return 1;
	}

	int LuaComponent::isAnyKeyDown(lua_State * state)
	{
		lua_pushboolean(state, Input::GetAnyKeyDown());
		return 1;
	}

	int LuaComponent::isAnyKeyUp(lua_State * state)
	{
		lua_pushboolean(state, Input::GetAnyKeyUp());
		return 1;
	}

	int LuaComponent::isButtonPressed(lua_State * state)
	{
		LuaComponent* comp = _components[state];
		lua_pushboolean(state, Input::GetMouseButton(comp->GetState()->GetNumbersFromStack()[0]));
		return 1;
	}

	int LuaComponent::isButtonDown(lua_State * state)
	{
		LuaComponent* comp = _components[state];
		lua_pushboolean(state, Input::GetMouseButtonDown(comp->GetState()->GetNumbersFromStack()[0]));
		return 1;
	}

	int LuaComponent::isButtonUp(lua_State * state)
	{
		LuaComponent* comp = _components[state];
		lua_pushboolean(state, Input::GetMouseButtonUp(comp->GetState()->GetNumbersFromStack()[0]));
		return 1;
	}

	int LuaComponent::getMousePos(lua_State * state)
	{
		lua_pushinteger(state, Input::GetMouseScreenPosition().x);
		lua_pushinteger(state, Input::GetMouseScreenPosition().y);
		return 2;
	}

	int LuaComponent::getMouseRelativePos(lua_State * state)
	{
		lua_pushinteger(state, Input::GetMouseRelativePosition().x);
		lua_pushinteger(state, Input::GetMouseRelativePosition().y);
		return 2;
	}

	int LuaComponent::getMouseDelta(lua_State * state)
	{
		lua_pushinteger(state, Input::MouseDelta().x);
		lua_pushinteger(state, Input::MouseDelta().y);
		return 2;
	}

	int LuaComponent::didMouseMove(lua_State* state)
	{
		lua_pushboolean(state, Input::MouseMoved());
		return 1;
	}

	int LuaComponent::setMouseLock(lua_State* state)
	{
		LuaComponent* comp = _components[state];
		Input::setMouseLock(comp->GetState()->GetBoolsFromStack()[0]);
		return 0;
	}

	int LuaComponent::toggleMouseLock(lua_State* state)
	{
		Input::toggleMouseLock();
		return 0;
	}
	/*
	int LuaComponent::isKeyDown(lua_State * state)
	{
		LuaComponent* comp = _components[state];
		sf::Keyboard::Key key = static_cast<sf::Keyboard::Key>((int)comp->GetState()->GetNumbersFromStack()[0]);
		lua_pushboolean(state, sf::Keyboard::isKeyPressed(key));
		return 1;
	}*/

	void LuaComponent::registerKeys()
	{
		_state.OpenTable("keys");
		for (char i = 0; i < sf::Keyboard::KeyCount; i++)
		{
			_state.PushToTable(Input::GetKeyName(i), sf::Keyboard::Key(i));
		}
		_state.SaveTable("keys","sge.keys");
	}
#pragma endregion

	int LuaComponent::raycast(lua_State* state)
	{
		std::cout << "Raycast through Lua discontinued for now" << std::endl;
		return 0;
		LuaComponent* comp = _components[state];
		GameObject* obj = comp->GetState()->GetObjectFromStack<GameObject>("sge.gameObject");
		GameObject* cam = comp->GetState()->GetObjectFromStack<GameObject>("sge.gameObject");
		//glm::vec3 campos = glm::vec3(0,1.7,0);
		//glm::vec3 playpos = glm::vec3(0, 0.961987, -5);
		//glm::vec2 mpos = glm::vec2(639, 511);
		std::vector<double> vals = comp->GetState()->GetNumbersFromStack();
		//std::cout << "Cam: " << vals[0] << ", " << vals[1] << ", " << obj->GetPosition().z << std::endl;

		float x = (2.0f * vals[1]) / sge::Game::GetInstance().getSize().x - 1.0f;
		float y = 1.0f - (2.0f * vals[0]) / sge::Game::GetInstance().getSize().y;

		glm::vec4 pos = vec4(x, y, -1, 1);
		
		glm::vec4 p = inverse(CameraComponent::GetMain()->GetProjection()) * pos;
		glm::vec4 p2 = glm::vec4(p.x, p.y, -1.0f, 0.0f);

		//std::cout << "P: " << p.x << ", " << p.y << ", " << p.z << ", " << p.w << ", " << std::endl;
		//std::cout << "P: " << p2.x << ", " << p2.y << ", " << p2.z << ", " << p2.w << ", " << std::endl;
		glm::vec3 v = (glm::vec3)(inverse(CameraComponent::GetMain()->GetView()) * p2);

		glm::vec3 vn = glm::normalize(v);
		//

		std::cout << "P: " << p.x << ", " << p.y << ", " << p.z << ", " << p.w << ", " << std::endl;
		//std::cout << "V: " << vn.x << ", " << vn.y << ", " << vn.z << std::endl;
		
		glm::vec3 start = obj->GetPosition() + cam->GetPosition();

		float dot = glm::dot(v, cam->forward());

		RaycastHit hit = Physics::Raycast(start, vn, 400);
		std::cout << "Casting Ray from: " << start.x << ", " << start.y << ", " << start.z << " | in dir: " << vn.x << ", " << vn.y << ", " << vn.z << std::endl;
		if (!hit.hit) {
			std::cout << "no hit" << std::endl;
			return 0;
		}
		
		LuaComponent* other = hit.collider->GetParent()->GetComponent<LuaComponent>();
		if (other != NULL)
			std::cout << "hit!" << std::endl;
				other->CallFunctionWithGameObject("onraycasthit", cam);
		return 0;
	}

	int LuaComponent::exitGame(lua_State* state)
	{
		Game::GetInstance().CloseGame();
		return 0;
	}
}