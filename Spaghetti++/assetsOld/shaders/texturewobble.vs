//DIFFUSE TEXTURE VERTEX SHADER
#version 330 // for glsl version (12 is for older versions , say opengl 2.1

uniform	mat4 	mvpMatrix;
uniform mat4	mMatrix;
uniform float	time;

in vec3 vertex;
in vec3 normal;
in vec2 uv;

out vec2 texCoord; //make sure the texture coord is interpolated
out vec3 fNormal;
//out vec3 lightCol;

void main( void ){
	float offset = vertex.x + vertex.y + vertex.z;
	float phase = (sin(offset) + 1) * 0.5f + cos(offset) * 4;
	float scale = (sin(time * phase) + 1) * 0.5f * 0.2f + 0.8f;
    gl_Position = mvpMatrix * (vec4(vertex * scale, 1.f));
	texCoord = uv;
	fNormal = (mMatrix * vec4(normal,1.f)).xyz;
}
