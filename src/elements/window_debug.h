#ifndef _WINDOW_DEBUG_H_
#define _WINDOW_DEBUG_H_

#include "window.h"

class Window_Debug : public Window
{
    public:
        Window_Debug();
        ~Window_Debug();

        bool show();
};

#endif //_WINDOW_DEBUG_H_