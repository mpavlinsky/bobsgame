
#ifdef GL_ES
precision mediump float;
#endif
 
uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

#define PI 3.1415927
#define PI2 (PI*2.0)

// http://glsl.heroku.com/e#7109.0 simplified by logos7@o2.pl
// different colors by @hintz

void main(void)
{
	vec2 position = (sin(time*0.3)+1.0) * 32.0 * ((2.0 * gl_FragCoord.xy - resolution) / resolution.xx);

	float r = length(position);
	float a = atan(position.x, position.y) + PI;
	float d = r - a + PI2;
	float n = PI2 * float(int((d / PI2)));
	float da = a + n;
	float pos = (PI*sin(0.02)*0.5*4.0*da * da - sin(time*0.5));
	vec3 norm;
	norm.xy = vec2(fract(pos) - .5, fract(d / PI2) - .5)*2.0;
	pos = floor(pos);
	float len = length(norm.xy);
	vec3 color = vec3(0.0);
	if (len < 1.0)
	{
		norm.z = sqrt(1.0 - len*len);
		vec3 lightdir = normalize(vec3(0.0, 1.0, 1.0));
		float dd = dot(lightdir, norm);
		dd = max(dd, 0.25);
		color = dd*vec3(0.8*cos(pos+2.0)+0.5, 0.5*cos(pos+4.0)+0.5, 0.8*cos(pos)+0.5);
		vec3 halfv = normalize(lightdir + vec3(0.0, 0.0, 1.0));
		float spec = dot(halfv, norm);
		spec = max(spec, 0.0);
		spec = pow(spec, 40.0);
		color += vec3(spec);
	}
	
	
	color *= 0.8;
	
	gl_FragColor = vec4( vec3( 0.7, 0.7, 0.7 ) * color, 1.0 );
	
	
}