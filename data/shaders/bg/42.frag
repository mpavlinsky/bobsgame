#ifdef GL_ES
precision mediump float;
#endif

// Posted by Trisomie21
// Switch MODE to test different configurations

uniform float time;
uniform vec2 resolution;

#define DOTS	 	0
#define STARFIELD 	1
#define BLUBBER 	2
#define SNOW	 	3

#define MODE 		2


#if MODE==DOTS
const float LAYERS	= 5.0;
const float SPEED	= 0.001;
const float SCALE	= 100.0;
const float DENSITY	= 0.6;
const float SATURATION	= 0.9;
const float BRIGHTNESS	= 10.0;
const float TWIST	= 0.0;
       vec2 ORIGIN	= resolution.xy*.5;
const vec3  PALETTE	= vec3(0.25, 1.0, -0.5);
#endif

#if MODE==STARFIELD
const float LAYERS	= 6.0;
const float SPEED	= 0.0004;
const float SCALE	= 1000.0;
const float DENSITY	= 0.98;
const float SATURATION	= 2.0;
const float BRIGHTNESS	= 40.0;
const float TWIST	= 0.0;
       vec2 ORIGIN	= resolution.xy*.5;
const vec3  PALETTE	= vec3(1.0, 1.0, 1.0);
#endif

#if MODE==BLUBBER
const float LAYERS	= 3.0;
const float SPEED	= 0.01;
const float SCALE	= 20.0;
const float DENSITY	= 0.1;
const float SATURATION	= 1.5;
const float BRIGHTNESS	= 5.0;
const float TWIST	= 0.0;
       vec2 ORIGIN	= resolution.xy*.5;
const vec3  PALETTE	= vec3(0.25, -1.0, -0.5);
#endif

#if MODE==SNOW
const float LAYERS	= 10.0;
const float SPEED	= 0.0001;
const float SCALE	= 1000.0;
const float DENSITY	= 0.9;
const float SATURATION	= 1.0;
const float BRIGHTNESS	= 10.0;
const float TWIST	= 0.04;
       vec2 ORIGIN	= vec2(resolution.x*.5,resolution.y*1.5);
const vec3  PALETTE	= vec3(1.0, 1.0, 1.0);
#endif

float rand(vec2 co){ return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453); }

void main( void ) {
	
	vec2   pos = gl_FragCoord.xy - ORIGIN;
	float dist = length(pos) / resolution.y;
	vec2 coord = vec2(pow(dist, 0.1), atan(pos.x, pos.y) / (3.1415926*2.0));
	
	vec3 color = vec3(0.0);
	for (float i = 0.0; i < LAYERS; ++i)
	{
		float t = i*10.0 + time*i*i;
		float r = coord.x - (t*SPEED);
		float c = fract(sin(time*.1+i)*TWIST + coord.y + i*.125);
		vec2  p = vec2(r, c*.5);
		vec2 uv = fract(p*SCALE);
		float a = 1.0-length(uv*2.0-1.0);
		vec3  m = fract(r*SCALE * PALETTE)*SATURATION+i*.2;
		float d = (rand(floor(p*SCALE))-DENSITY)*BRIGHTNESS;
		d = clamp(d*dist, 0.0, 1.0);
		color = max(color, a*m*d);
	}

	gl_FragColor =  vec4(color, 1.0);
}