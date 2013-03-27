/**
 * @file Contains the parts of the API concerning the EJV events.
 * @author Mads Clausen
 */

#ifndef EVENT_H
#define EVENT_H

namespace EJV_PluginAPI
{
    /**
     * Contains all of the event types.
     */
    enum EVENT_TYPE
    {
        EVENT_KEY_RELEASE,
        EVENT_KEY_PRESS,
        EVENT_MOUSE_RELEASE,
        EVENT_MOUSE_PRESS,
        EVENT_WORLD_LOAD,
        EVENT_BLOCK_PLACED,
        EVENT_BLOCK_DESTROYED,
        EVENT_CHAT_MESSAGE_SENT,
        EVENT_CHAT_MESSAGE_RECEIVED,
    };

    namespace event
    {
        /**
         * Used to trigger an event in the EJV core.
         *
         * @param type The type of event.
         */
        void triggerEvent (EVENT_TYPE type, ...);
    }
}



#endif // EVENT_H
