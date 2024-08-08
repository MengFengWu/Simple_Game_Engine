#include <iostream>
#include "SimpleGE.h"
//using namespace std;

Manager_Resource* myResource;
Manager_Render_2D* myRender;
Manager_Input* myInput;

class InputTest : public Input_Listener
{
	public:
		bool keyPressed(int key)
		{	
			if(key == SGE_KEY_3)
			{
				printf("fuck yeah\n");
				return true;
			}
			return false;
		}
};

InputTest myInputTest;

bool engineSetup()
{
	myResource = Manager_Resource::getInstance();
	if(!myResource)
	{
		printf("SGE Error: Could not initialize! (Resource)\n");
		return false;
	} 
	myRender = Manager_Render_2D::getInstance();
	if(!myRender)
	{
		printf("SGE Error: Could not initialize! (Render_2D)\n");
		return false;
	} 
	myInput = Manager_Input::getInstance();
	if(!myInput)
	{
		printf("SGE Error: Could not initialize! (Input)\n");
		return false;		
	}
	return true;
}

bool engineEnd()
{
	bool success = true;
	
	if(!Manager_Resource::destoryInstance())
	{
		printf("SGE Error: Could not free memory! (Resource)\n");
		success = false;
	}
	if(!Manager_Render_2D::destoryInstance())
	{
		printf("SGE Error: Could not free memory! (Render_2D)\n");
		success = false;
	}
	if(!Manager_Input::destoryInstance())
	{
		printf("SGE Error: Could not free memory! (Input)\n");
		success = false;		
	}
	return success;
}

int main()
{
	if(!engineSetup()) return 1;
	
	bool good = myResource->loadFromXMLFile("../resource/filetable.xml");
	std::cout << myResource->findResourcebyID(5)->getFileName() << std::endl;
	//std::cout << good << std::endl;

	myRender->init(1280, 720);
	myInput->init();
	myInput->addListener(&myInputTest);

	if(true)
	{
		while (!glfwWindowShouldClose(myRender->mWindow))
		{
			// Render here 
			// glClear(GL_COLOR_BUFFER_BIT);
			myRender->renderAll();
		}
	}
	
	if(!engineEnd()) return 1;
}
