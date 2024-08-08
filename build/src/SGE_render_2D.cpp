#ifndef _SGE_RENDER_2D_CPP_
#define _SGE_RENDER_2D_CPP_

#include "SGE_render_2D.h"

#include <stdio.h>

#define SAFE_DELETE(a) {delete (a); (a) = nullptr;}

/*
    Functions of Resource_Render_2D class.
*/

Resource_Render_2D::Resource_Render_2D() : Resource()
{

}

Resource_Render_2D::~Resource_Render_2D()
{

}

bool Resource_Render_2D::load()
{
    return true;
}

bool Resource_Render_2D::unload()
{
    return true;
}

/*
    Functions of Background_2D class
*/

Background_2D::Background_2D()
{

}

Background_2D::~Background_2D()
{

}

/*
    Functions of RenderObject_2D class
*/

RenderObject_2D::RenderObject_2D()
{

}

RenderObject_2D::~RenderObject_2D()
{

}

/*
    Functions of Manager_Render_2D class
*/

Manager_Render_2D* Manager_Render_2D::instance = nullptr;

Manager_Render_2D* Manager_Render_2D::getInstance()
{
    if(!instance)
    {
        instance = new Manager_Render_2D();
    }
    return instance;
}

bool Manager_Render_2D::destoryInstance()
{
    if(instance)
    {
        SAFE_DELETE(instance);
    }

    if(!instance) return true;
    else return false;
}

Manager_Render_2D::Manager_Render_2D()
{
    mShader = nullptr;
    mWindow = nullptr;
}

Manager_Render_2D::~Manager_Render_2D()
{
    if(mShader)
    {
        SAFE_DELETE(mShader);
    }
    glfwTerminate();
}

bool Manager_Render_2D::init(unsigned int width, unsigned int height, bool fullScreen, char* WindowTitle)
{
    mScreenWidth = width;
    mScreenHeight = height;
    
    //Inits GLFW
    if(glfwInit() == GLFW_FALSE)
    {
        printf("SGE Error: Fail to initialize GLFW! (Render_2D)\n");
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    //Creates window
    mWindow = glfwCreateWindow(width, height, WindowTitle, nullptr, nullptr);
    if(!mWindow)
    {
        printf("SGE Error: Could not create window! (Render_2D)\n");
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(mWindow);
    
    //Inits GLEW
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK)
	{
		printf("SGE Error: Fail to initialize GLEW: %s (Render_2D)\n", glewGetErrorString(err));
		glfwTerminate();
        return false;
	}

    //Inits Shaders
    if(!mShader)
    {
        mShader = new Shader("../src/shaderFiles/basic.vert", "../src/shaderFiles/basic.frag");
    }
    printf("SGE Info: Shader prepared. (Render_2D)\n");

    //Define the viewport
    glfwGetFramebufferSize(mWindow, &mScreenWidth, &mScreenHeight);
    glViewport(0, 0, mScreenWidth, mScreenHeight);

    //Get OpenGL version
    const GLubyte* version = glGetString(GL_VERSION);
    printf("SGE Info: OpenGL version: %s (Render_2D)\n", version);
    
    return true;
}

bool Manager_Render_2D::renderAll()
{
    if(!mShader)
    {
        printf("SGE Error: Shader hasn't been initialized. (Render_2D)\n");
        return false;
    }

    GLuint vertexArrayObject;
    glGenVertexArrays(1, &vertexArrayObject);

    glClearColor(0.5f, 0.5f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    mShader->useProgram();
    
    glBindVertexArray(vertexArrayObject);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
    //glPointSize(40.0f);
    glfwSwapBuffers(mWindow); // show on windows
    glfwPollEvents(); // check any event(ex. mousedown, keyup...)

    return true;
}

#endif //_RENDER_2D_CPP_