#include "components/Collider.h"
#include <iostream>

namespace sge {

	std::list<Collider*> Collider::_allColliders;
	Collider::Collider() : ObjectBehaviour()
	{
		Collider::_allColliders.push_back(this);
	}


	Collider::~Collider()
	{
		Collider::_allColliders.remove(this);
	}
	void Collider::Start()
	{
	}
	void Collider::Update()
	{
	}
	void Collider::FixedUpdate()
	{
	}
	void Collider::OnRender()
	{
	}
	void Collider::CollideWithAll()
	{
		size_t cols = _allColliders.size();
		//std::cout << cols << std::endl;
		for (std::list<Collider*>::iterator itr = _allColliders.begin(), end = _allColliders.end();itr != end; itr++) {
			//std::list<Collider*>::iterator toCol = itr; //Wanted a nested for loop but this saves one unnecessary check of the collider checking itself
			//toCol++;
			//while (toCol != end) {
			if((*itr) != this)
				Collide((*itr));
			//	toCol++;
			//}
		}
	}
	void Collider::OnCollision(Collider* other)
	{
	}
	void Collider::OnTrigger(Collider * other)
	{
	}
	void Collider::SetTrigger(bool trigger)
	{
		isTrigger = trigger;
	}
	bool Collider::IsTrigger()
	{
		return isTrigger;
	}
}