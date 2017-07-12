#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;

void main()
{    
    vec4 outColor = texture(texture_diffuse1, TexCoords);
	float fg = ( outColor.x + outColor.y + outColor.z ) / 3.0;
	FragColor = vec4(fg, fg, fg, 1.0);
}