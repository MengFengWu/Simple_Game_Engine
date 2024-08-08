#ifndef _SGE_INPUT_CPP_
#define _SGE_INPUT_CPP_

#include "SGE_input.h"
#include "SGE_render_2D.h"

#define SAFE_DELETE(a) {delete (a); (a) = nullptr;}

/*
    Functions of Input_Listener class.
*/

Input_Listener::Input_Listener() : mInTheList(false)
{

}

Input_Listener::~Input_Listener()
{

}

/*
    Functions of Manager_Input class.
*/

Manager_Input* Manager_Input::instance = nullptr;
std::list<Input_Listener*> Manager_Input::mInputListeners;

Manager_Input* Manager_Input::getInstance()
{
    if(!instance)
    {
        instance = new Manager_Input();
    }
    return instance;
}

bool Manager_Input::destoryInstance()
{
    if(instance)
    {
        SAFE_DELETE(instance);
    }

    if(!instance) return true;
    else return false;
}

Manager_Input::Manager_Input()
{
    mInputListenerCount = 0;
}

Manager_Input::~Manager_Input()
{

}

bool Manager_Input::init()
{
    Manager_Render_2D* gRenderManager = Manager_Render_2D::getInstance();
    if(gRenderManager->mWindow)
    {
        glfwSetKeyCallback(gRenderManager->mWindow, mCallbackFunction);
        return true;
    }
    else
    {
        printf("SGE Error: Could not find game window! (Input)\n");
        return false;
    }
}

/*
void Manager_Input::update()
{
    Manager_Render_2D* gRenderManager = Manager_Render_2D::getInstance();
    processInput(gRenderManager->mWindow);
}
*/

void Manager_Input::addListener(Input_Listener* listener)
{
    if(listener)
    {
        listener->setInputListenerID(mInputListenerCount);
        mInputListeners.push_back(listener);
        listener->mInTheList = true;
    }
}

void Manager_Input::removeListener(Input_Listener* listener)
{
    if(listener->mInTheList && !mInputListeners.empty())
    {
        std::list<Input_Listener*>::iterator it;
        for(it = mInputListeners.begin(); it != mInputListeners.end(); it++)
        {
            if((*it)->getInputListenerID() == listener->getInputListenerID())
            {
                mInputListeners.erase(it);
                listener->mInTheList = false;
            }
        }
    }
}

void Manager_Input::clear()
{
    mInputListeners.clear();
    mInputListenerCount = 0;
}

void Manager_Input::mCallbackFunction(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if(mInputListeners.empty()) return;

    std::list<Input_Listener*>::iterator it;
    for(it = mInputListeners.begin(); it != mInputListeners.end(); it++)
    {
        if(action == SGE_PRESS)
        {
            (*it)->keyPressed(key);
        }
        if(action == SGE_REPEAT)
        {
            (*it)->keyRepeated(key);
        }
        if(action == SGE_RELEASE)
        {
            (*it)->keyReleased(key);
        }
    }
}

#endif //_SGE_INPUT_CPP_