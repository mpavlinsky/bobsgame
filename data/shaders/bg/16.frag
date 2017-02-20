#ifdef GL_ES
precision mediump float;
#endif

// This should be the starting point of every effect - dist
// i have a fixation with lines - dist

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

//vec3 SUN_1 = vec3(0.714,0.494,0.357);
//vec3 SUN_2 = vec3(0.753,0.749,0.678);
//vec3 SUN_3 = vec3(0.741,0.745,0.753);
//vec3 SUN_4 = vec3(0.682,0.718,0.745);

vec3 SUN_1 = vec3(0.7,0,1);
vec3 SUN_2 = vec3(0.6,0,1);
vec3 SUN_3 = vec3(0,1,0);
vec3 SUN_4 = vec3(0,1,0.5);

vec2 complex_mul(vec2 factorA, vec2 factorB){
   return vec2( factorA.x*factorB.x - factorA.y*factorB.y, factorA.x*factorB.y + factorA.y*factorB.x);
}

vec2 complex_div(vec2 numerator, vec2 denominator){
   return vec2( numerator.x*denominator.x + numerator.y*denominator.y,
                numerator.y*denominator.x - numerator.x*denominator.y)/
          vec2(denominator.x*denominator.x + denominator.y*denominator.y);
}

vec2 torus_mirror(vec2 uv){
	return vec2(1.)-abs(fract(uv*.5)*2.-1.);
}

void main( void ) {
	vec2 aspect = vec2(1.,resolution.y/resolution.x);
	vec2 uv = (gl_FragCoord.xy / resolution.xy - 0.5)*aspect;
	float mouseW = -atan((sin(time*0.1) - 0.5), (0.5 - 0.5));
	vec2 mousePolar = vec2(-cos(mouseW), sin(mouseW));
	vec2 offset = 0.5 + complex_mul((sin(time*0.1)-0.5)*vec2(-1.,1.)*aspect, mousePolar)*aspect*8. ;
	
	vec2 pos = (complex_div(mousePolar*vec2(0.2), uv) - offset).yx;
	pos.y = torus_mirror(pos).y*2. - 1.;
	pos.x-=resolution.x/resolution.y/2.0;

	vec2 position = pos;//(( gl_FragCoord.xy / resolution.xy ) - 0.5) / vec2(resolution.y/resolution.x, 1.0);
	vec3 color = vec3(0.);
	float angle = atan(position.y,position.x);
	float d = length(position);
	
	color += 0.05/length(vec2(.04,2.*position.y+sin(position.x*4.+time*2.)))*SUN_1; // I'm sure there's an easier way to do this, this just happened to look nice and blurry.
	color += 0.05/length(vec2(.06,3.*position.y+sin(position.x*4.+time*3.)))*SUN_2;
	color += 0.05/length(vec2(.10,5.*position.y+sin(position.x*4.+time*5.)))*SUN_3;
	color += 0.05/length(vec2(.14,7.*position.y+sin(position.x*4.+time*7.)))*SUN_4;
	gl_FragColor = vec4(color, 1.0);
}