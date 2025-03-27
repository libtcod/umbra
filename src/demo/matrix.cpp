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
#include "matrix.hpp"

#include <SDL3/SDL_timer.h>
#include <stdio.h>

#include "globals.hpp"

/// @brief Random character selection for matrix trail effect.
constexpr std::array CHARACTERS{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', 'a', 'b', 'c', 'd', 'e',
                                'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u',
                                'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

bool Matrix::update() {
  const auto now = SDL_GetTicks();
  if (next_lead_ms <= now) {
    next_lead_ms = now + rng() % 200;
    auto& new_lead = leads.emplace_back();
    new_lead.x = rng() % (engine.getRootWidth() - 1);
    new_lead.y_duration_ms = 50 + rng() % 200;
    new_lead.next_y_ms = now + new_lead.y_duration_ms;
  }
  return getActive();
}

void Matrix::render() {
  const auto now = SDL_GetTicks();
  // Advance leads.
  for (auto& lead : leads) {
    if (lead.next_y_ms <= now) {
      ++lead.y;
      lead.next_y_ms = now + lead.y_duration_ms;
    }
  }
  // Remove leads past the end.
  leads.erase(
      std::remove_if(
          leads.begin(), leads.end(), [&](const MatrixLead& lead) { return lead.y >= engine.getRootHeight(); }),
      leads.end());
  // Render leads.
  for (const auto& lead : leads) {
    auto& tile = console.at({lead.x, lead.y});
    tile.ch = CHARACTERS.at(rng() % CHARACTERS.size());
    tile.fg = tcod::ColorRGB{63, 255, 63};
  }
  tcod::blit(*TCODConsole::root, console);
  // Fade lead colors.
  const auto fade_function = [](uint8_t v) -> uint8_t { return v ? v - (v / 50 + 1) : 0; };
  for (auto& tile : console) {
    tile.fg.r = fade_function(tile.fg.r);
    tile.fg.g = fade_function(tile.fg.g);
    tile.fg.b = fade_function(tile.fg.b);
  }
}

void Matrix::onActivate() {
  getEngine()->printCredits(51, 1);
  console = tcod::Console{engine.getRootWidth(), engine.getRootHeight()};
}
