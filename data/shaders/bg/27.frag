// Corrente Continua - 1k intro (win32)
// Zerothehero of Topopiccione
// 25/jul/2012

//@zerothehero: better formulas, visually improved

// mod by mojovideotech


#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;
const float di = 0.5772156649;
const float dh = 0.69314718;
const float twpi = 6.28318530718;
	
mat2 rotate2d(float _angle){
    return mat2(cos(_angle),-sin(_angle),
                sin(_angle),cos(_angle));
}


void main( void ) 
{
	float t = time*12.;
	float tt = time*0.005;
	vec2 p = ((gl_FragCoord.xy / resolution.xy )-0.5)*27.;
	p.x *= resolution.x/resolution.y;
	float a=0.,b=0.,c=0.,d=0.,e=0.;
	for (int i=-4; i<4; i++) {
		p = rotate2d(tt*-twpi)*p;
		float x = (p.x*di-p.y*dh*0.125);
		float y = (p.x*di*0.125+p.y*dh);
		c = (sin(x+t*(float(i))/18.0)+b+y+4.0);
		d = (cos(y+t*(float(i))/20.0)+x+a+3.0);
		e = (sin(y+t*(float(i))/17.5)+x-e+1.0);
		a -= .25/(c*c);
		b += .5/(d*d);
		e += .125;
	}
	gl_FragColor = vec4(log(-e+a+b-1.)/8.-0.2,log(-e-a-b-1.)/8.-0.2,log(e-a+b-1.)/5.-0.1, 1.0) ;

}