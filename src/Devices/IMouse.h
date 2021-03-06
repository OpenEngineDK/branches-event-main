// Interface for handling mouse events
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _INTERFACE_MOUSE_H_
#define _INTERFACE_MOUSE_H_

#include <Devices/Symbols.h>
#include <Core/IModule.h>
#include <EventSystem/EventSystem.h>

namespace OpenEngine {
namespace Devices {

using OpenEngine::Core::IModule;
using namespace OpenEngine::EventSystem;

/**
 * Mouse state.
 * Container for mouse state information.
 *
 * @struct MouseState IMouse.h Devices/IMouse.h
 */
struct MouseState {
    int x;                      //!< position on x-axis
    int y;                      //!< position on y-axis
    MouseButton buttons;        //!< currently activated buttons
    MouseState() : x(0), y(0), buttons(BUTTON_NONE) {}
};

/**
 * Mouse moved event argument.
 * Sent to handlers listening on mouseMovedEvent.
 * The same structure as \a MouseState but with a name more
 * consistiant with the event system.
 *
 * @struct MouseMovedEventArg IMouse.h Devices/IMouse.h
 */
struct MouseMovedEventArg {
    unsigned int x;             //!< absolute position on x-axis
    unsigned int y;             //!< absolute position on y-axis
    int dx;                     //!< relative movement on x-axis
    int dy;                     //!< relative movement on y-axis
    MouseButton buttons;        //!< currently activated buttons
    MouseMovedEventArg() : x(0), y(0), dx(0), dy(0), buttons(BUTTON_NONE) {}
};

/**
 * Mouse button change event argument.
 * Sent to handlers listening on mouseUpEvent and mouseDownEvent.
 *
 * @struct MouseButtonEventArg IMouse.h Devices/IMouse.h
 */
struct MouseButtonEventArg {
    MouseState state;           //!< current mouse state
    MouseButton button;         //!< button that triggered event
    MouseButtonEventArg() : button(BUTTON_NONE) {}
};

/**
 * Mouse event module interface.
 *
 * @class IMouse IMouse.h Devices/IMouse.h
 */
class IMouse : public virtual IModule {

public:

    //! Button-up event list
    static Event<MouseButtonEventArg> mouseUpEvent;

    //! Button-down event list
    static Event<MouseButtonEventArg> mouseDownEvent;

    //! Mouse movement event list
    static Event<MouseMovedEventArg> mouseMovedEvent;

    /**
     * Mouse module constructor.
     */
    IMouse();
    
    /**
     * Mouse module destructor.
     */
    virtual ~IMouse();

    //! Test for type membership. @see EModule::IsTypeOf()
    bool IsTypeOf(const std::type_info& inf);

    /**
     * Hide the mouse cursor.
     */
    virtual void HideCursor() = 0;

    /**
     * Show the mouse cursor.
     */
    virtual void ShowCursor() = 0;

    /**
     * Set cursor position.
     *
     * @param x Position on x-axis
     * @param y Position on y-axis
     */
    virtual void SetCursor(int x, int y) = 0;

    /**
     * Get the current mouse state.
     *
     * @return The current mouse state
     */
    virtual MouseState GetState() = 0;

    // implemented in IMouse.cpp
    bool IsPressed(MouseButton b);

};

} // NS Devices
} // NS OpenEngine

#endif // _INTERFACE_MOUSE_H_
