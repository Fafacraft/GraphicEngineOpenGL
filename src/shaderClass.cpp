#include "shaderClass.hpp"

std::string getFileContents(const char* filename) 
{
	std::string fullPath = std::string("./ressources/shaders/") + filename;

	std::ifstream in(fullPath, std::ios::binary);
	if (in) 
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	std::string vertexCode = getFileContents(vertexFile);
	std::string fragmentCode = getFileContents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// create the vertex shader and compile it for the GPU
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	compileErrors(vertexShader, "VERTEX");

	// create fragment shader and compile it for the GPU
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	compileErrors(fragmentShader, "FRAGMENT");

	// create the shader program and attach the vertex and fragment shaders to it
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	compileErrors(ID, "PROGRAM");

	// now that the shaders are linked to the gpu, we can delete them	
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Activate()
{
	glUseProgram(ID);
}

void Shader::Delete()
{
	glDeleteProgram(ID);
}

// is used to print out the errors that occur during the compilation of the shaders, useful for debugging
// without it, the program would just crash and not tell you that the shaders didn't compile correctly
void Shader::compileErrors(unsigned int shader, const char* type)
{
	GLint hasCompiled;
	char infolog[1024];
	// we manually input PROGRAM if we are linking the program, otherwise we input the type of shader
	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE) {
			glGetShaderInfoLog(shader, 1024, NULL, infolog);
			std::cout << "SHADER_COMPILATION_ERROR for: " << type << "\n" << infolog << std::endl;
		}
	}
	else {
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE) {
			glGetProgramInfoLog(shader, 1024, NULL, infolog);
			std::cout << "PROGRAM_LINKING_ERROR for: " << type << "\n" << infolog << std::endl;
		}
	}
}
