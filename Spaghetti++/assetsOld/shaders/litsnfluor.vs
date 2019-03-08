//DIFFUSE TEXTURE VERTEX SHADER
#version 330 // for glsl version (12 is for older versions , say opengl 2.1

uniform	mat4 	mvpMatrix;
uniform mat4	mMatrix;
uniform mat4	mvMatrix;

in vec3 vertex;
in vec3 normal;
in vec3 tangent;
in vec2 uv;

out vec2 texCoord; //make sure the texture coord is interpolated
out vec3 fNormal;
out vec3 fTangent;
out vec3 fBitangent;
out vec3 fPos;
out vec3 fcPos;
out vec3 fcNormal;
out vec3 fcTangent;
out vec3 fcBitangent;
out mat3 fBTN;
out mat3 fcBTN;
//out vec3 lightCol;

void main( void ){
	vec3 bitangent = cross(tangent,normal);
    gl_Position = mvpMatrix * vec4(vertex, 1.f);
	texCoord = uv;
	fNormal = (mMatrix * vec4(normal,0.f)).xyz;
	fTangent = (mMatrix * vec4(tangent,0.f)).xyz;
	fBitangent = (mMatrix * vec4(bitangent,0.f)).xyz;
	fPos = (mMatrix * vec4(vertex,1.f)).xyz;
	fcPos = (mvMatrix * vec4(vertex,1.f)).xyz;
	fcNormal = (mvMatrix * vec4(normal,0.f)).xyz;
	fcTangent = (mvMatrix * vec4(tangent,0.f)).xyz;
	fcBitangent = (mvMatrix * vec4(bitangent,0.f)).xyz;
	
	fBTN = mat3(normalize(fBitangent),normalize(fTangent),normalize(fNormal));
	fcBTN = mat3(normalize(fcBitangent),normalize(fcTangent),normalize(fcNormal));
}
