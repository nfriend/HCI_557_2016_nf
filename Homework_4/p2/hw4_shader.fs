#version 410 core                                                 

uniform sampler2D gradient_tex;
uniform sampler2D moon_tex;
uniform sampler2D cow_tex;

in vec2 pass_TexCoord; //this is the texture coord
in vec4 pass_Color;
out vec4 color;

void main(void)                                                   
{
    // This function finds the color component for each texture coordinate. 
	vec4 gradientTexColor = texture(gradient_tex, pass_TexCoord);
    vec4 moonTexColor = texture(moon_tex, pass_TexCoord);
	vec4 cowTexColor = texture(cow_tex, pass_TexCoord);

	// texture blending method 1
	// color = (gradientTexColor * .4) + moonTexColor + cowTexColor;

	// texture blending method 2
	if (cowTexColor.x != 0) {
		color = cowTexColor;
	} else {
		color = (gradientTexColor * .4) + moonTexColor;
	}
}