#ifdef GL_ES
precision mediump float;
#endif
// dashxdr was here 20120228
// whoops the rainbow colors weren't correct...
// ugh, can't stand the previous version... too dizzy

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;


float rainbow(float x)
{
	x=fract(0.16666 * abs(x));
	if(x>.5) x = 1.0-x;
	return smoothstep(.166666, .333333, 0.7);
}

void main( void ) {

	vec2 position = ( 2.0*gl_FragCoord.xy - resolution) / resolution.xx;

	//vec3 color = vec3(0.0);

	float r = length(position);
	float a = atan(position.y, position.x);

	float b = a*3.0/3.14159;
	//color = vec3(0.0, 0.0, 1.0);

	float t = .5*(1.0 + cos(a + 40.0 * r * (1.0 + sin(a*20.0)*.1) - time*3.0) * (5.0 / (r+5.0)));
	float rainbowColor = t;//rainbow(a);
	float everyOther = (t<0.5) ? 0.0 : 1.0;
	
	
	
	//gl_FragColor.rgba = vec4(color*t, 1.0);
	
	if(everyOther==0.0)gl_FragColor.rgba = vec4(0.85*rainbowColor,0,1.0*rainbowColor,1.0);
	else gl_FragColor.rgba = vec4(0,0.6*rainbowColor,0, 1.0);

}