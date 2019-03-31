#pragma once
#ifndef FLUORMATERIAL_HPP
#define FLUORMATERIAL_HPP

#include "materials/AbstractMaterial.hpp"
#include "core/Texture.hpp"
#include "GL/glew.h"
	class ShaderProgram;
namespace sge {

	/**
	 * This material is already a little bit more complicated, instead of a color we can pass in a texture,
	 * all attributes and uniforms are cached and we precompute the MVP matrix passing it in as one entity.
	 */
	class FluorescentMaterial : public AbstractMaterial
	{
	public:
		FluorescentMaterial(std::string diffuse, std::string specular, std::string normal);
		virtual ~FluorescentMaterial();

		virtual void render(sge::MeshComponent* mesh, sge::CameraComponent* cam) override;

		void setDiffuseTexture(Texture* pDiffuseTexture);

		void setGlowCol(vec4 color);
		void setSelectionMult(float mult);
		void setReactionMult(float mult);

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
		static GLint _aGlowCol;
		static GLint _aLightSelect;
		static GLint _aLightReact;

		static unsigned int block_index;

		vec4 _glowCol = vec4(0.7f, 0.4f, 0.1f, 0.3f);
		float _lightSelect = 0;
		float _lightReact = 1;
		Texture* _diffuseTexture;
		Texture* _specularTexture;
		Texture* _normalTexture;

		FluorescentMaterial(const FluorescentMaterial&);
		FluorescentMaterial& operator=(const FluorescentMaterial&);

	};
}
#endif // TEXTUREMATERIAL_HPP
