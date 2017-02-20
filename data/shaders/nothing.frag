

uniform sampler2D Tex0;



void main(void)
{
	vec4 colorMap = texture2D(Tex0, gl_TexCoord[0].st);


	gl_FragColor = colorMap;


}

