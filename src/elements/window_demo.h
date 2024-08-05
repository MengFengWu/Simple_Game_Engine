#ifndef _WINDOW_DEMO_H_
#define _WINDOW_DEMO_H_

#include "window.h"

class Window_Demo : public Window
{
    public:
        Window_Demo();
        ~Window_Demo();

        bool show();
};

#endif //_WINDOW_DEMO_H_