#include <iostream>
#include <CPlugin.h>
// #include <API.h>

#define termcolor_green     "\033[1;32m"
#define termcolor_red       "\033[1;31m"
#define termcolor_normal    "\033[0m"

using namespace EJV_PluginAPI;

class EJVPlugin : public CPlugin 
{
	public:
		void init()
		{
			name = "Sample Plugin";
			version = "1.0";

			//*
			EJV::BlockInfo *b = new EJV::BlockInfo();
			b->hardness = 2.0;
			unsigned int id;
			world::registerBlockType(b, id);

			unsigned int id2;
			EJV::BlockInfo *b2 = new EJV::BlockInfo;
			b2->hardness = 3.5;
			world::registerBlockType(b2, id2);
			//*/

			EJV::BlockInfo *b3 = world::getBlockType(1);

			std::cout << "From '" << termcolor_green << "plugin_test" << termcolor_normal << "': " << termcolor_red << "Hello, World!" << termcolor_normal << std::endl;
		}

		void onBlockPlaced(EJV::BlockInfo*, int, int, int);
};

void EJVPlugin::onBlockPlaced(EJV::BlockInfo *b, int x, int y, int z)
{

}

EJVPlugin *plug;

extern "C" void* plugin_getPlugin()
{
	plug = new EJVPlugin();
	return plug;
}