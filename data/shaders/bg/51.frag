#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

float noise(float s)
{
	
	return fract(cos(s*12354.123)*13.235235);
}


void main( void ) {

	vec2 p = ( gl_FragCoord.xy / resolution.xy ) -0.5;
	vec3 c=vec3(0);
	float a=(atan(p.x,p.y)*38.);
	float d=length(p);
	float rot=floor(cos(d*10.*2.*3.141))+.5;
	float lum=rot*floor(noise((a*0.005+floor(d*20.)+rot*time*0.1)*0.00005)*3.);
	lum=smoothstep(.01,.5,lum*cos(d*12.));
	c.x=d*lum;
	c.y=lum*0.5;
	c.z=lum/d*d;
	gl_FragColor = vec4( c, 1.0 );

}