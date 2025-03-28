/*
 * Umbra
 * Copyright (c) 2009, 2010 Mingos, Jice
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * The names of Mingos or Jice may not be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY MINGOS & JICE ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL MINGOS OR JICE BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>
#include <stdio.h>

#include "circle.hpp"
#include "credits.hpp"
#include "demo.hpp"
#include "globals.hpp"
#include "matrix.hpp"
#include "panel.hpp"
#include "rabbit.hpp"

UmbraEngine engine("data/cfg/umbra.txt", UMBRA_REGISTER_ALL);

class ModuleFactory : public UmbraModuleFactory {
 public:
  UmbraModule* createModule(const char* name) {
    if (strcmp(name, "matrix") == 0)
      return new Matrix();
    else if (strcmp(name, "demo") == 0)
      return new Demo();
    else if (strcmp(name, "rabbit") == 0)
      return new RabbitWidget();
    else if (strcmp(name, "panel") == 0)
      return new Panel();
    else if (strcmp(name, "credits") == 0)
      return new Credits();
    else if (strcmp(name, "circle") == 0)
      return new Circle();
    else
      return NULL;
  }
};

SDL_AppResult SDL_AppEvent(void*, SDL_Event* event) { return engine.onEvent(*event); }

SDL_AppResult SDL_AppIterate(void*) { return engine.onFrame(); }

SDL_AppResult SDL_AppInit(void**, int argc, char** argv) {
  // set window title
  engine.setWindowTitle("Umbra demo");
  engine.setKeyboardMode(UMBRA_KEYBOARD_SDL);
  // initialise and run the engine
  if (engine.loadModuleConfiguration("data/cfg/module.txt", new ModuleFactory()) && engine.initialise()) {
    return SDL_APP_CONTINUE;
  } else {
    return SDL_APP_FAILURE;
  }
}
void SDL_AppQuit(void*, SDL_AppResult) { engine.onQuit(); }
