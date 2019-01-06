#include "StartComponent.h"
#include "CameraComponent.h"
#include "SpriteComponent.h"
#include "CircleCollider.h"
#include "HorizontalPlayerFollower.h"
#include "PlayerControls.h"
#include "TextComponent.h"
#include "ShootComponent.h"
#include "EnemySpawner.h"
#include "DebugComponent.h"
#include "ScoreComponent.h"
#include "SoundManager.h"

namespace sge {

	StartComponent::StartComponent()
	{
	}


	StartComponent::~StartComponent()
	{
	}

	void sge::StartComponent::Start()
	{
		TextComponent* txt = new TextComponent();
		txt->SetText("Press Spacebar to play!");
		txt->SetSize(50);
		p_gameObj->AddComponent(txt);
		p_gameObj->setPosition(sf::Vector2f(-300, 300));
	}

	void sge::StartComponent::OnDestroy()
	{
	}

	void sge::StartComponent::Update()
	{
	}

	void sge::StartComponent::FixedUpdate()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !triggered) {
			launch();
			triggered = true;
			//GameObject::Destroy(p_gameObj);
		}
	}

	void sge::StartComponent::OnRender()
	{
	}

	void sge::StartComponent::OnCollision(Collider * other)
	{
	}

	void sge::StartComponent::OnTrigger(Collider * other)
	{
	}
	void StartComponent::launch()
	{
		GameObject* bigScore = GameObject::Find("BigScore");
		if (bigScore != NULL)
			GameObject::Destroy(bigScore);

		SoundManager::PlayBGM("BongoBongo.wav");
		
		GameObject* rect = new GameObject();
		ObjectBehaviour* rcomp = new SpriteComponent("gecko.png");
		rect->AddComponent(rcomp);
		rect->SetName("Player");
		rect->AddComponent(new Rigidbody2D());
		rect->AddComponent(new PlayerControls());
		rect->AddComponent(new ShootComponent());
		CircleCollider* ccol = new CircleCollider(80.0f);
		rect->AddComponent(ccol);
		GameObject* subrect = new GameObject(rect);
		ccol->SetParent(rect);
		//subrect->AddComponent(new RectangleComponent(200,200));
		subrect->setPosition(450, 200);
		subrect->setRotation(74);
		GameObject* topLimit = new GameObject();
		topLimit->setPosition(rect->getPosition() + sf::Vector2f(0, 512));
		//topLimit->AddComponent(new RectangleComponent(50,50));
		topLimit->AddComponent(new CircleCollider(0));
		topLimit->AddComponent(new HorizontalPlayerFollower());
		GameObject* bottomLimit = new GameObject();
		bottomLimit->setPosition(rect->getPosition() + sf::Vector2f(0, -512));
		bottomLimit->AddComponent(new CircleCollider(0));
		bottomLimit->AddComponent(new HorizontalPlayerFollower());
		std::cout << rect->GetComponent(typeid(Rigidbody2D)) << std::endl;
		//subrect->setPosition(120, 80);
		subrect->SetParent(rect);
		GameObject* camera = GameObject::Find("Camera");
		camera->setPosition(250, 0);
		GameObject* spawner = new GameObject();
		spawner->AddComponent(new EnemySpawner());

		GameObject* score = new GameObject();
		score->SetName("Score");
		TextComponent* txt = new TextComponent();
		txt->SetText("Score: 0");
		score->AddComponent(txt);
		score->setPosition(-380, -500);
		score->AddComponent(new ScoreComponent());

		GameObject* debug = new GameObject();
		debug->setPosition(-380, -300);
		debug->SetName("Debug");
		debug->AddComponent(new TextComponent());
		debug->AddComponent(new DebugComponent());
	}
}