#pragma once
#include "TransparencyMaterial.hpp"
#include "core/ShaderProgram.hpp"
#include "Settings.h"
#include "GameObject.h"
#include "components/CameraComponent.h"
#include "components/MeshComponent.h"
#include "core/AssetLoader.h"
#include "components/LightComponent.hpp"
namespace sge {
	ShaderProgram* TransparencyMaterial::_shader = NULL;

	GLint TransparencyMaterial::_uMVPMatrix = 0;
	GLint TransparencyMaterial::_uMMatrix = 0;
	GLint TransparencyMaterial::_uMVMatrix = 0;
	GLint TransparencyMaterial::_lightDir = 0;
	GLint TransparencyMaterial::_lightPosC = 0;
	GLint TransparencyMaterial::_lightsNr = 0;
	GLint TransparencyMaterial::_uDiffuseTexture = 0;
	GLint TransparencyMaterial::_uSpecularTexture = 0;
	GLint TransparencyMaterial::_uNormalTexture = 0;
	//GLint TextureMaterial::_time = 0.f;

	GLint TransparencyMaterial::_aVertex = 0;
	GLint TransparencyMaterial::_aNormal = 0;
	GLint TransparencyMaterial::_aTangent = 0;
	GLint TransparencyMaterial::_aUV = 0;

	unsigned int TransparencyMaterial::block_index = 0;

	TransparencyMaterial::TransparencyMaterial(std::string diffuse, std::string specular, std::string normal){
		_diffuseTexture = AssetLoader::GetTexture(diffuse);
		_specularTexture = AssetLoader::GetTexture(specular);
		_normalTexture = AssetLoader::GetTexture(normal);
		_lazyInitializeShader();
	}

	TransparencyMaterial::~TransparencyMaterial() {}

	void TransparencyMaterial::_lazyInitializeShader() {
		if (!_shader) {
			_shader = new ShaderProgram();
			_shader->addShader(GL_VERTEX_SHADER, "litsn.vs");
			_shader->addShader(GL_FRAGMENT_SHADER,"litsntp.fs");
			_shader->finalize();

			//cache all the uniform and attribute indexes
			_uMVPMatrix = _shader->getUniformLocation("mvpMatrix");
			_uMMatrix = _shader->getUniformLocation("mMatrix");
			_uMVMatrix = _shader->getUniformLocation("mvMatrix");
			_lightDir = _shader->getUniformLocation("lightPos");
			_lightPosC = _shader->getUniformLocation("lightPosC");
			_lightsNr = _shader->getUniformLocation("lightsNr");
			_uDiffuseTexture = _shader->getUniformLocation("diffuseTexture");
			_uSpecularTexture = _shader->getUniformLocation("specularTexture");
			_uNormalTexture = _shader->getUniformLocation("normalTexture");
			//	_time		= _shader->getUniformLocation("time");

			block_index = glGetUniformBlockIndex(_shader->getProgramID(), "Lights");


			GLuint binding_point_index = 2;
			glBindBufferBase(GL_UNIFORM_BUFFER, block_index, LightComponent::GetLightUBO());

			std::cout << "GL buffer data: " << block_index << std::endl;
			_aVertex = _shader->getAttribLocation("vertex");
			_aNormal = _shader->getAttribLocation("normal");
			_aTangent = _shader->getAttribLocation("tangent");
			_aUV = _shader->getAttribLocation("uv");
		}
	}

	void TransparencyMaterial::setDiffuseTexture(Texture* pDiffuseTexture) {
		_diffuseTexture = pDiffuseTexture;
	}

	void TransparencyMaterial::render(sge::MeshComponent* mesh, sge::CameraComponent* cam) {
		if (!_diffuseTexture) return;

		//return;
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
		glUniform1i(_uDiffuseTexture, 0);

		glActiveTexture(GL_TEXTURE1);
		//bind the texture to the current active slot
		glBindTexture(GL_TEXTURE_2D, _specularTexture->getId());
		//tell the shader the texture slot for the diffuse texture is slot 0
		glUniform1i(_uSpecularTexture, 1);

		glActiveTexture(GL_TEXTURE2);
		//bind the texture to the current active slot
		glBindTexture(GL_TEXTURE_2D, _normalTexture->getId());
		//tell the shader the texture slot for the diffuse texture is slot 0
		glUniform1i(_uNormalTexture, 2);

		//pass in a precalculate mvp matrix (see texture material for the opposite)
		mat4 mMatrix = mesh->GetParent()->GetCombinedTransform();
		mat4 vMatrix = cam->GetView();
		mat4 pMatrix = cam->GetProjection();
		glm::mat4 mvMatrix = vMatrix * mMatrix;
		glm::mat4 mvpMatrix = pMatrix * mvMatrix;
		glUniformMatrix4fv(_uMVPMatrix, 1, GL_FALSE, glm::value_ptr(mvpMatrix));
		glUniformMatrix4fv(_uMMatrix, 1, GL_FALSE, glm::value_ptr(mMatrix));
		glUniformMatrix4fv(_uMVMatrix, 1, GL_FALSE, glm::value_ptr(mvMatrix));

		//pass light direction
		//glm::vec3 dir = pWorld->getLightAt(0)->getWorldPosition();//glm::normalize(-pWorld->getLightAt(0)->getWorldTransform()[2])5;//glm::normalize(glm::vec3(-1, 1, -1));
		//std::cout << "Relative to cam: " << dir << std::endl;
		//glm::vec3 posC = vMatrix * glm::vec4(dir, 1.0f);
		//std::cout << "Relative to cam: " << posC << std::endl;
		//glUniform3f(_lightDir, dir.x, dir.y, dir.z);
		//glUniform3f(_lightPosC, posC.x, posC.y, posC.z);
		glUniform1i(_lightsNr, LightComponent::GetLightCount());
		//std::cout << LightComponent::GetLightCount() << std::endl;

		//	glUniform1f(_time, clock() / 1000.f);

			//now inform mesh of where to stream its data
		mesh->GetMesh()->streamToOpenGL(_aVertex, _aNormal, _aTangent, _aUV);
		_renderedPolys += mesh->GetMesh()->GetPolyCount();
		//mesh->GetMesh()->drawDebugInfo(mMatrix, vMatrix, pMatrix);
		//mesh->GetMesh()->streamToOpenGL(_aVertex, _aNormal, _aUV);
	}

}