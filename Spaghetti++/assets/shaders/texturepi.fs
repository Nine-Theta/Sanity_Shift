//DIFFUSE TEXTURE FRAGMENT SHADER
#version 330 // for glsl version (12 is for older versions , say opengl 2.1

uniform sampler2D diffuseTexture;
uniform vec3 sunDir;
noperspective in vec2 texCoord;
//in vec3 lightCol;
in vec3 fNormal;
out vec4 fragment_color;

void main( void ) {
	vec3 lightCol = ((1 + dot(sunDir,fNormal)) / 2) * vec3(1,1,1);
	fragment_color = vec4(lightCol,1) * texture(diffuseTexture,texCoord);
}
