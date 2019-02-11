#pragma once
#include "ObjectBehaviour.h"
#include "SFML/Graphics.hpp"
#include "GameObject.h"
#include <iostream>
namespace sge {
	class TextComponent : public ObjectBehaviour
	{
	public:
		TextComponent();
		~TextComponent();

		// Geerbt über ObjectBehaviour
		virtual void Start() override;
		virtual void OnDestroy() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void OnRender() override;
		virtual void OnCollision(Collider * other) override;
		virtual void OnTrigger(Collider * other) override;
		void SetText(std::string text);
		std::string GetText();
		void SetSize(int size);
		static void LoadFont(std::string fontName);

	private:
		sf::Text text = sf::Text();
		static sf::Font font;
	};
}

