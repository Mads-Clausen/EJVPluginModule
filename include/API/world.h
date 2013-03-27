/**
 * @file Contains the parts of the API concerning the EJV world(s).
 * @author Mads Clausen
 */

#ifndef WORLD_H
#define WORLD_H

#include <map>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <iostream>

#include "GlobalState.hpp"
// #include "Rules/StandardBlocks/StandardBlocks.hpp"

namespace EJV_PluginAPI
{
    /**
     * Contains all directions
     */
    enum DIRECTION
    {
        DIRECTION_UP,
        DIRECTION_DOWN,
        DIRECTION_NORTH,
        DIRECTION_EAST,
        DIRECTION_SOUTH,
        DIRECTION_WEST,
    };

    namespace world
    {
        /** @cond */
        void init();
        /** @endcond */


        /**
         * Used to get a block at a certain point in space.
         *
         * @param x The x-coordinate.
         * @param y The y-coordinate.
         * @param z The z-corrdinate.
         *
         * @return A pointer to the Block instance.
         */
        EJV::BlockInfo* getBlock(int x, int y, int z);


        /**
         * Sets a block in space to a block instance.
         *
         * @param b The pointer to the block instance.
         * @param x The x-coordinate.
         * @param y The y-coordinate.
         * @param z The z-corrdinate.
         */
        void setBlock(EJV::BlockInfo *b, int x, int y, int z);

        /**
         * Used to get a block pointer containing the default attributes of any block type.
         *
         * @param t The block type.
         *
         * @return A pointer to the Block instance.
         */
        EJV::BlockInfo* getBlockType(EJV::State::ID t);

        /**
         * Used to add a blocktype to the core register
         *
         * @param b The block pointer containing attributes. Cannot be deleted.
         * @param id The ID to register the block with.
         */
        void registerBlockType(EJV::BlockInfo *b, unsigned int &id);

        /**
         * Used to edit attributes of a default blocktype.
         *
         * @param id The blocktype ID.
         * @param b The pointer to the block containing attributes. Can be deleted.
         */
        void editBlockType(unsigned int id, EJV::BlockInfo *b);

        /**
         * Gets the highest block ID.
         *
         * @return The highest block ID found.
         */
        unsigned int getMaxBlockID();

        /**
         * Iterates over blocks and finds the ID of the block with the correct name.
         *
         * @param name The name to search for.
         *
         * @return The ID of the block found. -1 if no block was found.
         */
        int fetchBlockIDByName(const char *name);

        /**
         * Used to the current time in the world(in ticks)
         *
         * @return The time in ticks.
         */
        int getTime();

        /**
         * Used to get a block at a certain point in space.
         *
         * @param ticks The time(in ticks) to set.
         */
        void setTime(int ticks);
    }
}

#endif // WORLD_H
