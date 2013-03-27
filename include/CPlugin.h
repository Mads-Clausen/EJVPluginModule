#ifndef CPLUGIN_H
#define CPLUGIN_H

//*
#define termcolor_green     "\033[1;32m"
#define termcolor_red       "\033[1;31m"
#define termcolor_normal    "\033[0m"
#define termcolor_blue      "\033[1;34m"
#define termcolor_bold      "\033[4;0m"
//*/

#include <iostream>
#include <string>
#include <stdlib.h>
#include <iomanip>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
// TODO
#else
#include <dlfcn.h>
#endif

#include "API.h"

class CPlugin
{
    public:
        CPlugin()
        {
            name = "Unknown";
            version = "1.0";
        }

        ~CPlugin()
        {
            //*/
            #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
            #else
                #ifdef PLUGIN_DEBUG
                std::cout << "Closing plugin '" << termcolor_green << name << termcolor_normal << "'...";
                dlclose(_lib_handle__);
                std::cout << std::setw(20) << "Done." << std::endl;
                #endif
            #endif
            //*/
        };

        std::string name, version;

        void *_lib_handle__;

        virtual void init () {};
        virtual void destroy () {};

        virtual void onTick() {};


        // Callbacks
        virtual void onKeyPressed (char) {};
        virtual void onKeyReleased (char) {};
        virtual void onMousePressed (char) {};
        virtual void onMouseReleased (char) {};

        virtual void onWorldLoad () {};

        virtual void onBlockPlaced(EJV::BlockInfo*, int, int, int) {};
        virtual void onBlockDestroyed(EJV::BlockInfo*, int, int, int) {};
        virtual void onBlockClicked(EJV::BlockInfo*, int, int, int) {};

        virtual void onChatMessageSent(ChatMessage*) {};
        virtual void onChatMessageReceived(ChatMessage*) {};
};

#endif // CPLUGIN_H
