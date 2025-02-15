#ifndef VAO_HPP
#define VAO_HPP

#include <glad/glad.h>
#include <VBO.hpp>

class VAO 
{
	public:
		GLuint ID;
		VAO();

		void LinkAttrib(VBO& VBO, GLuint layout);
		void Bind();
		void Unbind();
		void Delete();
};

#endif // !VAO_HPP
