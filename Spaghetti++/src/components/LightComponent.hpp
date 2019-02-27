#pragma once
#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "glm/glm.hpp"
#include "ObjectBehaviour.h"
#include "core/GLLight.hpp"
#include "SFML/Graphics/Color.hpp"
#include "GameObject.h"
#include "CameraComponent.h"
#include "GL/glew.h"

/**
 * Exercise for the student: implement the Light class...
 * Imagine things like setLightType, setLightIntensity, setFalloffAngle etc, see the corresponding lectures
 */

enum Lighttype {
	DIRECTIONAL,
	POINT
};
namespace sge {
	using namespace glm;
	class LightComponent : public ObjectBehaviour
	{
	public:
		LightComponent(sf::Color color = sf::Color::White, float intensity = 1, float ambient = 0);
		virtual ~LightComponent();

		//override set parent to register/deregister light...
		//virtual void _setWorldRecursively(World* pWorld) override;
		static void GenLightUBO();
		static void RegisterLight(LightComponent* light);
		static void UnregisterLight(LightComponent* light);
		static GLLight* GetLights();
		static void UpdateLights();
		static GLuint GetLightUBO();
		static uint GetLightCount();

		void SetColor(sf::Color col);
		void SetSpotlightAngle(float sharpAngle, float maxAngle);
		void SetType(Lighttype type);
		void SetAmbient(float ambient);
		void SetFalloff(float minAngle, float maxAngle);
		void spotTest() {
			GLLight light = getGLStruct();
			glm::vec3 dir = glm::normalize(glm::vec3(light.pos.x, light.pos.y, light.pos.z) + glm::vec3(0, 0, 0.5f) - (glm::vec3(light.pos.x, light.pos.y, light.pos.z)));
			float proj = glm::dot(dir, glm::normalize(glm::vec3(light.dir.x, light.dir.y, light.dir.z)));
			float falloff = inverseLerp(proj, -1, -1);
			std::cout << "Projection: " << std::to_string(proj) << " - Falloff: " << std::to_string(falloff) << std::endl;
		}

		float inverseLerp(float value, float start, float end) {
			float top = abs(end - start);
			float dif = top - abs(end);
			float val = value + dif;
			return val / top;
		}

		GLLight getGLStruct();

	private:
		static std::vector<LightComponent*> _lights;
		static GLLight _glLights[16];
		static GLuint uboLightID;
		sf::Color _color;
		float _intensity;
		float _ambientContrib;
		Lighttype _type;
		float _falloffStart = -0.999999999999f;
		float _falloffMax = -1;

		static unsigned int _lightsCount;

		void SetEnabled(bool pActive) override;
		// Geerbt über ObjectBehaviour
		virtual void Start() override;
		virtual void OnDestroy() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void OnRender() override;
		virtual void OnCollision(Collider * other) override;
		virtual void OnTrigger(Collider * other) override;
	};
}
#endif // LIGHT_HPP
