#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include "shaderClass.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "EBO.hpp"


int main() {
	// initialize GLFW, which is an openSource library for OpenGL
	glfwInit();
	// tell GLFW to use the OpenGL version 3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// core or compatibility. Core contains all modern functions, compatibility also has all outdated ones.)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// our triangle vertices
	GLfloat vertices[] = {
		//						position				// color
		-0.5f, -0.5f * float(sqrt(3) / 3),	0.0f,	0.8f, 0.3f, 0.02f, // bottom left
		0.5f, -0.5f * float(sqrt(3) / 3),	0.0f,	0.8f, 0.3f, 0.02f, // bottom right
		0.0f, 0.5f * float(sqrt(3) * 2 / 3),0.0f,	1.0f, 0.6f, 0.32f, // top
		-0.25f, 0.5f * float(sqrt(3) / 6),	0.0f,	0.9f, 0.45f, 0.17f, // inner bottom left
		0.25f, 0.5f * float(sqrt(3) / 6),	0.0f,	0.9f, 0.45f, 0.17f, // inner bottom right
		0.0f, -0.5f * float(sqrt(3) / 3),	0.0f,	0.8f, 0.3f, 0.02f // inner top
	};

	GLuint indices[] = {
		0, 3, 5, // lower left triangle
		3, 2, 4, // lower right triangle
		5, 4, 1 // top triangle
	};

	GLFWwindow* window = glfwCreateWindow(800, 800, "FirstWindow", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate;
		return -1;
	}
	// make the window part of the current context.
	glfwMakeContextCurrent(window);

	// initialize GLAD to manage function pointers for OpenGL
	gladLoadGL();

	// area of the window to render to
	glViewport(0, 0, 800, 800);

	// The shader program is the GPU implementation of the vertex and fragment shaders, like a compiled program on how to render the vertices
	Shader shaderProgram("default.vert", "default.frag");

	// we need to create a Vertex Array Object (VAO) to store the vertex attribute pointers
	// it is basically a container for VBOs and EBOs, with their metadata (like vertex attribute pointers, layout, etc.)
	// It tells OpenGL how to interpret the vertex data (VBOs) and in what order to draw the vertices (EBOs)
	VAO VAO1;
	VAO1.Bind();

	// create a Vertex Buffer Object (VBO) and Element Buffer Object (EBO) to store the vertices and indices
	// They are used to store the vertex data and the indices of the vertices, respectively
	// VBOs = position, color, texture, normal, etc. and EBOs = order of vertices to draw
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	// we link the VBO to the VAO.
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	// unbind the VAO, VBO, and EBO from the OpenGL context to avoid accidental changes to them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();




	while (!glfwWindowShouldClose(window)) 
	{
		// clear the buffer with a background color
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// tell OpenGL which shader program we want to use
		shaderProgram.Activate();
		// bind the VAO to tell OpenGL we want to use this VAO to draw the vertices
		VAO1.Bind();
		// draw the triangle using GL_TRIANGLES primitive
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		// swap the buffers to show the new frame
		glfwSwapBuffers(window);

		// process all events such as resizing window, inputs... If not done, window will freeze.
		glfwPollEvents();
	}


	// ---- END ----
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate;
	return 0;
}