#include "Texture.h"

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
	type = texType;
	// numColChan = number of color channels in the image (3 for RGB, 4 for RGBA)
	int widthImg, heightImg, numColChan;
	// flip the image vertically when loading it, as OpenGL reads the image from the bottom left corner instead of the top left corner like most image viewers
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColChan, 0);

	glGenBuffers(1, &ID);
	// bind the texture to the first slot of the texture unit, which is a small buffer of textures that the GPU can use concurrently (0 to 31)
	glActiveTexture(slot);
	glBindTexture(texType, ID);

	// set the GL_TEXTURE_MIN_FILTER parameter of the texture to GL_NEAREST (nearest neighbor interpolation when the texture is scaled up)
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// how the texture wrap, on the s and t axis which are the x and y axis of the texture
	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// set the texture data to the actual image data
	glTexImage2D(texType, 0, format, widthImg, heightImg, 0, format, pixelType, bytes);
	// generate mipmaps for the texture, which are smaller resolution versions of the texture that are used when the texture is far away
	glGenerateMipmap(texType);

	stbi_image_free(bytes);
	glBindTexture(texType, 0);
}

void Texture::texUnit(Shader shader, const char* uniform, GLuint unit)
{
	// get the location of the uniform variable in the shader program
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	// set the uniform variable to the texture unit
	shader.Activate();
	glUniform1i(texUni, unit);
}

void Texture::Bind()
{
	glBindTexture(type, ID);
}

void Texture::Unbind()
{
	glBindTexture(type, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}