// added a bit of burning color

#ifdef GL_ES
precision highp float;
#endif

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;


// Trapped by curiouschettai

void main( void ) {  
	vec2 uPos = ( gl_FragCoord.xy / resolution.y );//normalize wrt y axis
	uPos -= vec2((resolution.x/resolution.y)/2.0, 0.5);//shift origin to center
	
	float multiplier = 0.001; // Grosseur
	const float step = 0.2; //segmentation
	const float loop = 30.0; //Longueur
	const float timeSCale = 1.05; // Vitesse
	
	vec3 blueGodColor = vec3(0.0);
	for(float i=1.0;i<loop;i++){		
		float t = time*timeSCale-step*i;
		vec2 point = vec2(0.75*sin(t), 0.5*sin(t*.02));
		point += vec2(0.75*cos(t*0.1), 0.5*sin(t*0.3));
		point /= 4. * sin(i);
		float componentColor= multiplier/((uPos.x-point.x)*(uPos.x-point.x) + (uPos.y-point.y)*(uPos.y-point.y))/i;
		blueGodColor += vec3(componentColor/2.0, componentColor/3.0, componentColor);
		//blueGodColor += vec3(componentColor/6.0, componentColor, componentColor/4.0);
	}
	
	
	vec3 color = vec3(0,0,0);
	color += pow(blueGodColor,vec3(1.1,1.1,0.8));
   
	
	gl_FragColor = vec4(color, 1.0);
}