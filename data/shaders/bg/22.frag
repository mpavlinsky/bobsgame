#ifdef GL_ES							//Definim una de les llibreries que usarem
precision mediump float;
#endif
uniform float time;
uniform vec2 resolution;
//vec3 SUN_FONS = vec3(1.,0.25,0.1);		//Atarongat
vec3 SUN_FONS = vec3(0.7,0,1.0);		//Atarongat
//vec3 SUN_SIN = vec3(0.25,0.5,1.);		//Blavos
vec3 SUN_SIN = vec3(0,1,0);		//Blavos
const float ssamount = 2.; 				//Element per a produir "supersampling" i evitar aliasing en l'imatge resultant.
const float mblur = 1.; 				//Genera motion blur, no funciona del tot bé.
float sqr(float a) {
	return a*a;
}
void main( void ) {
	vec3 color = vec3(0.);
	vec2 aspect = vec2(1.,resolution.y/resolution.x );
	for(float blur = 0.; blur < mblur; blur += 1.){
		float timed = blur/mblur/4.+float(time)*5.;
		for(float x = 0.; x < ssamount; x+=1.){
			for(float y = 0.; y < ssamount; y+=1.){
				vec2 position = gl_FragCoord.xy+vec2(x/ssamount,y/ssamount);
				position /= resolution;
				position -= 0.5;
				position.x+=1.;
				position.x*=2.;
				float d = length(position);
				color += 0.1/length(vec2(.01,.5*position.y*sqr(position.x)+sin(pow(position.x,3.)*8.+sqr(position.x)*32.+timed)*sin(position.y*sqr(position.x)*16.+sin(timed/8.))))*SUN_FONS;		//Molts cercles en una esfera que va rotant.
				color += 0.05/length(vec2(.01,2.*position.y*sqr(position.x)+sin(pow(position.x,3.)*2.+sqr(position.x)*8.+timed*4.)))*SUN_SIN;		//Sinus del cercle
			}	
		}
	}
	gl_FragColor = vec4(color/sqr(ssamount)/mblur, 1.0);
}