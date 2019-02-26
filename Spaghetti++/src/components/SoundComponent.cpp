#include "MeshComponent.h"
#include "core/AssetLoader.h"
#include "Game.h"
#include <assert.h>
#include "SoundComponent.h"

namespace sge {
	SoundComponent::SoundComponent(std::string path)
	{
		//Mesh* mesh = AssetLoader::GetMesh(path);
		//if(mesh == NULL)
			//_mesh = AssetLoader::GetMesh("ERROR.obj");
		_snd = AssetLoader::GetSound(path);//Mesh::load(Settings::GetSetting("meshDir") + path);
		//std::cout << _snd << std::endl;
		assert(_snd != NULL);
		alGenSources(1, &source);
		alSourcei(source, AL_BUFFER, _snd->GetBuffer());
		//_mesh.setOrigin(_mesh.getTexture()->getSize().x * 0.5f, _mesh.getTexture()->getSize().y * 0.5f);
		//_sprite.setOrigin(0.5f, 0.5f);
	}


	Sound * SoundComponent::GetSound()
	{
		return _snd;
	}

	SoundComponent::~SoundComponent()
	{
	}

	void sge::SoundComponent::Start()
	{
	}

	void sge::SoundComponent::OnDestroy()
	{
	}

	void sge::SoundComponent::Update()
	{
	}

	void sge::SoundComponent::FixedUpdate()
	{
		if (!IsPlaying()) {
			ALuint snd = _snd->GetBuffer();
			alSourcePlay(source);
		}
		vec3 pos = CameraComponent::GetMain()->GetView() * vec4(p_gameObj->GetCombinedPosition(),1);
		alSource3f(source, AL_POSITION, pos.x, pos.y, pos.z);
	}

	void sge::SoundComponent::OnRender()
	{
	}

	void SoundComponent::OnCollision(Collider* other)
	{
	}

	void SoundComponent::OnTrigger(Collider * other)
	{
	}

	bool SoundComponent::IsPlaying()
	{
		ALenum state;

		alGetSourcei(source, AL_SOURCE_STATE, &state);

		return (state == AL_PLAYING);
	}

}