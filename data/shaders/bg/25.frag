#ifdef GL_ES
precision mediump float;
#endif
// mods by dist

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;


void main( void )
{

	vec2 uPos = ( gl_FragCoord.xy / resolution.xy );//normalize wrt y axis
	//suPos -= vec2((resolution.x/resolution.y)/2.0, 0.0);//shift origin to center
	
	uPos.x -= 0.0;
	uPos.y -= 0.0;
	
	vec3 color = vec3(0.0);
	float vertColor = 0.0;
	for( float i = 0.0; i < 4.0; ++i )
	{
		float t = time *(0.09);
	
		uPos.y += sin( uPos.y/1.0+uPos.x/1.0*(i/0.5+1.0)+t ) * 3.1;
		float fTemp = abs(1.0 / uPos.y/0.09 / 100.0);
		vertColor += fTemp;
		color += vec3( fTemp*i/4.0, fTemp*i/8.0, pow(fTemp,i/4.0)/16.0 );
	}
	
	vec4 color_final = vec4(color, 1.0);
	gl_FragColor = color_final;
}