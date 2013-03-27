#include "PluginManager.h"
#include "Action.hpp"

#include <iostream>

PluginManager *pluginManager;

extern "C" void EJVmodule_init()
{
	// std::cout << "Hello, World!" << std::endl;
	pluginManager = new PluginManager();
    pluginManager->load();
}

extern "C" void EJVmodule_destroy()
{
    delete pluginManager;
}

extern "C" void EJVmodule_tick(EJV::Action::Base *base)
{

}
