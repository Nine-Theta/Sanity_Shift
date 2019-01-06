#pragma once
#include "ObjectBehaviour.h"
#include <list>
#include "SFML/Graphics.hpp"
namespace sge {
	class CameraComponent : public ObjectBehaviour
	{
	private:
		static std::list<CameraComponent*> cameras;
		float nearPlane = 1;
		float farPlane = 1000;
		bool ortho = true;
		float width = 1280;
		float height = 1024;
		float fov = 60;
		float scale = 1;
		sf::FloatRect viewPort;
		sf::View view;
	public:
		void OnDestroy();
		void OnRender();
		void Start();
		void UpdateCamera();
		CameraComponent();
		~CameraComponent();

		static std::list<CameraComponent*> GetCameras();

		// Geerbt über ObjectBehaviour
		void Update();
		void FixedUpdate();

		// Geerbt über ObjectBehaviour
		virtual void OnCollision(Collider* other) override;

		// Geerbt über ObjectBehaviour
		virtual void OnTrigger(Collider * other) override;
	};
}
