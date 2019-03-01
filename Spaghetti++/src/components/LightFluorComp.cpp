#include "MeshComponent.h"
#include "core/AssetLoader.h"
#include "Game.h"
#include <assert.h>
#include "LightFluorComp.h"

namespace sge {
	LightFlourComp::LightFlourComp()
	{

	}

	LightFlourComp::~LightFlourComp()
	{
	}

	void sge::LightFlourComp::Start()
	{
	}

	void sge::LightFlourComp::OnDestroy()
	{
	}

	void sge::LightFlourComp::Update()
	{
	}

	void sge::LightFlourComp::FixedUpdate()
	{
		//TODO: Add dot product light stuff
		glow = vec4(vec3(glow), 1);//vec4(vec3(glow), glow.w += )
	}

	void sge::LightFlourComp::OnRender()
	{
	}

	void LightFlourComp::OnCollision(Collider* other)
	{
	}

	void LightFlourComp::OnTrigger(Collider * other)
	{
	}
}