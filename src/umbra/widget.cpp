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
#include "widget.hpp"

#include <libtcod.hpp>

#include "engine.hpp"
#include "stylesheet.hpp"

void UmbraWidget::onEvent(const SDL_Event& ev) {
  TCOD_mouse_t tcod_mouse{};
  tcod::sdl2::process_event(ev, tcod_mouse);
  const int mouse_x = tcod_mouse.cx - (parent ? parent->rect.x : 0);
  const int mouse_y = tcod_mouse.cy - (parent ? parent->rect.y : 0);
  const int local_x = mouse_x - rect.x;
  const int local_y = mouse_y - rect.y;
  switch (ev.type) {
    case SDL_EVENT_MOUSE_MOTION: {
      const bool wasHover = rect.mouseHover;
      rect.mouseHover = rect.contains(mouse_x, mouse_y);
      if (!wasHover && rect.mouseHover) {
        onMouseEnter(this, UmbraMouseEvent(MOUSE_ENTER, tcod_mouse));
      } else if (wasHover && !rect.mouseHover) {
        onMouseLeave(this, UmbraMouseEvent(MOUSE_LEAVE, tcod_mouse));
      } else if (rect.mouseHover && !(tcod_mouse.dx == 0 && tcod_mouse.dy == 0)) {
        onMouseMove(this, UmbraMouseEvent(MOUSE_MOVE, tcod_mouse));
      }
      minimiseButton.mouseHover = minimiseButton.is(local_x, local_y);
      closeButton.mouseHover = closeButton.is(local_x, local_y);
      dragZone.mouseHover = dragZone.contains(local_x, local_y);
      if (isDragging) {
        rect.x = std::clamp(rect.x + tcod_mouse.dcx, 0, getEngine()->getRootWidth() - rect.w);
        rect.y = std::clamp(rect.y + tcod_mouse.dcy, 0, getEngine()->getRootHeight() - rect.h);
      }
    } break;
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
      if (ev.button.button == SDL_BUTTON_LEFT) {
        rect.mouseDown = rect.contains(mouse_x, mouse_y);
        minimiseButton.mouseDown = minimiseButton.is(local_x, local_y);
        closeButton.mouseDown = closeButton.is(local_x, local_y);
        dragZone.mouseDown = dragZone.contains(local_x, local_y);
        if (rect.mouseDown) onMouseClick(this, UmbraMouseEvent(MOUSE_CLICK, tcod_mouse));
        if (canDrag && dragZone.contains(local_x, local_y)) isDragging = true;
      }
      break;
    case SDL_EVENT_MOUSE_BUTTON_UP:
      if (ev.button.button == SDL_BUTTON_LEFT) {
        isDragging = false;
        rect.mouseDown = false;
        minimiseButton.mouseDown = false;
        closeButton.mouseDown = false;
        dragZone.mouseDown = false;
      }
      break;
    default:
      break;
  }
}

void UmbraWidget::setDragZone(int x, int y, int w, int h) {
  dragZone.set(x, y, w, h);
  if (w > 0 && h > 0) canDrag = true;
}
