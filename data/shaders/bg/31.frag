#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

#define PI 3.14159
#define TWO_PI (PI*2.0)
#define N 10.0

void main( void ) {
	vec2 v = (gl_FragCoord.xy - resolution/2.0) / min(resolution.y,resolution.x) * 10.0;

	float col = 0.0;
	
	for(float i = 0.0; i < N; i++) {
	  	float a = time*0.01+tan(time*0.001)+2.0;
		col += cos( TWO_PI*(v.x * cos(a*i) + v.y *tan(a*i)*cos(a*i)))*max(sin(a*i),-0.5);
	}
	
	col /= N;

	//gl_FragColor = 2.0*vec4(col, col*8.0*tan(sin(col)), col*10.0*tan(col), 1.0);
	gl_FragColor = 2.0*vec4(col, col*4.0*tan(sin(col)), col*10.0*tan(col), 1.0);
}

// jh