#ifndef _WINDOW_EDITOR_H_
#define _WINDOW_EDITOR_H_

#include "window.h"
#include "TextEditor.h"

class Window_Editor : public Window
{
    public:
        Window_Editor();
        ~Window_Editor();

        bool loadFile(const char* fileToEdit);
        bool show();
    
    private:
        TextEditor editor;
        char* mFileToEdit;
};

#endif //_WINDOW_EDITOR_H_