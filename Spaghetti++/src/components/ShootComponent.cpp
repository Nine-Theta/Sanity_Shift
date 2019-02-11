#include "ShootComponent.h"
#include "GameObject.h"
#include "SpriteComponent.h"
#include "CircleCollider.h"
#include "SelfDestructComp.h"
#include "SoundManager.h"

namespace sge {

	ShootComponent::ShootComponent()
	{
	}


	ShootComponent::~ShootComponent()
	{
	}

	void sge::ShootComponent::Start()
	{
	}

	void sge::ShootComponent::OnDestroy()
	{
	}

	void sge::ShootComponent::Update()
	{
	}

	void sge::ShootComponent::FixedUpdate()
	{//TODO: separate input class to manage key down and key up
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !lastShot) {
			shoot();
			SoundManager::PlaySound("LaserBlaster.wav");
		}
		lastShot = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
	}

	void sge::ShootComponent::OnRender()
	{
	}

	void sge::ShootComponent::OnCollision(Collider * other)
	{
	}

	void sge::ShootComponent::OnTrigger(Collider * other)
	{
	}

	void sge::ShootComponent::shoot()
	{
		//std::cout << "Fired a shot" << std::endl;
		GameObject* bullet = new GameObject();
		bullet->AddComponent(new SpriteComponent("glow.png"));
		bullet->setPosition(p_gameObj->GetCombinedPosition());
		bullet->setScale(0.3f,0.3f);
		Rigidbody2D* rbody = new Rigidbody2D();
		glm::vec2 velocity(1000, 0);
		velocity = vec2(cos(radians(p_gameObj->getRotation())), sin(radians(p_gameObj->getRotation()))) * 1000.f;//p_gameObj->getRotation());
		velocity += rbody->GetVelocity();
		rbody->SetVelocity(velocity.x,velocity.y);
		CircleCollider* col = new CircleCollider(10);
		col->SetTrigger(true);
		bullet->AddComponent(col);
		bullet->AddComponent(rbody);
		bullet->AddComponent(new SelfDestructComp(4));
		bullet->SetName("Bullet");
	}
}