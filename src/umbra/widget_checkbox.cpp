/*
* Umbra
* Copyright (c) 2009 Dominik Marczuk, Jice
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*     * Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*     * The names of Dominik Marczuk or Jice may not be used to endorse or promote products
*       derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY DOMINIK MARCZUK & JICE ``AS IS'' AND ANY
* EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL DOMINIK MARCZUK OR JICE BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "umbra.hpp"

UmbraCheckbox::UmbraCheckbox (void) {
    parent = NULL;
    area.set(0,0,0,0);
    text = "";
    checked = false;
    visible = true;
}

UmbraCheckbox::UmbraCheckbox (UmbraWidget * parent, int x, int y, int w, int h, const char * text) {
    this->parent = parent;
    area.set(x, y, w, h);
    this->text = text;
    checked = false;
    visible = true;
}

void UmbraCheckbox::set (UmbraWidget * parent, int x, int y, int w, int h, const char * text) {
    this->parent = parent;
    area.set(x, y, w, h);
    this->text = text;
    checked = false;
    visible = true;
}

void UmbraCheckbox::mouse (TCOD_mouse_t &ms) {
    if (!visible)
        return;
    if (area.isInside(ms.cx-parent->rect.x, ms.cy-parent->rect.y))
        area.mouseHover = true;
    else
        area.mouseHover = false;
    if (area.mouseHover && ms.lbutton_pressed) {
        area.mouseDown = true;
        checked = !checked;
        ms.lbutton_pressed=false;
    }
    else area.mouseDown = false;
}

void UmbraCheckbox::render (TCODConsole * con) {
    if (!visible)
        return;
    if (checked)
        con->putChar(area.x,area.y,TCOD_CHAR_CHECKBOX_SET,TCOD_BKGND_NONE);
    else
        con->putChar(area.x,area.y,TCOD_CHAR_CHECKBOX_UNSET,TCOD_BKGND_NONE);
    if (!text.empty())
        con->printLeftRect(area.x+2, area.y, area.w-2, area.h, TCOD_BKGND_NONE, text.c_str());
}
