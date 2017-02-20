#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

// a raymarching experiment by kabuto
// fork by s1e

const int MAXITER = 20;

vec3 field(vec3 p) {
	p *= 0.1;
	float f = .1;
	for (int i = 0; i < 5; i++) {
		//p = p.yzx;
		p = p.yzx/0.93 * mat3(.5,.695 + 0.005*sin(time/135.0),0,-.6,0.6,0,cos(time/12.0)*0.05,0.05+0.00058*cos(time/7.0),1);
		p += vec3(.3,.5,.7)*float(i);
		p = abs(fract(p)-.5);
		p *= 2.4;
		f *= 2.0;
	}
	p *= p;
	return sqrt(p+p.yzx)/f-0.001;
}

void main( void ) {
	vec3 dir = normalize(vec3((gl_FragCoord.xy-resolution*0.5)/resolution.x,0.84));
	vec3 pos = vec3(0, 0, time/16.0);
	vec3 color = vec3(0);
	for (int i = 0; i < MAXITER; i++) {
		vec3 f2 = field(pos);
		float f = min(min(f2.x,f2.y),f2.z);
		
		pos += dir*f;
		color += float(MAXITER-i)/f2;
	}
	vec3 color3 = vec3(1.-1./(1.+color*(0.0066)));
	color3 = color3 * color3 * color3 * color3 * color3 * color3 * color3 * color3 * color3 * color3;
	//gl_FragColor = vec4(,1);
	
	
	
	//gl_FragColor = vec4(color3/2.0 + vec3(color3.g/color3.r*color3.b)/2.0, 1);
	gl_FragColor = vec4(color3*0.9 + vec3(color3.g/color3.r*color3.b)*0.1, 1);
	
	
}