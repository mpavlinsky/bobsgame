#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

vec2 R = resolution;
vec2 Offset;
vec2 Scale=vec2(0.002,0.002);
float Saturation = 0.01; // 0 - 1;


vec3 lungth(vec2 x,vec3 c){
       return vec3(length(x+c.r),length(x+c.g),length(c.b));
}

void main( void ) {
	
	vec2 position = (gl_FragCoord.xy - resolution * .5) / resolution.yy;
	float th = atan(position.y, position.x) / (1.0 * 3.1415926);
	float dd = length(position) + 0.005;
	float d = 0.9 / dd + time;
	
    	vec2 x = gl_FragCoord.xy;
   	x=x*Scale*R/R.x;
    	x+sin(x.yx*sqrt(vec2(1,9)))/1.;
	x+=sin(x.yx*sqrt(vec2(73,5)))/5.;
    	x+=sin(x.yx*sqrt(vec2(93,7)))/3.;
	
	vec3 uv = vec3(th + d, th - d, th + sin(d) * 0.45);
	float a = 0.5 + cos(uv.x * 3.1415926 * 1.0) * 0.5;
	float b = 0.5 + cos(uv.y * 3.1415926 * 1.0) * 0.5;
	float c = 0.5 + cos(uv.z * 3.1415926 * 6.0) * 0.5;
	vec3 color = 	mix(vec3(0.5, 1.0, 1.0), 	vec3(0.1, 0.1, 0.2),  pow(a, 0.2)) * 0.9;
	color += 	mix(vec3(0.8, 0.2, 1.0), 	vec3(0.1, 0.1, 0.2),  pow(b, 0.2)) * 0.9;
	//color += 	mix(c2, 			vec3(0.1, 0.2, 0.2),  pow(c, 0.1)) * 0.75;

	gl_FragColor = vec4( (color * dd), 1.0);
}