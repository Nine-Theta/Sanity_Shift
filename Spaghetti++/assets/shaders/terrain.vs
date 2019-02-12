//DIFFUSE TEXTURE VERTEX SHADER
#version 330 // for glsl version (12 is for older versions , say opengl 2.1

uniform	mat4 	mvpMatrix;
uniform mat4	mMatrix;
uniform mat4	mvMatrix;
uniform sampler2D heightMap;
uniform float 	size;
uniform float	pixelUV;
uniform float 	heightMult;

in vec3 vertex;
in vec3 normal;
in vec2 uv;

out vec3 texCoord; //3d for triplanar mapping
out vec3 fNormal;
out vec3 fPos;
out vec3 fcPos;
out vec3 fcNormal;

out vec3 triplanarMap;
//out vec3 lightCol;

void main( void ){
	vec2 heightUV = (vertex.xz + vec2(1,1)) * 0.5f;
	float height 	= texture(heightMap,heightUV).r * heightMult;
	float h1 		= texture(heightMap,heightUV + vec2(pixelUV,0)).r * heightMult;
	float h2 		= texture(heightMap,heightUV + vec2(-pixelUV,0)).r * heightMult;
	float h3 		= texture(heightMap,heightUV + vec2(0,pixelUV)).r * heightMult;
	float h4 		= texture(heightMap,heightUV + vec2(0,-pixelUV)).r * heightMult;
	vec3 angle1		= normalize(vec3(heightUV.x + pixelUV, h1, heightUV.y) - vec3(heightUV.x - pixelUV, h2, heightUV.y));
	vec3 angle2		= normalize(vec3(heightUV.x, h4, heightUV.y - pixelUV) - vec3(heightUV.x, h3, heightUV.y + pixelUV));
	vec3 dNormal 	= normalize(cross(angle1,angle2));
	vec4 vert = vec4(vec3(vertex.x, height, vertex.z) * size,1);
    gl_Position = vec4((mvpMatrix * vert).xyzw);
	texCoord = vec3(heightUV.x, height * 0.5f, heightUV.y);
	fNormal = (mMatrix * vec4(dNormal,0.f)).xyz;
	fPos = (mMatrix * vert).xyz;
	fcPos = (mvMatrix * vert).xyz;
	fcNormal = (mvMatrix * vec4(dNormal,0.f)).xyz;
	
	triplanarMap = vec3(asin(abs(dNormal.y)) * 0.63661977f, asin(abs(dNormal.z)) * 0.63661977f, asin(abs(dNormal.x)) * 0.63661977f);
}
