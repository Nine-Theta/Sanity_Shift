#include <iostream>
#include <map>
#include <string>
#include <fstream>

#include "core/Sound.hpp"
namespace sge {
	Sound::Sound(std::string pFilename) : _indexBufferId(0), _vertexBufferId(0), _normalBufferId(0), _uvBufferId(0), _vertices(), _normals(), _uvs(), _indices()
	{
		if (!alutInit(0, NULL))
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
			exit(EXIT_FAILURE);
		}
	}

	/**
	 * Loads a sound into an OpenAL buffer and then throws it back out of memory again. Only stores the reference to the OpenAL buffer.
	 * 
	 *
	 * This class does not do caching. The asset loader will do that
	 */
	Sound* Sound::load(std::string pFilename)
	{
		std::cout << "Loading " << pFilename << "...";
		return NULL;
	}

	void Sound::_buffer()
	{
		glGenBuffers(1, &_indexBufferId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), &_indices[0], GL_STATIC_DRAW);

		glGenBuffers(1, &_vertexBufferId);
		glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferId);
		glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(glm::vec3), &_vertices[0], GL_STATIC_DRAW);

		glGenBuffers(1, &_normalBufferId);
		glBindBuffer(GL_ARRAY_BUFFER, _normalBufferId);
		glBufferData(GL_ARRAY_BUFFER, _normals.size() * sizeof(glm::vec3), &_normals[0], GL_STATIC_DRAW);

		glGenBuffers(1, &_uvBufferId);
		glBindBuffer(GL_ARRAY_BUFFER, _uvBufferId);
		glBufferData(GL_ARRAY_BUFFER, _uvs.size() * sizeof(glm::vec2), &_uvs[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Sound::streamToOpenGL(GLint pVerticesAttrib, GLint pNormalsAttrib, GLint pUVsAttrib) {
		if (pVerticesAttrib != -1) {
			glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferId);
			glEnableVertexAttribArray(pVerticesAttrib);
			glVertexAttribPointer(pVerticesAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
		}

		if (pNormalsAttrib != -1) {
			glBindBuffer(GL_ARRAY_BUFFER, _normalBufferId);
			glEnableVertexAttribArray(pNormalsAttrib);
			glVertexAttribPointer(pNormalsAttrib, 3, GL_FLOAT, GL_TRUE, 0, 0);
		}

		if (pUVsAttrib != -1) {
			glBindBuffer(GL_ARRAY_BUFFER, _uvBufferId);
			glEnableVertexAttribArray(pUVsAttrib);
			glVertexAttribPointer(pUVsAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferId);

		glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, (GLvoid*)0);

		// no current buffer, to avoid mishaps, very important for performance

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		//fix for serious performance issue
		if (pUVsAttrib != -1) glDisableVertexAttribArray(pUVsAttrib);
		if (pNormalsAttrib != -1) glDisableVertexAttribArray(pNormalsAttrib);
		if (pVerticesAttrib != -1) glDisableVertexAttribArray(pVerticesAttrib);
	}

	void Sound::drawDebugInfo(const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4&
	) {
		//demo of how to render some debug info using the good ol' direct rendering mode...
		glUseProgram(0);
		glMatrixMode(GL_PROJECTION);
		//  glLoadMatrixf(glm::value_ptr(pProjectionMatrix));
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(glm::value_ptr(pViewMatrix * pModelMatrix));

		glBegin(GL_LINES);
		//for each index draw the normal starting at the corresponding vertex
		for (size_t i = 0; i < _indices.size(); i++) {
			//draw normal for vertex
			if (true) {
				//now get normal end
				glm::vec3 normal = _normals[_indices[i]];
				glColor3fv(glm::value_ptr(normal));

				glm::vec3 normalStart = _vertices[_indices[i]];
				glVertex3fv(glm::value_ptr(normalStart));
				glm::vec3 normalEnd = normalStart + normal * 0.2f;
				glVertex3fv(glm::value_ptr(normalEnd));
			}

		}
		glEnd();
	}
	std::vector<unsigned int>& Sound::GetIndices()
	{
		return _indices;
	}
	std::vector<glm::vec3>& Sound::GetVertices()
	{
		return _vertices;
	}
}


