// Game engine interface
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _INTERFACE_GAME_ENGINE_H_
#define _INTERFACE_GAME_ENGINE_H_

namespace OpenEngine {
namespace Core {

// forward declarations
class IGameFactory;

/**
 * The Game Engine Interface.
 * The Game Engine acts as module container. The Game Engine is
 * responsible for performing module initialization and
 * deinitialization tasks. 
 * Follows the singelton pattern.
 *
 * @class IGameEngine IGameEngine.h Core/IGameEngine.h
 */
class IGameEngine {
protected:

    /**
     * Private constructor.
     *
     * @see Instance()
     */
    IGameEngine();

    //! The only existing instance.
    static IGameEngine* instance;

public:

    /**
     * Get game engine instance.
     *
     * @return Reference to GameEngine instance
     */
    static IGameEngine& Instance();

    /**
     * Remove the engine instance on destruction.
     */
    virtual ~IGameEngine();

    /**
     * Start the engine.
     *
     * The specified game factory is used to set up the engine modules
     * and other customization tasks.
     * The game engine is responsible for deleting the factory after
     * use.
     *
     * @see IGameFactory
     * @param factory Game factory
     */
    virtual void Start(IGameFactory* factory) = 0;

    /**
     * Shutdown engine. When Stop is called the engine loop
     * stops running and all modules gets deinitialized.
     */
    virtual void Stop() = 0;

};

} // NS Core
} // NS OpenEngine

#endif // _INTERFACE_GAME_ENGINE_H_
