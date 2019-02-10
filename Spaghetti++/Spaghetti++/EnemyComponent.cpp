#include "EnemyComponent.h"
#include "vec2.hpp"
#include "ScoreComponent.h"
#include "Game.h"
#include "CameraComponent.h"
#include "StartComponent.h"
#include "SoundManager.h"

namespace sge {

	EnemyComponent::EnemyComponent()
	{
	}


	EnemyComponent::~EnemyComponent()
	{
	}

	void sge::EnemyComponent::Start()
	{
		wave = randf() < 0.3f;
	}

	void sge::EnemyComponent::OnDestroy()
	{
		std::cout << "Destroyed an enemy" << std::endl;
	}

	void sge::EnemyComponent::Update()
	{
	}

	void sge::EnemyComponent::FixedUpdate()
	{
		if(wave)
			p_gameObj->setPosition(p_gameObj->getPosition() + sf::Vector2f(0, sinf(Time::TimeRunning() * PI) * 5));
	}

	void sge::EnemyComponent::OnRender()
	{
	}

	void sge::EnemyComponent::OnCollision(Collider * other)
	{
	}

	void sge::EnemyComponent::OnTrigger(Collider * other)
	{
		if (other->GetParent()->GetName() == "Bullet" && p_gameObj->GetObjectState() < GOState::DESTROYED) {
			GameObject::Destroy(other->GetParent());
			GameObject::Destroy(p_gameObj);
			GameObject* score = GameObject::Find("Score");
			ScoreComponent* scorec = (ScoreComponent*)score->GetComponent(typeid(ScoreComponent));
			scorec->AddScore(15);
			SoundManager::PlaySound("PlayerDeathSound.wav");
		}
		else if (other->GetParent()->GetName() == "Player" && p_gameObj->GetObjectState() < GOState::DESTROYED) {
			std::cout << "Enemy collided with player! Restarting game" << std::endl;
			Game::GetInstance().DestroyAllObjects();
			SoundManager::PlaySound("PlayerDeathSound.wav");
			GameObject* finalScore = new GameObject();
			TextComponent* txt = new TextComponent();
			txt->SetSize(70);
			GameObject* score = GameObject::Find("Score");
			ScoreComponent* scorec = (ScoreComponent*)score->GetComponent(typeid(ScoreComponent));
			std::string scoret = "Score: ";
			scoret.append(std::to_string(scorec->GetScore()));
			txt->SetText(scoret);
			finalScore->AddComponent(txt);
			finalScore->setPosition(-350, 0);
			finalScore->SetName("BigScore");

			SoundManager::StopBGM();
			GameObject* obj = new GameObject();
			CameraComponent* ccam = new CameraComponent();
			obj->AddComponent(ccam);
			obj->SetName("Camera");
			GameObject* rect = new GameObject();
			rect->AddComponent(new StartComponent());
			rect->SetName("StartS");
		}
	}
}