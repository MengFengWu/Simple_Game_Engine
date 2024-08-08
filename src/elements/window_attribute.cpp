#ifndef _WINDOW_ATTRIBUTE_CPP_
#define _WINDOW_ATTRIBUTE_CPP_

#include "window_attribute.h"
#include "window.h"

#include "imgui.h"

Window_Attribute::Window_Attribute() : Window("Attribute Panel", 240, 701, 1040, 19)
{

}

Window_Attribute::~Window_Attribute()
{

}

bool Window_Attribute::show()
{
    if(mVisible == false) return false;
    
    ImGui::SetNextWindowPos(mPos, ImGuiCond_Always);
    ImGui::SetNextWindowSize(mSize, ImGuiCond_Always);

    ImGui::Begin(mName, NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
    ImGui::End();
    return true;
}

#endif //_WINDOW_ATTRIBUTE_CPP_