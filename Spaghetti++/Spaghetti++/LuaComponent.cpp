#include "LuaComponent.h"
#include <string>
namespace sge {

	LuaComponent::LuaComponent(std::string file) : _state("components/" + file)
	{
	}

	LuaComponent::~LuaComponent()
	{
	}
	void LuaComponent::Start()
	{
		_state.CallFunction("start");
		std::cout << _state.CallFunction("returnTest", 3)[1] << std::endl;
	}
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
}