
uniform sampler2D Tex0;
uniform sampler2D Tex1;

uniform float width;
uniform float height;

varying vec2 TexCoord;

void main(void)
{

	//==============================================================================
	// if you are good at glsl and can optimize this, please give me some pointers
	//==============================================================================

	
	vec4 lightTexel = texture2D(Tex1,TexCoord);
	vec2 coord = vec2(gl_FragCoord.x/width,gl_FragCoord.y/height);
	vec4 bottomTexel = texture2D(Tex0,coord);
	vec4 finalColor = bottomTexel;

	//---------------------------
	//screen blending
	//---------------------------
	if(lightTexel.a>0.0)
	{

		//=========================================================================
		//this is for blending the light colors by *not* using GL_ONE, using GL_SRC instead
		//=========================================================================
		//un-premultiply alpha
		//lightTexel.r = lightTexel.r/lightTexel.a;
		//lightTexel.g = lightTexel.g/lightTexel.a;
		//lightTexel.b = lightTexel.b/lightTexel.a;

		//=========================================================================
		//this makes the center too bright
		//=========================================================================
		//lightTexel.a = lightTexel.a*2.0;
		//if(lightTexel.a>1.0)lightTexel.a=1.0;

		//=========================================================================
		//draw the light onto the bottom color
		//=========================================================================
		vec4 bottomWithLight;
		bottomWithLight.r = (lightTexel.r * lightTexel.a) + (bottomTexel.r * (1.0 - lightTexel.a));
		bottomWithLight.g = (lightTexel.g * lightTexel.a) + (bottomTexel.g * (1.0 - lightTexel.a));
		bottomWithLight.b = (lightTexel.b * lightTexel.a) + (bottomTexel.b * (1.0 - lightTexel.a));
		bottomWithLight.a = 1.0;

		//=========================================================================
		//now take the result and screen blend it against the bottom color
		//=========================================================================
		vec3 blendedColor;// = BlendScreen(bottomTexel.rgb, bottomWithLight.rgb);

		blendedColor.r = (bottomWithLight.r+bottomTexel.r)-((bottomWithLight.r*bottomTexel.r)/1.0);
		blendedColor.g = (bottomWithLight.g+bottomTexel.g)-((bottomWithLight.g*bottomTexel.g)/1.0);
		blendedColor.b = (bottomWithLight.b+bottomTexel.b)-((bottomWithLight.b*bottomTexel.b)/1.0);

		//=========================================================================
		//now draw that result onto the bottom color with alpha*2.0(blendFalloff)
		//=========================================================================
		//this * 3.0 for GL_ONE PREMULTIPLIED looks good
		//this * 10.0 for GL_SRC UN-PREMULTIPLIED looks good but a bit too focused and not spread enough
		float blendAlpha = lightTexel.a*3.0;
		if(blendAlpha>1.0)blendAlpha = 1.0;


		finalColor.r = (blendedColor.r * blendAlpha) + (bottomTexel.r * (1.0 - blendAlpha));
		finalColor.g = (blendedColor.g * blendAlpha) + (bottomTexel.g * (1.0 - blendAlpha));
		finalColor.b = (blendedColor.b * blendAlpha) + (bottomTexel.b * (1.0 - blendAlpha));
		finalColor.a = 1.0;

	}

	gl_FragColor = finalColor;

}
