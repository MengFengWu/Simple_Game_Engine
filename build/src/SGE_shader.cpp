#ifndef _SGE_SHADER_CPP_
#define _SGE_SHADER_CPP_

#include "SGE_shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    mFilePaths[SHADER_VERTEX] = vertexPath;
    mFilePaths[SHADER_FRAGMENT] = fragmentPath;
    mProgram = load();
}

Shader::~Shader()
{

}

std::string Shader::readFile(const char *filePath) {
	std::ifstream fileStream(filePath, std::ios::in);

	if (!fileStream.is_open())
    {
		printf("SGE Error: Could not read file %s. File doesn't exist. (Shader)\n", filePath);
		return "";
	}

	std::string content = "";
    std::string buffer = "";
	while(!fileStream.eof())
    {
		std::getline(fileStream, buffer);
		content.append(buffer + "\n");
	}

	fileStream.close();
	return content;
}

GLuint Shader::load(){
	GLuint vertShader = createShader(SHADER_VERTEX);
	GLuint fragShader = createShader(SHADER_FRAGMENT);

	printf("SGE Info: Linking program... (Shader)\n");

	GLuint program = glCreateProgram();
	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);
	glLinkProgram(program);

	//check(program);

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);
	return program;
}

//0: vertex shader, 1: fragment shader
GLuint Shader::createShader(SHADER_TYPE shaderType)
{
	GLuint shader;
    switch(shaderType)
    {
        case SHADER_VERTEX:
            shader = glCreateShader(GL_VERTEX_SHADER);
            break;
        case SHADER_FRAGMENT:
            shader = glCreateShader(GL_FRAGMENT_SHADER);
            break;
        default:
            break;
    }
	const char *shaderSource = readFile(mFilePaths[shaderType].c_str()).c_str();
    return compile(shaderType, shader, shaderSource);
}

GLuint Shader::compile(SHADER_TYPE shaderType, GLuint shader, const char* shaderSource)
{
	switch(shaderType)
    {
        case SHADER_VERTEX: 
            printf("SGE Info: Compiling vertex shader... (Shader)\n");
            break;
        case SHADER_FRAGMENT:
            printf("SGE Info: Compiling fragment shader... (Shader)\n");
            break;
        default:
            printf("SGE Error: Invalid shader type! (Shader)\n");
            break;
    }

	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);

	//check(shader);
	return shader;
}

/*
void Shader::check(GLuint shader)
{
	GLint result = GL_FALSE;
	int logLength;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
	std::vector<GLchar> shaderError((logLength > 1) ? logLength : 1);
	glGetShaderInfoLog(shader, logLength, NULL, &shaderError[0]);
	printf("SGE Info: %s (Shader)\n", shaderError[0]);
}
*/

#endif //_SGE_SHADER_CPP_