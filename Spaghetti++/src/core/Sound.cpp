#include <iostream>
#include <map>
#include <string>
#include <fstream>

#include "core/Sound.hpp"
namespace sge {
	ALuint Sound::GetBuffer()
	{
		return buffer;
	}
	std::string ErrorCheck(ALenum error)
	{
		if (error == AL_INVALID_NAME)
		{
			return "Invalid name";
		}
		else if (error == AL_INVALID_ENUM)
		{
			return " Invalid enum ";
		}
		else if (error == AL_INVALID_VALUE)
		{
			return " Invalid value ";
		}
		else if (error == AL_INVALID_OPERATION)
		{
			return " Invalid operation ";
		}
		else if (error == AL_OUT_OF_MEMORY)
		{
			return " Out of memory like! ";
		}
		else if (error == AL_NONE)
		{
			return " NO ERROR! ";
		}

		return " Don't know ";


	}
	Sound::Sound(std::string pFilename)
	{
		ALenum alErr = alGetError();
		if (alErr)
		{
			fprintf(stderr, "AL Error detected: ");
			std::cout << ErrorCheck(alErr) << std::endl;
		}
		ALvoid* data = alutLoadMemoryFromFile(pFilename.c_str(), &format, &size, &frequency);//alutCreateBufferFromFile(pFilename.c_str());
		alGenBuffers(1, &buffer);
		alBufferData(buffer, format, data, size, frequency);
		ALenum error = alutGetError();
		alErr = alGetError();
		if (buffer == AL_NONE || error || alErr)
		{
			fprintf(stderr, "AL Error detected: ");
			std::cout << ErrorCheck(alErr) << std::endl;
			std::cerr << "Error loading file " << pFilename << ": " << alutGetErrorString(error) << std::endl;
			//fprintf(stderr, "Error loading file: '%s'\n",
			//	alutGetErrorString(error));
			//alutExit();
			//exit(EXIT_FAILURE);
		}
		else
			std::cout << "Successfully loaded sound file: " << pFilename << std::endl;
		assert(alGetError() == AL_NONE);
		//delete data;
		//soundTest();
	}

	Sound::~Sound()
	{
		//dtor
	}

	static void* alcGetStringiSOFT;
	static void* alcResetDeviceSOFT;


	Sound * Sound::load(std::string pFilename)
	{
		Sound* snd = new Sound(pFilename);
		//snd->buffer = alutCreateBufferFromFile(pFilename.c_str());
		ALenum error = alutGetError();
		ALenum alErr = alGetError();
		if (snd->buffer == AL_NONE || error || alErr)
		{
			fprintf(stderr, "AL Error detected: ");
			std::cout << alErr << std::endl;
			fprintf(stderr, "Error loading file: '%s'\n",
				alutGetErrorString(error));
			delete snd;
			return NULL;
			//exit(EXIT_FAILURE);
		}
		return snd;
	}

	void Sound::InitHRTF()
	{
		ALboolean has_angle_ext;
		ALuint source, buffer;
		const char *soundname;
		const char *hrtfname;
		ALCint hrtf_state;
		ALCint num_hrtf;
		char *args[] = {
			(char*)"-hrtf",
			(char*)"48000",
			NULL
		};
		int length = 2;
		char** argv = args;
		if (InitAL(&argv, &length)) {
			printf("Successfully initialised OpenAL\n");

		}
		ALCdevice *device;
		device = alcGetContextsDevice(alcGetCurrentContext());
		if (!alcIsExtensionPresent(device, "ALC_SOFT_HRTF"))
		{
			fprintf(stderr, "Error: ALC_SOFT_HRTF not supported\n");
			CloseAL();
		}
		else {
			printf("ARC_SOFT_HRTF supported!\n");
		}
		/* Check for the AL_EXT_STEREO_ANGLES extension to be able to also rotate
	 * stereo sources.
	 */
		has_angle_ext = alIsExtensionPresent("AL_EXT_STEREO_ANGLES");
		printf("AL_EXT_STEREO_ANGLES%s found\n", has_angle_ext ? "" : " not");

		/* Check for user-preferred HRTF */
		if (strcmp(argv[0], "-hrtf") == 0)
		{
			hrtfname = argv[1];
			soundname = argv[2];
		}
		else
		{
			hrtfname = NULL;
			soundname = argv[0];
		}
#define LOAD_PROC(d, x)  ((x) = alcGetProcAddress((d), #x))
		LOAD_PROC(device, alcGetStringiSOFT);
		LOAD_PROC(device, alcResetDeviceSOFT);
#undef LOAD_PROC
		/* Enumerate available HRTFs, and reset the device using one. */
		alcGetIntegerv(device, ALC_NUM_HRTF_SPECIFIERS_SOFT, 1, &num_hrtf);
		if (!num_hrtf)
			printf("No HRTFs found\n");
		else
		{
			ALCint attr[5];
			ALCint index = -1;
			ALCint i;

			printf("Available HRTFs:\n");
			for (i = 0; i < num_hrtf; i++)
			{
				const ALCchar *name = ((LPALCGETSTRINGISOFT)alcGetStringiSOFT)(device, ALC_HRTF_SPECIFIER_SOFT, i);
				printf("    %d: %s\n", i, name);

				/* Check if this is the HRTF the user requested. */
				if (hrtfname && strcmp(name, hrtfname) == 0)
					index = i;
			}

			i = 0;
			attr[i++] = ALC_HRTF_SOFT;
			attr[i++] = ALC_TRUE;
			if (index == -1)
			{
				if (hrtfname)
					printf("HRTF \"%s\" not found\n", hrtfname);
				printf("Using default HRTF...\n");
			}
			else
			{
				printf("Selecting HRTF %d...\n", index);
				attr[i++] = ALC_HRTF_ID_SOFT;
				attr[i++] = index;
			}
			attr[i] = 0;

			if (!((LPALCRESETDEVICESOFT)alcResetDeviceSOFT)(device, attr))
				printf("Failed to reset device: %s\n", alcGetString(device, alcGetError(device)));
		}

		/* Check if HRTF is enabled, and show which is being used. */
		alcGetIntegerv(device, ALC_HRTF_SOFT, 1, &hrtf_state);
		if (!hrtf_state)
			printf("HRTF not enabled!\n");
		else
		{
			const ALchar *name = alcGetString(device, ALC_HRTF_SPECIFIER_SOFT);
			printf("HRTF enabled, using %s\n", name);
		}

		if (!alutInitWithoutContext(0, NULL))
		{
			ALenum error = alutGetError();
			fprintf(stderr, "%s\n", alutGetErrorString(error));
			exit(EXIT_FAILURE);
		}
	}

	ALenum Sound::GetFormat()
	{
		return format;
	}

	ALfloat Sound::GetFrequency()
	{
		return frequency;
	}

	Sound::Sound() : buffer(0)
	{
	}

	void Sound::soundTest()
	{
		ALuint source;
		/* Generate a single source, attach the buffer to it and start playing. */
		alGenSources(1, &source);
		alSourcei(source, AL_BUFFER, buffer);
		alSourcePlay(source);

		/* Normally nothing should go wrong above, but one never knows... */
		ALenum error = alGetError();
		if (error != ALUT_ERROR_NO_ERROR)
		{
			fprintf(stderr, "%s\n", alGetString(error));
			alutExit();
			//exit(EXIT_FAILURE);
		}
	}

	
}


