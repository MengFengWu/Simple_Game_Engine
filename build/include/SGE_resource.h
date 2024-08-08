/*
    SGE_Resource.h

    Class Resource and Manager_Resource.
*/

#ifndef _SGE_RESOURCE_H_
#define _SGE_RESOURCE_H_

#include <string>
#include <list>
#include <map>

//Enum to indicate resource type
typedef enum
{
    RESOURCE_NULL = 0,
    RESOURCE_GRAPHIC = 1,
    RESOURCE_AUDIO = 2
}RESOURCE_TYPE;

/*
    Resource class, indicate a resource object (i.e. a file).
*/
class Resource
{
    public:
        Resource();
        Resource(unsigned int resourceID, std::string fileName, RESOURCE_TYPE type);
        virtual ~Resource();
        virtual bool load();
        virtual bool unload();

        inline unsigned int getResourceID() const{return mResourceID;}
        inline std::string getFileName() const{return mFileName;}
        inline RESOURCE_TYPE getType() const{return mType;}

        inline void setResourceID(unsigned int resourceID){mResourceID = resourceID;}
        inline void setFileName(std::string fileName){mFileName = fileName;}
        inline void setType(RESOURCE_TYPE type){mType = type;}

    private:
        unsigned int mResourceID;
        std::string mFileName;
        RESOURCE_TYPE mType;
};

/*
    Manager_Resource class, manages resource objects.
*/
class Manager_Resource
{
    public:
        static Manager_Resource* getInstance();
        static bool destoryInstance();
        Manager_Resource(const Manager_Resource&) = delete;
        Manager_Resource& operator=(const Manager_Resource&) = delete;

        //Finds resource by its ID, returns NULL if not found.
        Resource* findResourcebyID(unsigned int UID);
        //Clears all resources.
        void clear();
        //Loads resources from XML file
        bool loadFromXMLFile(std::string Filename);

        unsigned int getResourceCount() const;

    private:
        Manager_Resource();
        ~Manager_Resource();
        static Manager_Resource* instance;

        unsigned int mResourceCount;
        std::list<Resource*> mResources;
};

#endif //_SGE_RESOURCE_H_