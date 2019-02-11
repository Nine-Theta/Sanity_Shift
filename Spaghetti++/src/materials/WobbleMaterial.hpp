#ifndef WOBBLEMATERIAL_HPP
#define WOBBLEMATERIAL_HPP

#include "materials/AbstractMaterial.hpp"
#include "GL/glew.h"

class ShaderProgram;
class Texture;

/**
 * This material is already a little bit more complicated, instead of a color we can pass in a texture,
 * all attributes and uniforms are cached and we precompute the MVP matrix passing it in as one entity.
 */
namespace sge {
	class WobbleMaterial : public AbstractMaterial
	{
	public:
		WobbleMaterial(std::string diffuse);
		virtual ~WobbleMaterial();

		virtual void render(sge::MeshComponent* mesh, sge::CameraComponent* cam = NULL) override;

		void setDiffuseTexture(Texture* pDiffuseTexture);

	protected:
	private:
		static ShaderProgram* _shader;
		static void _lazyInitializeShader();

		//in this example we cache all identifiers for uniforms & attributes
		static GLint _uMVPMatrix;
		static GLint _uMMatrix;
		static GLint _lightDir;
		static GLint _uDiffuseTexture;
		static GLint _time;

		static GLint _aVertex;
		static GLint _aNormal;
		static GLint _aUV;

		Texture* _diffuseTexture;

		WobbleMaterial(const WobbleMaterial&);
		WobbleMaterial& operator=(const WobbleMaterial&);

	};
}

#endif // TEXTUREMATERIAL_HPP
