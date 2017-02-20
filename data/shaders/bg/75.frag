// Energy Field
// By: Brandon Fogerty
// bfogerty at gmail dot com 
// xdpixel.com
// Special thanks to Inigo Montoya 

#ifdef GL_ES
precision highp float;
#endif

// test

uniform float time;
uniform vec2 resolution;

float gt;

float hash( float n ) { return fract(sin(n)*753.5453123); }

// Slight modification of iq's noise function.
float noise( in vec2 x )
{
    vec2 p = floor(x);
    vec2 f = fract(x);
    f = f*f*(3.0-2.0*f);
    
    float n = p.x + p.y*157.0;
    return mix(
                    mix( hash(n+  0.0), hash(n+  1.0),f.x),
                    mix( hash(n+157.0), hash(n+158.0),f.x),
            f.y);
}


float fbm(vec2 p, vec3 a)
{
     float v = 0.0;
     v += noise(p*a.x)*.5;
     v += noise(p*a.y)*.25;
     v += noise(p*a.z)*.125;
     return v;
}

vec3 drawLines( vec2 uv, vec3 fbmOffset, vec3 color1, vec3 color2 )
{
    float timeVal = gt * 0.1 + 1.0;
    vec3 finalColor = vec3( 0.0 );
    for( int i=0; i < 2; ++i )
    {
        float indexAsFloat = float(i);
        float amp = 40.0 + (indexAsFloat*5.0);
        float period = 7.0 + (indexAsFloat+1.0)+(time*0.0002);
        float thickness = 1.5*mix( 0.7, 1.0, noise(uv*10.0) );
        float t = abs( 0.2 / (sin(2.82 + 0.5 * uv.x + fbm( uv + timeVal * period, fbmOffset )) * amp) * thickness );
        
        finalColor +=  t * color1;
    }
    
    for( int i=0; i < 2; ++i )
    {
        float indexAsFloat = float(i);
        float amp = 30.0 + (indexAsFloat*7.0);
        float period = 8.0 + (indexAsFloat+.001);
        float thickness = 1.5*mix( 0.8, 1.0, noise(uv*10.0) );
        float t = abs( 0.5 / (sin(2.78 + 0.5 * uv.x + fbm( uv + timeVal * period, fbmOffset )) * amp) * thickness );
        
        finalColor +=  t * color2 * 0.6;
    }
    
    return finalColor * finalColor;
}

void main( void ) 
{

    vec2 uv = ( gl_FragCoord.xy / resolution.xy ) * 2.0 - 1.0;
    uv.x *= resolution.x/resolution.y;
    uv.xy = uv.yx;

    vec3 lineColor1 = vec3( 0.9, 0.4, 1.2 );
    vec3 lineColor2 = vec3( 0.6, 1.1, 0.3 );
    
    vec3 finalColor = vec3(0.0);

	gt = mod(time, 20.);
    
    float t = sin( gt ) * 0.5 + 0.5;
    float pulse = mix( 0.010, 0.020, t);
    
    //finalColor += drawLines( uv, vec3( 1.0, 20.0, 30.0), lineColor1, lineColor2 ) * pulse;
    finalColor += drawLines( uv, vec3( 3.0, 2.0, 1.0), lineColor1, lineColor2 );
    
    gl_FragColor = vec4( finalColor, 1.0 );

}