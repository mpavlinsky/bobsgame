#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

void main( void ) 
{

	vec2 p = ( gl_FragCoord.xy / resolution.xy )-0.5;
	float c = 0.0;
	float a=atan(p.x,p.y)*11.;
	float d=3.5/length(p);
	c=(atan(cos(d-a+time)*2.)*6./pow( (d),1.14 ));
	gl_FragColor = vec4( vec3(2.,1.5,8)*vec3( c*c, c*c-c, c*c*c/(1.+c) ), 1.0 );
	gl_FragColor *= vec4(0.5,0.5,0.5,1.0);

}