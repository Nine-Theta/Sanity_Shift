#include "SpriteComponent.h"
#include "SpriteLoader.h"
#include "Game.h"
#include <assert.h>

namespace sge {

	SpriteComponent::SpriteComponent(std::string path)
	{
		sf::Texture* tex = (sge::SpriteLoader::GetTexture(path));
		assert(tex != NULL);
		if(tex != NULL)
			_sprite = sf::Sprite(*tex);
		_sprite.setOrigin(_sprite.getTexture()->getSize().x * 0.5f, _sprite.getTexture()->getSize().y * 0.5f);
		//_sprite.setOrigin(0.5f, 0.5f);
	}


	SpriteComponent::~SpriteComponent()
	{
	}

	void sge::SpriteComponent::Start()
	{
	}

	void sge::SpriteComponent::OnDestroy()
	{
	}

	void sge::SpriteComponent::Update()
	{
	}

	void sge::SpriteComponent::FixedUpdate()
	{
	}

	void sge::SpriteComponent::OnRender()
	{
		sf::RenderStates state = sf::RenderStates::Default;
//		state.transform = p_gameObj->GetCombinedTransform();
//		sge::Game::GetInstance().draw(_sprite, state); //not setting transform. TODO: port to use GLM and GLSL instead of SFML
	}

	void SpriteComponent::OnCollision(Collider* other)
	{
	}

	void SpriteComponent::OnTrigger(Collider * other)
	{
	}

}