#include "ScoreComponent.h"


namespace sge {
	ScoreComponent::ScoreComponent()
	{
	}


	ScoreComponent::~ScoreComponent()
	{
	}

	void sge::ScoreComponent::Start()
	{
		txt = (TextComponent*)p_gameObj->GetComponent(typeid(TextComponent));
	}

	void sge::ScoreComponent::OnDestroy()
	{
	}

	void sge::ScoreComponent::Update()
	{
	}

	void sge::ScoreComponent::FixedUpdate()
	{
		if (txt == NULL) return;
		std::string newTxt = "Score: ";
		newTxt.append(std::to_string(score));
		txt->SetText(newTxt);
	}

	void sge::ScoreComponent::OnRender()
	{
	}

	void sge::ScoreComponent::OnCollision(Collider * other)
	{
	}

	void sge::ScoreComponent::OnTrigger(Collider * other)
	{
	}

	void sge::ScoreComponent::AddScore(int points)
	{
		score += points;
	}
	int ScoreComponent::GetScore()
	{
		return score;
	}
}