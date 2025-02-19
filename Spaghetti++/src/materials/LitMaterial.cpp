/*#include "glm.hpp"

#include "LitMaterial.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/ShaderProgram.hpp"
#include "mge/config.hpp"

ShaderProgram* LitMaterial::_shader = NULL;

GLint LitMaterial::_uMVPMatrix = 0;
GLint LitMaterial::_uMMatrix = 0;
GLint LitMaterial::_uMVMatrix = 0;
GLint LitMaterial::_lightDir = 0;
GLint LitMaterial::_lightPosC = 0;
GLint LitMaterial::_lightsNr = 0;
GLint LitMaterial::_uDiffuseTexture = 0;
//GLint TextureMaterial::_time = 0.f;

GLint LitMaterial::_aVertex = 0;
GLint LitMaterial::_aNormal = 0;
GLint LitMaterial::_aUV = 0;

unsigned int LitMaterial::block_index = 0;

LitMaterial::LitMaterial(Texture * pDiffuseTexture):_diffuseTexture(pDiffuseTexture) {
    _lazyInitializeShader();
}

LitMaterial::~LitMaterial() {}

void LitMaterial::_lazyInitializeShader() {
    if (!_shader) {
        _shader = new ShaderProgram();
        _shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH+"lit.vs");
        _shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH+"lit.fs");
        _shader->finalize();

        //cache all the uniform and attribute indexes
        _uMVPMatrix = _shader->getUniformLocation("mvpMatrix");
		_uMMatrix	= _shader->getUniformLocation("mMatrix");
		_uMVMatrix	= _shader->getUniformLocation("mvMatrix");
		_lightDir	= _shader->getUniformLocation("lightPos");
		_lightPosC	= _shader->getUniformLocation("lightPosC");
		_lightsNr	= _shader->getUniformLocation("lightsNr");
        _uDiffuseTexture = _shader->getUniformLocation("diffuseTexture");
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

void LitMaterial::setDiffuseTexture (Texture* pDiffuseTexture) {
    _diffuseTexture = pDiffuseTexture;
}

void LitMaterial::render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) {
    if (!_diffuseTexture) return;

    _shader->use();
	
    //Print the number of lights in the scene and the position of the first light.
    //It is not used, but this demo is just meant to show you THAT materials can access the lights in a world
    //if (pWorld->getLightCount() > 0) {
    //    std::cout << "TextureMaterial has discovered light is at position:" << pWorld->getLightAt(0)->getLocalPosition() << std::endl;
    //}

    //setup texture slot 0
    glActiveTexture(GL_TEXTURE0);
    //bind the texture to the current active slot
    glBindTexture(GL_TEXTURE_2D, _diffuseTexture->getId());
    //tell the shader the texture slot for the diffuse texture is slot 0
    glUniform1i (_uDiffuseTexture, 0);

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
	glUniform3f(_lightDir, dir.x,dir.y,dir.z);
	glUniform3f(_lightPosC, posC.x, posC.y, posC.z);
	glUniform1i(_lightsNr, pWorld->getLightCount());

//	glUniform1f(_time, clock() / 1000.f);

    //now inform mesh of where to stream its data
    pMesh->streamToOpenGL(_aVertex, _aNormal, _aUV);
}
*/
