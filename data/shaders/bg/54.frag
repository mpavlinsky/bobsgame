#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;
uniform sampler2D backbuffer;

#define speed 0.25

/*
 * Basic tunnel effect.
 * Thanks to Adrian Boeing for his tutorial at http://adrianboeing.blogspot.com.ar/2011/01/webgl-tunnel-effect-explained.html
 */

// added http://glsl.heroku.com/e#7892.17 by @hintz

// feature switches:
// #define hole 
//#define spikes
#define acryl
 //#define fading

float circle(vec2 center, float radius, vec2 position)
{
	float length = distance(position, center);

#ifdef spikes
	radius*=1.0-0.1/(0.8+0.1/(0.9-abs(sin(time-7.5*atan(position.y-center.y, position.x-center.x)))));
#endif
	
#ifdef acryl
	return length < radius ? sin(pow(length / radius, 40.0) * 3.0 + 0.3) : 0.0;
#else
	return length < radius ? 1.0-(pow(length / radius, 4.0)) : 0.0;
#endif
}

#ifdef hole
float circle2(vec2 center, float radius, vec2 position)
{
	float length = distance(position, center);
	
	radius*=0.3+0.21/(1.0+abs(sin(2.5/4.5*time-2.5*atan(position.y-center.y, position.x-center.x))));
	
	return length < radius ? sin(pow(length / radius, 20.0) * 3.0 + 0.3) : 0.0;
}
#endif

float c = cos(0.01*sin(time*0.1));
float s = sin(0.01*sin(time*0.1));
vec2 rotate(vec2 p)
{
	return vec2(c*p.x-s*p.y, c*p.y+s*p.x);
}
	
vec4 texture(vec2 position)
{
	float r = circle(vec2(sin(time*1.01), cos(time*0.98)), 1.0+sin(time*.9), position);
	float g = circle(vec2(cos(time*0.94), sin(time*0.97)), 1.0+sin(time*.8), position);
	float b = circle(vec2(sin(time*0.93), sin(time*0.99)), 1.0+sin(time*.7), position);
	float m = circle(vec2(-cos(time*1.02), -sin(time*0.96)), 1.0+sin(time*.6), position);
	float y = circle(vec2(-sin(time*0.92), -sin(time*1.03)), 1.0+sin(time*.5), position);
	float w = circle(vec2(-sin(time*1.05), cos(time*0.95)), 1.0+sin(time)*.4, position);
	float o = circle(vec2(cos(time*0.91), -cos(time*1.04)), 1.0+sin(time)*.3, position);
#ifdef hole
	r -= circle2(vec2(sin(time*1.01), cos(time*0.98)), 1.0+sin(time*.9), position);
	g -= circle2(vec2(cos(time*0.94), sin(time*0.97)), 1.0+sin(time*.8), position);
	b -= circle2(vec2(sin(time*0.93), sin(time*0.99)), 1.0+sin(time*.7), position);
	m -= circle2(vec2(-cos(time*1.02), -sin(time*0.96)), 1.0+sin(time*.6), position);
	y -= circle2(vec2(-sin(time*0.92), -sin(time*1.03)), 1.0+sin(time*.5), position);
	w -= circle2(vec2(-sin(time*1.05), cos(time*0.95)), 1.0+sin(time)*.4, position);
	o -= circle2(vec2(cos(time*0.91), -cos(time*1.04)), 1.0+sin(time)*.3, position);

	r = abs(r);
	g = abs(g);
	b = abs(b);
	m = abs(m);
	y = abs(y);
	w = abs(w);
	o = abs(o);
#endif	
	
#ifdef fading
	return vec4(r+y+m+o+w, g+y+0.5*o+w, b+m+w, 1.0)*0.06+texture2D(backbuffer, 0.995*rotate(gl_FragCoord.xy-0.5*resolution)/resolution+0.5)*0.95;
#else
	return vec4(r+y+m+o+w, g+y+0.5*o+w, b+m+w, 1.0);
#endif
}

#define M_PI 3.14159265359

void main(void) 
{
	// Normalize coords from 0->1 with 0.5, 0.5 at center and correct the aspect ratio.
	vec2 position = (gl_FragCoord.xy - 0.5 * resolution) / resolution.y;
	
	position*=0.25;
	
	// Cartesian coords to polar coords.
	float a = atan(position.y, position.x);
	float r = length(position);
 	// r = -r * sin(a); // This would create a plane instead of a tunnel.
	
	// Use the coordinates to read from a texture.
	// If we normalize a from 0->1, we can use r and a to "radially" read the image. 
	// If instead we use 1/r, we can simulate depth.
	//
	// vec2 p = vec2(0.1 / r, a / M_PI);
	vec2 p = sin(M_PI*fract(vec2(0.1 / r + 0.5 * time, 2.5*(a + speed * time) / M_PI)));
	
	// Use r to create a little distance fog.
#ifdef fading
	gl_FragColor = vec4(texture(p*4.0-2.0));
#else
	gl_FragColor = 6.0*r*vec4(texture(p*4.0-2.0));
	gl_FragColor *=vec4(sin(time),cos(time),1.,1.);
#endif
}