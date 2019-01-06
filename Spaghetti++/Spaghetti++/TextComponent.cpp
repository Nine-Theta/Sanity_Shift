#include "TextComponent.h"
#include "Game.h"

namespace sge {

	TextComponent::TextComponent()
	{
		text.setFont(font);
		text.setCharacterSize(24);
		text.setFillColor(sf::Color::White);
		text.setString("Unassigned text");
	}


	TextComponent::~TextComponent()
	{
	}

	void sge::TextComponent::Start()
	{
	}

	void sge::TextComponent::OnDestroy()
	{
	}

	void sge::TextComponent::Update()
	{
	}

	void sge::TextComponent::FixedUpdate()
	{
	}

	void sge::TextComponent::OnRender()
	{
		sf::RenderStates state = sf::RenderStates::Default;
		state.transform = p_gameObj->GetCombinedTransform();
		//std::cout << "Rendering text " << std::endl;
		sge::Game::GetInstance().draw(text, state);
	}

	void sge::TextComponent::OnCollision(Collider * other)
	{
	}

	void sge::TextComponent::OnTrigger(Collider * other)
	{
	}
	void TextComponent::SetText(std::string newText)
	{
		text.setString(newText);
	}
	std::string TextComponent::GetText()
	{
		return std::string();
	}
	void TextComponent::SetSize(int size)
	{
		text.setCharacterSize(size);
	}
	sf::Font sge::TextComponent::font;
	void TextComponent::LoadFont(std::string fontName)
	{
		if (!font.loadFromFile(fontName))
			std::cout << "Error loading font file" << std::endl;
	}
}