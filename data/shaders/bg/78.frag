
#ifdef GL_ES
precision mediump float;
#endif

#define PI2 (PI*2.0)

// http://glsl.heroku.com/e#7109.0 simplified by logos7@o2.pl
// different colors by @hintz


uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

const float PI = 3.1415926;
const float EPSILON = 0.1;

vec2 perspective(vec2 scaled) {
	float z = 1.2-scaled.y+cos((scaled.x)*scaled.y*6.)*.1;
	return vec2((scaled.x-.5)/z,sin((scaled.x-.5)*10./z)*.15+1./z)*.5;
}

float getval(vec2 car) {
	float r = sqrt(car.x * car.x + car.y * car.y);
	float theta = atan(car.y, car.x);
	
	return fract(time) * 2. + theta / (2. * PI) - r * 16.;
}

void main( void ) {
	vec2 mousepersp = perspective(mouse);
	vec2 vec = perspective(gl_FragCoord.xy / resolution.xy) - mousepersp;
	float val = getval(vec);
	float valx = getval(perspective((gl_FragCoord.xy + vec2(.01,0)) / resolution.xy) - mousepersp)-val;
	float valy = getval(perspective((gl_FragCoord.xy + vec2(0,.01)) / resolution.xy) - mousepersp)-val;
	float aa = sqrt(valx*valx+valy*valy)*250.;
	aa = aa > 200. ? 0. : atan(min(aa,PI*.4999))*.3;
	
	vec3 color = vec3(sqrt((1.-smoothstep(EPSILON-aa, EPSILON+aa, abs(fract(val)-.5)))/(1.+dot(vec,vec)*20.)));
	
	gl_FragColor = vec4(color, 1.0);
	
		vec2 position = (sin(time*0.3)+1.0) * 32.0 * ((2.0 * gl_FragCoord.xy - resolution) / resolution.xx);

	float r = length(position);
	float a = atan(position.x, position.y) + PI;
	float d = r + a + PI2;
	float n = PI2;// * float(int((d / PI2)));
	float da = a + n;
	float pos = (PI*sin(0.12)*1.5*1.0*da * da);
	vec3 norm;
	norm.xy = vec2(fract(pos) - 1.0, fract(d / PI2) - 1.0)*2.0;
	pos = floor(pos);
	float len = length(norm.xy);
	vec3 color2 = vec3(0.0);
	if (len < 1.0)
	{
		norm.z = sqrt(1.0 - len*len);
		vec3 lightdir = normalize(vec3(1.0, 1.0, 1.0));
		float dd = dot(lightdir, norm);
		dd = max(dd, 1.25);
		color2 = dd*vec3(1.0*cos(pos+2.0)+1.0, 1.0*cos(pos+4.0)+1.0, 1.0*cos(pos)+1.0);
		vec3 halfv = normalize(lightdir + vec3(0.0, 0.0, 1.0));
		float spec = dot(halfv, norm);
		spec = max(spec, 0.0);
		spec = pow(spec, 40.0);
		color2 += vec3(spec);
	}
	
	
	color2 *= 0.8;
	
	gl_FragColor *= vec4( vec3( 1.0, 1.0, 1.0 ) * color2, 1.0 );
}