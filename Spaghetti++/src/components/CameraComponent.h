#pragma once
#include "ObjectBehaviour.h"
#include <list>
#include "SFML/Graphics.hpp"
namespace sge {
	class CameraComponent : public ObjectBehaviour
	{
	private:
		static std::list<CameraComponent*> cameras;
		static CameraComponent* main;
		float nearPlane = 1;
		float farPlane = 1000;
		bool ortho = true;
		float width = 1280;
		float height = 1024;
		float fov = 60;
		float scale = 1;
		mat4 projectionM;
		mat4 viewM;
		sf::FloatRect viewPort;
		sf::View view;
	public:
		void OnDestroy();
		void OnRender();
		void Start();
		void UpdateCamera();
		void SetProjection(float fov, float aspect, float near, float far);
		void SetProjection(float width, float height, float far);
		mat4 GetView();
		mat4 GetProjection();
		CameraComponent();
		~CameraComponent();

		static std::list<CameraComponent*> GetCameras();
		static CameraComponent* GetMain();

		// Geerbt �ber ObjectBehaviour
		void Update();
		void FixedUpdate();

		// Geerbt �ber ObjectBehaviour
		virtual void OnCollision(Collider* other) override;

		// Geerbt �ber ObjectBehaviour
		virtual void OnTrigger(Collider * other) override;
	};
}
