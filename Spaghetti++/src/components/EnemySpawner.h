#pragma once
#include "ObjectBehaviour.h"
#include "GameObject.h"
#include "SpriteComponent.h"
#include "Time.h"
namespace sge {
	class EnemySpawner : public ObjectBehaviour
	{
	public:
		EnemySpawner();
		~EnemySpawner();

		// Geerbt über ObjectBehaviour
		virtual void Start() override;
		virtual void OnDestroy() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void OnRender() override;
		virtual void OnCollision(Collider * other) override;
		virtual void OnTrigger(Collider * other) override;
	private:
		float timeUntilSpawn = 0;
		void spawnNewEnemy();
	};

}