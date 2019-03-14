#pragma once
#include "MeshComponent.h"
#include "core/AssetLoader.h"
#include "Game.h"
#include <assert.h>
#include "SoundComponent.h"
#include "AL/efx-creative.h"
#include "AL/al.h"
#include "AL/alc.h"
#include "AL/alext.h"
#include "AL/efx.h"
#include "common/alhelpers.h"
#include "AL/efx-presets.h"

/* Effect object functions */
static LPALGENEFFECTS alGenEffects;
static LPALDELETEEFFECTS alDeleteEffects;
static LPALISEFFECT alIsEffect;
static LPALEFFECTI alEffecti;
static LPALEFFECTIV alEffectiv;
static LPALEFFECTF alEffectf;
static LPALEFFECTFV alEffectfv;
static LPALGETEFFECTI alGetEffecti;
static LPALGETEFFECTIV alGetEffectiv;
static LPALGETEFFECTF alGetEffectf;
static LPALGETEFFECTFV alGetEffectfv;
/* Auxiliary Effect Slot object functions */
static LPALGENAUXILIARYEFFECTSLOTS alGenAuxiliaryEffectSlots;
static LPALDELETEAUXILIARYEFFECTSLOTS alDeleteAuxiliaryEffectSlots;
static LPALISAUXILIARYEFFECTSLOT alIsAuxiliaryEffectSlot;
static LPALAUXILIARYEFFECTSLOTI alAuxiliaryEffectSloti;
static LPALAUXILIARYEFFECTSLOTIV alAuxiliaryEffectSlotiv;
static LPALAUXILIARYEFFECTSLOTF alAuxiliaryEffectSlotf;
static LPALAUXILIARYEFFECTSLOTFV alAuxiliaryEffectSlotfv;
static LPALGETAUXILIARYEFFECTSLOTI alGetAuxiliaryEffectSloti;
static LPALGETAUXILIARYEFFECTSLOTIV alGetAuxiliaryEffectSlotiv;
static LPALGETAUXILIARYEFFECTSLOTF alGetAuxiliaryEffectSlotf;
static LPALGETAUXILIARYEFFECTSLOTFV alGetAuxiliaryEffectSlotfv;
//filteres
static LPALGENFILTERS alGenFilters;
static LPALDELETEFILTERS alDeleteFilters;
static LPALISFILTER alIsFilter;
static LPALFILTERI alFilteri;
static LPALFILTERIV alFilteriv;
static LPALFILTERF alFilterf;
static LPALFILTERFV alFilterfv;
static LPALGETFILTERI alGetFilteri;
static LPALGETFILTERIV alGetFilteriv;
static LPALGETFILTERF alGetFilterf;
static LPALGETFILTERFV alGetFilterfv;


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
		loadEffects();
		//_mesh.setOrigin(_mesh.getTexture()->getSize().x * 0.5f, _mesh.getTexture()->getSize().y * 0.5f);
		//_sprite.setOrigin(0.5f, 0.5f);
	}


	Sound * SoundComponent::GetSound()
	{
		return _snd;
	}

	void SoundComponent::SetSound(std::string path)
	{
		assert(_snd != NULL);
		_snd = AssetLoader::GetSound(path);
		alSourcei(source, AL_BUFFER, _snd->GetBuffer());
	}

	SoundComponent::~SoundComponent()
	{
		alDeleteSources(1, &source);
		alDeleteEffects(1, &effect);
		alDeleteAuxiliaryEffectSlots(1, &effectSlot);
		alDeleteFilters(1, &filter);
	}

	void SoundComponent::loadEffects()
	{
#define LOAD_PROC(x,y)  ((x) = (y)alGetProcAddress(#x))
		LOAD_PROC(alGenEffects,LPALGENEFFECTS);
		LOAD_PROC(alDeleteEffects,LPALDELETEEFFECTS);
		LOAD_PROC(alIsEffect,LPALISEFFECT);
		LOAD_PROC(alEffecti,LPALEFFECTI);
		LOAD_PROC(alEffectiv,LPALEFFECTIV);
		LOAD_PROC(alEffectf,LPALEFFECTF);
		LOAD_PROC(alEffectfv,LPALEFFECTFV);
		LOAD_PROC(alGetEffecti,LPALGETEFFECTI);
		LOAD_PROC(alGetEffectiv,LPALGETEFFECTIV);
		LOAD_PROC(alGetEffectf,LPALGETEFFECTF);
		LOAD_PROC(alGetEffectfv,LPALGETEFFECTFV);
		LOAD_PROC(alGenAuxiliaryEffectSlots,LPALGENAUXILIARYEFFECTSLOTS);
		LOAD_PROC(alDeleteAuxiliaryEffectSlots,LPALDELETEAUXILIARYEFFECTSLOTS);
		LOAD_PROC(alIsAuxiliaryEffectSlot,LPALISAUXILIARYEFFECTSLOT);
		LOAD_PROC(alAuxiliaryEffectSloti,LPALAUXILIARYEFFECTSLOTI);
		LOAD_PROC(alAuxiliaryEffectSlotiv,LPALAUXILIARYEFFECTSLOTIV);
		LOAD_PROC(alAuxiliaryEffectSlotf,LPALAUXILIARYEFFECTSLOTF);
		LOAD_PROC(alAuxiliaryEffectSlotfv,LPALAUXILIARYEFFECTSLOTFV);
		LOAD_PROC(alGetAuxiliaryEffectSloti,LPALGETAUXILIARYEFFECTSLOTI);
		LOAD_PROC(alGetAuxiliaryEffectSlotiv,LPALGETAUXILIARYEFFECTSLOTIV);
		LOAD_PROC(alGetAuxiliaryEffectSlotf,LPALGETAUXILIARYEFFECTSLOTF);
		LOAD_PROC(alGetAuxiliaryEffectSlotfv,LPALGETAUXILIARYEFFECTSLOTFV);

		//Filters
		LOAD_PROC(alGenFilters, LPALGENFILTERS);
		LOAD_PROC(alDeleteFilters, LPALDELETEFILTERS);
		LOAD_PROC(alIsFilter, LPALISFILTER);
		LOAD_PROC(alFilteri, LPALFILTERI);
		LOAD_PROC(alFilteriv, LPALFILTERIV);
		LOAD_PROC(alFilterf, LPALFILTERF);
		LOAD_PROC(alFilterfv, LPALFILTERFV);
		LOAD_PROC(alGetFilteri, LPALGETFILTERI);
		LOAD_PROC(alGetFilteriv, LPALGETFILTERIV);
		LOAD_PROC(alGetFilterf, LPALGETFILTERF);
		LOAD_PROC(alGetFilterfv, LPALGETFILTERFV);
#undef LOAD_PROC


		alGenEffects(1, &effect);
		alGenAuxiliaryEffectSlots(1, &effectSlot);
		alEffecti(effect, AL_EFFECT_TYPE, AL_EFFECT_EAXREVERB);
		alAuxiliaryEffectSloti(effectSlot, AL_EFFECTSLOT_EFFECT, effect);
		alAuxiliaryEffectSloti(effectSlot, AL_EFFECTSLOT_AUXILIARY_SEND_AUTO, AL_TRUE);
		assert(alGetError() == AL_NO_ERROR && "Failed to set effect slot");

		EFXEAXREVERBPROPERTIES reverba = EFX_REVERB_PRESET_DRIVING_COMMENTATOR;
		EFXEAXREVERBPROPERTIES* reverb = &reverba;

		alEffectf(effect, AL_EAXREVERB_DENSITY, reverb->flDensity);
		alEffectf(effect, AL_EAXREVERB_DIFFUSION, reverb->flDiffusion);
		alEffectf(effect, AL_EAXREVERB_GAIN, reverb->flGain);
		alEffectf(effect, AL_EAXREVERB_GAINHF, reverb->flGainHF);
		alEffectf(effect, AL_EAXREVERB_GAINLF, reverb->flGainLF);
		alEffectf(effect, AL_EAXREVERB_DECAY_TIME, reverb->flDecayTime);
		alEffectf(effect, AL_EAXREVERB_DECAY_HFRATIO, reverb->flDecayHFRatio);
		alEffectf(effect, AL_EAXREVERB_DECAY_LFRATIO, reverb->flDecayLFRatio);
		alEffectf(effect, AL_EAXREVERB_REFLECTIONS_GAIN, reverb->flReflectionsGain);
		alEffectf(effect, AL_EAXREVERB_REFLECTIONS_DELAY, reverb->flReflectionsDelay);
		alEffectfv(effect, AL_EAXREVERB_REFLECTIONS_PAN, reverb->flReflectionsPan);
		alEffectf(effect, AL_EAXREVERB_LATE_REVERB_GAIN, reverb->flLateReverbGain);
		alEffectf(effect, AL_EAXREVERB_LATE_REVERB_DELAY, reverb->flLateReverbDelay);
		alEffectfv(effect, AL_EAXREVERB_LATE_REVERB_PAN, reverb->flLateReverbPan);
		alEffectf(effect, AL_EAXREVERB_ECHO_TIME, reverb->flEchoTime);
		alEffectf(effect, AL_EAXREVERB_ECHO_DEPTH, reverb->flEchoDepth);
		alEffectf(effect, AL_EAXREVERB_MODULATION_TIME, reverb->flModulationTime);
		alEffectf(effect, AL_EAXREVERB_MODULATION_DEPTH, reverb->flModulationDepth);
		alEffectf(effect, AL_EAXREVERB_AIR_ABSORPTION_GAINHF, reverb->flAirAbsorptionGainHF);
		alEffectf(effect, AL_EAXREVERB_HFREFERENCE, reverb->flHFReference);
		alEffectf(effect, AL_EAXREVERB_LFREFERENCE, reverb->flLFReference);
		alEffectf(effect, AL_EAXREVERB_ROOM_ROLLOFF_FACTOR, reverb->flRoomRolloffFactor);
		alEffecti(effect, AL_EAXREVERB_DECAY_HFLIMIT, reverb->iDecayHFLimit);
		std::cout << reverb->flAirAbsorptionGainHF << std::endl;

		alGenFilters(1, &filter);
		alFilteri(filter, AL_FILTER_TYPE,AL_FILTER_LOWPASS);

		//alEffecti(effect, AL_EFFECT_TYPE, AL_EFFECT_DISTORTION);
		//alAuxiliaryEffectSloti(effectSlot, AL_EFFECTSLOT_EFFECT, effect);

		alSourcef(source, AL_AIR_ABSORPTION_FACTOR, 0.1f);
		alSource3i(source, AL_AUXILIARY_SEND_FILTER, effectSlot, 0, filter);
		assert(alGetError() == AL_NO_ERROR && "Failed to setup sound source");
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
		/*if (!IsPlaying()) {
			ALuint snd = _snd->GetBuffer();
			alSourcePlay(source);
		}*/
		volume = clamp(volume + (1 / volumeGain) * TimeH::FixedDelta(), 0.f, 1.f);
		vec3 pos = CameraComponent::GetMain()->GetView() * vec4(p_gameObj->GetCombinedPosition(),1);
		vec3 vpos = p_gameObj->GetCombinedPosition() - CameraComponent::GetMain()->GetParent()->GetCombinedPosition();
		vec3 diff = vpos - lastPos;
		lastPos = vpos;
		diff /= TimeH::FixedDelta();
		alSource3f(source, AL_POSITION, pos.x, pos.y, pos.z);
		alSource3f(source, AL_VELOCITY, diff.x,diff.y,diff.z);
		alSourcef(source, AL_GAIN, volume);

		if (!IsDirect()) {
			alFilterf(filter, AL_LOWPASS_GAIN, 0.7f);
			alFilterf(filter, AL_LOWPASS_GAINHF, 0.1f);
		}
		else {
			alFilterf(filter, AL_LOWPASS_GAIN, 1.f);
			alFilterf(filter, AL_LOWPASS_GAINHF, 1.f);
		}
		//std::cout << IsDirect() << std::endl;
		//alDopplerFactor(1);
		//alDopplerVelocity(343);
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

	void SoundComponent::Play()
	{
		ALuint snd = _snd->GetBuffer();
		alSourcePlay(source);
		volumeGain = 1;
		volume = 1;
		std::cout << "PLAYING AUDIO CLIP" << std::endl;
	}

	void SoundComponent::Stop(float seconds)
	{
		volumeGain = -seconds;
	}

	bool SoundComponent::IsDirect()
	{
		if (CameraComponent::GetMain() == NULL) return false;
		vec3 cam = CameraComponent::GetMain()->GetParent()->GetCombinedPosition();
		vec3 pos = GetParent()->GetCombinedPosition();
		RaycastHit hit = Physics::Raycast(pos + 1.5f * normalize(pos - cam), normalize(pos - cam), length(pos - cam) - 1.5f);
		//std::cout << length(hit.point - cam) << " HIT: " << hit.hit << std::endl;
		if (!hit.hit) return true;
		if (length(hit.point - cam) < 1.4f) return true;
		return false;
	}

}