#include <iostream>
#include <string>
#include <stdexcept>

#include <assert.h>
#include <stdint.h>

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

Texture * Texture::loadDDS(const std::string & pFilename)
{
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
	if (image.get_num_mipmaps() == 0)
		glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	std::cout << "Loaded texture of type DDS: " << pFilename << "\n";
	return texture;
}

Texture * Texture::loadPNG(const std::string & pFilename)
{
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
		std::cout << "Loaded texture of type PNG: " << pFilename << "\n";
		return texture;
	}
	throw std::runtime_error("PNG could not be loaded: " + pFilename);
	return nullptr;
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
	std::string mFilename = pFilename;
	char* pch = (char*) strstr(mFilename.c_str(), ".png");
	if (pch != NULL) {
		strncpy(pch, ".dds", 4);
		std::cout << "PNG texture found, attempting to load DDS counterpart instead: " << mFilename << std::endl;
	}
	if (strstr(mFilename.c_str(), ".dds")) {
		try {
			Texture* texture = loadDDS(mFilename);
			return texture;
		}
		catch(std::exception& e){
			if(pch==NULL)
				std::cout << e.what() << '\n';
			else {
				std::cout << "Fallback to the old PNG system, attempting to load as PNG" << std::endl;
				char* pch = (char*)strstr(mFilename.c_str(), ".dds");
				strncpy(pch, ".png", 4);
			}
		}
	}
	if (strstr(mFilename.c_str(), ".png")) {
		try {
			Texture* texture = loadPNG(mFilename);
			return texture;
		}
		catch (std::exception& e) {
			std::cout << e.what() << '\n';
		}
	}
	//std::cerr << "Tried to load invalid texture: " << pFilename << std::endl;
    return nullptr;
}










