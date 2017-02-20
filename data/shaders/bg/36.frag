#ifdef GL_ES
precision mediump float;
#endif

// just a basic template - @dist
// + fun

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;
uniform sampler2D backbuffer;

void main( void ) {
	vec2 position = ( gl_FragCoord.xy / resolution.xy );
	vec2 positionn = ( position - vec2(0.5)) / vec2(resolution.y/resolution.x,1.0)*2.0;
	float dist = distance(vec2(0.0), positionn);
	float dist2 = float(int(dist*6.0))/6.0; // 10 steps in 1.
	float angle = atan(positionn.y, positionn.x);

	float value;
	value = abs(2.0-dist2) * abs(sin(sin(dist2*time*-2.)+0.5*time*(1.0+dist2)+angle*1.5));
	vec3 color = pow(value, 2.0) * vec3(0.7,0.0,1.0) * 0.4;
	
	gl_FragColor = vec4( color, 1.0 );

}