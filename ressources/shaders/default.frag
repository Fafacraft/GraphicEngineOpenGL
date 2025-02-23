#version 330 core
out vec4 FragColor;

// input from vertex shader
in vec3 ourColor;
in vec2 texCoord;

// texture sampler, which is the texture we're going to use
uniform sampler2D tex0;

void main()
{
	// called for each pixel, set the output color
   FragColor = texture(tex0, texCoord);
}