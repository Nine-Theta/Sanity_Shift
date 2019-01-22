#pragma once
#include "ObjectBehaviour.h"
#include "LuaState.h"
#include <map>

namespace sge {
	class LuaComponent :
		public ObjectBehaviour
	{
	public:
		LuaComponent(std::string file);
		~LuaComponent();

		// Geerbt über ObjectBehaviour
		virtual void Start() override;
		virtual void OnDestroy() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void OnRender() override;
		virtual void OnCollision(Collider * other) override;
		virtual void OnTrigger(Collider * other) override;

		LuaState* GetState();
	protected:
		LuaState _state;

		static int test(lua_State* state);
		static int getLParent(lua_State* state);
		static int setParent(lua_State* state);
		static int addComponent(lua_State* state);
		static int removeComponent(lua_State* state);
		static int gDelete(lua_State* state);
		static int getName(lua_State* state);
		static int setName(lua_State* state);
		static int getPos(lua_State* state);
		static int setPos(lua_State* state);
		static int getWorldPos(lua_State* state);
		static int getTime(lua_State* state);
		static int deltaTime(lua_State* state);
		static int fixedDelta(lua_State* state);

		static int newObject(lua_State* state);
		static int findObject(lua_State* state);

		static const struct luaL_Reg gameObjectMetaLib[];
		static const struct luaL_Reg timeLib[];
		static const struct luaL_Reg gameObjectLib[];

		static std::map <lua_State*, LuaComponent*> _components;
	};
}