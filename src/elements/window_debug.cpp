#ifndef _WINDOW_DEBUG_CPP_
#define _WINDOW_DEBUG_CPP_

#include "window_debug.h"
#include "window.h"

#include "imgui.h"

Window_Debug::Window_Debug() : Window("Debug Panel (for dev)", 200, 500, 300, 100)
{

}

Window_Debug::~Window_Debug()
{

}

bool Window_Debug::show()
{
    ImGui::Begin(mName);
    ImGui::End();
    return true;
}

#endif //_WINDOW_DEBUG_CPP_