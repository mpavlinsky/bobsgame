// by rotwang, overlapping pixels in different sizes.

// drifting around by @emackey

// "tunnelized" by kabuto

#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(11.9898,78.233))) * 43758.5453);
}

void main( void ) {

	vec2 dir = vec2(0, sin(time * 0.1) * .15);
	vec2 travel = time * vec2(-0.04, 0);
	float aspect = resolution.x / resolution.y;
	vec2 pos1 =  ( gl_FragCoord.xy - resolution.xy*.5) / resolution.y;
	pos1 = vec2(-.1/length(pos1),atan(pos1.y,pos1.x)/(2.*3.1415926));
	vec2 pos = pos1 + dir + travel;

	vec3 clr = vec3(0.0);
	for(int i=0;i<6;i++)
	{
		pos.y = fract(pos.y);
		float n = pow(10.0-float(i), 2.0)*2.;
		vec2 pos_z = floor(pos*n);
		float a = 1.0-step(0.2, rand(pos_z));
		float rr = rand(pos_z)*a;
		float gg = rand(pos_z+n)*a;
		float bb = rand(pos_z+n+n)*a;
		
		vec3 clr_a = vec3(rr, gg, bb);
		clr += clr_a*clr_a/4.0;
		pos += dir + travel;
	}
	
	
	gl_FragColor = vec4( sqrt(clr)/(1.-pos1.x*2.), 1.0 );
	
}