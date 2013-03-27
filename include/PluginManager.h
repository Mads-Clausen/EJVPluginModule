#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <vector>
#include <map>
#include <sys/types.h>
#include <errno.h>
#include <string>
#include <iostream>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include "win/dirent.h"
#include <windows.h>
#else
#include <dirent.h>
#include <dlfcn.h>
#endif

#include <GL/glfw.h>

#include "CPlugin.h"

#include "Action.hpp"

using namespace EJV_PluginAPI;

class PluginManager
{
    private:
        std::vector<CPlugin*> _cplugins;

    public:
        PluginManager(); // Constructors
        virtual ~PluginManager();

        void load();
        void load(const char*); // Loads with the path specified

        // Event handlers
        void onKeyEvent(int, int);
        void onMouseEvent(int, int);
};

#endif // PLUGINMANAGER_H
