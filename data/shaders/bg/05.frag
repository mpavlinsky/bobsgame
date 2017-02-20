#ifdef GL_ES
precision mediump float;
#endif

#define PI 3.14159
#define TAU 6.28318

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

vec3 arc(vec2 pos,vec4 btrir,float ang,vec2 p,vec3 color);

vec3 hsv2rgb(float h,float s,float v) {
	return mix(vec3(1.),clamp((abs(fract(h+vec3(3.,2.,1.)/3.)*6.-3.)-1.),0.,1.),s)*v;
}

void main( void ) {

	vec2 p = gl_FragCoord.xy;
	
	vec3 color = vec3(0.0);
	
	for(float i = 1.0;i < 16.0;i++)
	{
		float j = i-1.0;
		color += arc(resolution/2.,vec4((0.0),(PI),j*16.0,(j+1.0)*16.0),time*2.0/(((fract(j*0.4)-.5)*2.0)*4.0),p, hsv2rgb(i/14.0,1.0,1.0));
	}
	//color = closestColor(color);
	gl_FragColor = vec4(vec3(color*0.7),1.0);
	
	//gl_FragColor *= vec4(0.5,0.5,0.5,1.0);
}
//btrir = bottom angle, top angle, inner radius, outer radius
vec3 arc(vec2 pos,vec4 btrir,float ang,vec2 p,vec3 color)
{
	vec2 c = resolution/2.;
	
	float d = distance(p,vec2(c))/3.;
	
	float a = atan(p.x-c.x,p.y-c.y)+PI+ang;
	
	a = mod(a,TAU);
	
	if(a > btrir.x && a < btrir.y && d > btrir.z && d < btrir.w)
	{
		float diff = d-btrir.z;
		float rtrn = smoothstep(0.0,1.0,pow(sin(diff/16.*PI),0.25));
		
		float eb = 4.0;
		if(a < btrir.x+(PI/eb)) 
		{
			float ad = (btrir.x+(PI/eb))-a;
			rtrn *= 1.0-ad/(PI/eb);
		}
				
		if(a > btrir.y-(PI/eb))
		{
			float ad = a - (btrir.y-(PI/eb));
			rtrn *= 1.0-ad/(PI/eb);
		}
		return color*rtrn;
	}
	
	return vec3(0.0);
}
