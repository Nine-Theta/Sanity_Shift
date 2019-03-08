//DIFFUSE TEXTURE VERTEX SHADER
#version 330 // for glsl version (12 is for older versions , say opengl 2.1

uniform	mat4 	mvpMatrix;
uniform mat4	mMatrix;

in vec3 vertex;
in vec3 normal;
in vec2 uv;

noperspective out vec2 texCoord; //make sure the texture coord is interpolated
out vec3 fNormal;
//out vec3 lightCol;

void main( void ){
    gl_Position = mvpMatrix * vec4(vertex, 1.f);
	gl_Position = vec4(int(gl_Position.x), int(gl_Position.y), int(gl_Position.z), gl_Position.w);
	texCoord = uv;
	fNormal = (mMatrix * vec4(normal,1.f)).xyz;
}
