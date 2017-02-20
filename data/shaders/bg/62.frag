
#ifdef GL_ES
precision mediump float;
#endif

#extension GL_OES_standard_derivatives : enable

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

const float PI = 3.1415;
const vec3 PINK = vec3(1.0, 0.3, 0.7);

float intensity = 0.01;
float size = 1.0;
float offset = 0.5;

void main( void ) 
{
	vec2 p = (gl_FragCoord.xy * 2.0 - resolution)/ min(resolution.x, resolution.y);
	vec3 color = vec3(0.0);
	vec3 colorfull = vec3(abs(sin(time)), abs(cos(time/1.0)), abs(sin(time)));
	size = abs(cos(time/10.0));
	offset = abs(sin(time/10.0));
	for(int i = 0; i < 10; i++)
	{
		float x = cos(time/100.0 * float(i) * PI/5.0)  * offset;
		float y = sin(time/100.0 * float(i) * PI/5.0)  * offset;
		color += vec3( pow( intensity / (length(p + vec2(x,y) ) - size) , 1.0) );
	}
	gl_FragColor = vec4(vec3(color * colorfull) ,1.0);
}