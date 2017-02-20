#ifdef GL_ES
precision mediump float;
#endif

//Energize!
//Timing is still off...

//Added Rotation
//Added some color
//Added mouse input

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

vec2 rotate(vec2 point, float rads) {
	float cs = cos(rads);
	float sn = sin(rads);
	return point * mat2(cs, -sn, sn, cs);
}	


void main( void ) {
	
	float rads = radians(time*3.15);
	vec2 position = ( gl_FragCoord.xy -  resolution.xy*.5 ) / resolution.x;
	
	// 256 angle steps
	float angle = atan(position.y,position.x)/(2.*3.14159265359)+rads;
	angle -= floor(angle);
	float rad = length(position);
	
	float color = 0.0;
	for (int i = 0; i < 10; i++) {
		angle += mouse.x*0.1;
		float angleFract = fract(angle*256.);
		float angleRnd = floor(angle*256.)+1.;
		float angleRnd1 = fract(angleRnd*fract(angleRnd*.7235)*45.1);
		float angleRnd2 = fract(angleRnd*fract(angleRnd*.82657)*13.724);
		float t = time+angleRnd1*10.0+ sin(time*0.5);
		float radDist = sqrt(angleRnd2+float(i));
		
		float adist = radDist/rad*.1;
		float dist = (t*.1+adist);
		dist = abs(fract(dist)-.5);
		color += max(0.01,1.5-dist*40./adist)*(.5-abs(angleFract-.5))*5./adist/radDist;
		
		angle = fract(angle+.61);
	}

	float color1 = color*rad;
	gl_FragColor = vec4( color1,color1,color,color1)*.3;
}