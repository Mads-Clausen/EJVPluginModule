#include "PluginManager.h"

#include <iostream>
#define EJV_PLUGIN_PATH "/home/mads/EmptyJuiceBox/EmptyJuiceVoxel-master/modules/Rules/PluginManager/plugins/"

//*
#define termcolor_green     "\033[1;32m"
#define termcolor_red       "\033[1;31m"
#define termcolor_normal    "\033[0m"
#define termcolor_blue      "\033[1;34m"
#define termcolor_bold      "\033[4;0m"
//*/

std::vector<std::string> listDir(const char *path)
{
    DIR *dir;
    std::vector<std::string> files;
    dirent *pdir;
    dir = opendir(path);
    while((pdir = readdir(dir)))
    {
        files.push_back(std::string(pdir->d_name));
    }

    closedir(dir);

    return files;
}

bool isDir(const char *path)
{
    if(path == 0) return false;

    DIR *dir;
    bool exists = false;

    dir = opendir(path);

    if(dir != 0)
    {
        exists = true;
        (void) closedir(dir);
    }

    return exists;
}

PluginManager::PluginManager()
{

}

void PluginManager::onKeyEvent(int t, int key)
{
    switch(t)
    {
        case 1: // Press
            for(unsigned int i = 0; i < _cplugins.size(); ++i)
            {
                _cplugins[i]->onKeyPressed(key);
            }

            break;
        case 2: // Release
            for(unsigned int i = 0; i < _cplugins.size(); ++i)
            {
                _cplugins[i]->onKeyReleased(key);
            }

            break;
        default:
            break;
    }
}

void PluginManager::onMouseEvent(int t, int button)
{
    switch(button)
    {
        case GLFW_MOUSE_BUTTON_LEFT:
            button = 'l';
            break;
        case GLFW_MOUSE_BUTTON_RIGHT:
            button = 'r';
            break;
        case GLFW_MOUSE_BUTTON_MIDDLE:
            button = 'm';
            break;
        default:
            button = 'a';
            break;
    }

    switch(t)
    {
        case 1: // Press
            for(unsigned int i = 0; i < _cplugins.size(); ++i)
            {
                _cplugins[i]->onMousePressed(button);
            }

            break;
        case 2: // Release
            for(unsigned int i = 0; i < _cplugins.size(); ++i)
            {
                _cplugins[i]->onMouseReleased(button);
            }

            break;
        default:
            break;
    }
}

void PluginManager::load()
{
    #ifdef PLUGIN_DEBUG
    std::cout << std::endl <<   "========================================================" << std::endl;
    std::cout <<                "============ Loading plugins." << std::endl;
    std::cout <<                "========================================================" << std::endl << std::endl;
    #endif

    std::vector<std::string> files = listDir(EJV_PLUGIN_PATH);
    for(unsigned int i = 0; i < files.size(); ++i)
    {
        std::string dir = files[i];
        std::string path = std::string(EJV_PLUGIN_PATH);
        path += dir + "/";

        if(!isDir(path.c_str())) continue;

        std::string prefix("plugin_");
        if (!dir.compare(0, prefix.size(), prefix))
        {
            CPlugin* (*plugin_getPlugin) ();

            // std::cout << "Loading plugin from " << (path + "plugin.so").c_str() << std::endl;

            #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
                DWORD err;
                HINSTANCE hDLL = LoadLibrary((path + "plugin.dll").c_str());


                if(hDLL == 0)
                {
                    err = GetLastError();
                    std::cerr << "Unable to load plugin: " << (char) err << std::endl;
                    exit(-1);
                }
            #else
                void *handle = dlopen((path + "plugin.so").c_str(), RTLD_LAZY);
                char *err;
                err = dlerror();
                if(err != 0)
                    std::cout << "Error: " << err << std::endl;

                if(!handle)
                    exit(-1);

                dlerror();
                *(void**) (&plugin_getPlugin) = dlsym(handle, "plugin_getPlugin");

                if(plugin_getPlugin == 0)
                {
                    std::cerr << "Unable to load plugin." << std::endl;
                    exit(-1);
                }
            #endif

            CPlugin *plug = plugin_getPlugin();

            if(plug == 0)
            {
                std::cerr << "Plugin doesn't exist." << std::endl;
                exit(-1);
            }

            #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
            #else
                plug->_lib_handle__ = handle;
            #endif

            plug->init();
            _cplugins.push_back(plug);

            #ifdef PLUGIN_DEBUG
            std::cout << "Loaded plugin '" << termcolor_green << plug->name.c_str() << termcolor_normal << "' v" << termcolor_red << plug->version.c_str() << termcolor_normal << std::endl;
            #endif
        }
    }

    #ifdef PLUGIN_DEBUG
    std::cout << std::endl <<   "========================================================" << std::endl;
    std::cout <<                "============ Done loading plugins." << std::endl;
    std::cout <<                "========================================================" << std::endl << std::endl;
    #endif
}

PluginManager::~PluginManager()
{
    for(unsigned int i = 0; i < _cplugins.size(); ++i)
    {
        // std::cout << "Deleting plugin " << _cplugins[i]->name.c_str() << " v" << _cplugins[i]->version.c_str() << std::endl;
        delete (_cplugins[i]);
    }
}
