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
#include "credits.hpp"

Credits::Credits() {
  credits = tcod::Console(48, 11);
  text =
      "Umbra demo\n"
      "Copyright (c) 2009, 2010 Mingos, Jice\n"
      "\n"
      "Powered by:\n"
      "libtcod " TCOD_STRVERSION
      "\n"
      "Copyright (c) 2008, 2009 Jice\n"
      "\n"
      "Simple DirectMedia Layer 1.2.12\n"
      "Copyright (c) Sam Lantinga";
  rect.set(getEngine()->getRootWidth() / 2 - 24, getEngine()->getRootHeight() / 2 - 5, 48, 11);
  setTimeout(5000);
}

void Credits::render() {
  constexpr auto WHITE = tcod::ColorRGB{255, 255, 255};
  constexpr auto BLACK = tcod::ColorRGB{0, 0, 0};
  constexpr std::array DECORATOR = {0x250c, 0x2500, 0x2510, 0x2502, 0x20, 0x2502, 0x2514, 0x2500, 0x2518};
  tcod::draw_frame(credits, {0, 0, 48, 11}, DECORATOR, WHITE, BLACK);
  tcod::print_rect(credits, {1, 1, 46, 9}, text, WHITE, {}, TCOD_CENTER);
  tcod::blit(*TCODConsole::root, credits, {rect.x, rect.y}, {}, 1.0f, 0.75f);
}
