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
#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include <libtcod/libtcod.hpp>
#include <umbra/umbra.hpp>

class Circle : public UmbraModule {
 public:
  void onInitialise() override { circle.set(getEngine()->getRootWidth() / 2, getEngine()->getRootHeight() / 2, 7); }
  void onEvent(const SDL_Event& ev) override {
    TCOD_mouse_t tcod_mouse{};
    tcod::sdl2::process_event(ev, tcod_mouse);
    if (ev.type == SDL_EVENT_MOUSE_MOTION) isGreen = circle.contains(tcod_mouse.cx, tcod_mouse.cy);
    if (isGreen && ev.type == SDL_EVENT_MOUSE_BUTTON_DOWN && ev.button.button == SDL_BUTTON_LEFT) {
      setActive(false);
    }
  }
  void render() override;

 private:
  UmbraCircle circle{};
  TCODImage red{"data/img/red.png"};
  TCODImage green{"data/img/green.png"};
  bool isGreen{false};
};

#endif /* CIRCLE_HPP */
