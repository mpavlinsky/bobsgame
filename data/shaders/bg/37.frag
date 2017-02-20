/**
 * @author scones
 *
 * galaxy playground - glsl
 *
 **/

#ifdef GL_ES
precision highp float;
#endif

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

const float SQRT_2 = 1.41421356237;
const float PI = 3.14159265359;
const float PI_2 = 1.57079632679;

float galaxy(vec2 p) {
	float p_length = length(p);
	float color_factor = SQRT_2 - p_length;
	
	float r = (atan(p.y, p.x) + PI) /PI;
	float ra = fract(r - p_length * 1.4 + time);

	float a   = smoothstep(0.7, 1.0, ra);
	float a_2 = smoothstep(0.2, 1.0, ra);
	float b   = smoothstep(0.7, 1.0, 1.0 - ra);
	float b_2 = smoothstep(0.2, 1.0, 1.0 - ra);
	
	float shade =  a + b;
	shade *= 0.5 * color_factor;
	float shade_2 = a_2 + b_2;
	shade_2 *= 0.5 * (color_factor + 0.5);

	return shade + shade_2;
}



void main( void ) {

	vec2 p = (gl_FragCoord.xy / resolution.xy)*2.0-1.0;
	p.x *= resolution.x / resolution.y;
	
	float shade = galaxy(p);
	vec3 clr = vec3(shade*0.2, shade*0.66,shade*1.0);
	
	gl_FragColor = vec4( clr, 1.0 );
}

