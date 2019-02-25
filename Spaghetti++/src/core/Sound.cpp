#include <iostream>
#include <map>
#include <string>
#include <fstream>

#include "core/Sound.hpp"
namespace sge {
	Sound::Sound(std::string pFilename)
	{
		char *args[] = {
			(char*)"-hrtf",
			(char*)"48000.mhr",
			NULL
		};
		int length = 2;
		char** argv = args;
		InitAL(&argv, &length);
		if (!alutInitWithoutContext(0, NULL))
		{
			ALenum error = alutGetError();
			fprintf(stderr, "%s\n", alutGetErrorString(error));
			exit(EXIT_FAILURE);
		}
		buffer = alutCreateBufferFromFile(pFilename.c_str());
		if (buffer == AL_NONE)
		{
			ALenum error = alutGetError();
			fprintf(stderr, "Error loading file: '%s'\n",
				alutGetErrorString(error));
			alutExit();
			//exit(EXIT_FAILURE);
		}
		printf("Playing audio file as a test");
		soundTest();
	}

	Sound::~Sound()
	{
		//dtor
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


