#ifdef GL_ES
precision mediump float;
#endif

#extension GL_OES_standard_derivatives : enable

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;
uniform sampler2D backbuffer;


vec3 Hue(float hue){
	vec3 rgb = fract(hue + vec3(0.0, 2.0 / 3.0, 1.0 / 3.0));
	rgb = abs(rgb * 2.0 - 1.0);
	return clamp(rgb * 3.0 - 1.0, 0.0, 1.0);
}


vec2 trans(vec2 p){
	return vec2(p.x, p.y + sin(p.x + time*0.5) * 0.25);
}


void main( void ) {
	vec2 p = (gl_FragCoord.xy * 2.0 - resolution.xy) / min(resolution.x, resolution.y);
	vec3 destColor = vec3(0.0);
	
	if(length(mod(trans(p) * 10.0*sin(time*0.2)+1., 2.0) - 1.0) < 0.5) destColor = vec3(1.0);
	
	destColor *= Hue(length(p) - time*0.5);
	
	vec3 dist = vec3(length(p * 0.5));
	

	
	
	gl_FragColor = vec4(destColor, 1.0) + texture2D(backbuffer, (gl_FragCoord.xy / resolution)) * vec4(dist, 1.0);
}