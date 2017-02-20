#ifdef GL_ES
precision mediump float;
#endif
// mods by Casper from dist's source

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

float rand(vec2 co){
    return fract(cos(dot(co.xy ,vec2(12.9898,78.233))) * 758.5453);
}

void main( void )
{
	vec2 pos = gl_FragCoord.xy / resolution.xy;
	vec2 uPos = pos;
	if (mouse.x > 0.0 && mouse.y > 0.0){
		uPos -= mouse;
	}else{
		uPos.y -= 0.5;
	}
	
	vec3 color = vec3(0.0);
	float vertColor = 0.0;
	const float k = 4.;
	for( float i = 1.0; i < k; ++i )
	{
		float t = time * (2.0);
	
		uPos.y += sin( uPos.x*exp(i) - t) * 0.055;
		float fTemp = abs(1.0/(80.0*k) / uPos.y);
		vertColor += fTemp;
		color += vec3( fTemp*(i*0.33), fTemp*i/k, pow(fTemp,0.93)*1.2 );
	}
	for( float i = 2.0; i < k; ++i )
	{
		float t = time * (3.0);
	
		uPos.y += sin( uPos.x*exp(i) + t) * 0.015;
		float fTemp = abs(1.0/(80.0*k) / uPos.y);
		vertColor += fTemp;
		color += vec3( fTemp*(i*0.33), fTemp*i/k, pow(fTemp,0.93)*1.2 );
	}
	
	vec4 color_final = vec4(color, 1.0);
	gl_FragColor = color_final;
	float ft = fract(time);
	gl_FragColor.rgb += vec3( rand( pos +  7.+ ft ), 
				  rand( pos +  92.+ ft ),
				  rand( pos + 11.+ ft ) ) / 22.0;
}
