#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

// Fake DOF spheres by Kabuto
// Move mouse vertically to control focal plane
// gngbng remix

void main( void ) {

	vec3 pos = vec3(0,0,-10);
	vec3 dir = normalize(vec3((gl_FragCoord.xy - resolution.xy*0.5) / resolution.x, 1.0));

	//vec3 color = vec3(0.05,0.1,0.15) * gl_FragCoord.y / resolution.y;
	vec3 color = vec3(0,0.3,0) * gl_FragCoord.y / resolution.y;
	
	for (float y = 5.0; y >= -8.0; y-=5.0) {
		for (float x = -3.0; x <= 3.0; x+=3.0) {
		
		//color = vec3(.08,0,.1) * gl_FragCoord.y / resolution.y;
		
			// 
			vec3 s = vec3(x+sin(time+y*0.7),sin(time+x*0.5+y*0.5),y+sin(time-x*0.7));
			float t = dot(s-pos,dir);
			vec3 diff = (pos+t*dir-s)*3.0;
			float dist = length(diff);
			
			
			if(dist<0.1)color = vec3(0.2,0,0.15) * gl_FragCoord.y / resolution.y;
			
			// fake depth of field
			float dof = abs(1.0/(pos.z-s.z)-mouse.y*0.2+0.2)*2.0;
			float dofdist = (length(diff)-1.0)/dof;
			dofdist = max(-1.0,min(1.0,dofdist));
			dofdist = sign(dofdist)*(1.0-pow(1.0-abs(dofdist),1.5));
			float invalpha = dofdist*0.5+0.5;
			color = color*invalpha*0.995 + vec3(.7,0,0.8)*pow(dist,2.0)
				* dot(normalize(diff+vec3(0,0,6)),vec3(1))*(1.-invalpha);
				
				
		}
	}
	
	
	
	gl_FragColor = vec4(vec3(color), 1.0 );
	
	//gl_FragColor *= vec4(0.8,0.0,1.0,1.0);

}