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
#include "module.hpp"

#include <SDL3/SDL_timer.h>
#include <libtcod/parser.h>

#include <libtcod/sys.hpp>

#include "engine.hpp"
#include "log.hpp"

void UmbraModule::setActive(bool active) {
  if (status_ == UMBRA_UNINITIALISED) {
    onInitialise();
    status_ = UMBRA_INACTIVE;
  }
  if (active && status_ == UMBRA_INACTIVE) {
    status_ = UMBRA_ACTIVE;
    onActivate();
  } else if (!active && status_ >= UMBRA_ACTIVE) {
    status_ = UMBRA_INACTIVE;
    onDeactivate();
  }
}

void UmbraModule::setPause(bool paused) {
  if (status_ == UMBRA_UNINITIALISED) {
    onInitialise();
    status_ = UMBRA_INACTIVE;
  }
  if (paused && status_ != UMBRA_PAUSED) {
    status_ = UMBRA_PAUSED;
    onPause();
  } else if (!paused && status_ == UMBRA_PAUSED) {
    status_ = UMBRA_ACTIVE;
    onResume();
  }
}

void UmbraModule::initialiseTimeout() {
  if (timeout_ == 0)
    return;
  else
    timeout_end_ = SDL_GetTicks() + timeout_;
}

void UmbraModule::setFallback(const char* module_name) {
  UmbraModule* mod = getEngine()->getModule(module_name);
  if (mod) {
    setFallback(mod->getID());
  } else {
    UmbraLog::error("UmbraModule::setFallback | Unknown module \"%s\".", module_name);
  }
}

void UmbraModule::setParameter(std::string_view param_name, TCOD_value_t value) {
  for (UmbraModuleParameter& it : params_) {
    if (it.name == param_name) {
      // already exists. update value
      // this happens when value is overriden in module.cfg
      it.value = value;
      return;
    }
  }
  params_.emplace_back(UmbraModuleParameter{std::string{param_name}, value});
}

UmbraModule::UmbraModuleParameter& UmbraModule::getParameter(std::string_view param_name) {
  static UmbraModuleParameter def = {"", {0}};
  for (UmbraModuleParameter& it : params_) {
    if (it.name == param_name) return it;
  }
  return def;
}

auto UmbraModule::getEngine() -> UmbraEngine* { return UmbraEngine::getInstance(); }
