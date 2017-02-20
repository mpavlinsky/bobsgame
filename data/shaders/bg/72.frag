#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

const float PI=3.14159265;

/**************************
* @brief LibFunction
*/
vec3 Sim( vec3 p, float s ){
	vec3 ret = p;
	ret = p + s / 2.0;
	ret = fract( ret / s ) * s - s / 4.0;
	
	return ret;
}

vec2 Rot( vec2 p, float r ){
	vec2 ret;
	ret.x = p.x * sin( r ) * cos( r ) - p.y * cos( r );
	ret.y = p.x * cos( r ) + p.y  * sin( r );
	
	return ret;
}

vec2 RotSim( vec2 p, float s ){
	vec2 ret = p;
	ret = Rot( p , -PI / ( s * 2.0 ) );
	ret = Rot( p, floor( atan( ret.x, ret.y ) / PI * s ) * ( PI / s ) );
	
	return ret;
}

vec2 Zoom( vec2 p, float f ){
	return vec2( p.x * f, p.y * f );
}


/**************************
* @brief function
*/
vec2 MakeSymmetry( vec2 p ){
	vec2 ret=p;
	ret = RotSim( ret, sin( time *0.03 ) * 20.0 + 300.0 );
	ret.x = abs( ret.x );
	
	return ret;
}


float MakePoint( float x, float y, float fx, float fy, float sx, float sy, float t ){
	float xx = x + tan( t * fx ) * sy;
	float yy = y - tan( t * fy ) * sy;
	float a = 0.5 / sqrt( abs( abs( x * xx ) + abs( yy * y ) ) );
	float b = 0.5 / sqrt( abs( x * xx + yy * y ) );
	
	return a*b;
}


/**************************
* @brief main
*/
void main( void ) {
	
	vec2 p = gl_FragCoord.xy / resolution.y - vec2( ( resolution.x / resolution.y ) / 2.0, 0.5 );
	
	p = Rot( p, sin( time*0.2 + length( p ) ) * 4.0 );
	p = Zoom( p, sin( time * 0.3 ) * 0.5 + 0.8 );

	p = p * 2.0;
   
	float x = p.x;
	float y = p.y;
   
	float t=time*0.1;

	float a = MakePoint( x, y, 3.3, 2.9, 0.3, 0.3, t );
	a = a + MakePoint( x, y, 1.9, 2.0, 0.4, 0.4, t );
	a = a + MakePoint( x, y, 0.8, 0.7, 0.4, 0.5, t );
	a = a + MakePoint( x, y, 2.3, 0.1, 0.6, 0.3, t );
	a = a + MakePoint( x, y, 0.8, 1.7, 0.5, 0.4, t );
	a = a + MakePoint( x, y, 0.3, 1.0, 0.4, 0.4, t );
	a = a + MakePoint( x, y, 1.4, 1.7, 0.4, 0.5, t );
	a = a + MakePoint( x, y, 1.3, 2.1, 0.6, 0.3, t );
	a = a + MakePoint( x, y, 1.8, 1.7, 0.5, 0.4, t );   
   
	float b = MakePoint( x, y, 1.2, 1.9, 0.3, 0.3, t );
	b = b + MakePoint( x, y, 0.7, 2.7, 0.4, 0.4, t );
	b = b + MakePoint( x, y, 1.4, 0.6, 0.4, 0.5, t );
	b = b + MakePoint( x, y, 2.6, 0.4, 0.6, 0.3, t );
	b = b + MakePoint( x, y, 0.7, 1.4, 0.5, 0.4 ,t );
	b = b + MakePoint( x, y, 0.7, 1.7, 0.4, 0.4, t );
	b = b + MakePoint( x, y, 0.8, 0.5, 0.4, 0.5, t );
	b = b + MakePoint( x, y, 1.4, 0.9, 0.6, 0.3, t );
	b = b + MakePoint( x, y, 0.7, 1.3, 0.5, 0.4, t );
	
	float c = MakePoint( x, y, 3.7, 0.3, 0.3, 0.3, t );
	c = c + MakePoint( x, y, 1.9, 1.3, 0.4, 0.4, t );
	c = c + MakePoint( x, y, 0.8, 0.9, 0.4, 0.5, t );
	c = c + MakePoint( x, y, 1.2, 1.7, 0.6, 0.3, t );
	c = c + MakePoint( x, y, 0.3, 0.6, 0.5, 0.4, t );
	c = c + MakePoint( x, y, 0.3, 0.3, 0.4, 0.4, t );
	c = c + MakePoint( x, y, 1.4, 0.8, 0.4, 0.5, t );
	c = c + MakePoint( x, y, 0.2, 0.6, 0.6, 0.3, t );
	c = c + MakePoint( x, y, 1.3, 0.5, 0.5, 0.4, t );
	
	vec3 d = vec3( a, b, c ) / 31.0;
	
	gl_FragColor = vec4( d.x, d.y, d.z, 1.0 );
	gl_FragColor *= vec4(0.5,0.5,0.5,1.0);
}

