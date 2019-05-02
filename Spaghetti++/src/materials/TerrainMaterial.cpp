/*#include "glm.hpp"

#include "TerrainMaterial.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/ShaderProgram.hpp"
#include "mge/config.hpp"

ShaderProgram* TerrainMaterial::_shader = NULL;

GLint TerrainMaterial::_uMVPMatrix = 0;
GLint TerrainMaterial::_uMMatrix = 0;
GLint TerrainMaterial::_uMVMatrix = 0;
GLint TerrainMaterial::_uTileSize = 0;
GLint TerrainMaterial::_uTime = 0;
GLint TerrainMaterial::_uSize = 0;
GLint TerrainMaterial::_uHeight = 0;
GLint TerrainMaterial::_lightsNr = 0;
GLint TerrainMaterial::_uHeightmap = 0;
GLint TerrainMaterial::_uSplatmap = 0;
GLint TerrainMaterial::_uDiffuse1 = 0;
GLint TerrainMaterial::_uDiffuse2 = 0;
GLint TerrainMaterial::_uDiffuse3 = 0;
GLint TerrainMaterial::_uDiffuse4 = 0;
GLint TerrainMaterial::_uPixelUVratio = 0;
//GLint TextureMaterial::_time = 0.f;

GLint TerrainMaterial::_aVertex = 0;
GLint TerrainMaterial::_aNormal = 0;
GLint TerrainMaterial::_aUV = 0;

unsigned int TerrainMaterial::block_index = 0;

TerrainMaterial::TerrainMaterial(std::string heightmap, std::string splatmap, std::string d1, std::string d2, std::string d3, std::string d4, float sizeM, float texTileSizeM, float heightMult) {
	_heightmap = Texture::load(config::MGE_TEXTURE_PATH + heightmap);
	_splatmap = Texture::load(config::MGE_TEXTURE_PATH + splatmap);
	_diffuse1 = Texture::load(config::MGE_TEXTURE_PATH + d1);
	_diffuse2 = Texture::load(config::MGE_TEXTURE_PATH + d2);
	_diffuse3 = Texture::load(config::MGE_TEXTURE_PATH + d3);
	_diffuse4 = Texture::load(config::MGE_TEXTURE_PATH + d4);
	_size = sizeM;
	_tileSize = sizeM / texTileSizeM;
	_pixelUVratio = 1 / _heightmap->GetSize().x;
	_heightMult = heightMult;
    _lazyInitializeShader();
}

TerrainMaterial::~TerrainMaterial() {}

void TerrainMaterial::_lazyInitializeShader() {
    if (!_shader) {
        _shader = new ShaderProgram();
        _shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH+"terrain.vs");
        _shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH+"terrain.fs");
        _shader->finalize();

        //cache all the uniform and attribute indexes
        _uMVPMatrix = _shader->getUniformLocation("mvpMatrix");
		_uMMatrix	= _shader->getUniformLocation("mMatrix");
		_uMVMatrix	= _shader->getUniformLocation("mvMatrix");
		_uTime		= _shader->getUniformLocation("time");
		_uTileSize	= _shader->getUniformLocation("tileSize");
		_uSize		= _shader->getUniformLocation("size");
		_uHeight	= _shader->getUniformLocation("heightMult");
		_lightsNr	= _shader->getUniformLocation("lightsNr");
        _uHeightmap = _shader->getUniformLocation("heightMap");
        _uSplatmap = _shader->getUniformLocation("splatMap");
        _uDiffuse1 = _shader->getUniformLocation("diffuse1");
        _uDiffuse2 = _shader->getUniformLocation("diffuse2");
        _uDiffuse3 = _shader->getUniformLocation("diffuse3");
        _uDiffuse4 = _shader->getUniformLocation("diffuse4");
        _uPixelUVratio = _shader->getUniformLocation("pixelUV");
	//	_time		= _shader->getUniformLocation("time");

		block_index = glGetUniformBlockIndex(_shader->getProgramID(), "Lights");


		GLuint binding_point_index = 2;
		glBindBufferBase(GL_UNIFORM_BUFFER, block_index, World::getLightUBO());

		std::cout << "GL buffer data: " << block_index << std::endl;
        _aVertex = _shader->getAttribLocation("vertex");
        _aNormal = _shader->getAttribLocation("normal");
        _aUV =     _shader->getAttribLocation("uv");
    }
}

void TerrainMaterial::render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) {
    if (!_heightmap) return;

    _shader->use();
	
    //Print the number of lights in the scene and the position of the first light.
    //It is not used, but this demo is just meant to show you THAT materials can access the lights in a world
    //if (pWorld->getLightCount() > 0) {
    //    std::cout << "TextureMaterial has discovered light is at position:" << pWorld->getLightAt(0)->getLocalPosition() << std::endl;
    //}

    //setup texture slot 0
    glActiveTexture(GL_TEXTURE0);
    //bind the texture to the current active slot
    glBindTexture(GL_TEXTURE_2D, _heightmap->getId());
    //tell the shader the texture slot for the diffuse texture is slot 0
    glUniform1i (_uHeightmap, 0);

	//setup texture slot 0
	glActiveTexture(GL_TEXTURE1);
	//bind the texture to the current active slot
	glBindTexture(GL_TEXTURE_2D, _splatmap->getId());
	//tell the shader the texture slot for the diffuse texture is slot 1
	glUniform1i(_uSplatmap, 1);

	//setup texture slot 0
	glActiveTexture(GL_TEXTURE2);
	//bind the texture to the current active slot
	glBindTexture(GL_TEXTURE_2D, _diffuse1->getId());
	//tell the shader the texture slot for the diffuse texture is slot 2
	glUniform1i(_uDiffuse1, 2);

	//setup texture slot 0
	glActiveTexture(GL_TEXTURE3);
	//bind the texture to the current active slot
	glBindTexture(GL_TEXTURE_2D, _diffuse2->getId());
	//tell the shader the texture slot for the diffuse texture is slot 3
	glUniform1i(_uDiffuse2, 3);

	//setup texture slot 0
	glActiveTexture(GL_TEXTURE4);
	//bind the texture to the current active slot
	glBindTexture(GL_TEXTURE_2D, _diffuse3->getId());
	//tell the shader the texture slot for the diffuse texture is slot 4
	glUniform1i(_uDiffuse3, 4);

	//setup texture slot 0
	glActiveTexture(GL_TEXTURE5);
	//bind the texture to the current active slot
	glBindTexture(GL_TEXTURE_2D, _diffuse4->getId());
	//tell the shader the texture slot for the diffuse texture is slot 5
	glUniform1i(_uDiffuse4, 5);

    //pass in a precalculate mvp matrix (see texture material for the opposite)
	glm::mat4 mvMatrix = pViewMatrix * pModelMatrix;
    glm::mat4 mvpMatrix = pProjectionMatrix * mvMatrix;
    glUniformMatrix4fv ( _uMVPMatrix, 1, GL_FALSE, glm::value_ptr(mvpMatrix));
	glUniformMatrix4fv (_uMMatrix, 1, GL_FALSE, glm::value_ptr(pModelMatrix));
	glUniformMatrix4fv (_uMVMatrix, 1, GL_FALSE, glm::value_ptr(mvMatrix));

	//pass light direction
	glm::vec3 dir = pWorld->getLightAt(0)->getWorldPosition();//glm::normalize(-pWorld->getLightAt(0)->getWorldTransform()[2]);//glm::normalize(glm::vec3(-1, 1, -1));
	//std::cout << "Relative to cam: " << dir << std::endl;
	glm::vec3 posC = pViewMatrix * glm::vec4(dir, 1.0f);
	//std::cout << "Relative to cam: " << posC << std::endl;
	glUniform1f(_uTileSize, _tileSize);
	glUniform1f(_uTime, clock());
	//std::cout << _pixelUVratio << std::endl;
	glUniform1f(_uSize, _size);
	glUniform1f(_uHeight, _heightMult);
	glUniform1i(_lightsNr, pWorld->getLightCount());
	glUniform1f(_uPixelUVratio, _pixelUVratio);

//	glUniform1f(_time, clock() / 1000.f);

    //now inform mesh of where to stream its data
    pMesh->streamToOpenGL(_aVertex, _aNormal, _aUV);
}

*/