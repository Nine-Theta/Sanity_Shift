#pragma once
#include "ObjectBehaviour.h"
#include "SFML/Graphics.hpp"
#include "core/Mesh.hpp"
#include "materials/AbstractMaterial.hpp"
namespace sge {
	class SoundComponent : public ObjectBehaviour
	{
	public:
		Sound* GetSound();
		void SetSound(std::string path);
		bool IsPlaying();
		void Play();
		void Stop(float seconds = 0.1f);
		void SetVolume(float volume);
		void SetRolloffFactor(float factor);
		bool IsDirect();
		SoundComponent(std::string filepath);
		~SoundComponent();
	private:
		Sound* _snd;
		ALuint source;
		static ALuint effect;// = UINT32_MAX;
		static ALuint effectSlot;
		static ALuint filter;
		vec3 lastPos;
		float volumeGain = 1;
		float volume = 1;
		float maxVolume = 1;
		float rolloffFactor = 1;

		static float filterCount;

		virtual void loadEffects();

		// Geerbt über ObjectBehaviour
		virtual void Start() override;
		virtual void OnDestroy() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void OnRender() override;

		// Geerbt über ObjectBehaviour
		virtual void OnCollision(Collider* other) override;

		// Geerbt über ObjectBehaviour
		virtual void OnTrigger(Collider * other) override;
	};
}
