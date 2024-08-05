#ifndef _WINDOW_H_
#define _WINDOW_H_

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#include "imgui.h"

class Window
{
    public:
        Window(const char* name, int width, int height, int posX, int posY);
        ~Window();

        bool setName(const char* name);

        virtual bool show();
    
    protected:
        char* mName;

        ImVec2 mSize;
        ImVec2 mPos;
};

#endif //_WINDOW_H_