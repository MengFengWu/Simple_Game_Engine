#ifndef _OS_GETPATH_CPP_
#define _OS_GETPATH_CPP_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "os_getPath.h"

#ifdef _WIN32 || _WIN64
#include <windows.h>
#include <shlwapi.h>

char* getExecutablePath()
{
    static char path[MAX_PATH];
    if (GetModuleFileName(NULL, path, MAX_PATH) == 0) {
        return NULL;
    }
    PathRemoveFileSpec(path);
    return path;
}

#elif defined __APPLE__
#include <mach-o/dyld.h>

char* getExecutablePath()
{
    static char path[PATH_MAX];
    uint32_t size = PATH_MAX;

    _NSGetExecutablePath(path, &size);
    return path;
}

#else
#include <unistd.h>
#include <libgen.h>

char* getExecutablePath()
{
    static char path[PATH_MAX];
    ssize_t len = readlink("/proc/self/exe", path, sizeof(path) - 1);
    if (len == -1) {
        return NULL;
    }
    path[len] = '\0';
    return dirname(path);
}
#endif

#endif //_OS_GETPATH_CPP_