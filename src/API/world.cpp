#include "API/world.h"

#include "Metadata.hpp"

//*
#define termcolor_green     "\033[1;32m"
#define termcolor_red       "\033[1;31m"
#define termcolor_normal    "\033[0m"
#define termcolor_blue      "\033[1;34m"
#define termcolor_bold      "\033[4;0m"
//*/

using namespace EJV_PluginAPI;

/**
 * Contains all default block attributes
 */
std::map<unsigned int, EJV::BlockInfo*> blockAttribs;
unsigned int biggestBlockID = 0;

void split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;

    while(std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
}

void updateMaxBlockID()
{
    for(std::map<unsigned int, EJV::BlockInfo*>::iterator it = blockAttribs.begin(); it != blockAttribs.end(); ++it)
        biggestBlockID = (it->first > biggestBlockID ? it->first : biggestBlockID);
}

unsigned int world::getMaxBlockID()
{
    return biggestBlockID;
}

/*
void world::init()
{
    #ifdef PLUGIN_DEBUG
    std::cout << std::endl <<   "========================================================" << std::endl;
    std::cout <<                "============ Loading block information." << std::endl;
    std::cout <<                "========================================================" << std::endl << std::endl;
    #endif

    std::string line;
    std::ifstream file ("data/block_info.txt");

    if(file.is_open())
    {
        while(file.good())
        {
            getline(file, line);
            std::vector<std::string> elems;
            split(line, ' ', elems);

            if(elems.size() < 3)
                continue;

            if(elems[0] == "##")
                continue;

            EJV::BlockInfo *b = new EJV::BlockInfo();
            b->hardness = atof(elems[1].c_str());

            std::string n;
            for(unsigned int i = 2; i < elems.size(); ++i)
                n.append(elems[i] + (i == elems.size() - 1 ? "" : " "));

            EJV::State::GET().registerBlock(*b);
            // blockAttribs.insert(std::pair<unsigned int, EJV::BlockInfo*>(, b));

            #ifdef PLUGIN_DEBUG
            std::cout << termcolor_normal << "Loaded block '" << termcolor_green << b->name << "\033[0m' with ID " << termcolor_red
                    << b->type << termcolor_normal << " and hardness " << termcolor_blue << b->hardness << termcolor_normal << std::endl;
            #endif

            // TODO: register with core
        }

        file.close();
    }

    #ifdef PLUGIN_DEBUG
    std::cout << std::endl <<   "========================================================" << std::endl;
    std::cout <<                "============ Done loading block information." << std::endl;
    std::cout <<                "========================================================" << std::endl << std::endl;
    #endif

    updateMaxBlockID();
}
//*/

void world::registerBlockType(EJV::BlockInfo *b, unsigned int &id)
{
    EJV::Metadata md;
    id = md.registerData(b);
    // blockAttribs.insert(std::pair<unsigned int, EJV::BlockInfo*>(id, b));

    #ifdef PLUGIN_DEBUG
    std::cout << termcolor_normal << "Added block with ID " << termcolor_red
            << id << termcolor_normal << " and hardness " << termcolor_blue << b->hardness << termcolor_normal << std::endl;
    #endif
}

EJV::BlockInfo* world::getBlockType(EJV::State::ID id)
{
    return 0;
}

int world::fetchBlockIDByName(const char *name)
{

}
