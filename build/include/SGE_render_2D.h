/*
    Render_2D.h

    Class Resource_Render_2D, Background_2D, RenderObject_2D and Manager_Render_2D.
*/

#ifndef _SGE_RENDER_2D_H_
#define _SGE_RENDER_2D_H_

#include "SGE_resource.h"
#include "SGE_shader.h"

#include <list>
#include <stdint.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

/*
    Resource_Render_2D class, indicates a resource which is to be rendered.
*/
class Resource_Render_2D : public Resource
{
    public:
        Resource_Render_2D();
        ~Resource_Render_2D();
        bool load();
        bool unload();
};

/*
    Background_2D class, indicates the background of the game.
*/
class Background_2D
{
    public:
        Background_2D();
        ~Background_2D();

    protected:
        double mPosX;
        double mPosY;
        bool mVisible;
        uint16_t mColorKey;
};

/*
    RenderObject_2D class, includes a RenderResource and parameters for rendering.
*/
class RenderObject_2D : public Background_2D
{
    public:
        RenderObject_2D();
        ~RenderObject_2D();

    protected:
        double mVelX;
        double mVelY;
};

/*
    Manager_Render_2D class, manages Render objects.
*/
class Manager_Render_2D
{
    public:
        static Manager_Render_2D* getInstance();
        static bool destoryInstance();
        Manager_Render_2D(const Manager_Render_2D&) = delete;
        Manager_Render_2D& operator=(const Manager_Render_2D&) = delete;

        bool init(unsigned int width = 1280, unsigned int height = 720, bool fullScreen = false, char* WindowTitle = (char*)"untitle"); 
        bool renderAll();
        
        GLFWwindow* mWindow;

    private:
        Manager_Render_2D();
        ~Manager_Render_2D();
        static Manager_Render_2D* instance;

        //GLFWwindow* mWindow;

        Shader *mShader;

        int mScreenWidth;
        int mScreenHeight;
        std::list<Background_2D*> mRenderObjects;
};

#endif //_SGE_RENDER_2D_H_