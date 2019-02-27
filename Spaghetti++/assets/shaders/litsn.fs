//DIFFUSE TEXTURE FRAGMENT SHADER
#version 330 // for glsl version (12 is for older versions , say opengl 2.1

uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;
uniform sampler2D normalTexture;
uniform vec3 lightPos;
uniform vec3 lightPosC;

uniform int lightsNr;
in vec2 texCoord;
//in vec3 lightCol;
in vec3 fNormal;
in vec3 fTangent;
in vec3 fBitangent;
in vec3 fPos;
in vec3 fcPos;
in vec3 fcNormal;
in vec3 fcTangent;
in vec3 fcBitangent;

in mat3 fBTN;
in mat3 fcBTN;


out vec4 fragment_color;

struct Light{
	vec4 pos;
	vec4 cpos;
	vec4 dir;
	vec4 color;
	int type;
	float ambient;
	float minRad;
	float maxRad;
};

layout (std140) uniform Lights
{
	Light[16] wLights;
};

vec3 lightColor = vec3(1,1.f,0.05f);
//mat3 fBTN;
//mat3 fcBTN;
vec3 ftNormal;
vec3 fctNormal;

int when_eq(int x, int y) {
	return 1 - abs(sign(x - y));
}

float lerp (float value, float from, float to) {
    return (1.f - from) * value + from;
}

float inverseLerp(float value, float start, float end){
	float top = abs(end - start);
	float dif = top - abs(end);
	float val = value + dif;
	return val / top;
}

float distanceFalloff(Light lt){
	float dist = distance(lt.pos.xyz,fPos);
	float distFalloff = clamp(1.0 - dist*dist/(lt.color.w*lt.color.w), 0.0, 1.0); 
	distFalloff *= distFalloff;
	return max(distFalloff, when_eq(0, lt.type));
}

float spotAngleFalloff(Light lt){
	vec3 dir = normalize(lt.pos.xyz - fPos);
	float proj = dot(dir, lt.dir.xyz);
	float falloff = smoothstep(min(lt.minRad,lt.maxRad), max(lt.minRad,lt.maxRad), proj);//clamp(inverseLerp(proj,lt.minRad,lt.maxRad),0,1);
	return clamp(falloff * falloff,0,1);
}

vec3 specularCol(Light lt){
	vec3 distS 	= fcPos - lt.cpos.xyz;
	vec3 ray 	= normalize(distS);
	vec3 bounce = normalize(-reflect(ray,normalize(fcNormal)));// normalize(ray - 2 * (dot(normalize(fcNormal),ray)));
	vec3 view 	= normalize(fcPos);
	float shininess = 90;
	vec3 specColor = vec3(1,1,1);
	vec3 specular =  lt.color.rgb * specColor * pow(max(dot(bounce,view),0),shininess);
	return specular;
}

const float pi = 3.14159265;
vec4 specularTex = texture(specularTexture,texCoord); 

vec3 blinnPhongCol(Light lt){
	float shininess = 1 + specularTex.a * 1024;
	float energyConservation = ( 8.0 + shininess ) / ( 8.0 * pi ); 
	vec3 distS 	= lt.cpos.xyz - fcPos;
	vec3 ray 	= normalize(distS);
	vec3 view 	= -normalize(fcPos);
	vec3 halfway = normalize(ray + view);// normalize(ray - 2 * (dot(normalize(fcNormal),ray)));
	float spec = pow(max(dot(fctNormal, halfway), 0.0), shininess);
	vec3 specColor = specularTex.rgb;
	vec3 specular =  lt.color.rgb * specColor * spec;//pow(max(dot(bounce,view),0),shininess);
	return energyConservation * specular;
}

vec3 diffuseCol(Light lt){
	//float distFalloff = 1 - clamp(distance(lt.pos.xyz, fPos),0,lt.color.w) / lt.color.w;
	vec3 dir = normalize(lt.pos.xyz - fPos) * when_eq(1, lt.type) + normalize(lt.dir.xyz) * when_eq(0, lt.type);
	float angleFalloff = clamp(dot(dir,ftNormal),0,1);//((1 + dot(dir,fNormal)) / 2.0f);
	vec3 lCol = lerp(angleFalloff,0,1 - lt.ambient) * lt.color.rgb;	//((1 + dot(sunDir,fNormal)) / 2.0f) * vec3(1,1,1);
	return lCol;
}

void main( void ) {
	//lightColor = wLights[0].color.rgb;
	//float radius = 3.0f;
	//fBTN = mat3(normalize(fBitangent),normalize(fTangent),normalize(fNormal));
	//fcBTN = mat3(normalize(fcBitangent),normalize(fcTangent),normalize(fcNormal));
	fctNormal = normalize(fcBTN * (vec3(texture(normalTexture,texCoord) * 2 - 1)));
	ftNormal = normalize(fBTN * (vec3(texture(normalTexture,texCoord) * 2 - 1)));
	vec3 col = vec3(0,0,0);
	vec3 specCol = vec3(0,0,0);
	for(int i = 0; i < lightsNr; i++){
		vec3 spec 	= blinnPhongCol(wLights[i]);// * distFalloff;
		vec3 lCol 	= diffuseCol(wLights[i]);
		
		float falloff =  distanceFalloff(wLights[i]) * spotAngleFalloff(wLights[i]);
		col += lCol * falloff + wLights[i].ambient;
		specCol +=  spec * falloff;
	}
	vec4 texCol = texture(diffuseTexture,texCoord);
	fragment_color = vec4(col,1) * texCol + vec4(specCol,1);
}
