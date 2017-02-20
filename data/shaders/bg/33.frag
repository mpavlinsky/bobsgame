#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

void main( void ) {

	vec2 posScale = vec2(resolution.y,resolution.x)/sqrt(resolution.x*resolution.y);
	vec2 position = (( gl_FragCoord.xy / resolution.xy ) );
	
	float sum = 0.;
	float sum2 = 0.;
	float sum3 = 0.;
	float t = time * 0.2;
	float sum4 = 0.;
	
	for (float i = 0.; i < 10.; i++) {
		float vy = (fract(i*.13)-.5);
		float vx = sqrt(1.-vy*vy)-.8;
		float y2 = i*.161235+t*vy+.5;
		float x2 = i*i*.3165+.5+t*vx+.5;
		vec2 p0 = (fract(position-vec2(x2,y2))-vec2(.5));
		vec2 p = p0/posScale;
		float sp = (fract(i/2.)*4.-1.);
		float r = length(p);
		float e = (.5-abs(p0.x))*(.5-abs(p0.y))/(r*r);
		float ph = (p.x*vx+p.y*vy)*350.;
		sum += cos(ph)*e;
		sum2 += sin(ph)*e;
		sum3 += sp*sqrt(e);
		sum4 += e;

	}
	
	float color = sqrt(sum*sum+sum2*sum2)/sum4;
	sum3 = atan(sum3*.1)/1.571;
	//gl_FragColor = vec4(color*sqrt(1.+sum3)*.5,abs(color)-.5,color*sqrt(1.-sum3)*.7, 1.0 );
	gl_FragColor = vec4(color*sqrt(1.+sum3)*.3,color*sqrt(1.-sum3)*0.8,abs(color)-.3, 1.0 );
}