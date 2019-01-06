#include "SelfDestructComp.h"
#include "GameObject.h"

namespace sge {

	SelfDestructComp::SelfDestructComp(float sdTime)
	{
		time = sdTime;
	}


	SelfDestructComp::~SelfDestructComp()
	{
	}

	void sge::SelfDestructComp::Start()
	{
	}

	void sge::SelfDestructComp::OnDestroy()
	{
	}

	void sge::SelfDestructComp::Update()
	{
	}

	void sge::SelfDestructComp::FixedUpdate()
	{
		time -= Time::FixedDelta();
		//std::cout << time << std::endl;
		if (time < 0)
			GameObject::Destroy( p_gameObj);
	}

	void sge::SelfDestructComp::OnRender()
	{
	}

	void sge::SelfDestructComp::OnCollision(Collider * other)
	{
	}

	void sge::SelfDestructComp::OnTrigger(Collider * other)
	{
	}
}