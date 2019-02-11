#include "DebugComponent.h"
#include "GameObject.h"
#include "Game.h"
#include "TextComponent.h"

namespace sge {

	DebugComponent::DebugComponent()
	{
	}


	DebugComponent::~DebugComponent()
	{
	}

	void sge::DebugComponent::Start()
	{
		txt = (TextComponent*) p_gameObj->GetComponent(typeid(TextComponent));
		//txt = p_gameObj->GetComponent<TextComponent>();
	}

	void sge::DebugComponent::OnDestroy()
	{
	}

	void sge::DebugComponent::Update()
	{
	}

	void sge::DebugComponent::FixedUpdate()
	{
		if (txt != NULL) {
			//Should be in update but too little time to fix, works anyway
			std::string newText = "FPS: ";
			newText += std::to_string(TimeH::GetFramerate());
			newText.append("\nObjects Alive: ");
			newText += std::to_string((Game::GetInstance().GetObjectCount()));
			txt->SetText(newText);
		}
	}

	void sge::DebugComponent::OnRender()
	{
	}

	void sge::DebugComponent::OnCollision(Collider * other)
	{
	}

	void sge::DebugComponent::OnTrigger(Collider * other)
	{
	}
}