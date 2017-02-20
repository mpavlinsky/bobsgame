#ifdef GL_ES
precision highp float;
#endif
// by @DonMilham

uniform float time;
uniform vec2 resolution;

void main( void ) {

	vec2 position = gl_FragCoord.xy / resolution.xy;
	float t = time + position.x;

	vec2 o, off;

	o = 1.0 - abs(2.0 * fract(15.0 * position) - 1.0);
	off = .5 * o + .4 * pow(o, vec2(8));
	float grid2 = .5 * max(off.x, off.y);

	o = 1.0 - abs(2.0 * fract(1.0 * position) - 1.0);
	off = .5 * o + .5 * pow(o, vec2(11));
	float grid1 = .5 * max(off.x, off.y);

	vec4 grid = vec4(0, .5 * grid2 + grid1, 0, 1);

	float f = clamp(1.0 - abs(position.y - .1 *sin(t*4.0)-.5), 0.0, 1.0);
	float func1 = pow(f, 22.0);

	vec4 func = .9 * vec4(func1, func1, func1, 1);
	gl_FragColor.r = 1.0; 
	gl_FragColor.g = 1.0; 
	gl_FragColor.b = 1.0; 
	gl_FragColor.a = 0.0;
	gl_FragColor = grid + func;



}