#ifdef GL_ES
precision mediump float;
#endif

// Posted by Trisomie21

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;
uniform sampler2D backbuffer;

void main( void ) {

	float scale = resolution.y / 100.0;
	float ring = 50.0;
	float radius = resolution.x*2.0;
	float gap = scale*.8;
	vec2 pos = gl_FragCoord.xy - resolution.xy*.5;
	
	float d = length(pos);
	
	// Create the wiggle
	d += (sin(pos.y*0.25/scale+time)*sin(pos.x*0.25/scale+time*.5))*scale*2.0;
	
	// Compute the distance to the closest ring
	float v = mod(d + radius/(ring*2.0), radius/ring);
	v = abs(v - radius/(ring*2.0));
	v = clamp((v-gap)*.1, 0.0, 1.0)*.5;
	
	//gl_FragColor = vec4(v,v,v, 1.0);
	gl_FragColor = vec4(v,v,v, 1.0);
	
	{
	vec2 uv = gl_FragCoord.xy / resolution.xy;		
	vec2 d = 4./resolution;
	float dx = texture2D(backbuffer, uv + vec2(-1.,0.)*d).x - texture2D(backbuffer, uv + vec2(1.,0.)*d).x ;
	float dy = texture2D(backbuffer, uv + vec2(0.,-1.)*d).x - texture2D(backbuffer, uv + vec2(0.,1.)*d).x ;
	d = vec2(dx,dy)*resolution/1024.;
	gl_FragColor.z = pow(clamp(1.-1.5*length(uv  - vec2(.4,.6) + d*2.0),0.,1.),4.0);
	
	//gl_FragColor.y = gl_FragColor.z*0.5 + gl_FragColor.x*0.4;
	gl_FragColor.y = gl_FragColor.z*2.0 + gl_FragColor.x*1.4;
	gl_FragColor.rgb*=0.7;
	
	//float r = gl_FragColor.r;
	//float g = gl_FragColor.g;
	//float b = gl_FragColor.b;
	//gl_FragColor = vec4(g,r,b,1);
	
	}
}