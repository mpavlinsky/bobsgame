#ifdef GL_ES
precision mediump float;
#endif

#define zNear 0.001
#define PI 3.14159265359

// INTERNET
// kanatacrude - more like i/o

uniform float time;
//uniform vec2 mouse;
uniform vec2 resolution;

float t = time * 0.2;

bool one(vec2 pos) {
	return pos.x > 0.45 && pos.x < 0.55 && pos.y > 0.1 && pos.y < 0.9;
}

bool zero(vec2 pos) {
	pos -= 0.5;
	pos.x *= 1.7;
	float d = length(pos);
	
	return d > 0.3 && d < 0.4;
}

void main( void ) {

	vec2 position = gl_FragCoord.xy / resolution.xy;

	position -= 0.5;
	position *= 0.8;
	
 	position.x /= resolution.y / resolution.x;
	position.x += sin(time * 1.0) * 0.01;
	position.y += sin(time * 1.0 + 10.3) * 0.01;
	
	vec3 rayDir = normalize(vec3(position, zNear));
	vec3 rayPos = vec3(position, 0);

	float a = rayDir.x * rayDir.x + rayDir.y * rayDir.y;
	float b = 2.0 * (rayPos.x * rayDir.x + rayPos.y * rayDir.y);
	float c = rayPos.x * rayPos.x + rayPos.y * rayPos.y - 1.0;
	
	float d = (-b + sqrt(b * b - 4.0 * a * c)) / (2.0 * a);
		
	vec3 cp = rayPos + rayDir * d;
	float ca = (atan(cp.y, cp.x) + PI) / (2.0 * PI);
	
	vec2 sp = vec2(cp.z * 1000.0, mod(ca * 20.0 + t, 20.0));
	sp.x += sin(floor(sp.y)) * time * 4.0 + t * 6.0;

	vec2 tp = mod(sp, 1.0);
	//bool w = mod(ca + cp.z + time * 0.1, 0.2) < 0.1;
	//if (mod(cp.z + time * 0.005, 0.01) < 0.005)
	//  w = !w;
	
	bool w;
	if (mod(floor(sp.x) * floor(sp.y), 173.0) < 121.0) {
		w = zero(tp);
	}
	else {
		w = one(tp);
	}

	gl_FragColor = vec4(vec3(0.0, 0.7, 0.7) * float(w) / pow(cp.z * 80.0, 2.0) * (1.0 - abs(sin(floor(sp.y))) * 0.995), 1.0);
}