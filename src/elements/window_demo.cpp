#ifndef _WINDOW_DEMO_CPP_
#define _WINDOW_DEMO_CPP_

#include "window_demo.h"
#include "window.h"

#include "imgui.h"

Window_Demo::Window_Demo() : Window("Demo Panel", 800, 400, 240, 19)
{

}

Window_Demo::~Window_Demo()
{

}

bool Window_Demo::show()
{
    ImGui::SetNextWindowPos(mPos, ImGuiCond_Always);
    ImGui::SetNextWindowSize(mSize, ImGuiCond_Always);

    ImGui::Begin(mName);
    ImGui::End();
    return true;
}

#endif //_WINDOW_DEMO_CPP_