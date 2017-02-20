#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
uniform vec2 resolution;
#define q(a,b,c) (abs(fract(a/b)-.5)-c*.5)*b
#define u resolution
void main()
{
	vec3 p=vec3(0,-1,time);
	for(float i=-0.2;i<=1.;i+=.01){
		float r=length(p.xy),
		      d=.7+.3*cos(time/3.),
			a=q(r,3.,.2),b=q(p.z,1.,d),c=q((atan(p.y,p.x)+time*.3*cos(floor(r/3.))*sin(floor(p.z)*13.73))*r,(acos(.5)*r),d),
		      e=min(max(a,max(b,c)),.25),
		      s=3.*i*i-2.*i*i*i-i;
		p+=e*normalize(vec3((2.*gl_FragCoord.xy-u)/max(u.x,u.y),1));
		gl_FragColor=vec4(s,i*(i-2.),-2.*s,1)*2.+i+1./(1.+abs(max(max(min(a,b),min(b,c)),min(a,c))*20.)*2.);
		if(e<.001)break;
	}
}
