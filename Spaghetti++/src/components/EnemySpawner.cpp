#include "components/EnemySpawner.h"
#include <iostream>
#include "SFML/System.hpp"
#include "components/SelfDestructComp.h"
#include "components/CircleCollider.h"
#include "components/EnemyComponent.h"

namespace sge {

	EnemySpawner::EnemySpawner()
	{
	}


	EnemySpawner::~EnemySpawner()
	{
	}

	void sge::EnemySpawner::Start()
	{
	}

	void sge::EnemySpawner::OnDestroy()
	{
	}

	void sge::EnemySpawner::Update()
	{
	}

	void sge::EnemySpawner::FixedUpdate()
	{
		//std::cout << timeUntilSpawn << std::endl;
		timeUntilSpawn -= sge::TimeH::FixedDelta();
		if (timeUntilSpawn < 0)
			spawnNewEnemy();
	}

	void sge::EnemySpawner::OnRender()
	{
	}

	void sge::EnemySpawner::OnCollision(Collider * other)
	{
	}

	void sge::EnemySpawner::OnTrigger(Collider * other)
	{
	}
	void EnemySpawner::spawnNewEnemy()
	{
		std::cout << "Spawning an enemy" << std::endl;
		timeUntilSpawn = randf() * 1.5f + 0.2f;
		GameObject* enemy = new GameObject();
		enemy->AddComponent(new SpriteComponent("enemy.png"));
		enemy->setPosition(p_gameObj->getPosition() + glm::vec2(1280, -312 + randf() * 624));
		Rigidbody2D* rbody = new Rigidbody2D();
		rbody->SetDrag(0);
		rbody->SetVelocity(randf() * -300 - 100, 0);
		enemy->AddComponent(rbody);
		enemy->AddComponent(new SelfDestructComp(8));
		enemy->SetName("Enemy");
		CircleCollider* col = new CircleCollider(40);
		col->SetTrigger(true);
		enemy->AddComponent(col);
		enemy->AddComponent(new EnemyComponent());
	}
}