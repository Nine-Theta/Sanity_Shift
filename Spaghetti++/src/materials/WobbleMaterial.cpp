#include "WobbleMaterial.hpp"
#include "core/ShaderProgram.hpp"
#include "Settings.h"
#include "GameObject.h"
#include "components/CameraComponent.h"
#include "components/MeshComponent.h"
#include "core/AssetLoader.h"
//#include "mge/config.hpp"
namespace sge {
	ShaderProgram* WobbleMaterial::_shader = NULL;

	GLint WobbleMaterial::_uMVPMatrix = 0;
	GLint WobbleMaterial::_uMMatrix = 0;
	GLint WobbleMaterial::_lightDir = 0;
	GLint WobbleMaterial::_uDiffuseTexture = 0;
	GLint WobbleMaterial::_time = 0.f;

	GLint WobbleMaterial::_aVertex = 0;
	GLint WobbleMaterial::_aNormal = 0;
	GLint WobbleMaterial::_aUV = 0;

	WobbleMaterial::WobbleMaterial(std::string diffuse) {
		_diffuseTexture = AssetLoader::GetTexture(diffuse);
		_lazyInitializeShader();
	}

	WobbleMaterial::~WobbleMaterial() {}

	void WobbleMaterial::_lazyInitializeShader() {
		if (!_shader) {
			_shader = new ShaderProgram();
			_shader->addShader(GL_VERTEX_SHADER, "texturewobble.vs");
			_shader->addShader(GL_FRAGMENT_SHADER, "texture.fs");
			_shader->finalize();

			//cache all the uniform and attribute indexes
			_uMVPMatrix = _shader->getUniformLocation("mvpMatrix");
			_uMMatrix = _shader->getUniformLocation("mMatrix");
			_lightDir = _shader->getUniformLocation("sunDir");
			_uDiffuseTexture = _shader->getUniformLocation("diffuseTexture");
			_time = _shader->getUniformLocation("time");

			_aVertex = _shader->getAttribLocation("vertex");
			_aNormal = _shader->getAttribLocation("normal");
			_aUV = _shader->getAttribLocation("uv");
		}
	}

	void WobbleMaterial::setDiffuseTexture(Texture* pDiffuseTexture) {
		_diffuseTexture = pDiffuseTexture;
	}

	void WobbleMaterial::render(sge::MeshComponent* mesh, sge::CameraComponent* cam) {
		//if (!_diffuseTexture) return;
		std::cout << "Rendering material\n";
		if (cam == NULL)
			cam = CameraComponent::GetMain();
		_shader->use();

		//Print the number of lights in the scene and the position of the first light.
		//It is not used, but this demo is just meant to show you THAT materials can access the lights in a world
		//if (pWorld->getLightCount() > 0) {
		//    std::cout << "TextureMaterial has discovered light is at position:" << pWorld->getLightAt(0)->getLocalPosition() << std::endl;
		//}

		//setup texture slot 0
		glActiveTexture(GL_TEXTURE0);
		//bind the texture to the current active slot
		//glBindTexture(GL_TEXTURE_2D, _diffuseTexture->getId());
		//tell the shader the texture slot for the diffuse texture is slot 0
		glUniform1i(_uDiffuseTexture, 0);

		//pass in a precalculate mvp matrix (see texture material for the opposite)
		glm::mat4 mvpMatrix = cam->GetProjection() * cam->GetView() * mesh->GetParent()->GetCombinedTransform();
		glUniformMatrix4fv(_uMVPMatrix, 1, GL_FALSE, glm::value_ptr(mvpMatrix));
		//glUniformMatrix4fv(_uMMatrix, 1, GL_FALSE, glm::value_ptr(pModelMatrix));

		//pass light direction
		glm::vec3 dir = glm::normalize(glm::vec3(-1, 1, -1));
		glUniform3f(_lightDir, dir.x, dir.y, dir.z);

		//glUniform1f(_time, clock() / 1000.f);
		//now inform mesh of where to stream its data
		mesh->GetMesh()->streamToOpenGL(_aVertex, _aNormal, _aUV);
	}
}
