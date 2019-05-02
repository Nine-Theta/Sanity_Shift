#pragma once
#ifndef SPECULARMATERIAL_HPP
#define SPECULARMATERIAL_HPP

#include "materials/AbstractMaterial.hpp"
#include "core/Texture.hpp"
#include "GL/glew.h"
	class ShaderProgram;

namespace sge {

	/**
	 * This material is already a little bit more complicated, instead of a color we can pass in a texture,
	 * all attributes and uniforms are cached and we precompute the MVP matrix passing it in as one entity.
	 */
	class SpecularMaterial : public AbstractMaterial
	{
	public:
		SpecularMaterial(std::string diffuse, std::string specular, std::string normal, bool debug = false);
		virtual ~SpecularMaterial();

		virtual void render(sge::MeshComponent* mesh, sge::CameraComponent* cam) override;

		void setDiffuseTexture(Texture* pDiffuseTexture);

	protected:
	private:
		static ShaderProgram* _shader;
		static void _lazyInitializeShader();

		//in this example we cache all identifiers for uniforms & attributes
		static GLint _uMVPMatrix;
		static GLint _uMMatrix;
		static GLint _uMVMatrix;
		static GLint _lightDir;
		static GLint _lightPosC;
		static GLint _lightsNr;
		static GLint _uDiffuseTexture;
		static GLint _uSpecularTexture;
		static GLint _uNormalTexture;
		//	static GLint _time;

		static GLint _aVertex;
		static GLint _aNormal;
		static GLint _aUV;
		static GLint _aTangent;

		static unsigned int block_index;

		Texture* _diffuseTexture;
		Texture* _specularTexture;
		Texture* _normalTexture;

		bool _debug;

		SpecularMaterial(const SpecularMaterial&);
		SpecularMaterial& operator=(const SpecularMaterial&);

	};
}
#endif // TEXTUREMATERIAL_HPP
