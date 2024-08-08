/*
    Shader.h

    class Shader
*/

#ifndef _SGE_SHADER_H_
#define _SGE_SHADER_H_

#include <stdio.h>
#include <string>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

typedef enum
{
    SHADER_VERTEX = 0,
    SHADER_FRAGMENT = 1
}SHADER_TYPE;

class Shader
{
    public:
        Shader(const char* vertexPath, const char* fragmentPath);
        ~Shader();

        inline void useProgram(){glUseProgram(mProgram);}
        inline GLuint getProgram(){return mProgram;}

    private:
        GLuint mProgram;
        std::string mFilePaths[2];

        std::string readFile(const char *filePath);
        GLuint load();
        GLuint createShader(SHADER_TYPE shaderType);
        GLuint compile(SHADER_TYPE shaderType, GLuint shader, const char* shaderSource);
        //void check(GLuint shader);
};

#endif //_SGE_SHADER_H_