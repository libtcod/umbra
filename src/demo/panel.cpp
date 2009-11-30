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

#include "main.hpp"

Panel::Panel (void) {
    width = 16;
    height = 24;
    posx = 0;
    posy = (getEngine()->getRootHeight() - height) / 2;
    rect.set(posx,posy,width,height);
    panel = new TCODConsole(width,height);
    priority = 0; //always on top
    lastHover = 0;
    delay = 3000;
}

void Panel::render (void) {
    panel->setBackgroundColor(TCODColor::red);
    panel->setForegroundColor(TCODColor::yellow);
    panel->printFrame(0,0,rect.w,rect.h,true,TCOD_BKGND_SET,NULL);
    TCODConsole::blit(panel,0,0,rect.w,rect.h,TCODConsole::root,posx,posy,1.0f,0.5f);
}

bool Panel::update (void) {
    uint32 time = TCODSystem::getElapsedMilli();
    if (rect.mouseHover) {
        lastHover = time;
        posx = 0;
    }
    else if (time >= lastHover + delay) {
        posx--;
        posx = MAX(posx,(-width)+1);
        rect.set(posx,posy,width,height);
    }
    return isActive();
}

void Panel::mouse (TCOD_mouse_t &ms) {
    UmbraWidget::mouse(ms);
    return;
}
