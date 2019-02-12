#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include "core/Texture.hpp"

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
    // load from file and store in cache
    sf::Image image;
    if (image.loadFromFile(pFilename)) {
        //normal image 0,0 is top left, but opengl considers 0,0 to be bottom left, so we flip the image internally
        image.flipVertically();
        //create a wrapper for the id (texture is nothing more than that) and
        //load corresponding data into opengl using this id
        Texture * texture = new Texture();

		texture->SetSize(glm::vec2(image.getSize().x, image.getSize().y));
        glBindTexture (GL_TEXTURE_2D, texture->getId());
        glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
		glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);
        return texture;
    } else {
        return nullptr;
    }
}










