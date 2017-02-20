#ifdef GL_ES
precision mediump float;
#endif

#extension GL_OES_standard_derivatives : enable

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

//----------------------------------------------------------
// metaballss by pailhead in 2014-Jun-2
// original:  https://www.shadertoy.com/view/4sXXWM
// small modifications & antialiasing by I.G.P.
// This must be nice in 3d too...
//----------------------------------------------------------

#define COUNT 55

#define SPEED 0.25

#define SIZE 44.

//----------------------------------------------------------
float rn(float x)
{
    return  fract(sin(x*.4686)*3718.927);
}

//----------------------------------------------------------
void mainImage( out vec4 fragColor, in vec2 fragCoord ) 
{
	float ts = time * SPEED;   // time scaled
	
	vec3 COLOR_MASKS[16];  // blob colors
	COLOR_MASKS[0] = vec3(0.20, 0.30, 1.00 );
  	COLOR_MASKS[1] = vec3(0.53, 0.85, 0.25 );
  	COLOR_MASKS[2] = vec3(1.00, 0.56, 0.15 );
  	COLOR_MASKS[3] = vec3(1.00, 0.00, 0.30 );
  	COLOR_MASKS[4] = vec3(0.05, 0.55, 0.30 );
	COLOR_MASKS[5] = vec3(0.50, 1.00, 0.40 );
  	COLOR_MASKS[6] = vec3(1.00, 0.15, 1.00 );
  	COLOR_MASKS[7] = vec3(0.20, 0.30, 0.50 );
  	COLOR_MASKS[8] = vec3(0.35, 1.00, 0.50 );
  	COLOR_MASKS[9] = vec3(0.70, 0.60, 0.50 );
  	COLOR_MASKS[10]= vec3(0.34, 1.00, 0.50 );
  	COLOR_MASKS[11]= vec3(0.20, 0.50, 0.50 );
  	COLOR_MASKS[12]= vec3(0.60, 0.10, 0.65 );
  	COLOR_MASKS[13]= vec3(0.40, 0.40, 0.85 );
  	COLOR_MASKS[14]= vec3(1.00, 0.30, 0.35 );
  	COLOR_MASKS[15]= vec3(1.00, 0.00, 0.50 );
	
	//screen space
	vec2 fragP = ( fragCoord / resolution.xy );
	vec2 fragPN = fragP * 2.0 - 1.0;   //-1 .. 1
	float aspect = resolution.x / resolution.y;
	fragPN.x *= aspect;
	// vec2 mouseP = fragP - mouse;   // mouse
	float vH = 10.0;   // camera disance - fov
	vec3 vD = normalize(vec3(-fragPN,vH));   // view dir
	vec3 lD = normalize(vec3(cos(time),.750,sin(time)));   // light dir	
	vec3 ld = normalize(vec3(.7, .750,2.));
	
	vec2 mbPos[COUNT];
	vec3 nn = vec3(.0);
	vec3 cc = vec3(.0);

	for(int i=0; i<COUNT; i++){
		float rn1 = rn(float(i+47));
		float rn2 = rn(float(i-21));
		float rn3 = rn(float(i-52));
		mbPos[i] = vec2(sin(rn1*6.14+ts * rn2)*aspect,
			        cos(rn2*6.14+ts * rn3));
		mbPos[i] = fragPN - mbPos[i]*.8;
		float rr = cos(rn3*6.28 +ts * rn1)*.2 +.5;
		mbPos[i] *= rr * (1000. / SIZE);   // blob coord
		float bL = length( mbPos[i] );     // blob length
		float bA = smoothstep( 1.0, 0.97, bL );
		float bH = exp(-bL*2.15678);
		vec3 bN = vec3(mbPos[i]*.3*bH,bH-.01);
		vec3 bC = COLOR_MASKS[i-(i/15)*15];
		bC *= bH;
		nn += vec3(mbPos[i]*.5*bH,bH);
		cc += bC;
	}
	vec2 mp = mouse.xy / resolution.xy;
	
	vec2 mB = fragPN - (mp.xy*2. -1.)*vec2(aspect,1.);
	mB *= 6.;
	float mBL = length( mB );
	float mBH = exp(-mBL*2.15678);
	vec3 mBN = vec3(mB*.5*mBH, mBH);
	vec3 mBC = vec3(1., 0.5, .0);
	mBC *= mBH;
	
	//float sq = float((mB.x < 1. && mB.x > -1.)   //quad
	//              && (mB.y < 1. && mB.y > -1.));
	
	nn += mBN;
	vec3 n = normalize( vec3(nn.x, nn.y, nn.z-0.01) );
	float aB = smoothstep(0.0, 0.12, n.z);  // antialiasing edge !!!
	cc += mBC;
	cc /= nn.z;
	//n *= aB;
	//float ndl = dot(n,lD)*.5 +.5;   //wrap
	float ndl = dot(n,lD);   //wrap
	ndl = ndl*.7 +.3;
	vec3 h = normalize(vD+lD);
	float ndh = dot(n,h);
	ndh = ndh*.5 +.5;
	ndh = pow(ndh,70.5)*.35;
	vec3 fc = cc*ndl +ndh;
	
	float frs = dot(n,vD);
	frs = 1.0-clamp(frs,.0,1.);
	frs = pow(frs,2.0);
	frs = frs*.4 +.121;
	fc += frs;
	fragColor = vec4( fc*aB, 1.);
}

void main( void ) 
{
	mainImage( gl_FragColor, gl_FragCoord.xy );
}