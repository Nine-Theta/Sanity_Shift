#ifndef LITMATERIAL_HPP
#define LITMATERIAL_HPP

#include "mge/materials/AbstractMaterial.hpp"
#include "GL/glew.h"

class ShaderProgram;
class Texture;

/**
 * This material is already a little bit more complicated, instead of a color we can pass in a texture,
 * all attributes and uniforms are cached and we precompute the MVP matrix passing it in as one entity.
 */
class LitMaterial : public AbstractMaterial
{
    public:
        LitMaterial (Texture* pDiffuseTexture);
        virtual ~LitMaterial ();

        virtual void render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;

        void setDiffuseTexture (Texture* pDiffuseTexture);

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
	//	static GLint _time;

        static GLint _aVertex ;
        static GLint _aNormal;
        static GLint _aUV ;

		static unsigned int block_index;

        Texture* _diffuseTexture;

        LitMaterial(const LitMaterial&);
        LitMaterial& operator=(const LitMaterial&);

};

#endif // TEXTUREMATERIAL_HPP
