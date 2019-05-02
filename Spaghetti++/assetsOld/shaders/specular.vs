//DIFFUSE TEXTURE VERTEX SHADER
#version 330 // for glsl version (12 is for older versions , say opengl 2.1

uniform	mat4 	mvpMatrix;
uniform mat4	mMatrix;
uniform mat4	mvMatrix;

in vec3 vertex;
in vec3 normal;
in vec2 uv;

out vec2 texCoord; //make sure the texture coord is interpolated
out vec3 fNormal;
out vec3 fPos;
out vec3 fcPos;
out vec3 fcNormal;
//out vec3 lightCol;

void main( void ){
    gl_Position = mvpMatrix * vec4(vertex, 1.f);
	texCoord = uv;
	fNormal = (mMatrix * vec4(normal,0.f)).xyz;
	fPos = (mMatrix * vec4(vertex,1.f)).xyz;
	fcPos = (mvMatrix * vec4(vertex,1.f)).xyz;
	fcNormal = (mvMatrix * vec4(normal,0.f)).xyz;
}
