#ifndef TERRAINMATERIAL_HPP
#define TERRAINMATERIAL_HPP

#include "mge/materials/AbstractMaterial.hpp"
#include "GL/glew.h"

class ShaderProgram;
class Texture;

/**
 * This material is already a little bit more complicated, instead of a color we can pass in a texture,
 * all attributes and uniforms are cached and we precompute the MVP matrix passing it in as one entity.
 */
class TerrainMaterial : public AbstractMaterial
{
    public:
        TerrainMaterial (std::string heightmap, std::string splatmap, std::string d1, std::string d2, std::string d3, std::string d4, float sizeM, float texTileSizeM = 10, float heightMult = 1);
        virtual ~TerrainMaterial ();

        virtual void render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;

       // void setDiffuseTexture (Texture* pDiffuseTexture);

    protected:
    private:
        static ShaderProgram* _shader;
        static void _lazyInitializeShader();

        //in this example we cache all identifiers for uniforms & attributes
        static GLint _uMVPMatrix;
		static GLint _uMMatrix;
		static GLint _uMVMatrix;
		static GLint _uTileSize;
		static GLint _uTime;
		static GLint _uSize;
		static GLint _uHeight;
		static GLint _lightsNr;
        static GLint _uHeightmap;
        static GLint _uSplatmap;
        static GLint _uDiffuse1;
        static GLint _uDiffuse2;
        static GLint _uDiffuse3;
        static GLint _uDiffuse4;
        static GLint _uPixelUVratio;
	//	static GLint _time;

        static GLint _aVertex ;
        static GLint _aNormal;
        static GLint _aUV ;

		static unsigned int block_index;
		float _size;
		float _tileSize;
		float _pixelUVratio;
		float _heightMult;

        Texture* _heightmap;
        Texture* _splatmap;
        Texture* _diffuse1;
        Texture* _diffuse2;
        Texture* _diffuse3;
        Texture* _diffuse4;

        TerrainMaterial(const TerrainMaterial&);
        TerrainMaterial& operator=(const TerrainMaterial&);

};

#endif // TEXTUREMATERIAL_HPP
