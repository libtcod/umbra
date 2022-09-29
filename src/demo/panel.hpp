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
#ifndef PANEL_HPP
#define PANEL_HPP
#include <libtcod/libtcod.hpp>
#include <umbra/umbra.hpp>

#include "globals.hpp"

class Panel : public UmbraWidget {
 public:
  Panel() {
    rect.set(posx, posy, width, height);
    bQuit.onMouseClick.connect(this, &Panel::onQuit);
  }
  bool update() override;
  void render() override;
  void mouse(TCOD_mouse_t& ms) override {
    UmbraWidget::mouse(ms);
    bQuit.mouse(ms);
    return;
  }
  void onQuit(UmbraWidget*, UmbraEvent) { engine.deactivateAll(true); }

 private:
  int width{24};
  int height{48};
  int posx{0};
  int posy{(getEngine()->getRootHeight() - height) / 2};
  uint32_t delay{3000};
  uint64_t lastHover{0};  // the time the mouse last hovered over the panel
  TCODConsole panel{width, height};
  UmbraButton bQuit{this, 2, 2, 20, 3, "Quit"};
};

#endif
