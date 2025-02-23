#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTex;

out vec3 ourColor;
out vec2 texCoord;

// uniform variable for scale factor, which we can set from our C++ code
uniform float scale;

void main()
{
	// for each vertex, we calculate the new position by adding the vertex position with the vertex position multiplied by the scale factor
   gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);
   // set ourColor to the input color we got from the vertex data
   ourColor = aColor;
   // set TexCoord to the input texture coordinates we got from the vertex data, to pass it to the fragment shader
   texCoord = aTex;
}