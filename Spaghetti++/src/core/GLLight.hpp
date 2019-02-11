#pragma once

struct v3 {
	float x;
	float y;
	float z;
	float w;
};

struct GLLight {
	v3 pos;
	v3 cpos;
	v3 dir;
	v3 color;
	int type; 
	float ambient;
	float minRad;
	float maxRad;
};
