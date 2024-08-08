#ifndef _MENUBAR_CPP_
#define _MENUBAR_CPP_

#include "menubar.h"
#include "imgui.h"

Menubar::Menubar()
{

}

Menubar::~Menubar()
{

}

bool Menubar::show()
{
    if (ImGui::BeginMainMenuBar())
    {
        if(ImGui::BeginMenu("File"))
        {
            if(ImGui::MenuItem("Create")) 
            { 
            }
            if(ImGui::MenuItem("Open", "Ctrl-O")) 
            { 
            }
            if(ImGui::MenuItem("Save", "Ctrl-S")) 
            {
            }
            if(ImGui::MenuItem("Save as..")) 
            { 
            }
            ImGui::EndMenu();
        }
        if(ImGui::BeginMenu("Edit"))
        {
            if(ImGui::MenuItem("Undo", "Ctrl-Z")) 
            { 
            }
            if(ImGui::MenuItem("Redo", "Shift-Ctrl-Z")) 
            { 
            }
            ImGui::EndMenu();
        }
        if(ImGui::BeginMenu("View"))
        {
            if(ImGui::MenuItem("Palettes"))
            { 
            }
            ImGui::EndMenu(); 
        }
        if(ImGui::BeginMenu("Add"))
        {
            if(ImGui::MenuItem("Object", "Shift-Ctrl-O"))
            { 
            }
            ImGui::EndMenu(); 
        }
        if(ImGui::BeginMenu("Tools"))
        {
            if(ImGui::MenuItem("Simulate", "Shift-Ctrl-S"))
            { 
            }
            ImGui::EndMenu(); 
        }
        if(ImGui::BeginMenu("Help"))
        {
            if(ImGui::MenuItem("Tutorial"))
            { 
            }
            if(ImGui::MenuItem("About"))
            { 
            }
            ImGui::EndMenu();            
        }
        ImGui::EndMainMenuBar();
    }

    return true;
}

#endif //_MENUBAR_CPP_