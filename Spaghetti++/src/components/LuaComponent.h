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
		static int playAudio(lua_State* state);
		static int bufferAudio(lua_State* state);
		static int streamAudio(lua_State* state);
		static int stopStream(lua_State* state);
		static int getLParent(lua_State* state);
		static int setParent(lua_State* state);
		static int setActive(lua_State* state);
		static int sendMessage(lua_State* state);
		static int setText(lua_State* state);
		static int addComponent(lua_State* state);
		static int removeComponent(lua_State* state);
		static int gDelete(lua_State* state);
		static int gDeleteAll(lua_State* state);
		static int getName(lua_State* state);
		static int setName(lua_State* state);
		static int getPos(lua_State* state);
		static int forward(lua_State* state);
		static int up(lua_State* state);
		static int right(lua_State* state);
		static int setPos(lua_State* state);
		static int addForce(lua_State* state);
		static int rotate(lua_State* state);
		static int setWorldRotation(lua_State* state);
		static int setRotation(lua_State* state);
		static int setRotationQ(lua_State* state);
		static int getWorldPos(lua_State* state);
		static int setWorldPos(lua_State* state);

		static int getTime(lua_State* state);
		static int deltaTime(lua_State* state);
		static int fixedDelta(lua_State* state);
		static int setTimeScale(lua_State* state);
		static int getTimeScale(lua_State* state);

		static int newObject(lua_State* state);
		static int findObject(lua_State* state);
		static int deleteAll(lua_State* state);

		static int isKeyPressed(lua_State* state);
		static int isKeyDown(lua_State* state);
		static int isKeyUp(lua_State* state);
		static int isAnyKeyPressed(lua_State* state);
		static int isAnyKeyDown(lua_State* state);
		static int isAnyKeyUp(lua_State* state);

		static int isButtonPressed(lua_State* state);
		static int isButtonDown(lua_State* state);
		static int isButtonUp(lua_State* state);
		static int getMousePos(lua_State* state);
		static int getMouseRelativePos(lua_State* state);
		static int getMouseDelta(lua_State* state);
		static int didMouseMove(lua_State* state);
		static int setMouseLock(lua_State* state);
		static int toggleMouseLock(lua_State* state);

		//static const type_info& ParseComponentType(std::string type);

		static const struct luaL_Reg gameObjectMetaLib[];
		static const struct luaL_Reg timeLib[];
		static const struct luaL_Reg audioLib[];
		static const struct luaL_Reg gameObjectLib[];
		static const struct luaL_Reg keysMetaLib[];
		static const struct luaL_Reg mouseLib[];

		static std::map <lua_State*, LuaComponent*> _components;

		void registerKeys();

		static constexpr unsigned int hash(const char* str, int h = 0)
		{
			return !str[h] ? 5381 : (hash(str, h + 1) * 33) ^ str[h];
		}

		inline
		static unsigned int hash(const std::string& str)
		{
			return hash(str.c_str());
		}
	};
}