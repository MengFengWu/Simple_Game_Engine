#ifndef _SGE_INPUT_H_
#define _SGE_INPUT_H_

#include "SGE_keyname.h"

#include <list>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Input_Listener
{
    public:
        Input_Listener();
        ~Input_Listener();

        inline unsigned int getInputListenerID() const{return mInputListenerID;}
        inline void setInputListenerID(unsigned int inputListenerID){mInputListenerID = inputListenerID;}

        //Keyboard events
        virtual bool keyPressed(int key){return false;}
        virtual bool keyRepeated(int key){return false;}
        virtual bool keyReleased(int key){return false;}

        bool mInTheList;

    private:
        unsigned int mInputListenerID;
};

class Manager_Input
{
    public:
        static Manager_Input* getInstance();
        static bool destoryInstance();
        Manager_Input(const Manager_Input&) = delete;
        Manager_Input& operator=(const Manager_Input&) = delete;

        bool init();

        //void update();
        void addListener(Input_Listener* listener);
        void removeListener(Input_Listener* listener);
        void clear();

    private:
        Manager_Input();
        ~Manager_Input();
        static Manager_Input* instance;

        unsigned int mInputListenerCount;
        static std::list<Input_Listener*> mInputListeners;
        static void mCallbackFunction(GLFWwindow* window, int key, int scancode, int action, int mode);
};

#endif //_SGE_INPUT_H_