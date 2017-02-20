#ifdef GL_ES
#define MED mediump
#else  
#define MED 
#endif
attribute vec4 a_position; 
attribute vec2 a_texCoord0; 
varying MED vec2 v_texCoords;
void main()
{

	gl_Position = ftransform();
	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
	
	
	
	v_texCoords = gl_TexCoord[0].st;
	//gl_Position = a_position;
}