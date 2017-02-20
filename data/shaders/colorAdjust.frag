uniform float gameGamma;
uniform float gameSaturation;
uniform float gameHue;
uniform float gameBrightness;
uniform float gameContrast;

uniform sampler2D Tex0;
varying vec2 TexCoord;

void main(void)
{

	vec4 finalColor = texture2D(Tex0,TexCoord);

	if(finalColor.r>0.15||finalColor.g>0.15||finalColor.b>0.15)finalColor = pow(finalColor, vec4(1.0/gameGamma));

	vec3 luminanceCoefficient = vec3(0.2125, 0.7154, 0.0721);
	vec3 averageLuminance = vec3(0.5, 0.5, 0.5);
	vec3 brightnessAdjustedColor = finalColor.rgb * gameBrightness;
	vec3 intensity = vec3(dot(brightnessAdjustedColor, luminanceCoefficient));
	vec3 saturationAdjustedColor = mix(intensity, brightnessAdjustedColor, gameSaturation);
	vec3 contrastAdjustedColor = mix(averageLuminance, saturationAdjustedColor, gameContrast);
	finalColor.rgb = contrastAdjustedColor;

	gl_FragColor = finalColor;

}

