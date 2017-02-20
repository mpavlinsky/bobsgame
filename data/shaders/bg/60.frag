#ifdef GL_ES
precision mediump float;
#endif

// posted by Trisomie21

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

const float pi_2_f = 3.1416*2.0;
const float lineTickness = 0.0;
const float lumaCount = 50.0;
const float hueCount = 50.0;

void main( void ) {

	vec2 position =  gl_FragCoord.xy - (resolution.xy/2.0);
	
	float d = length(position);
	
	float v = mod(d + time/20.0*resolution.x + resolution.x/(lumaCount*2.0), resolution.x/lumaCount);
	v = abs(v - resolution.x/(lumaCount*2.0)) - lineTickness;
	
	float angle = acos(position.y/d) / pi_2_f;
	if(position.x>0.0) angle += (0.5-angle)*2.0;
	angle += time/60.0;
	
	float unit = d * pi_2_f;
	float a = mod(angle*unit + unit/(hueCount*2.0) , unit/hueCount);
	a = abs(a - unit/(hueCount*2.0)) - lineTickness;
	a = clamp(a, 0.0, 1.0);

	angle += .05;
	float u = 100.0;
	float r = mod(angle*u + u/(5.0*2.0) , u/3.0);
	r = abs(r - u/(5.0*2.0)) - 1.0;
	r = clamp(r, 0.0, 1.0);

	d /= length(resolution.xy);
	v = min(v, a)*d;

	float dr = .2+(sin(time*1.1)+1.0)/8.0;
	float dg = .2+(sin(time*1.2)+1.0)/8.0;
	float db = .2+(sin(time*1.4)+1.0)/8.0;
	gl_FragColor = vec4(v/(r+dr),v/(r+dg),v/(r+db),1);
}