#ifdef GL_ES
#define MED mediump
#else
#define MED 
#endif

attribute vec4 a_position; 
attribute vec2 a_texCoord0; 
uniform vec2 dir;
uniform vec2 size;
varying MED vec2 v_texCoords0;
varying MED vec2 v_texCoords1;
varying MED vec2 v_texCoords2;
varying MED vec2 v_texCoords3;
varying MED vec2 v_texCoords4;
const vec2 futher = vec2(3.2307692308, 3.2307692308);
const vec2 closer = vec2(1.3846153846, 1.3846153846);
void main()
{

	gl_Position = ftransform();
	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
	
	
	vec2 sizeAndDir = dir / size;
	vec2 f = futher*sizeAndDir;
	vec2 c = closer*sizeAndDir;
	
	v_texCoords0 = gl_TexCoord[0].st - f;
	v_texCoords1 = gl_TexCoord[0].st - c;	
	v_texCoords2 = gl_TexCoord[0].st;
	v_texCoords3 = gl_TexCoord[0].st + c;
	v_texCoords4 = gl_TexCoord[0].st + f;
	
	//gl_Position = a_position;
}