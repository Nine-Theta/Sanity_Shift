#pragma once
#include <vector>
#include <GL/glew.h>
#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>


#include "AL/al.h"
#include "AL/alc.h"
#include "AL/alext.h"
#include "AL/alut.h"
#include "common/alhelpers.h"

class World;
namespace sge {
	/**
	 * Represents an OpenAL buffered audio stream
	 */
	class Sound
	{
	public:


		ALuint GetBuffer();

		Sound(std::string pFilename);
		virtual ~Sound();

	protected:

		void soundTest();
		ALuint buffer;
	};
}
