#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;
const float PI = 3.14159265358979323;// lol ya right, but hey, I memorized it

vec4 pixelAt(vec2 uv,float z)
{
	vec4 result;
	float thickness = 0.05;
	float movementSpeed = 3.0;
	float wavesInFrame = 2.0;
	float waveHeight = 0.3;
	float point = (sin(time * movementSpeed + 
			   uv.x * wavesInFrame * 2.0 * PI) *
		       waveHeight*z);
	const float sharpness = 5.40;
	float dist = 1.0 - abs(clamp((point - uv.y) / thickness, -1.0, 1.0));
	float val;
	float brightness = 1.8;

	// All of the threads go the same way so this if is easy
	if (sharpness != 1.0)
		dist = pow(dist, sharpness);
	
	dist *= brightness;
		
	result = vec4(vec3(0.3, 0.6, 0.3) * dist, 1.0);
	
	return result;
}

void main( void ) {

	vec2 fc = gl_FragCoord.xy;
	vec2 uv 	= fc / resolution - 0.5;
	vec4 pixel;
	
	pixel = pixelAt(uv,0.);
	
	// I can't really do postprocessing in this shader, so instead of
	// doing the texturelookup, I restructured it to be able to compute
	// what the other pixel might be. The real code would lookup a texel
	// and wouldnt loop.
	const float e = 32.0, s = 1.0 / e;
	for (float i = 0.0; i < e; ++i) {
		pixel += pixelAt(uv + (uv * (i*s)),sin(i*0.1)) * (0.3-i*s*0.325);
	}
	pixel /= 1.0;
	
	gl_FragColor = pixel;
}