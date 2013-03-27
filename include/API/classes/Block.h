/**
 * @file Contains the Block class which is used in the API.
 * @author Mads Clausen
 */

#ifndef BLOCK_H
#define BLOCK_H

#include <string>

struct Block
{
    float hardness;
    int type, facing;
    bool breakable;
    std::string name;
};

#endif // BLOCK_H
