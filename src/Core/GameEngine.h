// Game Engine implementation.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _GAME_ENGINE_H_
#define _GAME_ENGINE_H_

#include <Core/IGameEngine.h>
#include <EventSystem/EventSystem.h>

using namespace OpenEngine::EventSystem;

namespace OpenEngine {
namespace Core {

struct TickArg {
    float deltaTime;
    TickArg() : deltaTime(0.0) {}
};

/**
 * Game Engine implementation.
 * Acts as game module container responsible for performing
 * initialization and deinitialization tasks.
 * Follows the singelton pattern.
 *
 * @class GameEngine GameEngine.h Core/GameEngine.h
 */
class GameEngine : public IGameEngine {
private:

    // Engine running flag
    bool running;

    GameEngine();
    void InitModules();
    void DeinitModules();
    void StartGameLoop();
    void ProcessModules(const float delta);

public:

    static IGameEngine& Instance();
    ~GameEngine();

    void Start(IGameFactory* factory);
    void Stop();

    static Event<void*> initializeEvent;
    static Event<void*> deinitializeEvent;
    static Event<TickArg> processEvent;
};

} // NS Core
} // NS OpenEngine

#endif
