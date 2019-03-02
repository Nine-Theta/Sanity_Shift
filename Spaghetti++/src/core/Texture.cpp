#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include "core/Texture.hpp"
#include "core/nv_dds.h"

using namespace nv_dds;
Texture::Texture(): _id() {
    glGenTextures (1, &_id);
}

Texture::~Texture()
{
	glDeleteTextures(1, &_id);
}

GLuint Texture::getId() {
	return _id;
}

glm::vec2 Texture::GetSize()
{
	return _size;
}

void Texture::SetSize(glm::vec2 size)
{
	_size = size;
}

// importer for textures
Texture* Texture::load(const std::string& pFilename)
{
	if (strstr(pFilename.c_str(), ".dds")) {
		CDDSImage image;
		image.load(pFilename);
		Texture * texture = new Texture();
		glBindTexture(GL_TEXTURE_2D, texture->getId());

		glCompressedTexImage2DARB(GL_TEXTURE_2D, 0, image.get_format(),
		   image.get_width(), image.get_height(), 0, image.get_size(),
		   image);
		texture->SetSize(glm::vec2(image.get_width(), image.get_height()));
		for (int i = 0; i < image.get_num_mipmaps(); i++)
		{
			CSurface mipmap = image.get_mipmap(i);

			glCompressedTexImage2DARB(GL_TEXTURE_2D, i + 1, image.get_format(),
				mipmap.get_width(), mipmap.get_height(), 0, mipmap.get_size(),
				mipmap);
		}
		if(image.get_num_mipmaps() == 0)
			glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
		printf("Loaded texture of type DDS\n");
		return texture;
	}
	else if (strstr(pFilename.c_str(), ".png")) {
		// load from file and store in cache
		sf::Image image;
		if (image.loadFromFile(pFilename)) {
			//normal image 0,0 is top left, but opengl considers 0,0 to be bottom left, so we flip the image internally
			image.flipVertically();
			//create a wrapper for the id (texture is nothing more than that) and
			//load corresponding data into opengl using this id
			Texture * texture = new Texture();
			glHint(GL_TEXTURE_COMPRESSION_HINT, GL_NICEST);
			texture->SetSize(glm::vec2(image.getSize().x, image.getSize().y));
			glBindTexture(GL_TEXTURE_2D, texture->getId());
			//glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
			glTexImage2D(GL_TEXTURE_2D, 0, GL_COMPRESSED_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr()); //Use when low on memory, slow!
			glGenerateMipmap(GL_TEXTURE_2D);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glBindTexture(GL_TEXTURE_2D, 0);
			printf("Loaded texture of type PNG\n");
			return texture;
		}
	}
    else {
		std::cerr << "Tried to load invalid texture format: " << pFilename << std::endl;
        return nullptr;
    }
	return nullptr;
}










