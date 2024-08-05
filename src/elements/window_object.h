#ifndef _WINDOW_OBJECT_H_
#define _WINDOW_OBJECT_H_

#include "window.h"

class Window_Object : public Window
{
    public:
        Window_Object();
        ~Window_Object();

        bool show();
};

#endif //_WINDOW_OBJECT_H_