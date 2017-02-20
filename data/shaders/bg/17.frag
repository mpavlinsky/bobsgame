#ifdef GL_ES
precision highp float;
#endif
 
// moded by seb.cc
 
uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;
 
const float COUNT = 3.0;
 
//MoltenMetal by CuriousChettai@gmail.com
//Linux fix
 
void main( void ) {  
	vec2 uPos = ( gl_FragCoord.xy / resolution.y );//normalize wrt y axis
	uPos -= vec2((resolution.x/resolution.y)/2.0, 0.5);//shift origin to center
	
	float vertColor = 0.0;
	for(float i=0.0; i<COUNT; i++){
		float t = time*(i*0.1+1.)/3.0 + (i*0.1+0.1); 
		uPos.y += sin(-t+uPos.x*2.0)*0.45 -t*0.3;
		uPos.x += sin(-t+uPos.y*5.0)*0.25 ;
		float value = (sin(uPos.y*10.0*0.5)+sin(uPos.x*10.1+t*0.3) );
		
		//float d=1./pow(distance(mouse,uPos),2.);
		
		float stripColor = 1.0/sqrt(abs(value));
		
		vertColor += stripColor/10.0;
	}
	
	float temp = vertColor;	
	vec3 color = vec3(temp*max(0.1,abs(sin(time*0.1))), max(0.1,temp*abs(sin(time*0.03+1.))), max(0.1,temp*abs(sin(time*0.02+3.))));	
	color *= color.r+color.g+color.b;
	gl_FragColor = vec4(color, 1.0);
}
