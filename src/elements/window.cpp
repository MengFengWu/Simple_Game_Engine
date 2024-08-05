#ifndef _WINDOW_CPP_
#define _WINDOW_CPP_

#include "window.h"

#include "imgui.h"
#include <stdlib.h>
#include <string.h>

Window::Window(const char* name, int width, int height, int posX, int posY)
                : mSize(width, height), mPos(posX, posY)
{
    mName = (char*)malloc((strlen(name) + 1) * sizeof(char));
    strcpy(mName, name);
}

Window::~Window()
{
    if(mName != NULL)
    {
        free(mName);
    }
}

bool Window::setName(const char* name)
{
    if(mName != NULL)
    {
        free(mName);
    }
    mName = (char*)malloc((strlen(name) + 1) * sizeof(char));
    strcpy(mName, name);
    return true;
}

bool Window::show()
{
    ImGui::SetNextWindowPos(mPos, ImGuiCond_Always);
    ImGui::SetNextWindowSize(mSize, ImGuiCond_Always);
    
    ImGui::Begin(mName);

    static float f = 0.0f;
    static int counter = 0;

    ImGui::Text("Add more stuff here!");
    //ImGui::Checkbox("Demo Window", &show_demo_window);
    //ImGui::Checkbox("Another Window", &show_another_window);

    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
    //ImGui::ColorEdit3("clear color", (float*)&clear_color);

    if (ImGui::Button("Button"))
        counter++;
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);

    //ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    ImGui::End();

    return true;
}

#endif //_WINDOW_CPP_