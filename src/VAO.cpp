#include <VAO.hpp>

VAO::VAO()
{
	// generate the VAO, 1 is the number of VAOs we want to generate
	glGenVertexArrays(1, &ID);
}

void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	VBO.Bind();
	// this function tells opengl how to interpret the vertex data, that's what a VAO is for
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	// enable the vertex attribute array, which means that we tell opengl to use the data from the VBO
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

void VAO::Bind()
{
	glBindVertexArray(ID);
}

void VAO::Unbind()
{
	glBindVertexArray(0);
}

void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}