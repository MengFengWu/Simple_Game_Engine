#ifndef _WINDOW_OBJECT_CPP_
#define _WINDOW_OBJECT_CPP_

#include "window_object.h"
#include "window.h"

#include "imgui.h"

Window_Object::Window_Object() : Window("Object Panel", 800, 419, 240, 419)
{

}

Window_Object::~Window_Object()
{

}

bool Window_Object::show()
{
    if(mVisible == false) return false;
    
    ImGui::SetNextWindowPos(mPos, ImGuiCond_Always);
    ImGui::SetNextWindowSize(mSize, ImGuiCond_Always);

    ImGui::Begin(mName, NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
    ImGui::End();
    return true;
}

#endif //_WINDOW_OBJECT_CPP_