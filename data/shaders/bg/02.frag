

#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

const float PI = 3.14159265358979323846264;
const float hbar = 1.05457172647e-34;
const float MASS = 2.;
	
vec3 hsv(float h,float s,float v) { return mix(vec3(1.),clamp((abs(fract(h+vec3(3.,2.,1.)/3.)*6.-3.)-1.),0.,1.),s)*v; }

float wavefn(int n, int m, vec2 pos) { 
	return 3. * sin(float(n) * PI * pos.x) * sin(float(m) * PI * pos.y); 
}
float omega(int n, int m) {
	float fn = float(n);
	float fm = float(m);
	
	return 0.2/**hbar*/*PI*PI*(fn*fn+fm*fm)/MASS;
}
vec2 phasor(float magnitude, float omega, float t) {
	float phase = omega*t;
	return magnitude*vec2(cos(phase), sin(phase));
}
vec2 cpxmult(vec2 a, vec2 b) {
	return vec2(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
}

void main( void ) {

float t = time * 5.0;

	vec2 pos = gl_FragCoord.xy / resolution.xy/2.;
	
	vec2 ret = vec2(0.);
ret += phasor(wavefn(14,13,pos), omega(14,13), t/1000.);
ret += phasor(wavefn(4,4,pos), omega(4,4), t/1000.);
	
	float hue = (atan(ret.x, ret.y) / (PI * 4.0));
	float value = exp(-sqrt(ret.x * ret.x + ret.y * ret.y));
	//gl_FragColor = vec4(hsv(0.1, 1.0, value), 1.0);
	gl_FragColor = vec4(hsv(0.4, 1.0, value), 1.0);
}