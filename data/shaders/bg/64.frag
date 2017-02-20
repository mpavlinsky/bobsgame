#ifdef GL_ES
precision mediump float;
#endif

// Tenjix

#define PI 3.1415926535897932384626433832795

uniform float time;
uniform vec2 resolution;

const float position = 0.0;
const float scale = 0.27;
const float intensity = 0.6;
const float speed = 2.5;

float band(vec2 pos, float amplitude, float frequency) {
	float wave = scale * amplitude * sin(10.0 * PI * frequency * pos.x + time * speed) / PI;
	wave = wave + cos((2.0+pos.x*PI*.1)*450.)*0.03;
	float light = clamp(amplitude * frequency * 0.002, 0.001 + 0.001 / scale, 5.0) * scale / abs(wave - pos.y);
	return light;
}

void main( void ) {

	vec3 color = vec3(0.9, 0.0, 0.5);
	color = color == vec3(0.0)? vec3(0.5, 0.5, 1.0) : color;
	vec2 pos = (gl_FragCoord.xy / resolution.xy);
	pos.y += - 0.5 - position;
	
	float spectrum = 0.0;

	spectrum += band(pos, 2.0*0.1, 0.2);
	spectrum += band(pos, 2.0*0.2, 0.2);
	spectrum += band(pos, 2.0*0.3, 0.2);
	spectrum += band(pos, 2.0*0.4, 0.2);
	spectrum += band(pos, 2.0*0.5, 0.2);
	spectrum += band(pos, 2.0*0.6, 0.2);
	spectrum += band(pos, 2.0*0.7, 0.2);
	spectrum += band(pos, 2.0*0.8, 0.2);
	spectrum += band(pos, 2.0*0.9, 0.2);
	spectrum += band(pos, 2.0*1.0, 0.2);
	spectrum += band(pos, 2.0*1.1, 0.2);
	spectrum += band(pos, 2.0*1.2, 0.2);
	
	gl_FragColor = vec4(color/2.0 * spectrum, spectrum/2.0);
	
}