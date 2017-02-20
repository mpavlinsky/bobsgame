#ifdef GL_ES
precision mediump float;
#endif

// Tenjix

#define PI 3.1415926535897932384626433832795

uniform float time;
uniform vec2 resolution;
uniform vec2 mouse;

const float position = 0.0;
const float scale = 0.27;
const float intensity = 0.6;
const float speed = 2.5;

float band(vec2 pos, float amplitude, float frequency, vec2 mouse) {
	float wave = scale * amplitude * sin(10.0 * PI * frequency * pos.x + time * speed) / PI;
	wave = wave + cos((1.0+pos.x*PI*.1)*40.)*0.03;
	float light = clamp(amplitude * frequency * 0.002, 0.001 + 0.001 / scale, 5.0) * scale / abs(wave - pos.y);
	return light;
}

void main( void ) {

	vec3 color = vec3(0.4, 0.0, 0.9);
	vec2 uv = (gl_FragCoord.xy / resolution.xy);
	vec2 pos = uv;
	pos.y += - 0.5 - position;
	
	float spectrum = 0.0;
	
	for (float i=0.;i<10.;i++) {
		spectrum += band(pos, 2.0*((i+1.)/10.), 0.2, mouse);
		//if (uv.x*40.<i+1.) { break; }
	}
	
	gl_FragColor = vec4(color/2.0 * spectrum, spectrum/2.0);
	
}