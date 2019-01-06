#pragma once
#include "TextComponent.h"
#include "ObjectBehaviour.h"
#include "GameObject.h"
#include <assert.h>
namespace sge {
	class ScoreComponent :
		public ObjectBehaviour
	{
	public:
		ScoreComponent();
		~ScoreComponent();

		// Geerbt über ObjectBehaviour
		virtual void Start() override;
		virtual void OnDestroy() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void OnRender() override;
		virtual void OnCollision(Collider * other) override;
		virtual void OnTrigger(Collider * other) override;
		void AddScore(int points);
		int GetScore();
	private:
		TextComponent* txt;
		int score = 0;
	};
}
