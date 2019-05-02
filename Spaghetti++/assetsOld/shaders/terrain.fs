//DIFFUSE TEXTURE FRAGMENT SHADER
#version 330 // for glsl version (12 is for older versions , say opengl 2.1

uniform sampler2D heightMap;
uniform sampler2D splatMap;
uniform sampler2D diffuse1;
uniform sampler2D diffuse2;
uniform sampler2D diffuse3;
uniform sampler2D diffuse4;
uniform float tileSize;
uniform float time;

uniform int lightsNr;
in vec3 texCoord;
//in vec3 lightCol;
in vec3 fNormal;
in vec3 fPos;
in vec3 fcPos;
in vec3 fcNormal;


in vec3 triplanarMap;

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
	return falloff * falloff;
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
float shininess = 1;

vec3 blinnPhongCol(Light lt){
	float energyConservation = ( 8.0 + shininess ) / ( 8.0 * pi ); 
	vec3 distS 	= lt.cpos.xyz - fcPos;
	vec3 ray 	= normalize(distS);
	vec3 view 	= -normalize(fcPos);
	vec3 halfway = normalize(ray + view);// normalize(ray - 2 * (dot(normalize(fcNormal),ray)));
	float spec = pow(max(dot(fcNormal, halfway), 0.0), shininess);
	vec3 specColor = vec3(1,1,1);
	vec3 specular =  lt.color.rgb * specColor * spec;//pow(max(dot(bounce,view),0),shininess);
	return energyConservation * specular;
}

vec3 diffuseCol(Light lt){
	//float distFalloff = 1 - clamp(distance(lt.pos.xyz, fPos),0,lt.color.w) / lt.color.w;
	vec3 dir = normalize(lt.pos.xyz - fPos) * when_eq(1, lt.type) + normalize(lt.dir.xyz) * when_eq(0, lt.type);
	float angleFalloff = clamp(dot(dir,fNormal),0,1);//((1 + dot(dir,fNormal)) / 2.0f);
	vec3 lCol = lerp(angleFalloff,0,1 - lt.ambient) * lt.color.rgb;	//((1 + dot(sunDir,fNormal)) / 2.0f) * vec3(1,1,1);
	return lCol;
}

vec4 colFromUV(vec2 UV){

	vec4 splatCol = texture(splatMap,texCoord.xz);
	vec2 newUV = UV * tileSize;
	vec4 diffuseCol = texture(diffuse1, newUV) * splatCol.r;
	diffuseCol = texture(diffuse2, newUV) * splatCol.g + diffuseCol;
	diffuseCol = texture(diffuse3, newUV) * splatCol.b + diffuseCol;
	diffuseCol = texture(diffuse4, newUV + vec2(sin(time * 0.0007f + fPos.x * 0.2f), cos(time * 0.0006f + fPos.z * 0.2f)) * 0.1) * splatCol.a + diffuseCol;
	return diffuseCol;
}

void main( void ) {
	//lightColor = wLights[0].color.rgb;
	//float radius = 3.0f;
	
	vec3 col = vec3(0,0,0);
	vec3 specCol = vec3(0,0,0);
	for(int i = 0; i < lightsNr; i++){
		vec3 spec 	= blinnPhongCol(wLights[i]);// * distFalloff;
		vec3 lCol 	= diffuseCol(wLights[i]);
		
		float falloff =  distanceFalloff(wLights[i]) * spotAngleFalloff(wLights[i]);
		col += lCol * falloff + wLights[i].ambient;
		specCol +=  spec * falloff;
	}
	vec4 diffuseCol = colFromUV(texCoord.xz) * triplanarMap.r;
	diffuseCol 		= diffuseCol + colFromUV(texCoord.xy) * triplanarMap.g;
	diffuseCol 		= diffuseCol + colFromUV(texCoord.zy) * triplanarMap.b;
	fragment_color = vec4(col,1) * diffuseCol  + vec4(specCol,1);
	
	//fragment_color = vec4(triplanarMap, 1);
}
