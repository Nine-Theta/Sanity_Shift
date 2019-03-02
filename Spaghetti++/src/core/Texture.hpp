#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <map>
#include <string>
#include <GL/glew.h>
#include "glm/glm.hpp"

class Texture
{
	public:
		static Texture* load(const std::string& pTexturePath);

		GLuint getId();

		glm::vec2 GetSize();
		void SetSize(glm::vec2 size);
	protected:
	    Texture();
		virtual ~Texture();
		static Texture* loadDDS(const std::string& pFilename);
		static Texture* loadPNG(const std::string& pTexturePath);

        static Texture* _loadFromFile(const std::string pTexturePath);

	    //OpenGL id for texture buffer
		GLuint _id;

		glm::vec2 _size;
};

#endif // TEXTURE_HPP
