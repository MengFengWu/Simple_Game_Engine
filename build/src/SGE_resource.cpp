#ifndef _SGE_RESOURCE_CPP_
#define _SGE_RESOURCE_CPP_

#include "SGE_resource.h"
#include "tinyxml2.h"

#include <stdio.h>

#define SAFE_DELETE(a) {delete (a); (a) = nullptr;}

/*
    Functions of Resource class.
*/

Resource::Resource()
{
    mResourceID = 0;
    mType = RESOURCE_NULL;
}

Resource::Resource(unsigned int resourceID, std::string fileName, RESOURCE_TYPE type)
{
    mResourceID = resourceID;
    mFileName = fileName;
    mType = type;
}

Resource::~Resource()
{
    unload();
}

bool Resource::load()
{
    return true;
}

bool Resource::unload()
{
    return true;
}

/*
    Functions of Manager_Resource class.
*/

Manager_Resource* Manager_Resource::instance = nullptr;

Manager_Resource* Manager_Resource::getInstance()
{
    if(!instance)
    {
        instance = new Manager_Resource();
    }
    return instance;
}

bool Manager_Resource::destoryInstance()
{
    if(instance)
    {
        SAFE_DELETE(instance);
    }

    if(!instance) return true;
    else return false;
}

Manager_Resource::Manager_Resource()
{
    mResourceCount = 0;
}

Manager_Resource::~Manager_Resource()
{
    clear();
}

Resource* Manager_Resource::findResourcebyID(unsigned int UID)
{
    if(mResources.empty()) return nullptr;

    std::list<Resource*>::iterator it;
    for(it = mResources.begin(); it != mResources.end(); it++)
    {
        if((*it)->getResourceID() == UID)
        {
            return (*it);
        }
    }
}

void Manager_Resource::clear()
{
    std::list<Resource*>::iterator it;
    for(it = mResources.begin(); it != mResources.end(); it++)
    {
        SAFE_DELETE(*it);
    }
}

bool Manager_Resource::loadFromXMLFile(std::string Filename)
{
    tinyxml2::XMLDocument doc;
    if(doc.LoadFile(Filename.c_str()) == tinyxml2::XML_SUCCESS)
    {
        tinyxml2::XMLNode* ResourceTree = doc.FirstChildElement("resources");
        if(ResourceTree)
        {
            printf("in resource tree...\n");
            for(tinyxml2::XMLNode* child = ResourceTree->FirstChild(); child; child = child->NextSibling())
            {
                tinyxml2::XMLElement *Element = child->ToElement();
                if(Element)
                {
                    Resource *resource = NULL;
                    for(const tinyxml2::XMLAttribute* ElementAttrib = Element->FirstAttribute(); ElementAttrib; ElementAttrib = ElementAttrib->Next())
                    {
                        std::string AttribName = ElementAttrib->Name();
                        std::string AttribValue = ElementAttrib->Value();

                        if(AttribName == "type")
                        {
                            resource = new Resource();
                            if(AttribValue == "graphic")
                            {
                                printf("add graphic resource...\n");
                            }
                            if(AttribValue == "audio")
                            {
                                printf("add audio resource...\n");
                            }
                        }
                        if(resource)
                        {
                            if(AttribName == "UID")
                            {
                                resource->setResourceID(atoi(AttribValue.c_str()));
                            }
                            if(AttribName == "filename")
                            {
                                resource->setFileName(AttribValue);
                            }
                        }
                    }
                    if(resource)
                    {
                        mResources.push_back(resource);
                        mResourceCount++;
                    }
                }
            }
        return true;
        }
    }
    return false;
}

unsigned int Manager_Resource::getResourceCount() const
{
    return mResourceCount;
}

#endif //_SGE_RESOURCE_CPP_