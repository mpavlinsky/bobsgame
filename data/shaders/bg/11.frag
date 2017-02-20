/**
 * @author scones
 *
 * galaxy playground - glsl
 * + background stars found at http://glsl.heroku.com/e#5454.15 
 **/

// logos7@o2.pl - rottion added

#ifdef GL_ES
precision highp float;
#endif

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

const float SQRT_2 = 1.41421356237;
const float PI = 3.14159265359;
const float PI_2 = 1.57079632679;
const float spiral_coefficient = 1.78;
const float SPEED	= 0.015;
const float BRIGHTNESS	= 20.0;
  vec2 ORIGIN	= resolution.xy*.5;


const float seed = 0.1;

const float max_red = 210.0 / 255.0;

float rand(vec2 co){
	// implementation found at: lumina.sourceforge.net/Tutorials/Noise.html
	co.x += seed;
	return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 434658.5453116487577816842168767168087910388737310);
}

float noise2f( in vec2 p )
{
	vec2 ip = vec2(floor(p));
	vec2 u = fract(p);
	// http://www.iquilezles.org/www/articles/morenoise/morenoise.htm
	u = u*u*(3.0-2.0*u);
	//u = u*u*u*((6.0*u-15.0)*u+10.0);
	
	float res = mix(
		mix(rand(ip),  rand(ip+vec2(1.0,0.0)),u.x),
		mix(rand(ip+vec2(0.0,1.0)),   rand(ip+vec2(1.0,1.0)),u.x),
		u.y)
	;
	return res*res;
	//return 2.0* (res-0.5);
}

float fbm(vec2 c) {
	float f = 0.0;
	float w = 1.0;
	for (int i = 0; i < 4; i++) {
		f+= w*noise2f(c);
		c*=2.0;
		w*=0.5;
	}
	return f;
}

float ft() {
	float t = time + 6000.0;
	t = (1.0/ t ) * 10000.0;
	return t;
}


float pattern(  vec2 p, out vec2 q, out vec2 r ) {
	q.x = fbm( p  +0.00*time);
	q.y = fbm( p + vec2(1.0));
	
	r.x = fbm( p +1.0*q + vec2(1.7,9.2)+0.15);
	r.y = fbm( p+ 1.0*q + vec2(8.3,2.8)+0.126);
	return fbm(p +1.0*r + 0.00000* time);
}


float parting(float part) {
	float result = part;
	if (part < 0.5) {
		result = 0.5;
	} else {
		result *= 2.0;
		result -= 1.0;
	}
	return result;
}

float light_density(vec2 p, float p_length) {
	float color_factor = SQRT_2 - p_length + 0.0;
	
	float r = (atan(p.y, p.x) + PI) / (PI);

	float result;
		

	float part_1 = fract(r  - sqrt(p_length) * spiral_coefficient);
	float part_2 = 1.0 - part_1;
	float spiral = parting(part_1) + parting(part_2);

	vec2 foo, bar, moo, meh;
	float noisy = fbm(vec2(spiral, p_length)) ;
	noisy *= noisy * noisy;
	float general_noise = fbm(p) / 1.8;
	result = (spiral * noisy) * color_factor + general_noise * (color_factor + 0.1);

	return result;
}

vec3 star_distribution(float luminosity, float dist) {
	float rand_dist = fbm(vec2(luminosity, dist));
	float rand_dist_2 = fbm(vec2(dist));
	float red   = clamp(80.0/255.0 * (dist) , 170.0/255.0, 1.0) * (luminosity);
	float green = clamp(190.0/255.0 * (dist), 170.0/255.0, 1.0) * (luminosity);
	float blue  = clamp(2.0 * dist, 100.0/255.0, 1.0) * (luminosity);
	// Background stars
	vec2   pos = gl_FragCoord.xy - ORIGIN;
	vec2 coord = vec2(pow(dist, 0.1), atan(pos.x, pos.y) / (PI*2.0));
	
	float a = pow((1.0-dist),20.0);
	float t = time*-.01;
	float r = coord.x - (t*SPEED);
	float c = fract(a+coord.y + 0.0*.543);
	vec2  p = vec2(r, c*.5)*4000.0;
	vec2 uv = fract(p)*2.0-1.0;
	float m = clamp((rand(floor(p))-.9)*BRIGHTNESS, 0.0, 1.0);
	float star =  clamp((1.0-length(uv*2.0))*m*dist, 0.0, 1.0);
	
	return vec3(red+star,green+star,blue+star);
}

vec3 galaxy(vec2 p) {
	float p_length = length(p) - 0.000;
	float result;

	result = light_density(p, p_length);

	return star_distribution(result, p_length);
	
	return vec3(result);
}



void main( void ) {



	vec2 p = (gl_FragCoord.xy / resolution.xy)*2.0-1.0;
	
	p/=1.5;
	
	p.x *= resolution.x / resolution.y;
	float c = max(1.-length(p)*1., 0.);
	float c2 = max(1.-length(p * vec2(.25, 2.))*2., 0.);
	vec3 core = c*c * vec3(1., 1., 1.) + c2*c2 * vec3(.5, .5, 1.);
	float fc = cos(time*0.5);
	float fs = sin(time*0.5);

	vec2 pp = vec2(fc * p.x - fs * p.y, fc * p.y + fs * p.x);
	
	vec3 clr = galaxy(pp);
	
	float r = fbm(vec2(cos(time/12.),sin(time/11.)));
	float g = fbm(vec2(sin(time/12.),sin(time/4.)));
	float b = fbm(vec2(sin(time/21.),cos(time/10.)));

	vec3 spinColor = vec3(r,g,b);
	
	vec3 bgColor = vec3(clr);
	
	vec3 tclr = (bgColor*0.8)+(spinColor*0.1);
	

	
	gl_FragColor = vec4(tclr, 1.0);

}

