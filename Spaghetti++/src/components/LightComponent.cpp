#include "components/LightComponent.hpp"
namespace sge {
	unsigned int LightComponent::_lightsCount = 0;

	LightComponent::LightComponent(const std::string& pName, const glm::vec3& pPosition, sf::Color color, float intensity, float ambient)// :GameObject(pName, pPosition), _color(color), _intensity(intensity), _ambientContrib(ambient)
	{
		if (_lightsCount == 0) {
			SetType(Lighttype::DIRECTIONAL);
			SetAmbient(0.1f);
		}
		else
			SetType(Lighttype::POINT);
		_lightsCount++;
		SetSpotlightAngle(70, 80);
	}

	LightComponent::~LightComponent() {
		_lightsCount--;
	}

	//Override setWorldRecursively to make sure we are registered
	//to the world we are a part of.
	/*void LightComponent::_setWorldRecursively(World* pWorld) {

		//store the previous and new world before and after storing the given world
		World* previousWorld = _world;
		GameObject::_setWorldRecursively(pWorld);
		World* newWorld = _world;

		//check whether we need to register or unregister
		if (previousWorld != nullptr) previousWorld->unregisterLight(this);
		if (newWorld != nullptr) newWorld->registerLight(this);

	}*/

	void LightComponent::SetColor(sf::Color col)
	{
		_color = col;
	}

	void LightComponent::SetSpotlightAngle(float sharpAngle, float maxAngle)
	{
	}

	void LightComponent::SetType(Lighttype type)
	{
		_type = type;
	}

	void LightComponent::SetAmbient(float ambient)
	{
		_ambientContrib = ambient;
	}

	void LightComponent::SetFalloff(float minAngle, float maxAngle)
	{
		if (minAngle == maxAngle)
			maxAngle += 0.0000001f;
		_falloffStart = glm::cos(glm::radians(minAngle));
		_falloffMax = glm::cos(glm::radians(maxAngle));
	}


}