#ifndef _WINDOW_RESOURCE_CPP_
#define _WINDOW_RESOURCE_CPP_

#include "window_resource.h"
#include "window.h"

#include "imgui.h"

Window_Resource::Window_Resource() : Window("Resource Panel", 240, 701, 0, 19)
{

}

Window_Resource::~Window_Resource()
{

}

bool Window_Resource::show()
{
    ImGui::SetNextWindowPos(mPos, ImGuiCond_Always);
    ImGui::SetNextWindowSize(mSize, ImGuiCond_Always);
    
    ImGui::Begin(mName, NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
    ImGui::End();
    return true;
}

#endif //_WINDOW_RESOURCE_CPP_