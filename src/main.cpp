#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

const char* vertexShaderSource = "#version 330 core\n" // vertex shader positions the vertices of the triangle
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n" // fragment shader colors the pixels inside the triangle
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n" // this will be the triangle's color
"}\n\0";

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
		-0.5f, -0.5f * float(sqrt(3) / 3), 0.0f,
		0.5f, -0.5f * float(sqrt(3) / 3), 0.0f,
		0.0f, 0.5f * float(sqrt(3) * 2 / 3), 0.0f
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

	// create a vertex shader and compile it for the GPU
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// create fragment shader and compile it for the GPU
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// create a shader program and attach the vertex and fragment shaders to it
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// now that the shaders are linked to the gpu, we can delete them	
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	// create a vertex array object (VAO) to store the vertex attribute configurations, and a vertex buffer object (VBO) to store the actual vertex data
	GLuint VAO, VBO;
	// generate the VAO and VBO with one object each
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// make the VAO the active object
	glBindVertexArray(VAO);
	// bind the VBO and tell OpenGL we want to use it as an array buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// copy the vertices into the buffer object's memory
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// tell OpenGL how to interpret the vertex data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// enable the vertex attribute
	glEnableVertexAttribArray(0);

	// unbind the VAO and VBO, to prevent accidental changes to the VAO and VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);





	while (!glfwWindowShouldClose(window)) 
	{
		// clear the buffer with a background color
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// tell OpenGL which shader program we want to use
		glUseProgram(shaderProgram);
		// bind the VAO to tell OpenGL we want to use it
		glBindVertexArray(VAO);
		// draw the triangle using GL_TRIANGLES primitive
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// swap the buffers to show the new frame
		glfwSwapBuffers(window);

		// process all events such as resizing window, inputs... If not done, window will freeze.
		glfwPollEvents();
	}


	// ---- END ----
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	glfwDestroyWindow(window);
	glfwTerminate;
	return 0;
}