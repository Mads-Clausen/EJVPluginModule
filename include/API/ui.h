/**
 * @file Contains the parts of the API concerning the EJV user interface.
 * @author Mads Clausen
 */

#ifndef UI_H
#define UI_H

namespace EJV_PluginAPI
{
    /**
     * Contains all of the keys which are not printable ASCII characters.
     */
    enum KEYS
    {
        KEY_BACKSPACE,
        KEY_ENTER,
        KEY_LSHIFT,
        KEY_RSHIFT,
        KEY_ESC,
        KEY_CAPSLOCK,
        KEY_TAB,
        KEY_RCTRL,
        KEY_LCTRL,
        KEY_RALT,
        KEY_LALT,
        KEY_RIGHT,
        KEY_LEFT,
        KEY_UP,
        KEY_DOWN,
    };
}

#endif // UI_H
