//MG
#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

vec2 noise(vec2);
float perlin(vec2);
float fbm(vec2);
float pattern( in vec2 );

void main() {
	vec2 p=(gl_FragCoord.xy/resolution.y)*10.0;
	p.x-=resolution.x/resolution.y*5.0;p.y-=5.0;
	float dist,f1,f2;
	vec2 f3=vec2(1.0,1.0);
	
	float fx=(fbm(p)+0.5)/2.0;
	f1=0.5/(abs(sin(p.x+time)*2.0-p.y));
	f2=0.5/(abs(cos(p.x-time)*4.0-p.y));
	f1*=fx*f3.x;f2*=fx*f3.y;
	//gl_FragColor=vec4(f1+f2*4.0,f1*2.0+f2*2.0,f1*4.0+f2,1.0);
	gl_FragColor=vec4(f1*2.0+f2*2.0,f1+f2*4.0,f1*4.0+f2,1.0);
}

float fbm(vec2 p) {
	float tme=time*0.5;
	float f=0.0;
	f+=perlin(p+tme);
	f+=perlin(vec2(p.x+tme*0.5,p.y)*2.0)*0.5;
	f+=perlin(vec2(p.x,p.y-tme*0.25)*4.0)*0.25;
	f+=perlin((p-tme*0.125)*8.0)*0.125;
	f+=perlin((p+tme*0.0625)*16.0)*0.0625;
	return f/1.0;
}

float perlin(vec2 p) {
	vec2 q=floor(p);
	vec2 r=fract(p);
	float s=dot(noise(q),p-q);
	float t=dot(noise(vec2(q.x+1.0,q.y)),p-vec2(q.x+1.0,q.y));
	float u=dot(noise(vec2(q.x,q.y+1.0)),p-vec2(q.x,q.y+1.0));
	float v=dot(noise(vec2(q.x+1.0,q.y+1.0)),p-vec2(q.x+1.0,q.y+1.0));
	float Sx=3.0*(r.x*r.x)-2.0*(r.x*r.x*r.x);
	float a=s+Sx*(t-s);
	float b=u+Sx*(v-u);
	float Sy=3.0*(r.y*r.y)-2.0*(r.y*r.y*r.y);
	return a+Sy*(b-a);
}

vec2 noise(vec2 n) {
	vec2 ret;
	ret.x=fract(sin(dot(n.xy, vec2(12.9898, 78.233)))* 43758.5453)*2.0-1.0;
	ret.y=fract(sin(dot(n.xy, vec2(34.9865, 65.946)))* 28618.3756)*2.0-1.0;
	return normalize(ret);
}