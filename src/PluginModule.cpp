#include "PluginManager.h"
#include "Action.hpp"

#include <iostream>

PluginManager *pluginManager;

extern "C" void init()
{
	// std::cout << "Hello, World!" << std::endl;
	pluginManager = new PluginManager();
    pluginManager->load();
}

extern "C" void destroy()
{
    delete pluginManager;
}

extern "C" void tick(EJV::Action::Base *base)
{

}
