#ifdef GL_ES
precision highp float;
#endif

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

// added a bit of burning color

// Trapped by curiouschettai

void main( void ) {  

	vec2 res = resolution;

	vec2 uPos = ( gl_FragCoord.xy / res.y );//normalize wrt y axis
	uPos -= vec2((res.x/res.y)/2.0, 0.5);//shift origin to center
	
	float multiplier = 0.023; // Grosseur
	const float seg = 1.0; //segmentation
	const float loop = 5.0; //Longueur
	const float timeSCale = 0.55; // Vitesse
	
	vec3 blueGodColor = vec3(0);
	
	for(float i=1.0;i<loop;i++){		
		float t = time*timeSCale-seg*i;
		vec2 point = vec2(0.95*sin(t), 0.5*sin(t*.2));
		point += vec2(1.65*cos(t*0.1), 0.5*sin(t*.9));
		point /= 4. * sin(i);
		float componentColor= multiplier/((uPos.x-point.x)*(uPos.x-point.y) + (uPos.y-point.y)*(uPos.y-point.y))/i;
		
		//blueGodColor += vec3(componentColor/7.0, componentColor/9.0, componentColor);
		blueGodColor += vec3(componentColor/2.0, componentColor/9.0, componentColor);
	}
	
	
	vec3 color = vec3(0,0,0);
	color += pow(blueGodColor,vec3(0.8,1.0,1.1));
   
	
	gl_FragColor = vec4(color, 1.0);
}