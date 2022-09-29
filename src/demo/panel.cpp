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
#include "panel.hpp"

#include <SDL_timer.h>

#include <algorithm>

void Panel::render() {
  constexpr std::array DECORATOR = {0x250c, 0x2500, 0x2510, 0x2502, 0x20, 0x2502, 0x2514, 0x2500, 0x2518};
  const auto bg = tcod::ColorRGB{63, 63, 63};
  auto fg = tcod::ColorRGB{203, 203, 203};
  tcod::draw_frame(panel, {0, 0, rect.w, rect.h}, DECORATOR, fg, bg);
  if (bQuit.rect.mouseHover) fg = tcod::ColorRGB{255, 255, 255};
  panel.setDefaultForeground(fg);
  panel.setDefaultForeground(bg);
  bQuit.render(&panel);
  tcod::blit(*TCODConsole::root, panel, {posx, posy}, {0, 0, rect.w, rect.h}, 1.0f, 0.5f);
}

bool Panel::update() {
  const uint64_t time = SDL_GetTicks64();
  if (rect.mouseHover) {
    lastHover = time;
    posx += 3;
    posx = std::min(posx, 0);
    rect.set(posx, posy, width, height);
  } else if (time >= lastHover + delay) {
    posx -= 2;
    posx = std::max(posx, (-width) + 1);
    rect.set(posx, posy, width, height);
  }
  return getActive();
}
