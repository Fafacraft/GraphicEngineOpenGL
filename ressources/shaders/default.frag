#version 330 core
out vec4 FragColor;

// inpout from vertex shader
in vec3 ourColor;

void main()
{
	// called for each pixel, set the output color
   FragColor = vec4(ourColor, 1.0f);
}