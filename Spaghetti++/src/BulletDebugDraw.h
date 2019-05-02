#pragma once
#include <map>
#include <iostream>
#include <string>
#include "bullet/btBulletDynamicsCommon.h"
	class BulletDebugDraw : public btIDebugDraw
	{
	public:
		BulletDebugDraw();
		~BulletDebugDraw();
	};