#include "components/LightComponent.hpp"
namespace sge {
	unsigned int LightComponent::_lightsCount = 0;
	std::vector<LightComponent*> LightComponent::_lights;
	GLLight LightComponent::_glLights[16];
	GLuint LightComponent::uboLightID;

	LightComponent::LightComponent(sf::Color color, float intensity, float ambient):ObjectBehaviour(), _color(color), _intensity(intensity), _ambientContrib(ambient)
	{
		SetType(Lighttype::POINT);
		if (_lightsCount == 0) {
			//SetType(Lighttype::DIRECTIONAL);
			//SetAmbient(0.1f);
		}
		else
			SetType(Lighttype::POINT);
		_lightsCount++;
		SetSpotlightAngle(180, 180);
	}

	LightComponent::~LightComponent() {
		_lightsCount--;
		UnregisterLight(this);
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

	void LightComponent::GenLightUBO()
	{
		if (uboLightID > 0) return;
		glGenBuffers(1, &uboLightID);
		glBindBuffer(GL_UNIFORM_BUFFER, uboLightID);
		glBufferData(GL_UNIFORM_BUFFER, sizeof(_glLights), _glLights, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void LightComponent::RegisterLight(LightComponent * light)
	{
		std::cout << "Registering light " << light->GetParent()->GetName() << std::endl;
		_lights.push_back(light);
	}

	void LightComponent::UnregisterLight(LightComponent * light)
	{
		std::cout << "Unregistering light " << light->GetParent()->GetName() << std::endl;
		if (_lights.size() == 0) return;
		_lights.erase(std::remove(_lights.begin(), _lights.end(), light), _lights.end());
	}

	GLLight * LightComponent::GetLights()
	{
		return _glLights;
	}

	void LightComponent::UpdateLights()
	{
		for (unsigned int i = 0; i < _lightsCount; i++) {
			_glLights[i] = _lights.at(i)->getGLStruct();
		}
		if (_glLights == NULL) return;
		glBindBuffer(GL_UNIFORM_BUFFER, uboLightID);
		GLvoid* p = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);
		memcpy(p, _glLights, sizeof(_glLights));
		glUnmapBuffer(GL_UNIFORM_BUFFER);
	}

	GLuint LightComponent::GetLightUBO()
	{
		return uboLightID;
	}

	uint LightComponent::GetLightCount()
	{
		return _lightsCount;
	}

	void LightComponent::SetColor(sf::Color col)
	{
		_color = col;
	}

	void LightComponent::SetSpotlightAngle(float sharpAngle, float maxAngle)
	{
		SetFalloff(sharpAngle, maxAngle);
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

	GLLight LightComponent::getGLStruct()
	{
		GLLight light;
		light.type = _type;
		glm::vec3 pos = GetParent()->GetCombinedPosition();
		light.pos.x = pos.x;
		light.pos.y = pos.y;
		light.pos.z = pos.z;
		glm::mat4 view = CameraComponent::GetMain()->GetView();
		pos = view * glm::vec4(pos, 1);
		light.cpos.x = pos.x;
		light.cpos.y = pos.y;
		light.cpos.z = pos.z;
		glm::vec3 fwd = glm::normalize(GetParent()->forward());
		light.dir.x = fwd.x;
		light.dir.y = fwd.y;
		light.dir.z = fwd.z;
		light.color.x = _color.r * 0.0039215686274509803921568627451f;
		light.color.y = _color.g * 0.0039215686274509803921568627451f;
		light.color.z = _color.b * 0.0039215686274509803921568627451f;
		light.color.w = _intensity;
		light.minRad = _falloffStart;
		light.ambient = _ambientContrib;
		light.maxRad = _falloffMax;
		return light;
	}

	void LightComponent::Start()
	{
		RegisterLight(this);
		SetSpotlightAngle(129, 180);
	}

	void LightComponent::OnDestroy()
	{
	}

	void LightComponent::Update()
	{
	}

	void LightComponent::FixedUpdate()
	{
	}

	void LightComponent::OnRender()
	{
	}

	void LightComponent::OnCollision(Collider * other)
	{
	}

	void LightComponent::OnTrigger(Collider * other)
	{
	}


}