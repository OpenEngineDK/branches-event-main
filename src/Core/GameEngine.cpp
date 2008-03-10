// Game Engine implementation.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Core/GameEngine.h>
#include <Core/IGameFactory.h>
#include <Core/Exceptions.h>
#include <Logging/Logger.h>
#include <Utils/Timer.h>
#include <math.h>

namespace OpenEngine {
namespace Core {

using OpenEngine::Utils::Timer;
using namespace std;

Event<void*> GameEngine::initializeEvent;
Event<void*> GameEngine::deinitializeEvent;
Event<TickArg> GameEngine::processEvent;

/**
 * GameEngine constructor
 * Private because GameEngine is a singleton.
 *
 * @see GameEngine::Instance()
 */
GameEngine::GameEngine()
    : running(false) {

}

/**
 * GameEngine destructor
 */
GameEngine::~GameEngine() {

}

/**
 * Get game engine instance.
 *
 * @return Reference to game engine instance
 */
IGameEngine& GameEngine::Instance() {
    if (instance == NULL)
        instance = new GameEngine();
    return *instance;
}

/**
 * Initialize all modules.
 * Calls the initialize function on every module in the engine.
 *
 * @see IModule::Initialize()
 */
void GameEngine::InitModules() {
  GameEngine::initializeEvent.Notify(NULL);
}

/**
 * Deinitialize all modules.
 * Calls the deinitialize function on every module in the engine.
 *
 * @see IModule::DeinitModules()
 */
void GameEngine::DeinitModules() {
  GameEngine::deinitializeEvent.Notify(NULL);
}

/**
 * Main game engine loop.
 * Built in accordance with the game loop described in [CTA 36].
 */
void GameEngine::StartGameLoop() {
    double time0;               // last time
    double time1;               // current time
    float delta;                // elapsed time since last independent run
  
    // set starting times
    time0 = Timer::GetTime();

    while (running) {

        // read elapsed time
        time1 = Timer::GetTime();

        // set the current elapsed time
        delta = (float) (time1 - time0);

	// run the independent modules
        ProcessModules(delta);

        // update to the new last time
        time0 = time1;
    }
}

/**
 * Run all modules that are not dependent on the tick time.
 *
 * @param delta Delta time.
 * @param percent Percentage of current tick frame.
 */
void GameEngine::ProcessModules(const float delta) {
  TickArg tickArg;
  tickArg.deltaTime = delta;
  GameEngine::processEvent.Notify(tickArg);
}

/**
 * Start is the recommended way of initializing and starting up
 * the engine. By supplying a GameFactory this method asks the
 * factory for basic modules like the Frame, SceneGraph and a
 * Renderer. They are all added to the engine, initialized and
 * the main game loop is started. All module creation and engine
 * setup is done by the GameFactory supplied.
 *
 * @param factory IGameFactory pointer to factory defining all setup.
 */
void GameEngine::Start(IGameFactory* factory) {
    if (running) {
        logger.warning << "Ignoring start request - engine already running." << logger.end;
        return;
    }

    // Call setup to add all other modules and do other setup.
    bool start = factory->SetupEngine(*this);

    // If setup was successful start the engine.
    if (start) {
        delete factory;
        running = true;
        InitModules();
        StartGameLoop();
        DeinitModules();
    } else logger.error << "Factory setup failed." << logger.end;
}

/**
 * @see IGameEngine::Stop()
 */
void GameEngine::Stop() {
    running = false;
}

} // NS Core
} // NS OpenEngine
