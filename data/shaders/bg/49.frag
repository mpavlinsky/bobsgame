#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

float two_pi = 4.0 * asin(1.0);
const float proj_coeff = 0.02;
const float rot_coeff = 0.1;
const float move_coeff = 0.1;
const float fog_coeff = 1.8;
const float fog_exp = 1.8;

const vec2 hex_coord_mult = vec2(1.0, 3.0);
const float hex_threshold = 0.1;

float hex(vec2 p) {
	p.x *= 0.57735*2.0;
	p.y += mod(floor(p.x), 2.0)*0.5;
	p = abs((mod(p, 1.0) - 0.5));
	return abs(max(p.x*1.5 + p.y, p.y*2.0) - 1.0);
}

vec3 color_mult(vec2 pos) {
	return clamp(vec3(0.5 * (sin(pos.x * two_pi) + 1.0), 0.5 * (cos(pos.y * two_pi) + 1.0), 1.0), 0.0, 1.0);
}


vec4 texture(vec2 pos) {
	return vec4(vec3(hex(hex_coord_mult * pos) > hex_threshold) * color_mult(pos), 1.0);
}

void main( void ) {

	vec2 mouse_pixel = mouse * resolution.xy;
	float res_min = min(resolution.x, resolution.y);
	vec2 away_from_center = (mouse_pixel - gl_FragCoord.xy) / res_min;
	
	float phi01 = mod(atan(away_from_center.y, away_from_center.x) / two_pi + rot_coeff * time, 1.0);
	float r01 = mod(proj_coeff / dot(away_from_center, away_from_center) + move_coeff * time, 1.0);
	
	vec2 pos = vec2(phi01, r01);
	gl_FragColor = fog_coeff * pow(length(away_from_center), fog_exp) * texture(pos/vec2(0.57735, 1.)*20.);
}